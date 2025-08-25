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

#include "BaseFile.hxx"

#define INVALID_BINFILE_VALUE       (-1)

#define BINFILEHANDLE(x) ((HANDLE)x)

#ifdef _WIN64
typedef U64 BFH;
#else
typedef U32 BFH;
#endif

struct BinFile;
struct BinFileFinder;
struct BinFileFolder;

typedef BinFile* (CLASSCALL* BINFILERELEASEACTION)(BinFile* self, CONST OBJECTRELEASETYPE mode);
typedef BOOL(CLASSCALL* BINFILEISACTIOVEACTION)(BinFile* self);
typedef BOOL(CLASSCALL* BINFILEOPENACTION)(BinFile* self, LPCSTR name, U32 type);
typedef VOID(CLASSCALL* BINFILECLOSEACTION)(BinFile* self);
typedef U32(CLASSCALL* BINFILEREADACTION)(BinFile* self, LPVOID content, U32 size);
typedef U32(CLASSCALL* BINFILEWRITEACTION)(BinFile* self, LPVOID content, U32 size);
typedef BOOL(CLASSCALL* BINFILEFLUSHACTION)(BinFile* self);
typedef S32(CLASSCALL* BINFILESETPOINTERACTION)(BinFile* self, S32 distance, U32 method);
typedef S32(CLASSCALL* BINFILEGETPOINTERACTION)(BinFile* self);
typedef S32(CLASSCALL* BINFILEGETSIZEACTION)(BinFile* self);
typedef U32(CLASSCALL* BINFILEGETSTRINGACTION)(BinFile* self, LPSTR string, U32 length);
typedef U32(CDECLAPI* BINFILESETSTRINGACTION)(BinFile* self, LPSTR format, ...);
typedef BinFileFolder*(CLASSCALL* BINFILEGETFOLDERACTION)(BinFile* self);

// INHERITANCE: BaseFileSelf
#pragma pack(push, 1)
typedef struct BinFileSelf
{
    BINFILERELEASEACTION            Release;
    BINFILEISACTIOVEACTION          IsActive;
    BINFILEOPENACTION               Open;
    BINFILECLOSEACTION              Close;
    BINFILEREADACTION               Read;
    BINFILEWRITEACTION              Write;
    BINFILEFLUSHACTION              Flush;
    BINFILESETPOINTERACTION         SetPointer;
    BINFILEGETPOINTERACTION         GetPointer;
    BINFILEGETSIZEACTION            GetSize;
    BINFILEGETSTRINGACTION          GetString;
    BINFILESETSTRINGACTION          SetString;
    BINFILEGETFOLDERACTION          GetFolder;
} BINFILESELF, * BINFILESELFPTR;
#pragma pack(pop)

// INHERITANCE: BaseFile
#pragma pack(push, 1)
typedef struct BinFile
{
    BINFILESELFPTR  Self;
    BFH             Value;
} BINFILE, * BINFILEPTR;
#pragma pack(pop)

typedef BinFile* (CLASSCALL* BINFILEFOLDERGETFILEACTION)(BinFileFolder* self);
typedef BinFileFinder* (CLASSCALL* BINFILEFOLDERGETFILEFINDERACTION)(BinFileFolder* self);
typedef BOOL(CLASSCALL* BINFILEFOLDERCREATEFOLDERACTION)(BinFileFolder* self, LPCSTR name);

// INHERITANCE: BaseFileFolderSelf
#pragma pack(push, 1)
typedef struct BinFileFolderSelf
{
    BINFILEFOLDERGETFILEACTION          GetFile;
    BINFILEFOLDERGETFILEFINDERACTION    GetFileFinder;
    BINFILEFOLDERCREATEFOLDERACTION     CreateFolder;
} BINFILEFOLDERSELF, * BINFILEFOLDERSELFPTR;
#pragma pack(pop)

// INHERITANCE: BaseFileFolder
#pragma pack(push, 1)
typedef struct BinFileFolder
{
    BINFILEFOLDERSELFPTR Self;
} BINFILEFOLDER, * BINFILEFOLDERPTR;
#pragma pack(pop)

typedef BinFileFinder* (CLASSCALL* BINFILEFINDERRELEASEACTION)(BinFileFinder* self, CONST OBJECTRELEASETYPE mode);
typedef BOOL(CLASSCALL* BINFILEFINDEROPENACTION)(BinFileFinder* self, LPCSTR path);
typedef VOID(CLASSCALL* BINFILEFINDERCLOSEACTION)(BinFileFinder* self);
typedef BOOL(CLASSCALL* BINFILEFINDERNEXTACTION)(BinFileFinder* self);
typedef LPCSTR(CLASSCALL* BINFILEFINDERGETNAMEACTION)(BinFileFinder* self);
typedef DWORD(CLASSCALL* BINFILEFINDERGETATTRIBUTESACTION)(BinFileFinder* self);
typedef DWORD(CLASSCALL* BINFILEFINDERGETSIZEACTION)(BinFileFinder* self);

// INHERITANCE: BaseFileFinderSelf
#pragma pack(push, 1)
typedef struct BinFileFinderSelf
{
    BINFILEFINDERRELEASEACTION          Release;
    BINFILEFINDEROPENACTION             Open;
    BINFILEFINDERCLOSEACTION            Close;
    BINFILEFINDERNEXTACTION             Next;
    BINFILEFINDERGETNAMEACTION          GetName;
    BINFILEFINDERGETATTRIBUTESACTION    GetAttributes;
    BINFILEFINDERGETSIZEACTION          GetSize;
} BINFILEFINDERSELF, * BINFILEFINDERSELFPTR;
#pragma pack(pop)

// INHERITANCE: BaseFileFinder
#pragma pack(push, 1)
typedef struct BinFileFinder
{
    BINFILEFINDERSELFPTR    Self;
    U8                      IsActive;
    HANDLE                  Handle;
    WIN32_FIND_DATAA        Data;
} BINFILEFINDER, * BINFILEFINDERPTR;
#pragma pack(pop)
