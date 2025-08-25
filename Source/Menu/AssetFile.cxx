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
#include "BaseFile.hxx"
#include "BinFile.hxx"
#include "BinFileContent.hxx"
#include "ZipFile.hxx"

#include <stdio.h>
#include <stdlib.h>

#define ZIP_HEADER_MAGIC                0x8B1F

// 0x10091344
STATIC ASSETFILESELF AssetFileSelf =
{
    AssetFileRelease,
    AssetFileIsActive,
    AssetFileOpen,
    AssetFileClose,
    AssetFileRead,
    AssetFileWrite,
    AssetFileFlush,
    AssetFileSetPointer,
    AssetFileGetPointer,
    AssetFileGetSize,
    (ASSETFILEGETSTRINGACTION)BaseFileGetString,
    (ASSETFILESETSTRINGACTION)BaseFileSetString,
    AssetFileUnk12
};

// 0x100774d0
ASSETFILEPTR CLASSCALL AssetFileActivate(ASSETFILEPTR self)
{
    self->Self = &AssetFileSelf;

    self->Value = (BFH)INVALID_BINFILE_VALUE;

    return self;
}

// 0x100774f0
ASSETFILEPTR CLASSCALL AssetFileRelease(ASSETFILEPTR self, CONST OBJECTRELEASETYPE mode)
{
    AssetFileDispose(self);

    if (mode & OBJECTRELEASETYPE_ALLOCATED) { free(self); }

    return self;
}

// 0x10077510
ASSETFILEPTR CLASSCALL AssetFileDispose(ASSETFILEPTR self)
{
    AssetFileClose(self);

    return self;
}

// 0x10077560
BOOL CLASSCALL AssetFileIsActive(ASSETFILEPTR self)
{
    return IsAssetFileActive(self->Value);
}

// 0x10077570
BOOL CLASSCALL AssetFileOpen(ASSETFILEPTR self, LPCSTR name, U32 type)
{
    self->Self->Close(self);

    self->Value = AcquireAssetFileIndex(name);

    return self->Value != INVALID_BINFILE_VALUE ? OpenAssetFile(self->Value) : FALSE;
}

// 0x10077720
VOID CLASSCALL AssetFileClose(ASSETFILEPTR self)
{
    if (self->Self->IsActive(self)) { CloseAssetFile(self->Value); }
}

// 0x10077740
U32 CLASSCALL AssetFileRead(ASSETFILEPTR self, LPVOID content, U32 size)
{
    if (!self->Self->IsActive(self)) { return 0; }

    return ReadAssetFile(self->Value, content, size);
}

// 0x10077b20
U32 CLASSCALL AssetFileWrite(ASSETFILEPTR self, LPVOID content, U32 length)
{
    return 0;
}

// 0x10077b30
BOOL CLASSCALL AssetFileFlush(ASSETFILEPTR self)
{
    return TRUE;
}

// 0x10077b40
S32 CLASSCALL AssetFileSetPointer(ASSETFILEPTR self, S32 distance, U32 method)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_OFFSET; }

    return SelectAssetFileOffset(self->Value, distance, method);
}

// 0x10077c30
S32 CLASSCALL AssetFileGetPointer(ASSETFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_OFFSET; }

    return AcquireAssetFileOffset(self->Value);
}

// 0x10077cb0
S32 CLASSCALL AssetFileGetSize(ASSETFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_SIZE; }

    return AcquireAssetFileSize(self->Value);
}

// 0x100774e0
LPVOID CLASSCALL AssetFileUnk12(ASSETFILEPTR self)
{
    return NULL; // &PTR_100e93d8; // TODO NOT IMPLEMENTED
}

// 0x100775b0
BOOL OpenAssetFile(BFH indx)
{
    if (indx == INVALID_BINFILE_VALUE) { return FALSE; }

    switch (AssetsState.Files[indx].Type)
    {
    case FILECONTENTTYPE_FILE:
    {
        CHAR path[MAX_FILE_NAME_LENGTH];
        sprintf(path, "%s%s",
            AssetsState.Archives[AssetsState.Files[indx].Archive].Name, AssetsState.Files[indx].Name);

        BINFILEPTR file = &AssetsState.Files[indx].File;
        if (BinFileOpen(file, path, FILEOPENTYPE_READ))
        {
            U16 magic = 0;
            BinFileRead(file, &magic, sizeof(U16));

            if (magic != ZIP_HEADER_MAGIC)
            {
                BinFileSetPointer(file, 0, FILE_BEGIN);

                return TRUE;
            }

            BinFileClose(file);

            AssetsState.Files[indx].Type = FILECONTENTTYPE_ZIP;

            return ZipFileOpen(&AssetsState.Files[indx].Zip, path, FILEOPENTYPE_READ);
        }

        return FALSE;
    }
    case FILECONTENTTYPE_ZIP:
    {
        CHAR path[MAX_FILE_NAME_LENGTH];
        sprintf(path, "%s%s",
            AssetsState.Archives[AssetsState.Files[indx].Archive].Name, AssetsState.Files[indx].Name);

        return ZipFileOpen(&AssetsState.Files[indx].Zip, path, FILEOPENTYPE_READ);
    }
    case FILECONTENTTYPE_COMBINED:
    case FILECONTENTTYPE_COMPRESSED:
    {
        if (AssetsState.Files[indx].IsActive) { return FALSE; }

        AssetsState.Files[indx].Offset = 0;
        AssetsState.Files[indx].IsActive = TRUE;

        return TRUE;
    }
    }

    return FALSE;
}

// 0x10076d00
BOOL IsAssetFileActive(BFH indx)
{
    if (indx == INVALID_BINFILE_VALUE) { return FALSE; }

    switch (AssetsState.Files[indx].Type)
    {
    case FILECONTENTTYPE_FILE: { return BinFileIsActive(&AssetsState.Files[indx].File); }
    case FILECONTENTTYPE_COMBINED:
    case FILECONTENTTYPE_COMPRESSED: { return AssetsState.Files[indx].IsActive; }
    case FILECONTENTTYPE_ZIP: { return ZipFileIsActive(&AssetsState.Files[indx].Zip); }
    }

    return FALSE;
}

// 0x10076d70
VOID CloseAssetFile(BFH indx)
{
    switch (AssetsState.Files[indx].Type) {
    case FILECONTENTTYPE_FILE: { BinFileClose(&AssetsState.Files[indx].File); break; }
    case FILECONTENTTYPE_COMBINED:
    case FILECONTENTTYPE_COMPRESSED: { AssetsState.Files[indx].IsActive = FALSE; break; }
    case FILECONTENTTYPE_ZIP: { ZipFileClose(&AssetsState.Files[indx].Zip); break; }
    }

    return;
}
