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

#include "Action.hxx"
#include "Activate.hxx"
#include "AssetFile.hxx"
#include "Assets.hxx"
#include "BinArchive.hxx"
#include "BinAsset.hxx"
#include "BinFile.hxx"
#include "BinFileContent.hxx"
#include "Input.hxx"
#include "Module.hxx"
#include "Window.hxx"
#include "ZipFile.hxx"

#include <stdlib.h>

// 0x1002d4e0
VOID ActivateBinAssetMainBKState()
{
    ActivateBinAssetMainBK();
    ActivateReleaseBinAssetMainBK();
}

// 0x1002d4f0
VOID ActivateBinAssetMainBK()
{
    ActivateBinAsset(&AssetsState.Assets.MainBK);
}

// 0x1002d500
VOID ActivateReleaseBinAssetMainBK()
{
    atexit(ReleaseBinAssetMainBKAction);
}

// 0x1002d510
VOID ReleaseBinAssetMainBKAction()
{
    DisposeBinAsset(&AssetsState.Assets.MainBK);
}

// 0x1002d520
VOID ActivateBinAssetMainBTState()
{
    ActivateBinAssetMainBT();
    ActivateReleaseBinAssetMainBT();
}

// 0x1002d530
VOID ActivateBinAssetMainBT()
{
    ActivateBinAsset(&AssetsState.Assets.MainBT);
}

// 0x1002d540
VOID ActivateReleaseBinAssetMainBT()
{
    atexit(ReleaseBinAssetMainBTAction);
}

// 0x1002d550
VOID ReleaseBinAssetMainBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.MainBT);
}

// 0x1002d560
VOID ActivateBinAssetSplBTState()
{
    ActivateBinAssetSplBT();
    ActivateReleaseBinAssetSplBT();
}

// 0x1002d570
VOID ActivateBinAssetSplBT()
{
    ActivateBinAsset(&AssetsState.Assets.SplBT);
}

// 0x1002d580
VOID ActivateReleaseBinAssetSplBT()
{
    atexit(ReleaseBinAssetSplBTAction);
}

// 0x1002d590
VOID ReleaseBinAssetSplBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.SplBT);
}

// 0x1002d5a0
VOID ActivateBinAssetRamkaState()
{
    ActivateBinAssetRamka();
    ActivateReleaseBinAssetRamka();
}

// 0x1002d5b0
VOID ActivateBinAssetRamka()
{
    ActivateBinAsset(&AssetsState.Assets.Ramka);
}

// 0x1002d5c0
VOID ActivateReleaseBinAssetRamka()
{
    atexit(ReleaseBinAssetRamkaAction);
}

// 0x1002d5d0
VOID ReleaseBinAssetRamkaAction()
{
    DisposeBinAsset(&AssetsState.Assets.Ramka);
}

// 0x1002d5e0
VOID ActivateBinAssetSp2BTState()
{
    ActivateBinAssetSp2BT();
    ActivateReleaseBinAssetSp2BT();
}

// 0x1002d5f0
VOID ActivateBinAssetSp2BT()
{
    ActivateBinAsset(&AssetsState.Assets.Sp2BT);
}

// 0x1002d600
VOID ActivateReleaseBinAssetSp2BT()
{
    atexit(ReleaseBinAssetSp2BTAction);
}

// 0x1002d610
VOID ReleaseBinAssetSp2BTAction()
{
    DisposeBinAsset(&AssetsState.Assets.Sp2BT);
}

// 0x1002d620
VOID ActivateBinAssetSp3BTState()
{
    ActivateBinAssetSp3BT();
    ActivateReleaseBinAssetSp3BT();
}

// 0x1002d630
VOID ActivateBinAssetSp3BT()
{
    ActivateBinAsset(&AssetsState.Assets.Sp3BT);
}

// 0x1002d640
VOID ActivateReleaseBinAssetSp3BT()
{
    atexit(ReleaseBinAssetSp3BTAction);
}

