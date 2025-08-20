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

#pragma once

#include "BinFile.hxx"

#define INVALID_ASSET_FILE_OFFSET           (-1)
#define INVALID_ASSET_FILE_SIZE             (-1)
#define INVALID_ASSET_FILE_STRING_LENGTH    (-1)

struct AssetFile;

typedef AssetFile* (CLASSCALL* ASSETFILERELEASEACTION)(AssetFile* self, CONST OBJECTRELEASETYPE mode);
typedef BOOL(CLASSCALL* ASSETFILEISACTIOVEACTION)(AssetFile* self);
typedef BOOL(CLASSCALL* ASSETFILEOPENACTION)(AssetFile* self, LPCSTR name);
typedef VOID(CLASSCALL* ASSETFILECLOSEACTION)(AssetFile* self);
typedef U32(CLASSCALL* ASSETFILEREADACTION)(AssetFile* self, LPVOID content, U32 size);
typedef U32(CLASSCALL* ASSETFILEUNKNOWN5ACTION)(AssetFile* self); // TODO
typedef U32(CLASSCALL* ASSETFILEUNKNOWN6ACTION)(AssetFile* self); // TODO
typedef S32(CLASSCALL* ASSETFILESELECTOFFSETACTION)(AssetFile* self, LONG distance, DWORD method);
typedef S32(CLASSCALL* ASSETFILEACQUIREOFFSETACTION)(AssetFile* self);
typedef S32(CLASSCALL* ASSETFILEACQUIRESIZEACTION)(AssetFile* self);
typedef S32(CLASSCALL* ASSETFILEACQUIRESTRINGACTION)(AssetFile* self, LPSTR content, CONST U32 length);
// TODO

// INHERITANCE: BaseFileSelf
typedef struct AssetFileSelf
{
    ASSETFILERELEASEACTION          Release;
    ASSETFILEISACTIOVEACTION        IsActive;
    ASSETFILEOPENACTION             Open;
    ASSETFILECLOSEACTION            Close;
    ASSETFILEREADACTION             Read;
    ASSETFILEUNKNOWN5ACTION         Unk05; // TODO
    ASSETFILEUNKNOWN6ACTION         Unk06; // TODO
    ASSETFILESELECTOFFSETACTION     SelectOffset;
    ASSETFILEACQUIREOFFSETACTION    AcquireOffset;
    ASSETFILEACQUIRESIZEACTION      AcquireSize;
    ASSETFILEACQUIRESTRINGACTION    AcquireString;
    // TODO
} ASSETFILESELF, * ASSETFILESELFPTR;

// INHERITANCE: BaseFile
typedef struct AssetFile
{
    ASSETFILESELFPTR    Self;
    BFH                 Value;
} ASSETFILE, * ASSETFILEPTR;