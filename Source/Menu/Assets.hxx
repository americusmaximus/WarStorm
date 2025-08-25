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

#include "BinArchive.hxx"
#include "BinFileContent.hxx"

#define MAX_BINARY_ARCHIVE_COUNT    16
#define MAX_BINARY_CHUNK_COUNT      8
#define MAX_BINARY_FILE_COUNT       4096

typedef struct AssetStateModuleContainer
{
    BINARCHIVE          Archives[MAX_BINARY_ARCHIVE_COUNT]; // 0x100b7258
    BINFILECONTENT      Files[MAX_BINARY_FILE_COUNT];       // 0x100b93d8
    struct
    {
        U32             Count;                              // 0x100b71d0
        BINFILECHUNK    Values[MAX_BINARY_CHUNK_COUNT];     // 0x100b71d8
    } Chunks;
} ASSETSTATEMODULECONTAINER, * ASSETSTATEMODULECONTAINERPTR;

EXTERN ASSETSTATEMODULECONTAINER AssetsState;

BFH AcquireAssetFileIndex(LPCSTR name);
BOOL IsAssetFileActive(BFH indx);
BOOL OpenAssetFile(BFH indx);
LPVOID AcquireBinFileChunk(BFH indx, U32 chunk);
LPVOID InitializeBinFileChunk(BFH indx, U32 chunk, U32 size);
LPVOID ReadAssetFileChunk(BFH indx, U32 chunk);
S32 AcquireAssetFileOffset(BFH indx);
S32 AcquireAssetFileSize(BFH indx);
S32 SelectAssetFileOffset(BFH indx, S32 distance, DWORD method);
U32 AcquireBinFileChunkSize(BFH indx, U32 offset);
U32 ReadAssetFile(BFH indx, LPVOID content, U32 size);
U32 ReadAssetFileMultiChunk(LPVOID result, BFH indx, U32 offset, U32 size);
U32 ReadAssetFileSingleChunk(LPVOID result, BFH indx, U32 offset, U32 size);
VOID CloseAssetFile(BFH indx);