// 0x1002d650
VOID ReleaseBinAssetSp3BTAction()
{
    DisposeBinAsset(&AssetsState.Assets.Sp3BT);
}

// 0x1002d660
VOID ActivateBinAssetSp3RBState()
{
    ActivateBinAssetSp3RB();
    ActivateReleaseBinAssetSp3RB();
}

// 0x1002d670
VOID ActivateBinAssetSp3RB()
{
    ActivateBinAsset(&AssetsState.Assets.Sp3RB);
}

// 0x1002d680
VOID ActivateReleaseBinAssetSp3RB()
{
    atexit(ReleaseBinAssetSp3RBAction);
}

// 0x1002d690
VOID ReleaseBinAssetSp3RBAction()
{
    DisposeBinAsset(&AssetsState.Assets.Sp3RB);
}

// 0x1002d6a0
VOID ActivateBinAssetLoadBTState()
{
    ActivateBinAssetLoadBT();
    ActivateReleaseBinAssetLoadBT();
}

// 0x1002d6b0
VOID ActivateBinAssetLoadBT()
{
    ActivateBinAsset(&AssetsState.Assets.LoadBT);
}

// 0x1002d6c0
VOID ActivateReleaseBinAssetLoadBT()
{
    atexit(ReleaseBinAssetLoadBTAction);
}

// 0x1002d6d0
VOID ReleaseBinAssetLoadBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.LoadBT);
}

// 0x1002d6e0
VOID ActivateBinAssetMplBTState()
{
    ActivateBinAssetMplBT();
    ActivateReleaseBinAssetMplBT();
}

// 0x1002d6f0
VOID ActivateBinAssetMplBT()
{
    ActivateBinAsset(&AssetsState.Assets.MplBT);
}

// 0x1002d700
VOID ActivateReleaseBinAssetMplBT()
{
    atexit(ReleaseBinAssetMplBTAction);
}

// 0x1002d710
VOID ReleaseBinAssetMplBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.MplBT);
}

// 0x1002d720
VOID ActivateBinAssetScrollBarBTState()
{
    ActivateBinAssetScrollBarBT();
    ActivateReleaseBinAssetScrollBarBT();
}

// 0x1002d730
VOID ActivateBinAssetScrollBarBT()
{
    ActivateBinAsset(&AssetsState.Assets.ScrollBarBT);
}

// 0x1002d740
VOID ActivateReleaseBinAssetScrollBarBT()
{
    atexit(ReleaseBinAssetScrollBarBTAction);
}

// 0x1002d750
VOID ReleaseBinAssetScrollBarBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.ScrollBarBT);
}

// 0x1002d760
VOID ActivateBinAssetScrollBarSPState()
{
    ActivateBinAssetScrollBarSP();
    ActivateReleaseBinAssetScrollBarSP();
}

// 0x1002d770
VOID ActivateBinAssetScrollBarSP()
{
    ActivateBinAsset(&AssetsState.Assets.ScrollBarSP);
}

// 0x1002d780
VOID ActivateReleaseBinAssetScrollBarSP()
{
    atexit(ReleaseBinAssetScrollBarSPAction);
}

// 0x1002d790
VOID ReleaseBinAssetScrollBarSPAction()
{
    DisposeBinAsset(&AssetsState.Assets.ScrollBarSP);
}

// 0x1002d7a0
VOID ActivateBinAssetMp2BTState()
{
    ActivateBinAssetMp2BT();
    ActivateReleaseBinAssetMp2BT();
}

// 0x1002d7b0
VOID ActivateBinAssetMp2BT()
{
    ActivateBinAsset(&AssetsState.Assets.Mp2BT);
}

// 0x1002d7c0
VOID ActivateReleaseBinAssetMp2BT()
{
    atexit(BinAssetMp2BTAction);
}

// 0x1002d7d0
VOID BinAssetMp2BTAction()
{
    DisposeBinAsset(&AssetsState.Assets.Mp2BT);
}

