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
#include "ZipFile.hxx"

typedef enum FileContentType
{
    FILECONTENTTYPE_NONE            = 0,
    FILECONTENTTYPE_FILE            = 1, // Actual file
    FILECONTENTTYPE_COMBINED        = 2, // An archive with no data compression
    FILECONTENTTYPE_ZIP             = 3, // Gzip file
    FILECONTENTTYPE_COMPRESSED      = 8, // An archive with data compression
    FILECONTENTTYPE_FORCE_DWORD     = 0x7FFFFFF
} FILECONTENTTYPE, * FILECONTENTTYPEPTR;

#pragma pack(push, 1)
typedef struct BinFileContent
{
    LPSTR               Name;
    FILECONTENTTYPE     Type;
    U32                 Archive;
    BFH                 Value;
    U32                 Size;
    U32                 Chunk;
    U32                 Offset;
    BOOL                IsActive;
    ZIPFILE             Zip;
    BINFILE             File;
} BINFILECONTENT, * BINFILECONTENTPTR;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BinFileInfo
{
    U32                 Name;
    FILECONTENTTYPE     Type;
    U32                 Index;
    U32                 Size;
    U32                 Chunk;
} BINFILEINFO, * BINFILEINFOPTR;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BinFileChunk
{
    BFH                 Index;
    U32                 Chunk;
    U32                 Size;
    LPVOID              Content;
} BINFILECHUNK, * BINFILECHUNKPTR;
#pragma pack(pop)
