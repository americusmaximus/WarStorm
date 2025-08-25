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

#include "Basic.hxx"
#include "Native.Basic.hxx"
#include "Objects.hxx"

#define INVALID_FILE_OFFSET         (-1)
#define INVALID_FILE_STRING_LENGTH  (-1)

#define FILEOPENTYPE_READ           0x0
#define FILEOPENTYPE_WRITE          0x1
#define FILEOPENTYPE_CREATE         0x2

#define FILEOPENTYPE_ACTION_MASK    0xFFFF

#define FILEOPENTYPE_DIRECTORY      0x10000

struct BaseFile;
struct BaseFileFolder;
struct BaseFileFinder;

typedef BaseFile* (CLASSCALL* BASEFILERELEASEACTION)(BaseFile* self, CONST OBJECTRELEASETYPE mode);
typedef BOOL(CLASSCALL* BASEFILEISACTIOVEACTION)(BaseFile* self);
typedef BOOL(CLASSCALL* BASEFILEOPENACTION)(BaseFile* self, LPCSTR name, U32 type);
typedef VOID(CLASSCALL* BASEFILECLOSEACTION)(BaseFile* self);
typedef U32(CLASSCALL* BASEFILEREADACTION)(BaseFile* self, LPVOID content, U32 size);
typedef U32(CLASSCALL* BASEFILEWRITEACTION)(BaseFile* self, LPVOID content, U32 size);
typedef BOOL(CLASSCALL* BASEFILEFLUSHACTION)(BaseFile* self);
typedef S32(CLASSCALL* BASEFILESETPOINTERACTION)(BaseFile* self, S32 distance, U32 method);
typedef S32(CLASSCALL* BASEFILEGETPOINTERACTION)(BaseFile* self);
typedef S32(CLASSCALL* BASEFILEGETSIZEACTION)(BaseFile* self);
typedef U32(CLASSCALL* BASEFILEGETSTRINGACTION)(BaseFile* self, LPSTR string, U32 length);
typedef U32(CDECLAPI* BASEFILESETSTRINGACTION)(BaseFile* self, LPSTR format, ...);
typedef BaseFileFolder* (CLASSCALL* BASEFILEGETFOLDERACTION)(BaseFile* self);

#pragma pack(push, 1)
typedef struct BaseFileSelf
{
    BASEFILERELEASEACTION           Release;
    BASEFILEISACTIOVEACTION         IsActive;
    BASEFILEOPENACTION              Open;
    BASEFILECLOSEACTION             Close;
    BASEFILEREADACTION              Read;
    BASEFILEWRITEACTION             Write;
    BASEFILEFLUSHACTION             Flush;
    BASEFILESETPOINTERACTION        SetPointer;
    BASEFILEGETPOINTERACTION        GetPointer;
    BASEFILEGETSIZEACTION           GetSize;
    BASEFILEGETSTRINGACTION         GetString;
    BASEFILESETSTRINGACTION         SetString;
    BASEFILEGETFOLDERACTION         GetFolder;
} BASEFILESELF, * BASEFILESELFPTR;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BaseFile
{
    BASEFILESELFPTR    Self;
} BASEFILE, * BASEFILEPTR;
#pragma pack(pop)

typedef BaseFile* (CLASSCALL* BASEFILEFOLDERGETFILEACTION)(BaseFileFolder* self);
typedef BaseFileFinder* (CLASSCALL* BASEFILEFOLDERGETFILEFINDERACTION)(BaseFileFolder* self);
typedef BOOL(CLASSCALL* BASEFILEFOLDERCREATEFOLDERACTION)(BaseFileFolder* self, LPCSTR name);

#pragma pack(push, 1)
typedef struct BaseFileFolderSelf
{
    BASEFILEFOLDERGETFILEACTION         GetFile;
    BASEFILEFOLDERGETFILEFINDERACTION   GetFileFinder;
    BASEFILEFOLDERCREATEFOLDERACTION    CreateFolder;
} BASEFILEFOLDERSELF, * BASEFILEFOLDERSELFPTR;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BaseFileFolder
{
    BASEFILEFOLDERSELFPTR   Self;
} BASEFILEFOLDER, * BASEFILEFOLDERPTR;
#pragma pack(pop)

typedef BaseFileFinder* (CLASSCALL* BASEFILEFINDERRELEASEACTION)(BaseFileFinder* self, CONST OBJECTRELEASETYPE mode);
typedef BOOL(CLASSCALL* BASEFILEFINDEROPENACTION)(BaseFileFinder* self, LPCSTR path);
typedef VOID(CLASSCALL* BASEFILEFINDERCLOSEACTION)(BaseFileFinder* self);
typedef BOOL(CLASSCALL* BASEFILEFINDERNEXTACTION)(BaseFileFinder* self);
typedef LPCSTR(CLASSCALL* BASEFILEFINDERGETNAMEACTION)(BaseFileFinder* self);
typedef DWORD(CLASSCALL* BASEFILEFINDERGETATTRIBUTESACTION)(BaseFileFinder* self);
typedef DWORD(CLASSCALL* BASEFILEFINDERGETSIZEACTION)(BaseFileFinder* self);

#pragma pack(push, 1)
typedef struct BaseFileFinderSelf
{
    BASEFILEFINDERRELEASEACTION          Release;
    BASEFILEFINDEROPENACTION             Open;
    BASEFILEFINDERCLOSEACTION            Close;
    BASEFILEFINDERNEXTACTION             Next;
    BASEFILEFINDERGETNAMEACTION          GetName;
    BASEFILEFINDERGETATTRIBUTESACTION    GetAttributes;
    BASEFILEFINDERGETSIZEACTION          GetSize;
} BASEFILEFINDERSELF, * BASEFILEFINDERSELFPTR;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BaseFileFinder
{
    BASEFILEFINDERSELFPTR   Self;
} BASEFILEFINDER, * BASEFILEFINDERPTR;
#pragma pack(pop)