// 0x1002d7e0
VOID ActivateBinAssetMp3BTState()
{
    ActivateBinAssetMp3BT();
    ActivateReleaseBinAssetMp3BT();
}

// 0x1002d7f0
VOID ActivateBinAssetMp3BT()
{
    ActivateBinAsset(&AssetsState.Assets.Mp3BT);
}

// 0x1002d800
VOID ActivateReleaseBinAssetMp3BT()
{
    atexit(BinAssetMp3BTAction);
}

// 0x1002d810
VOID BinAssetMp3BTAction()
{
    DisposeBinAsset(&AssetsState.Assets.Mp3BT);
}

// 0x1002d820
VOID ActivateBinAssetMp4BTState()
{
    ActivateBinAssetMp4BT();
    ActivateReleaseBinAssetMp4BT();
}

// 0x1002d830
VOID ActivateBinAssetMp4BT()
{
    ActivateBinAsset(&AssetsState.Assets.Mp4BT);
}

// 0x1002d840
VOID ActivateReleaseBinAssetMp4BT()
{
    atexit(BinAssetMp4BTAction);
}

// 0x1002d850
VOID BinAssetMp4BTAction()
{
    DisposeBinAsset(&AssetsState.Assets.Mp4BT);
}

// 0x1002d860
VOID ActivateBinAssetOpBTState()
{
    ActivateBinAssetOpBT();
    ActivateReleaseBinAssetOpBT();
}

// 0x1002d870
VOID ActivateBinAssetOpBT()
{
    ActivateBinAsset(&AssetsState.Assets.OpBT);
}

// 0x1002d880
VOID ActivateReleaseBinAssetOpBT()
{
    atexit(BinAssetOpBTAction);
}

// 0x1002d890
VOID BinAssetOpBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.OpBT);
}

// 0x1002d8a0
VOID ActivateBinAssetRgBTState()
{
    ActivateBinAssetRgBT();
    ActivateReleaseBinAssetRgBT();
}

// 0x1002d8b0
VOID ActivateBinAssetRgBT()
{
    ActivateBinAsset(&AssetsState.Assets.RgBT);
}

// 0x1002d8c0
VOID ActivateReleaseBinAssetRgBT()
{
    atexit(BinAssetRgBTAction);
}

// 0x1002d8d0
VOID BinAssetRgBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.RgBT);
}

// 0x1002d8e0
VOID ActivateBinAssetRsBTState()
{
    ActivateBinAssetRsBT();
    ActivateReleaseBinAssetRsBT();
}

// 0x1002d8f0
VOID ActivateBinAssetRsBT()
{
    ActivateBinAsset(&AssetsState.Assets.RsBT);
}

// 0x1002d900
VOID ActivateReleaseBinAssetRsBT()
{
    atexit(BinAssetRsBTAction);
}

// 0x1002d910
VOID BinAssetRsBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.RsBT);
}

// 0x1002d920
VOID ActivateBinAssetStatPicState()
{
    ActivateBinAssetStatPic();
    ActivateReleaseBinAssetStatPic();
}

// 0x1002d930
VOID ActivateBinAssetStatPic()
{
    ActivateBinAsset(&AssetsState.Assets.StatPic);
}

// 0x1002d940
VOID ActivateReleaseBinAssetStatPic()
{
    atexit(BinAssetStatPicAction);
}

// 0x1002d950
VOID BinAssetStatPicAction()
{
    DisposeBinAsset(&AssetsState.Assets.StatPic);
}

// 0x1002d960
VOID ActivateBinAssetWinJapState()
{
    ActivateBinAssetWinJap();
    ActivateReleaseBinAssetWinJap();
}

// 0x1002d970
VOID ActivateBinAssetWinJap()
{
    ActivateBinAsset(&AssetsState.Assets.WinJap);
}

// 0x1002d980
VOID ActivateReleaseBinAssetWinJap()
{
    atexit(BinAssetWinJapAction);
}

// 0x1002d990
VOID BinAssetWinJapAction()
{
    DisposeBinAsset(&AssetsState.Assets.WinJap);
}

