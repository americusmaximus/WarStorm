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

struct AssetFile;

typedef AssetFile* (CLASSCALL* ASSETFILERELEASEACTION)(AssetFile* self, CONST OBJECTRELEASETYPE mode);
typedef BOOL(CLASSCALL* ASSETFILEISACTIOVEACTION)(AssetFile* self);
typedef BOOL(CLASSCALL* ASSETFILEOPENACTION)(AssetFile* self, LPCSTR name, U32 type);
typedef VOID(CLASSCALL* ASSETFILECLOSEACTION)(AssetFile* self);
typedef U32(CLASSCALL* ASSETFILEREADACTION)(AssetFile* self, LPVOID content, U32 size);
typedef U32(CLASSCALL* ASSETFILEWRITEACTION)(AssetFile* self, LPVOID content, U32 size);
typedef BOOL(CLASSCALL* ASSETFILEFLUSHACTION)(AssetFile* self);
typedef S32(CLASSCALL* ASSETFILESETPOINTERACTION)(AssetFile* self, S32 distance, U32 method);
typedef S32(CLASSCALL* ASSETFILEGETPOINTERACTION)(AssetFile* self);
typedef S32(CLASSCALL* ASSETFILEGETSIZEACTION)(AssetFile* self);
typedef U32(CLASSCALL* ASSETFILEGETSTRINGACTION)(AssetFile* self, LPSTR string, U32 length);
typedef U32(CDECLAPI* ASSETFILESETSTRINGACTION)(AssetFile* self, LPSTR format, ...);
typedef LPVOID(CLASSCALL* ASSETFILEUNKNOWN12ACTION)(AssetFile* self); // TODO

// INHERITANCE: BaseFileSelf
#pragma pack(push, 1)
typedef struct AssetFileSelf
{
    ASSETFILERELEASEACTION          Release;
    ASSETFILEISACTIOVEACTION        IsActive;
    ASSETFILEOPENACTION             Open;
    ASSETFILECLOSEACTION            Close;
    ASSETFILEREADACTION             Read;
    ASSETFILEWRITEACTION            Write;
    ASSETFILEFLUSHACTION            Flush;
    ASSETFILESETPOINTERACTION       SetPointer;
    ASSETFILEGETPOINTERACTION       GetPointer;
    ASSETFILEGETSIZEACTION          GetSize;
    ASSETFILEGETSTRINGACTION        GetString;
    ASSETFILESETSTRINGACTION        SetString;
    ASSETFILEUNKNOWN12ACTION        Unk12;      // TODO
} ASSETFILESELF, * ASSETFILESELFPTR;
#pragma pack(pop)

// INHERITANCE: BaseFile
#pragma pack(push, 1)
typedef struct AssetFile
{
    ASSETFILESELFPTR    Self;
    BFH                 Value;
} ASSETFILE, * ASSETFILEPTR;
#pragma pack(pop)
