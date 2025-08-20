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

#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>

#define MAX_ASSET_FILE_NAME_LENGTH  1024
#define ZIP_HEADER_MAGIC            0x8B1F

// 0x10091344
STATIC ASSETFILESELF AssetFileSelf =
{
    ReleaseAssetFile,
    IsAssetFileActive,
    OpenAssetFile,
    CloseAssetFile,
    ReadAssetFile,
    AssetFileUnk05,
    AssetFileUnk06,
    SelectAssetFileOffset,
    AcquireAssetFileOffset,
    AcquireAssetFileSize,
    AcquireAssetFileString,
    // TODO
};

// 0x100774d0
ASSETFILEPTR CLASSCALL ActivateAssetFile(ASSETFILEPTR self)
{
    self->Self = &AssetFileSelf;
    self->Value = (BFH)INVALID_BINFILE_VALUE;

    return self;
}

// 0x100774f0
ASSETFILEPTR CLASSCALL ReleaseAssetFile(ASSETFILEPTR self, CONST OBJECTRELEASETYPE mode)
{
    DisposeAssetFile(self);

    if (mode & OBJECTRELEASETYPE_ALLOCATED) { free(self); }

    return self;
}

// 0x10077510
ASSETFILEPTR CLASSCALL DisposeAssetFile(ASSETFILEPTR self)
{
    CloseAssetFile(self);

    return self;
}

// 0x10077560
BOOL CLASSCALL IsAssetFileActive(ASSETFILEPTR self)
{
    return IsAssetFileActive(self->Value);
}

// 0x10077570
BOOL CLASSCALL OpenAssetFile(ASSETFILEPTR self, LPCSTR name)
{
    self->Self->Close(self);

    self->Value = AcquireAssetFileIndex(name);

    return self->Value != INVALID_BINFILE_VALUE ? OpenAssetFile(self->Value) : FALSE;
}

// 0x10077720
VOID CLASSCALL CloseAssetFile(ASSETFILEPTR self)
{
    if (self->Self->IsActive(self)) { CloseAssetFile(self->Value); }
}

// 0x10077740
U32 CLASSCALL ReadAssetFile(ASSETFILEPTR self, LPVOID content, U32 size)
{
    if (!self->Self->IsActive(self)) { return 0; }

    return ReadAssetFile(self->Value, content, size);
}

// 0x10077b20
U32 CLASSCALL AssetFileUnk05(ASSETFILEPTR self) // TODO
{
    return 0; // TODO
}

// 0x10077b30
U32 CLASSCALL AssetFileUnk06(ASSETFILEPTR self) // TODO
{
    return 1; // TODO
}

// 0x10077b40
S32 CLASSCALL SelectAssetFileOffset(ASSETFILEPTR self, LONG distance, DWORD method)
{
    if (!self->Self->IsActive(self)) { return INVALID_ASSET_FILE_OFFSET; }

    return SelectAssetFileOffset(self->Value, distance, method);
}

// 0x10077c30
S32 CLASSCALL AcquireAssetFileOffset(ASSETFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_ASSET_FILE_OFFSET; }

    return AcquireAssetFileOffset(self->Value);
}

// 0x10077cb0
S32 CLASSCALL AcquireAssetFileSize(ASSETFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_ASSET_FILE_OFFSET; }

    return AcquireAssetFileSize(self->Value);
}

// 0x10074830
S32 CLASSCALL AcquireAssetFileString(ASSETFILEPTR self, LPSTR content, CONST U32 length)
{
    CONST U32 size = self->Self->Read(self, content, length - 1);

    if (size == 0) { return INVALID_ASSET_FILE_STRING_LENGTH; }

    U32 actual = length;

    U32 count = 0;
    while (count < size)
    {
        if (content[count] == '\r') { actual = content[count + 1] == '\n'; break; }
        if (content[count] == '\n') { actual = content[count + 1] == '\r'; break; }

        count = count + 1;
    }

    if (count != length)
    {
        content[count] = NULL;

        CONST U32 offset = actual - size + 1 + count;

        if (offset != 0) { self->Self->SelectOffset(self, offset, FILE_CURRENT); }

        return count;
    }

    content[length - 1] = NULL;

    return length - 1;
}

// 0x10076d00
BOOL IsAssetFileActive(CONST BFH indx)
{
    if (indx == INVALID_BINFILE_VALUE) { return FALSE; }

    switch (AssetsState.Files[indx].Type)
    {
    case BINFILECONTENTTYPE_FILE: { return IsBinFileActive(AssetsState.Files[indx].File); }
    case BINFILECONTENTTYPE_ZIP: { return FUN_100751c0(AssetsState.Files[indx].Zip); }
    case BINFILECONTENTTYPE_COMBINED:
    case BINFILECONTENTTYPE_COMPRESSED: { return AssetsState.Files[indx].IsActive; }
    }

    return FALSE;
}

// 0x10076bb0
BFH AcquireAssetFileIndex(LPCSTR name)
{
    CHAR path[MAX_ASSET_FILE_NAME_LENGTH];

    CONST U32 length = strlen(name) + 1;

    for (U32 x = 0; x < length; x++) { path[x] = tolower(name[x]); }

    BFH indx = crc32(0, (BYTE*)path, length) & (MAX_BINARY_FILE_COUNT - 1);

    for (BFH x = 0; x < MAX_BINARY_FILE_COUNT; x++)
    {
         TODO NOT IMPLEMENTED
         CONST BINFILECONTENTPTR file = &AssetsState.Files[indx];
         
         if (file->Type != BINFILECONTENTTYPE_NONE && _strcmpi(file->Name, name) == 0) { return indx; }
         
         indx = (indx + 1) % MAX_BINARY_FILE_COUNT;
    }

    return INVALID_BINFILE_VALUE;
}

// 0x100775b0
BOOL OpenAssetFile(CONST BFH indx)
{
    if (indx == INVALID_BINFILE_VALUE) { return FALSE; }

    switch (AssetsState.Files[indx].Type)
    {
    case BINFILECONTENTTYPE_FILE:
    {
        CHAR path[MAX_FILE_NAME_LENGTH];
        sprintf(path, "%s%s", AssetsState.Archives[AssetsState.Files[indx].Archive].Name, AssetsState.Files[indx].Name);

        BINFILEPTR file = &AssetsState.Files[indx].File;
        if (OpenBinFile(file, path, BINFILEOPENTYPE_READ))
        {
            U16 magic = 0;
            ReadBinFile(file, &magic, sizeof(U16));

            if (magic != ZIP_HEADER_MAGIC)
            {
                PointBinFile(file, 0, FILE_BEGIN);

                return TRUE;
            }

            CloseBinFile(file);

            AssetsState.Files[indx].Type = BINFILECONTENTTYPE_ZIP;

            return FUN_10078fe0(&AssetsState.Files[indx].Zip, path, 0); // TODO
        }

        return FALSE;
    }
    case BINFILECONTENTTYPE_ZIP:
    {
        CHAR path[MAX_FILE_NAME_LENGTH];
        sprintf(path, "%s%s", AssetsState.Archives[AssetsState.Files[indx].Archive].Name, AssetsState.Files[indx].Name);

        return FUN_10078fe0(&AssetsState.Files[indx].Zip, path, 0); // TODO
    }
    case BINFILECONTENTTYPE_COMBINED:
    case BINFILECONTENTTYPE_COMPRESSED:
    {
        if (AssetsState.Files[indx].IsActive) { return FALSE; }

        AssetsState.Files[indx].Offset = 0;
        AssetsState.Files[indx].IsActive = TRUE;

        return TRUE;
    }
    }

    return FALSE;
}