// 0x1002d9a0
VOID ActivateBinAssetWinRusState()
{
    ActivateBinAssetWinRus();
    ActivateReleaseBinAssetWinRus();
}

// 0x1002d9b0
VOID ActivateBinAssetWinRus()
{
    ActivateBinAsset(&AssetsState.Assets.WinRus);
}

// 0x1002d9c0
VOID ActivateReleaseBinAssetWinRus()
{
    atexit(BinAssetWinRusAction);
}

// 0x1002d9d0
VOID BinAssetWinRusAction()
{
    DisposeBinAsset(&AssetsState.Assets.WinRus);
}

// 0x1002d9e0
VOID ActivateBinAssetMsgBoxBTState()
{
    ActivateBinAssetMsgBoxBT();
    ActivateReleaseBinAssetMsgBoxBT();
}

// 0x1002d9f0
VOID ActivateBinAssetMsgBoxBT()
{
    ActivateBinAsset(&AssetsState.Assets.MsgBoxBT);
}

// 0x1002da00
VOID ActivateReleaseBinAssetMsgBoxBT()
{
    atexit(ReleaseBinAssetMsgBoxBTAction);
}

// 0x1002da10
VOID ReleaseBinAssetMsgBoxBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.MsgBoxBT);
}

// 0x1002da20
VOID ActivateBinAssetColorsBTState()
{
    ActivateBinAssetColorsBT();
    ActivateReleaseBinAssetColorsBT();
}

// 0x1002da30
VOID ActivateBinAssetColorsBT()
{
    ActivateBinAsset(&AssetsState.Assets.ColorsBT);
}

// 0x1002da40
VOID ActivateReleaseBinAssetColorsBT()
{
    atexit(ReleaseBinAssetColorsBTAction);
}

// 0x1002da50
VOID ReleaseBinAssetColorsBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.ColorsBT);
}

// 0x1002da60
VOID ActivateBinAssetBunCloseBTState()
{
    ActivateBinAssetBunCloseBT();
    ActivateReleaseBinAssetBunCloseBT();
}

// 0x1002da70
VOID ActivateBinAssetBunCloseBT()
{
    ActivateBinAsset(&AssetsState.Assets.BunCloseBT);
}

// 0x1002da80
VOID ActivateReleaseBinAssetBunCloseBT()
{
    atexit(ReleaseBinAssetBunCloseBTAction);
}

// 0x1002da90
VOID ReleaseBinAssetBunCloseBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.BunCloseBT);
}

// 0x1002daa0
VOID ActivateBinAssetSpeedBarState()
{
    ActivateBinAssetSpeedBar();
    ActivateReleaseBinAssetSpeedBar();
}

// 0x1002dab0
VOID ActivateBinAssetSpeedBar()
{
    ActivateBinAsset(&AssetsState.Assets.SpeedBar);
}

// 0x1002dac0
VOID ActivateReleaseBinAssetSpeedBar()
{
    atexit(ReleaseBinAssetSpeedBarAction);
}

// 0x1002dad0
VOID ReleaseBinAssetSpeedBarAction()
{
    DisposeBinAsset(&AssetsState.Assets.SpeedBar);
}

// 0x1002dae0
VOID ActivateBinAssetSpeedBTState()
{
    ActivateBinAssetSpeedBT();
    ActivateReleaseBinAssetSpeedBT();
}

// 0x1002daf0
VOID ActivateBinAssetSpeedBT()
{
    ActivateBinAsset(&AssetsState.Assets.SpeedBT);
}

// 0x1002db00
VOID ActivateReleaseBinAssetSpeedBT()
{
    atexit(ReleaseBinAssetSpeedBTAction);
}

// 0x1002db10
VOID ReleaseBinAssetSpeedBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.SpeedBT);
}

// 0x1002db20
VOID ActivateBinAssetNbRamkaBTState()
{
    ActivateBinAssetNbRamkaBT();
    ActivateReleaseBinAssetNbRamkaBT();
}

