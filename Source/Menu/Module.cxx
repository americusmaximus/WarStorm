/*
Copyright (c) 2024 - 2025 Americus Maximus

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

#include "Assets.hxx"
#include "AssetFile.hxx"
#include "BaseFile.hxx"
#include "BinFile.hxx"
#include "Game.hxx"
#include "Logger.hxx"
#include "State.hxx"
#include "Settings.hxx"

#include <..\Text\Resources.hxx>

// 0x1002bd40
VOID AcquireIniFileState(VOID)
{
    State.IsIniActive = GetPrivateProfileIntA("debug", "useinifile", FALSE, State.App->Ini);
}

// 0x1002e450
// a.k.a. CA_ETEXT_Init
BOOL InitializeModuleAction()
{
    ClipCursor(NULL);

    State.Module = State.App->Module;
    State.Renderer = State.Module->Renderer;

    AcquireStartArguments(NULL);

    LogMessage("CA_ETEXT_Init()\n");
    AcquireIniFileState();

    LogMessage("DPLAY_Done()\n");
    ReleaseNetworkStateContainer();

    switch (AcquireGameStatus())
    {
    case STATUS_LOADING:
    {
        LogMessage("LoadSavedGame(%s)\n", State.Module->Game.SaveFile);

        if (LoadSaveState(State.Module->Game.SaveFile))
        {
            State.App->InitModule = GAME_MODULE_STATE_INDEX;

            LogMessage("return TRUE\n");

            return TRUE;
        }

        LogMessage("LoadSavedGame(%s) failed.\n", State.Module->Game.SaveFile);

        return FALSE;
    }
    case STATUS_QUIT: { LogMessage("RK_EXITTOOS\n"); return FALSE; }
    case STATUS_RESTART:
    {
        if (RestartGame() && InitializeGameState())
        {
            State.App->InitModule = GAME_MODULE_STATE_INDEX;

            return TRUE;
        }
    }
    }

    {
        STRINGVALUE name, value;
        AcquireSettingsValue(&name, IDS_MENU);
        AcquireStringValue(&value, StringsState.Scratch);

        STRINGVALUE setting;
        STRINGVALUEPTR actual = AcquireSettingsValue(&setting, name, value);

        LogMessage("BFILE : main resources in \"%s\"\n", actual->Value);

        ReleaseStringValue(actual);

        InitializeBinArchives(IDS_MENU);
    }

    {
        STRINGVALUE name, value;
        AcquireSettingsValue(&name, IDS_COMMON);
        AcquireStringValue(&value, StringsState.Scratch);

        STRINGVALUE setting;
        STRINGVALUEPTR actual = AcquireSettingsValue(&setting, name, value);

        LogMessage("BFILE : common resources in \"%s\"\n", actual->Value);

        ReleaseStringValue(actual);

        InitializeBinArchives(IDS_COMMON);
    }

    {
        BINFILEFINDER finder;
        BinFileFinderActivate(&finder);

        STRINGVALUE name, value;
        AcquireSettingsValue(&name, IDS_ADDONS);

        AcquireStringValue(&value, StringsState.Scratch);
        AcquireStringValue(&value, "%s*.ssx", name.Value);

        if (BinFileFinderOpen(&finder, value.Value))
        {
            do
            {
                // TODO NOT IMPLEMENTED
            } while (BinFileFinderNext(&finder));
        }

        ReleaseStringValue(&name);
        ReleaseStringValue(&value);

        BaseFileFinderDispose((BASEFILEFINDERPTR)&finder);
    }

    {
        ASSETFILE asset;
        AssetFileActivate(&asset);

        if (!FUN_1002d0b0("menu.lng", &asset)) { LogMessage("Cannot load menu.lng\n"); }

        AssetFileDispose(&asset);
    }

    {
        ASSETFILE asset;
        AssetFileActivate(&asset);

        if (!FUN_1002d0b0("menures.lng", &asset)) { LogMessage("Cannot load menures.lng\n"); }

        AssetFileDispose(&asset);
    }

    InitializeBinAsset(&AssetsState.Assets.MainBK, "main_bk.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.MainBT, "main_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.SplBT, "sp1_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Ramka, "ramka.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Sp2BT, "sp2_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Sp3BT, "sp3_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Sp3RB, "sp3_rb.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.LoadBT, "load_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.MplBT, "mp1_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.ScrollBarBT, "scrollbar_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.ScrollBarSP, "scrollbar_sp.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Mp2BT, "mp2_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Mp3BT, "mp3_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Mp4BT, "mp4_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.OpBT, "op_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.RgBT, "rg_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.RsBT, "rs_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.StatPic, "stat_pic.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.WinJap, "win_jap.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.WinRus, "win_rus.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.MsgBoxBT, "msgbox_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.ColorsBT, "colors_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.BunCloseBT, "bunclose_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.SpeedBar, "speedbar.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.SpeedBT, "speed_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.NbRamkaBT, "nbramka_bk.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.NBrifBT, "nbrif_bt.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.NBrifBK, "nbrif_bk.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.MsglBT0, "msg1_bt0.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.MsglBT1, "msg1_bt1.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.MsglcBT0, "msg1c_bt0.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.MsglcBT1, "msg1c_bt1.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Msg2BT10, "msg2_bt10.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Msg2BT11, "msg2_bt11.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Msg2BT20, "msg2_bt20.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Msg2BT21, "msg2_bt21.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Rombik, "rombik.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.MsgBox, "msgbox.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.Zvezdy, "zvezdy.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.ZvM, "zv_m.pck", FALSE);
    InitializeBinAsset(&AssetsState.Assets.ZvGold, "zv_gold.pck", FALSE);

    InitializeFontAsset(&AssetsState.Fonts.Comic, "font_comic30", FONTTYPE_BASIC);
    InitializeFontAsset(&AssetsState.Fonts.Plastilin1, "font_plastilin1", FONTTYPE_COMPLEX);
    InitializeFontAsset(&AssetsState.Fonts.Plastilin3, "font_plastilin3", FONTTYPE_COMPLEX);
    InitializeFontAsset(&AssetsState.Fonts.Plastilin2, "font_plastilin2", FONTTYPE_COMPLEX);
    InitializeFontAsset(&AssetsState.Fonts.Plastilin1M, "font_plastilin1_m", FONTTYPE_COMPLEX);
    InitializeFontAsset(&AssetsState.Fonts.Plastilin3M, "font_plastilin3_m", FONTTYPE_COMPLEX);
    InitializeFontAsset(&AssetsState.Fonts.Plastilin2M, "font_plastilin2_m", FONTTYPE_COMPLEX);
    InitializeFontAsset(&AssetsState.Fonts.PlastilinS, "font_plastilin_s", FONTTYPE_COMPLEX);
    InitializeFontAsset(&AssetsState.Fonts.Main, "font_phermes", FONTTYPE_COMPLEX);

    LogMessage("load \"menu_texts\"\n");

    SelectWindowInputState((WINDOWINPUTSTATE)(WINDOWINPUTSTATE_KEYBOARD | WINDOWINPUTSTATE_MOUSE));

    WindowState.IsActive = TRUE;

    LogMessage("CADraw_Reset()\n");

    State.Renderer->Actions.Initialize();

    LogMessage("CADraw_Set800x600()\n");
    if (State.Renderer->Actions.InitializeWindow(GRAPHICS_RESOLUTION_800, GRAPHICS_RESOLUTION_600))
    {
        State.Renderer->Actions.DrawMainSurfaceColorRectangle(0, 0,
            GRAPHICS_RESOLUTION_640, GRAPHICS_RESOLUTION_480, BLACK_PIXEL);
        State.Renderer->Actions.WriteMainSurfaceRendererSurfaceRectangle(0, 0,
            GRAPHICS_RESOLUTION_640, GRAPHICS_RESOLUTION_480);
        State.Renderer->Actions.DrawStencilSurfaceWindowRectangle();

        AdjustBinAssetImage(&AssetsState.Assets.MainBK);
        AdjustBinAssetImage(&AssetsState.Assets.MainBT);
        AdjustBinAssetImage(&AssetsState.Assets.SplBT);
        AdjustBinAssetImage(&AssetsState.Assets.Ramka);
        AdjustBinAssetImage(&AssetsState.Assets.Sp2BT);
        AdjustBinAssetImage(&AssetsState.Assets.Sp3BT);
        AdjustBinAssetImage(&AssetsState.Assets.Sp3RB);
        AdjustBinAssetImage(&AssetsState.Assets.LoadBT);
        AdjustBinAssetImage(&AssetsState.Assets.MplBT);
        AdjustBinAssetImage(&AssetsState.Assets.ScrollBarBT);
        AdjustBinAssetImage(&AssetsState.Assets.ScrollBarSP);
        AdjustBinAssetImage(&AssetsState.Assets.Mp2BT);
        AdjustBinAssetImage(&AssetsState.Assets.Mp3BT);
        AdjustBinAssetImage(&AssetsState.Assets.Mp4BT);
        AdjustBinAssetImage(&AssetsState.Assets.OpBT);
        AdjustBinAssetImage(&AssetsState.Assets.RgBT);
        AdjustBinAssetImage(&AssetsState.Assets.RsBT);
        AdjustBinAssetImage(&AssetsState.Assets.StatPic);
        AdjustBinAssetImage(&AssetsState.Assets.WinJap);
        AdjustBinAssetImage(&AssetsState.Assets.WinRus);
        AdjustBinAssetImage(&AssetsState.Assets.MsgBoxBT);
        AdjustBinAssetImage(&AssetsState.Assets.ColorsBT);
        AdjustBinAssetImage(&AssetsState.Assets.BunCloseBT);
        AdjustBinAssetImage(&AssetsState.Assets.SpeedBar);
        AdjustBinAssetImage(&AssetsState.Assets.SpeedBT);
        AdjustBinAssetImage(&AssetsState.Assets.NbRamkaBT);
        AdjustBinAssetImage(&AssetsState.Assets.NBrifBT);
        AdjustBinAssetImage(&AssetsState.Assets.NBrifBK);
        AdjustBinAssetImage(&AssetsState.Assets.MsglBT0);
        AdjustBinAssetImage(&AssetsState.Assets.MsglBT1);
        AdjustBinAssetImage(&AssetsState.Assets.MsglcBT0);
        AdjustBinAssetImage(&AssetsState.Assets.MsglcBT1);
        AdjustBinAssetImage(&AssetsState.Assets.Msg2BT10);
        AdjustBinAssetImage(&AssetsState.Assets.Msg2BT11);
        AdjustBinAssetImage(&AssetsState.Assets.Msg2BT20);
        AdjustBinAssetImage(&AssetsState.Assets.Msg2BT21);
        AdjustBinAssetImage(&AssetsState.Assets.Rombik);
        AdjustBinAssetImage(&AssetsState.Assets.MsgBox);
        AdjustBinAssetImage(&AssetsState.Assets.Zvezdy);
        AdjustBinAssetImage(&AssetsState.Assets.ZvM);
        AdjustBinAssetImage(&AssetsState.Assets.ZvGold);

        InitializeFontAsset(&AssetsState.Fonts.Comic);
        InitializeFontAsset(&AssetsState.Fonts.Plastilin1);
        InitializeFontAsset(&AssetsState.Fonts.Plastilin3);
        InitializeFontAsset(&AssetsState.Fonts.Plastilin2);
        InitializeFontAsset(&AssetsState.Fonts.Plastilin1M);
        InitializeFontAsset(&AssetsState.Fonts.Plastilin3M);
        InitializeFontAsset(&AssetsState.Fonts.Plastilin2M);
        InitializeFontAsset(&AssetsState.Fonts.PlastilinS);
        InitializeFontAsset(&AssetsState.Fonts.Main);

        AssetsState.Fonts.Main.Height = AssetsState.Fonts.Main.Height + 2;
        AssetsState.Fonts.Main.Offset = 3;

        InitializeShortcuts(&Shortcuts);

        LogMessage("SoundInit()\n");

        InitializeSoundState(&SoundState.State, State.Module->Sound);
        InitializeCursorState(&CursorState.Cursor, "menu_cur");

        State.Main = ActivateMainControl(ALLOCATE(MAINCONTROL));

        {
            // TODO NOT IMPLEMENTED

            // IDS_MUTE_MENU_MUSIC
        }

        LogMessage("skeleton->init()\n");

        State.Main->Self->Unk01(State.Main);

        return TRUE;
    }

    MessageBoxA(State.Window->HWND,
        AcquireAssetMessage(&DAT_100b5da8, "MNTXT_UNABLE_640_480"), "DDraw Error", MB_ICONHAND | MB_OK);

    return FALSE;
}

// 0x10079ae0
VOID AcquireStartArguments(LPCSTR value)
{
    U32 count = 0;
    U32 length = 0;

    LPCSTR actual = value == NULL ? State.Window->Args : value;

    AcquireStartArguments(actual, NULL, NULL, &count, &length);

    State.Arguments.All = (LPSTR)malloc(length);
    State.Arguments.Args = (LPSTR*)malloc(count * sizeof(LPSTR));

    AcquireStartArguments(actual, State.Arguments.Args, State.Arguments.All, &count, &length);

    State.Arguments.Count = count;
}

// 0x10079b60
VOID AcquireStartArguments(LPCSTR value, LPSTR* args, LPSTR values, U32* count, U32* length)
{
    BOOL start = FALSE;
    BOOL end = FALSE;

    *length = 0;
    *count = 0;

    if (value == NULL) { return; }

    while (*value != NULL)
    {
        // Skip spaces and tabs.
        for (; *value == ' ' || *value == '\t'; value = value + 1) {}

        if (*value == NULL) { break; }

        if (args != NULL)
        {
            *args = values;
            args = args + 1;
        }

        *count = *count + 1;

        while (TRUE)
        {
            U32 slashes = 0;
            BOOL append = TRUE;
            CHAR current = *value;

            // Count contiguous slashes.
            while (current == '\\')
            {
                value = value + 1;
                slashes = slashes + 1;
                current = *value;
            }

            if (*value == '\"')
            {
                if ((slashes & 1) == 0)
                {
                    if (start && value[1] == '\"')
                    {
                        value = value + 1;
                    }
                    else { append = FALSE; }

                    start = !end;
                    end = start;
                }

                slashes = slashes >> 1;
            }

            for (; slashes != 0; slashes = slashes - 1)
            {
                if (values != NULL)
                {
                    *values = '\\';
                    values = values + 1;
                }

                *length = *length + 1;
            }

            current = *value;

            if (current == NULL || (!start && (current == ' ' || current == '\t'))) { break; }

            if (append)
            {
                if (values != NULL)
                {
                    *values = current;
                    values = values + 1;
                }

                *length = *length + 1;
            }

            value = value + 1;
        }

        if (values != NULL)
        {
            *values = NULL;
            values = values + 1;
        }

        *length = *length + 1;
    }
}
