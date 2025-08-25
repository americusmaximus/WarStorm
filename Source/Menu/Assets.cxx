/*
Copyright (c) 2025 Americus Maximus

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "AssetFile.hxx"
#include "Assets.hxx"
#include "BinFile.hxx"
#include "BinFileContent.hxx"
#include "ZipFile.hxx"

#include <stdlib.h>

#define MAX_ASSET_FILE_NAME_LENGTH      1024

ASSETSTATEMODULECONTAINER AssetsState;

// 0x100766f0
LPVOID InitializeBinFileChunk(BFH indx, U32 chunk, U32 size)
{
    if (AssetsState.Chunks.Values[AssetsState.Chunks.Count].Content != NULL)
    {
        free(AssetsState.Chunks.Values[AssetsState.Chunks.Count].Content);
    }

    AssetsState.Chunks.Values[AssetsState.Chunks.Count].Index = indx;
    AssetsState.Chunks.Values[AssetsState.Chunks.Count].Chunk = chunk;
    AssetsState.Chunks.Values[AssetsState.Chunks.Count].Size = size;

    AssetsState.Chunks.Values[AssetsState.Chunks.Count].Content = malloc(size);

    LPVOID result = AssetsState.Chunks.Values[AssetsState.Chunks.Count].Content;

    AssetsState.Chunks.Count = (AssetsState.Chunks.Count + 1) % MAX_BINARY_CHUNK_COUNT;

    return result;
}

// 0x10076bb0
BFH AcquireAssetFileIndex(LPCSTR name)
{
    CHAR path[MAX_ASSET_FILE_NAME_LENGTH];

    CONST U32 length = strlen(name);

    for (U32 x = 0; x < length; x++) { path[x] = tolower(name[x]); }

    BFH indx = crc32(0, (BYTE*)path, length + 1) & (MAX_BINARY_FILE_COUNT - 1);

    for (BFH x = 0; x < MAX_BINARY_FILE_COUNT; x++)
    {
        CONST BINFILECONTENTPTR file = &AssetsState.Files[indx];

        if (file->Type != FILECONTENTTYPE_NONE)
        {
            CONST U32 archive = AssetsState.Files[indx].Archive;

            if (AssetsState.Archives[archive].Length < length)
            {
                if (strnicmp(AssetsState.Archives[archive].Folder, path, AssetsState.Archives[archive].Length) == 0)
                {
                    if (strcmpi(AssetsState.Files[indx].Name,
                        (LPCSTR)((ADDR)path + AssetsState.Archives[archive].Length)) == 0) // TODO strcmpi ?
                    {
                        return x;
                    }
                }
            }
        }

        indx = (indx + 1) % MAX_BINARY_FILE_COUNT;
    }

    return INVALID_BINFILE_VALUE;
}

// 0x10077770
U32 ReadAssetFile(BFH indx, LPVOID content, U32 size)
{
    switch (AssetsState.Files[indx].Type)
    {
    case FILECONTENTTYPE_FILE:
    {
        BINFILEPTR file = &AssetsState.Files[indx].File;

        if (file->Self->IsActive(file)) { return file->Self->Read(file, content, size); }

        break;
    }
    case FILECONTENTTYPE_COMBINED:
    {
        CONST U32 result =
            ReadAssetFileSingleChunk(content, indx, AssetsState.Files[indx].Offset, size);

        AssetsState.Files[indx].Offset = AssetsState.Files[indx].Offset + result;

        return result;
    }
    case FILECONTENTTYPE_ZIP:
    {
        ZIPFILEPTR file = &AssetsState.Files[indx].Zip;

        if (file->Self->IsActive(file)) { return file->Self->Read(file, content, size); }

        break;
    }
    case FILECONTENTTYPE_COMPRESSED:
    {
        CONST U32 result =
            ReadAssetFileMultiChunk(content, indx, AssetsState.Files[indx].Offset, size);

        AssetsState.Files[indx].Offset = AssetsState.Files[indx].Offset + result;

        return result;
    }
    }

    return 0;
}

// 0x10077850
U32 ReadAssetFileMultiChunk(LPVOID result, BFH indx, U32 offset, U32 size)
{
    if (AssetsState.Files[indx].Size <= offset) { return 0; }

    U32 chunk = offset / AssetsState.Files[indx].Chunk;

    // Offset within current chunk, 0 for non-initial chunk.
    U32 start = offset - chunk * AssetsState.Files[indx].Chunk;

    U32 completed = 0;
    U32 left = size;

    if (AssetsState.Files[indx].Size < offset + size)
    {
        left = AssetsState.Files[indx].Size - offset;
        size = left;
    }

    while (left != 0)
    {
        CONST U32 length = left < AssetsState.Files[indx].Chunk - start
            ? left : AssetsState.Files[indx].Chunk - start;

        LPVOID content = ReadAssetFileChunk(indx, chunk);

        if (content == NULL) { break; }

        memcpy((LPVOID)((ADDR)result + completed), (LPVOID)((ADDR)content + start), length);

        completed = completed + length;
        left = left - length;

        start = 0; // Start reading from the beginning of chunk for non-first chunk.
        chunk = chunk + 1;
    }

    return size;
}

// 0x10077920
LPVOID ReadAssetFileChunk(BFH indx, U32 chunk)
{
    LPVOID result = AcquireBinFileChunk(indx, chunk);

    if (result == NULL)
    {
        CONST U32 archive = AssetsState.Files[indx].Archive;
        BINFILEPTR file = &AssetsState.Archives[archive].File;

        if (file->Self->IsActive(file))
        {
            file->Self->Open(file, AssetsState.Archives[archive].Name, FILEOPENTYPE_READ);
        }

        CONST U32 index = AssetsState.Files[indx].File.Value + chunk;

        file->Self->SetPointer(file, AssetsState.Archives[archive].Offsets[index], FILE_BEGIN);

        CONST U32 length =
            AssetsState.Archives[archive].Offsets[index + 1] - AssetsState.Archives[archive].Offsets[index];

        Bytef* content = (Bytef*)malloc(length);

        U32 read = AcquireBinFileChunkSize(indx, chunk * AssetsState.Files[indx].Chunk);

        result = InitializeBinFileChunk(indx, chunk, read);

        if (file->Self->Read(file, content, length) != length) { return NULL; }

        uncompress((Bytef*)result, (uLongf*)&read, content, length);

        free(content);
    }

    return result;
}

// 0x10077a20
LPVOID AcquireBinFileChunk(BFH indx, U32 chunk)
{
    for (U32 x = 0; x < MAX_BINARY_CHUNK_COUNT; x++)
    {
        if (AssetsState.Chunks.Values[x].Index == indx
            && AssetsState.Chunks.Values[x].Chunk == chunk && AssetsState.Chunks.Values[x].Content != NULL)
        {
            return AssetsState.Chunks.Values[x].Content;
        }
    }

    return NULL;
}

// 0x10077a60
U32 AcquireBinFileChunkSize(BFH indx, U32 offset)
{
    return AssetsState.Files[indx].Size < AssetsState.Files[indx].Chunk + offset
        ? AssetsState.Files[indx].Size - offset : AssetsState.Files[indx].Chunk;
}

// 0x10077a90
U32 ReadAssetFileSingleChunk(LPVOID result, BFH indx, U32 offset, U32 size)
{
    CONST U32 archive = AssetsState.Files[indx].Archive;
    BINFILEPTR file = &AssetsState.Archives[archive].File;

    if (!file->Self->IsActive(file))
    {
        file->Self->Open(file, AssetsState.Archives[archive].Name, FILEOPENTYPE_READ);
    }

    if (AssetsState.Files[indx].Size < offset + size) { size = AssetsState.Files[indx].Size - offset; }

    if (size != 0)
    {
        file->Self->SetPointer(file, AssetsState.Files[indx].Value + offset, FILE_BEGIN);
        file->Self->Read(file, result, size);
    }

    return size;
}

// 0x10077b70
S32 SelectAssetFileOffset(BFH indx, S32 distance, DWORD method)
{
    switch (AssetsState.Files[indx].Type)
    {
    case FILECONTENTTYPE_FILE: { return BinFileSetPointer(&AssetsState.Files[indx].File, distance, method); }
    case FILECONTENTTYPE_COMBINED:
    case FILECONTENTTYPE_COMPRESSED:
    {
        switch (method)
        {
        case FILE_BEGIN: { AssetsState.Files[indx].Offset = distance; break; }
        case FILE_CURRENT: { AssetsState.Files[indx].Offset = AssetsState.Files[indx].Offset + distance; break; }
        case FILE_END: { AssetsState.Files[indx].Offset = AssetsState.Files[indx].Size - distance; break; }
        }

        return AssetsState.Files[indx].Offset;
    }
    case FILECONTENTTYPE_ZIP: { return ZipFileSetPointer(&AssetsState.Files[indx].Zip, distance, method); }
    }

    return 0;
}

// 0x10077c50
S32 AcquireAssetFileOffset(BFH indx)
{
    switch (AssetsState.Files[indx].Type)
    {
    case FILECONTENTTYPE_FILE: { return BinFileGetPointer(&AssetsState.Files[indx].File); }
    case FILECONTENTTYPE_COMBINED:
    case FILECONTENTTYPE_COMPRESSED: { return AssetsState.Files[indx].Offset; }
    case FILECONTENTTYPE_ZIP: { return ZipFileGetPointer(&AssetsState.Files[indx].Zip); }
    }

    return 0;
}

// 0x10077cd0
S32 AcquireAssetFileSize(BFH indx)
{
    switch (AssetsState.Files[indx].Type)
    {
    case FILECONTENTTYPE_FILE:
    {
        BINFILEPTR file = &AssetsState.Files[indx].File;

        if (BinFileIsActive(file)) { return BinFileGetSize(file); }

        if (!OpenAssetFile(indx)) { return INVALID_FILE_SIZE; }

        CONST S32 size = BinFileGetSize(file);

        CloseAssetFile(indx);

        return size;
    }
    case FILECONTENTTYPE_COMBINED:
    case FILECONTENTTYPE_COMPRESSED: { return AssetsState.Files[indx].Size; }
    }

    return 0;
}