// 0x1002db30
VOID ActivateBinAssetNbRamkaBT()
{
    ActivateBinAsset(&AssetsState.Assets.NbRamkaBT);
}

// 0x1002db40
VOID ActivateReleaseBinAssetNbRamkaBT()
{
    atexit(ReleaseBinAssetNbRamkaBTAction);
}

// 0x1002db50
VOID ReleaseBinAssetNbRamkaBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.NbRamkaBT);
}

// 0x1002db60
VOID ActivateBinAssetNBrifBTState()
{
    ActivateBinAssetNBrifBT();
    ActivateReleaseBinAssetNBrifBT();
}

// 0x1002db70
VOID ActivateBinAssetNBrifBT()
{
    ActivateBinAsset(&AssetsState.Assets.NBrifBT);
}

// 0x1002db80
VOID ActivateReleaseBinAssetNBrifBT()
{
    atexit(ReleaseBinAssetNBrifBTAction);
}

// 0x1002db90
VOID ReleaseBinAssetNBrifBTAction()
{
    DisposeBinAsset(&AssetsState.Assets.NBrifBT);
}

// 0x1002dba0
VOID ActivateBinAssetNBrifBKState()
{
    ActivateBinAssetNBrifBK();
    ActivateReleaseBinAssetNBrifBK();
}

// 0x1002dbb0
VOID ActivateBinAssetNBrifBK()
{
    ActivateBinAsset(&AssetsState.Assets.NBrifBK);
}

// 0x1002dbc0
VOID ActivateReleaseBinAssetNBrifBK()
{
    atexit(ReleaseBinAssetNBrifBKAction);
}

// 0x1002dbd0
VOID ReleaseBinAssetNBrifBKAction()
{
    DisposeBinAsset(&AssetsState.Assets.NBrifBK);
}

// 0x1002dbe0
VOID ActivateBinAssetMsglBT0State()
{
    ActivateBinAssetMsglBT0();
    ActivateReleaseBinAssetMsglBT0();
}

// 0x1002dbf0
VOID ActivateBinAssetMsglBT0()
{
    ActivateBinAsset(&AssetsState.Assets.MsglBT0);
}

// 0x1002dc00
VOID ActivateReleaseBinAssetMsglBT0()
{
    atexit(ReleaseBinAssetMsglBT0Action);
}

// 0x1002dc10
VOID ReleaseBinAssetMsglBT0Action()
{
    DisposeBinAsset(&AssetsState.Assets.MsglBT0);
}

// 0x1002dc20
VOID ActivateBinAssetMsglBT1State()
{
    ActivateBinAssetMsglBT1();
    ActivateReleaseBinAssetMsglBT1();
}

// 0x1002dc30
VOID ActivateBinAssetMsglBT1()
{
    ActivateBinAsset(&AssetsState.Assets.MsglBT1);
}

// 0x1002dc40
VOID ActivateReleaseBinAssetMsglBT1()
{
    atexit(ReleaseBinAssetMsglBT1Action);
}

// 0x1002dc50
VOID ReleaseBinAssetMsglBT1Action()
{
    DisposeBinAsset(&AssetsState.Assets.MsglBT1);
}

// 0x1002dc60
VOID ActivateBinAssetMsglcBT0State()
{
    ActivateBinAssetMsglcBT0();
    ActivateReleaseBinAssetMsglcBT0();
}

// 0x1002dc70
VOID ActivateBinAssetMsglcBT0()
{
    ActivateBinAsset(&AssetsState.Assets.MsglcBT0);
}

// 0x1002dc80
VOID ActivateReleaseBinAssetMsglcBT0()
{
    atexit(ReleaseBinAssetMsglcBT0Action);
}

// 0x1002dc90
VOID ReleaseBinAssetMsglcBT0Action()
{
    DisposeBinAsset(&AssetsState.Assets.MsglcBT0);
}

