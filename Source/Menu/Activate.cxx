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

#include "Activate.hxx"
#include "Assets.hxx"
#include "BinArchive.hxx"
#include "BinFile.hxx"
#include "BinFileContent.hxx"
#include "ZipFile.hxx"

#include <stdlib.h>

// 0x10076540
VOID ActivateBinFilesState()
{
    ActivateBinFiles();
    ReleaseBinFiles();
}

// 0x10076550
VOID ActivateBinFiles()
{
    ActivateItems(AssetsState.Files,
        sizeof(BINFILECONTENT), MAX_BINARY_FILE_COUNT, (ACTIVATEACTION)BinFileContentActivate);
}

// 0x10076570
VOID ReleaseBinFiles()
{
    atexit(ReleaseBinFilesAction);
}

// 0x10076580
VOID ReleaseBinFilesAction()
{
    ReleaseItems(AssetsState.Files,
        sizeof(BINFILECONTENT), MAX_BINARY_FILE_COUNT, (RELEASEACTION)BinFileContentRelease);
}

// 0x10076640
VOID ActivateBinArchiveState()
{
    ActivateBinArchives();
    ReleaseBinArchives();
}

// 0x10076650
VOID ActivateBinArchives()
{
    ActivateItems(AssetsState.Archives,
        sizeof(BINARCHIVE), MAX_BINARY_ARCHIVE_COUNT, (ACTIVATEACTION)BinArchiveActivate);
}

// 0x10076670
VOID ReleaseBinArchives()
{
    atexit(ReleaseBinArchivesAction);
}

// 0x10076680
VOID ReleaseBinArchivesAction()
{
    ReleaseItems(AssetsState.Archives,
        sizeof(BINARCHIVE), MAX_BINARY_ARCHIVE_COUNT, (RELEASEACTION)BinArchiveRelease);
}

// 0x10082243
VOID ActivateItems(LPVOID pointer, U32 size, U32 count, ACTIVATEACTION action)
{
    ADDR address = (ADDR)pointer;

    for (U32 x = 0; x < count; x++)
    {
        action((LPVOID)(address + (ADDR)(x * size)));
        address = address + (ADDR)size;
    }
}

// 0x10082165
VOID ReleaseItems(LPVOID pointer, U32 size, U32 count, RELEASEACTION action)
{
    ADDR address = (ADDR)pointer + (ADDR)(size * count);

    for (U32 x = count; x != 0; x--)
    {
        action((LPVOID)(address + (ADDR)(x * size)));
        address = address - (ADDR)size;
    }
}

// 0x10097000
VOID Activate()
{
    // TODO FUN_10001000();
    // TODO FUN_10001a90();
    // TODO FUN_10001c80();
    // TODO FUN_10001e70();
    // TODO FUN_10001fc0();
    // TODO FUN_100025e0();
    // TODO FUN_10002a10();
    // TODO FUN_10003260();
    // TODO FUN_100035b0();
    // TODO FUN_100037c0();
    // TODO FUN_100038d0();
    // TODO FUN_10003900();
    // TODO FUN_100081b0();
    // TODO FUN_100081e0();
    // TODO FUN_10008f30();
    // TODO thunk_FUN_10008f80();
    // TODO FUN_100096f0();
    // TODO FUN_1000b080();
    // TODO FUN_1000b710();
    // TODO FUN_1000bca0();
    // TODO FUN_1000ee40();
    // TODO FUN_1000ff00();
    // TODO FUN_1000ff30();
    // TODO FUN_10010850();
    // TODO FUN_10011be0();
    // TODO FUN_10014220();
    // TODO FUN_100165e0();
    // TODO FUN_10016fa0();
    // TODO thunk_FUN_10016fe0();
    // TODO FUN_10017cb0();
    // TODO FUN_10019e20();
    // TODO FUN_1001aab0();
    // TODO FUN_10020230();
    // TODO FUN_10020260();
    // TODO FUN_10020ab0();
    // TODO thunk_FUN_10023bd0();
    // TODO thunk_FUN_10023bf0();
    // TODO thunk_FUN_10023c10();
    // TODO FUN_100241a0();
    // TODO FUN_10024500();
    // TODO FUN_10025c30();
    // TODO FUN_10025c60();
    // TODO FUN_10026840();
    // TODO FUN_10026b90();
    // TODO FUN_10026bc0();
    // TODO FUN_100282b0();
    // TODO FUN_10029ef0();
    // TODO FUN_1002a210();
    // TODO FUN_1002ab30();
    // TODO FUN_1002b670();
    // TODO FUN_1002bb80();
    // TODO FUN_1002c1f0();
    // TODO FUN_1002cb90();
    // TODO FUN_1002ccf0();
    // TODO FUN_1002d2a0();
    // TODO FUN_1002d450();
    // TODO FUN_1002d480();
    // TODO FUN_1002d4b0();
    // TODO FUN_1002d4e0();
    // TODO FUN_1002d520();
    // TODO FUN_1002d560();
    // TODO FUN_1002d5a0();
    // TODO FUN_1002d5e0();
    // TODO FUN_1002d620();
    // TODO FUN_1002d660();
    // TODO FUN_1002d6a0();
    // TODO FUN_1002d6e0();
    // TODO FUN_1002d720();
    // TODO FUN_1002d760();
    // TODO FUN_1002d7a0();
    // TODO FUN_1002d7e0();
    // TODO FUN_1002d820();
    // TODO FUN_1002d860();
    // TODO FUN_1002d8a0();
    // TODO FUN_1002d8e0();
    // TODO FUN_1002d920();
    // TODO FUN_1002d960();
    // TODO FUN_1002d9a0();
    // TODO FUN_1002d9e0();
    // TODO FUN_1002da20();
    // TODO FUN_1002da60();
    // TODO FUN_1002daa0();
    // TODO FUN_1002dae0();
    // TODO FUN_1002db20();
    // TODO FUN_1002db60();
    // TODO FUN_1002dba0();
    // TODO FUN_1002dbe0();
    // TODO FUN_1002dc20();
    // TODO FUN_1002dc60();
    // TODO FUN_1002dca0();
    // TODO FUN_1002dce0();
    // TODO FUN_1002dd20();
    // TODO FUN_1002dd60();
    // TODO FUN_1002dda0();
    // TODO FUN_1002dde0();
    // TODO FUN_1002de20();
    // TODO FUN_1002de60();
    // TODO FUN_1002dea0();
    // TODO FUN_1002dee0();
    // TODO FUN_1002df20();
    // TODO FUN_1002df90();
    // TODO FUN_1002dfd0();
    // TODO FUN_1002e010();
    // TODO FUN_1002e050();
    // TODO FUN_1002e090();
    // TODO FUN_1002e0d0();
    // TODO FUN_1002e110();
    // TODO FUN_1002e150();
    // TODO FUN_1002e190();
    // TODO FUN_1002e410();
    // TODO thunk_FUN_1002f340();
    // TODO FUN_1002f450();
    // TODO FUN_1002f480();
    ActivateBinFileFolder();
    // TODO thunk_FUN_100750c0();
    // TODO thunk_FUN_100754d0();
    // TODO FUN_10075fd0();
    // TODO FUN_10076020();
    // TODO FUN_10076070();
    // TODO FUN_100760c0();
    ActivateBinFilesState();
    ActivateBinArchiveState();
    // TODO thunk_FUN_10077450();
    ActivateZipFileFolder();
    ActivateZipWriterFolder();
    // TODO FUN_10080830();
}