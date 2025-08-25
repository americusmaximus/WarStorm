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

#include <zlib.h>

struct ZipFile;
struct ZipFileFinder;
struct ZipFileFolder;

typedef ZipFile* (CLASSCALL* ZIPFILERELEASEACTION)(ZipFile* self, CONST OBJECTRELEASETYPE mode);
typedef BOOL(CLASSCALL* ZIPFILEISACTIOVEACTION)(ZipFile* self);
typedef BOOL(CLASSCALL* ZIPFILEOPENACTION)(ZipFile* self, LPSTR name, U32 type);
typedef VOID(CLASSCALL* ZIPFILECLOSEACTION)(ZipFile* self);
typedef U32(CLASSCALL* ZIPFILEREADACTION)(ZipFile* self, LPVOID content, U32 size);
typedef U32(CLASSCALL* ZIPFILEWRITEACTION)(ZipFile* self, LPVOID content, U32 size);
typedef BOOL(CLASSCALL* ZIPFILEFLUSHACTION)(ZipFile* self);
typedef S32(CLASSCALL* ZIPFILESETPOINTERACTION)(ZipFile* self, S32 distance, U32 method);
typedef S32(CLASSCALL* ZIPFILEGETPOINTERACTION)(ZipFile* self);
typedef S32(CLASSCALL* ZIPFILEGETSIZEACTION)(ZipFile* self);
typedef U32(CLASSCALL* ZIPFILEGETSTRINGACTION)(ZipFile* self, LPSTR string, U32 length);
typedef U32(CDECLAPI* ZIPFILESETSTRINGACTION)(ZipFile* self, LPSTR format, ...);
typedef ZipFileFolder*(CLASSCALL* ZIPFILEGETFOLDERACTION)(ZipFile* self);

// INHERITANCE: BaseFileSelf
#pragma pack(push, 1)
typedef struct ZipFileSelf
{
    ZIPFILERELEASEACTION            Release;
    ZIPFILEISACTIOVEACTION          IsActive;
    ZIPFILEOPENACTION               Open;
    ZIPFILECLOSEACTION              Close;
    ZIPFILEREADACTION               Read;
    ZIPFILEWRITEACTION              Write;
    ZIPFILEFLUSHACTION              Flush;
    ZIPFILESETPOINTERACTION         SetPointer;
    ZIPFILEGETPOINTERACTION         GetPointer;
    ZIPFILEGETSIZEACTION            GetSize;
    ZIPFILEGETSTRINGACTION          GetString;
    ZIPFILESETSTRINGACTION          SetString;
    ZIPFILEGETFOLDERACTION          GetFolder;
} ZIPFILESELF, * ZIPFILESELFPTR;
#pragma pack(pop)

// INHERITANCE: BaseFile
#pragma pack(push, 1)
typedef struct ZipFile
{
    ZIPFILESELFPTR  Self;
    gzFile          Value;
} ZIPFILE, * ZIPFILEPTR;
#pragma pack(pop)

typedef ZipFile* (CLASSCALL* ZIPFILEFOLDERGETFILEACTION)(ZipFileFolder* self);
typedef ZipFileFinder* (CLASSCALL* ZIPFILEFOLDERGETFILEFINDERACTION)(ZipFileFolder* self);
typedef BOOL(CLASSCALL* ZIPFILEFOLDERCREATEFOLDERACTION)(ZipFileFolder* self, LPCSTR name);

#pragma pack(push, 1)
// INHERITANCE: BaseFileFolderSelf
typedef struct ZipFileFolderSelf
{
    ZIPFILEFOLDERGETFILEACTION          GetFile;
    ZIPFILEFOLDERGETFILEFINDERACTION    GetFileFinder;
    ZIPFILEFOLDERCREATEFOLDERACTION     CreateFolder;
} ZIPFILEFOLDERSELF, * ZIPFILEFOLDERSELFPTR;
#pragma pack(pop)

#pragma pack(push, 1)
// INHERITANCE: BaseFileFolder
typedef struct ZipFileFolder
{
    ZIPFILEFOLDERSELFPTR    Self;
} ZIPFILEFOLDER, * ZIPFILEFOLDERPTR;
#pragma pack(pop)

typedef ZipFileFinder ZIPFILEFINDER, * ZIPFILEFINDERPTR;

struct ZipWriter;
struct ZipWriterFinder;
struct ZipWriterFolder;