// 0x1002dca0
VOID ActivateBinAssetMsglcBT1State()
{
    ActivateBinAssetMsglcBT1();
    ActivateReleaseBinAssetMsglcBT1();
}

// 0x1002dcb0
VOID ActivateBinAssetMsglcBT1()
{
    ActivateBinAsset(&AssetsState.Assets.MsglcBT1);
}

// 0x1002dcc0
VOID ActivateReleaseBinAssetMsglcBT1()
{
    atexit(ReleaseBinAssetMsglcBT1Action);
}

// 0x1002dcd0
VOID ReleaseBinAssetMsglcBT1Action()
{
    DisposeBinAsset(&AssetsState.Assets.MsglcBT1);
}

// 0x1002dce0
VOID ActivateBinAssetMsg2BT10State()
{
    ActivateBinAssetMsg2BT10();
    ActivateReleaseBinAssetMsg2BT10();
}

// 0x1002dcf0
VOID ActivateBinAssetMsg2BT10()
{
    ActivateBinAsset(&AssetsState.Assets.Msg2BT10);
}

// 0x1002dd00
VOID ActivateReleaseBinAssetMsg2BT10()
{
    atexit(ReleaseBinAssetMsg2BT10Action);
}

// 0x1002dd10
VOID ReleaseBinAssetMsg2BT10Action()
{
    DisposeBinAsset(&AssetsState.Assets.Msg2BT10);
}

// 0x1002dd20
VOID ActivateBinAssetMsg2BT11State()
{
    ActivateBinAssetMsg2BT11();
    ActivateReleaseBinAssetMsg2BT11();
}

// 0x1002dd30
VOID ActivateBinAssetMsg2BT11()
{
    ActivateBinAsset(&AssetsState.Assets.Msg2BT11);
}

// 0x1002dd40
VOID ActivateReleaseBinAssetMsg2BT11()
{
    atexit(ReleaseBinAssetMsg2BT11Action);
}

// 0x1002dd50
VOID ReleaseBinAssetMsg2BT11Action()
{
    DisposeBinAsset(&AssetsState.Assets.Msg2BT11);
}

// 0x1002dd60
VOID ActivateBinAssetMsg2BT20State()
{
    ActivateBinAssetMsg2BT20();
    ActivateReleaseBinAssetMsg2BT20();
}

// 0x1002dd70
VOID ActivateBinAssetMsg2BT20()
{
    ActivateBinAsset(&AssetsState.Assets.Msg2BT20);
}

// 0x1002dd80
VOID ActivateReleaseBinAssetMsg2BT20()
{
    atexit(ReleaseBinAssetMsg2BT20Action);
}

// 0x1002dd90
VOID ReleaseBinAssetMsg2BT20Action()
{
    DisposeBinAsset(&AssetsState.Assets.Msg2BT20);
}

// 0x1002dda0
VOID ActivateBinAssetMsg2BT21State()
{
    ActivateBinAssetMsg2BT21();
    ActivateReleaseBinAssetMsg2BT21();
}

// 0x1002ddb0
VOID ActivateBinAssetMsg2BT21()
{
    ActivateBinAsset(&AssetsState.Assets.Msg2BT21);
}

// 0x1002ddc0
VOID ActivateReleaseBinAssetMsg2BT21()
{
    atexit(ReleaseBinAssetMsg2BT21Action);
}

// 0x1002ddd0
VOID ReleaseBinAssetMsg2BT21Action()
{
    DisposeBinAsset(&AssetsState.Assets.Msg2BT21);
}

// 0x1002dde0
VOID ActivateBinAssetRombikState()
{
    ActivateBinAssetRombik();
    ActivateReleaseBinAssetRombik();
}

// 0x1002ddf0
VOID ActivateBinAssetRombik()
{
    ActivateBinAsset(&AssetsState.Assets.Rombik);
}

// 0x1002de00
VOID ActivateReleaseBinAssetRombik()
{
    atexit(ReleaseBinAssetRombikAction);
}

// 0x1002de10
VOID ReleaseBinAssetRombikAction()
{
    DisposeBinAsset(&AssetsState.Assets.Rombik);
}

