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
#include "FontAsset.hxx"

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

    struct
    {
        BINASSET    Sp2BT;                                  // 0x100b46c8

        BINASSET    MsgBox;                                 // 0x100b4b38

        BINASSET    MsglcBT1;                               // 0x100b4d78
        BINASSET    MsglcBT0;                               // 0x100b4d88
        BINASSET    Ramka;                                  // 0x100b4d98

        BINASSET    BunCloseBT;                             // 0x100b4fd8
        BINASSET    Sp3BT;                                  // 0x100b4fe8

        BINASSET    NBrifBT;                                // 0x100b5378
        BINASSET    NBrifBK;                                // 0x100b5388

        BINASSET    SpeedBT;                                // 0x100b57f8
        BINASSET    SpeedBar;                               // 0x100b5808
        BINASSET    StatPic;                                // 0x100b5818

        BINASSET    OpBT;                                   // 0x100b5830
        BINASSET    SplBT;                                  // 0x100b5840
        BINASSET    RsBT;                                   // 0x100b5850
        BINASSET    WinRus;                                 // 0x100b5860
        BINASSET    ColorsBT;                               // 0x100b5870
        BINASSET    MainBK;                                 // 0x100b5880
        BINASSET    MainBT;                                 // 0x100b5890
        BINASSET    MsgBoxBT;                               // 0x100b58a0
        BINASSET    ZvGold;                                 // 0x100b58b0
        BINASSET    ZvM;                                    // 0x100b58c0
        BINASSET    RgBT;                                   // 0x100b58d0
        BINASSET    ScrollBarBT;                            // 0x100b58e0

        BINASSET    Zvezdy;                                 // 0x100b5b20
        BINASSET    Sp3RB;                                  // 0x100b5b30
        BINASSET    ScrollBarSP;                            // 0x100b5b40
        BINASSET    LoadBT;                                 // 0x100b5b50

        BINASSET    Mp3BT;                                  // 0x100b5d98

        BINASSET    Msg2BT21;                               // 0x100b5dc0
        BINASSET    Msg2BT20;                               // 0x100b5dd0
        BINASSET    Msg2BT11;                               // 0x100b5de0
        BINASSET    Msg2BT10;                               // 0x100b5df0

        BINASSET    NbRamkaBT;                              // 0x100b5e00
        BINASSET    Mp4BT;                                  // 0x100b5e10

        BINASSET    MsglBT0;                                // 0x100b5e38
        BINASSET    Rombik;                                 // 0x100b5e48
        BINASSET    WinJap;                                 // 0x100b5e58
        BINASSET    MplBT;                                  // 0x100b5e68
        BINASSET    MsglBT1;                                // 0x100b5e78

        BINASSET    Mp2BT;                                  // 0x100b5e98
    } Assets;

    struct
    {
        FONTASSET   Plastilin2M;                            // 0x100b46d8

        FONTASSET   Plastilin3;                             // 0x100b4908

        FONTASSET   Main;                                   // 0x100b4b48

        FONTASSET   Plastilin3M;                            // 0x100b4da8

        FONTASSET   Plastilin1M;                            // 0x100b5148

        FONTASSET   Plastilin2;                             // 0x100b5398

        FONTASSET   Plastilin1;                             // 0x100b55c8

        FONTASSET   PlastilinS;                             // 0x100b58f0

        FONTASSET   Comic;                                  // 0x100b5b68
    } Fonts;
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