typedef ZipWriter* (CLASSCALL* ZIPWRITERRELEASEACTION)(ZipWriter* self, CONST OBJECTRELEASETYPE mode);
typedef BOOL(CLASSCALL* ZIPWRITERISACTIOVEACTION)(ZipWriter* self);
typedef BOOL(CLASSCALL* ZIPWRITEROPENACTION)(ZipWriter* self, LPSTR name, U32 type);
typedef VOID(CLASSCALL* ZIPWRITERCLOSEACTION)(ZipWriter* self);
typedef U32(CLASSCALL* ZIPWRITERREADACTION)(ZipWriter* self, LPVOID content, U32 size);
typedef U32(CLASSCALL* ZIPWRITERWRITEACTION)(ZipWriter* self, LPVOID content, U32 size);
typedef BOOL(CLASSCALL* ZIPWRITERFLUSHACTION)(ZipWriter* self);
typedef S32(CLASSCALL* ZIPWRITERSETPOINTERACTION)(ZipWriter* self, S32 distance, U32 method);
typedef S32(CLASSCALL* ZIPWRITERGETPOINTERACTION)(ZipWriter* self);
typedef S32(CLASSCALL* ZIPWRITERGETSIZEACTION)(ZipWriter* self);
typedef U32(CLASSCALL* ZIPWRITERGETSTRINGACTION)(ZipWriter* self, LPSTR string, U32 length);
typedef U32(CDECLAPI* ZIPWRITERSETSTRINGACTION)(ZipWriter* self, LPSTR format, ...);
typedef ZipWriterFolder* (CLASSCALL* ZIPWRITERGETFOLDERACTION)(ZipWriter* self);

// INHERITANCE: ZipFileSelf
#pragma pack(push, 1)
typedef struct ZipWriterSelf
{
    ZIPWRITERRELEASEACTION          Release;
    ZIPWRITERISACTIOVEACTION        IsActive;
    ZIPWRITEROPENACTION             Open;
    ZIPWRITERCLOSEACTION            Close;
    ZIPWRITERREADACTION             Read;
    ZIPWRITERWRITEACTION            Write;
    ZIPWRITERFLUSHACTION            Flush;
    ZIPWRITERSETPOINTERACTION       SetPointer;
    ZIPWRITERGETPOINTERACTION       GetPointer;
    ZIPWRITERGETSIZEACTION          GetSize;
    ZIPWRITERGETSTRINGACTION        GetString;
    ZIPWRITERSETSTRINGACTION        SetString;
    ZIPWRITERGETFOLDERACTION        GetFolder;
} ZIPWRITERSELF, * ZIPWRITERSELFPTR;
#pragma pack(pop)

// INHERITANCE: ZipFile
#pragma pack(push, 1)
typedef struct ZipWriter
{
    ZIPWRITERSELFPTR    Self;
    gzFile              Value;
    LPVOID              Buffer;
    U32                 Length;
    U32                 Size;
    U32                 Current;
} ZIPWRITER, * ZIPWRITERPTR;
#pragma pack(pop)

typedef ZipWriter* (CLASSCALL* ZIPWRITERFOLDERGETFILEACTION)(ZipWriterFolder* self);
typedef ZipWriterFinder* (CLASSCALL* ZIPWRITERFOLDERGETFILEFINDERACTION)(ZipWriterFolder* self);
typedef BOOL(CLASSCALL* ZIPWRITERFOLDERCREATEFOLDERACTION)(ZipWriterFolder* self, LPCSTR name);

#pragma pack(push, 1)
// INHERITANCE: ZipFileFolderSelf
typedef struct ZipWriterFolderSelf
{
    ZIPWRITERFOLDERGETFILEACTION        GetFile;
    ZIPWRITERFOLDERGETFILEFINDERACTION  GetFileFinder;
    ZIPWRITERFOLDERCREATEFOLDERACTION   CreateFolder;
} ZIPWRITERFOLDERSELF, * ZIPWRITERFOLDERSELFPTR;
#pragma pack(pop)

#pragma pack(push, 1)
// INHERITANCE: ZipFileFolder
typedef struct ZipWriterFolder
{
    ZIPWRITERFOLDERSELFPTR  Self;
} ZIPWRITERFOLDER, * ZIPWRITERFOLDERPTR;
#pragma pack(pop)

typedef ZipWriterFinder ZIPWRITERFINDER, * ZIPWRITERFINDERPTR;