// 0x1002de20
VOID ActivateBinAssetMsgBoxState()
{
    ActivateBinAssetMsgBox();
    ActivateReleaseBinAssetMsgBox();
}

// 0x1002de30
VOID ActivateBinAssetMsgBox()
{
    ActivateBinAsset(&AssetsState.Assets.MsgBox);
}

// 0x1002de40
VOID ActivateReleaseBinAssetMsgBox()
{
    atexit(ReleaseBinAssetMsgBoxAction);
}

// 0x1002de50
VOID ReleaseBinAssetMsgBoxAction()
{
    DisposeBinAsset(&AssetsState.Assets.MsgBox);
}

// 0x1002de60
VOID ActivateBinAssetZvezdyState()
{
    ActivateBinAssetZvezdy();
    ActivateReleaseBinAssetZvezdy();
}

// 0x1002de70
VOID ActivateBinAssetZvezdy()
{
    ActivateBinAsset(&AssetsState.Assets.Zvezdy);
}

// 0x1002de80
VOID ActivateReleaseBinAssetZvezdy()
{
    atexit(ReleaseBinAssetZvezdyAction);
}

// 0x1002de90
VOID ReleaseBinAssetZvezdyAction()
{
    DisposeBinAsset(&AssetsState.Assets.Zvezdy);
}

// 0x1002dea0
VOID ActivateBinAssetZvMState()
{
    ActivateBinAssetZvM();
    ActivateReleaseBinAssetZvM();
}

// 0x1002deb0
VOID ActivateBinAssetZvM()
{
    ActivateBinAsset(&AssetsState.Assets.ZvM);
}

// 0x1002dec0
VOID ActivateReleaseBinAssetZvM()
{
    atexit(ReleaseBinAssetZvMAction);
}

// 0x1002ded0
VOID ReleaseBinAssetZvMAction()
{
    DisposeBinAsset(&AssetsState.Assets.ZvM);
}

// 0x1002dee0
VOID ActivateBinAssetZvGoldState()
{
    ActivateBinAssetZvGold();
    ActivateReleaseBinAssetZvGold();
}

// 0x1002def0
VOID ActivateBinAssetZvGold()
{
    ActivateBinAsset(&AssetsState.Assets.ZvGold);
}

// 0x1002df00
VOID ActivateReleaseBinAssetZvGold()
{
    atexit(ReleaseBinAssetZvGoldAction);
}

// 0x1002df10
VOID ReleaseBinAssetZvGoldAction()
{
    DisposeBinAsset(&AssetsState.Assets.ZvGold);
}

// 0x1002f330
// 0x1002f340
VOID ActivateWindowState()
{
    ActivateWindowState(&WindowState.Window, InitializeModuleAction, ExecuteModuleAction, ReleaseModuleAction);
}

// 0x10075fd0
VOID ActivateInputInitializeState()
{
    ActivateInputInitialize();
    ActivateReleaseInputInitialize();
}

// 0x10075fe0
VOID ActivateInputInitialize()
{
    InitializeActionHandler(&InputState.Initialize,
        &ActionState.Initialize, INPUT_ACTION_HANDLER_PRIORITY, InitializeDirectInputAction);
}

// 0x10076000
VOID ActivateReleaseInputInitialize()
{
    atexit(ReleaseInputInitializeAction);
}

// 0x10076010
VOID ReleaseInputInitializeAction()
{
    ReleaseActionHandler(&InputState.Initialize);
}

// 0x10076020
VOID ActivateInputExecuteState()
{
    ActivateInputExecute();
    ActivateReleaseInputExecute();
}

// 0x10076030
VOID ActivateInputExecute()
{
    InitializeActionHandler(&InputState.Execute,
        &ActionState.Execute, INPUT_ACTION_HANDLER_PRIORITY, AcquireDirectInputAction);
}

// 0x10076050
VOID ActivateReleaseInputExecute()
{
    atexit(ReleaseInputExecuteAction);
}

// 0x10076060
VOID ReleaseInputExecuteAction()
{
    ReleaseActionHandler(&InputState.Execute);
}

// 0x10076070
VOID ActivateInputReleaseState()
{
    ActivateInputRelease();
    ActivateReleaseInputRelease();
}

// 0x100760a0
VOID ActivateReleaseInputRelease()
{
    atexit(ReleaseInputReleaseAction);
}

// 0x100760b0
VOID ReleaseInputReleaseAction()
{
    ReleaseActionHandler(&InputState.Release);
}

// 0x10076080
VOID ActivateInputRelease()
{
    InitializeActionHandler(&InputState.Release,
        &ActionState.Release, INPUT_ACTION_HANDLER_PRIORITY, ReleaseDirectInputAction);
}

// 0x100760c0
VOID ActivateInputMessageState()
{
    ActivateInputMessage();
    ActivateReleaseInputMessage();
}

// 0x100760d0
VOID ActivateInputMessage()
{
    InitializeActionHandler(&InputState.Message,
        &ActionState.Message, INPUT_ACTION_HANDLER_PRIORITY, (ACTIONHANDLERLAMBDA)InputMessageAction);
}

// 0x100760f0
VOID ActivateReleaseInputMessage()
{
    atexit(ReleaseInputMessageAction);
}

// 0x10076100
VOID ReleaseInputMessageAction()
{
    ReleaseActionHandler(&InputState.Message);
}

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
    ActivateBinAssetMainBKState();
    ActivateBinAssetMainBTState();
    ActivateBinAssetSplBTState();
    ActivateBinAssetRamkaState();
    ActivateBinAssetSp2BTState();
    ActivateBinAssetSp3BTState();
    ActivateBinAssetSp3RBState();
    ActivateBinAssetLoadBTState();
    ActivateBinAssetMplBTState();
    ActivateBinAssetScrollBarBTState();
    ActivateBinAssetScrollBarSPState();
    ActivateBinAssetMp2BTState();
    ActivateBinAssetMp3BTState();
    ActivateBinAssetMp4BTState();
    ActivateBinAssetOpBTState();
    ActivateBinAssetRgBTState();
    ActivateBinAssetRsBTState();
    ActivateBinAssetStatPicState();
    ActivateBinAssetWinJapState();
    ActivateBinAssetWinRusState();
    ActivateBinAssetMsgBoxBTState();
    ActivateBinAssetColorsBTState();
    ActivateBinAssetBunCloseBTState();
    ActivateBinAssetSpeedBarState();
    ActivateBinAssetSpeedBTState();
    ActivateBinAssetNbRamkaBTState();
    ActivateBinAssetNBrifBTState();
    ActivateBinAssetNBrifBKState();
    ActivateBinAssetMsglBT0State();
    ActivateBinAssetMsglBT1State();
    ActivateBinAssetMsglcBT0State();
    ActivateBinAssetMsglcBT1State();
    ActivateBinAssetMsg2BT10State();
    ActivateBinAssetMsg2BT11State();
    ActivateBinAssetMsg2BT20State();
    ActivateBinAssetMsg2BT21State();
    ActivateBinAssetRombikState();
    ActivateBinAssetMsgBoxState();
    ActivateBinAssetZvezdyState();
    ActivateBinAssetZvMState();
    ActivateBinAssetZvGoldState();
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
    ActivateWindowState();
    // TODO FUN_1002f450();
    // TODO FUN_1002f480();
    ActivateBinFileFolder();
    // TODO thunk_FUN_100750c0();
    // TODO thunk_FUN_100754d0();
    ActivateInputInitializeState();
    ActivateInputExecuteState();
    ActivateInputReleaseState();
    ActivateInputMessageState();
    ActivateBinFilesState();
    ActivateBinArchiveState();
    ActivateAssetFileFolder();
    ActivateZipFileFolder();
    ActivateZipWriterFolder();
    // TODO FUN_10080830();
}
