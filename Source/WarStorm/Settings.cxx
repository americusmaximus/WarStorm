/*
Copyright (c) 2024 Americus Maximus

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

#include "Renderer.hxx"
#include "Settings.hxx"
#include "State.hxx"
#include "Strings.hxx"

#include <..\Text\Resources.hxx>

#include <stdio.h>

#define MAX_SETTINGS_VALUE_LENGTH           64
#define MAX_SETTINGS_DATA_VALUE_LENGTH      256
#define MAX_SETTINGS_OUTPUT_VALUE_LENGTH    512

// 0x00401070
STRINGVALUEPTR CLASSCALL AcquireSettingsValue(STRINGVALUEPTR self, CONST U32 indx, ...)
{
    CHAR setting[MAX_SETTINGS_VALUE_LENGTH];
    LoadStringA(State.Module->Text, indx, setting, MAX_SETTINGS_VALUE_LENGTH);

    CHAR output[MAX_SETTINGS_OUTPUT_VALUE_LENGTH];

    va_list args;
    va_start(args, indx);
    vsprintf(output, setting, args);
    va_end(args);

    self->Value = (LPSTR)malloc(strlen(output) + 1);

    strcpy(self->Value, output);

    return self;
}

// 0x00401190
STRINGVALUEPTR AcquireSettingsValue(STRINGVALUEPTR result, STRINGVALUE name, STRINGVALUE value)
{
    AcquireStringValue(result, &value);

    STRINGVALUE nm, val;
    AcquireStringValue(&nm, &name);
    AcquireStringValue(&val, &value);

    AcquireSettingsValue(result, IDS_GAME, nm, val);

    ReleaseStringValue(&name);
    ReleaseStringValue(&value);

    return result;
}

// 0x00401250
STRINGVALUEPTR AcquireSettingsValue(STRINGVALUEPTR result, CONST U32 indx, STRINGVALUE name, STRINGVALUE value)
{
    CHAR setting[MAX_SETTINGS_VALUE_LENGTH];
    LoadStringA(State.Module->Text, indx, setting, MAX_SETTINGS_VALUE_LENGTH);

    if (State.IsIniActive)
    {
        CHAR output[MAX_SETTINGS_DATA_VALUE_LENGTH];
        GetPrivateProfileStringA(setting, name.Value, value.Value, output, MAX_SETTINGS_DATA_VALUE_LENGTH, State.App->Ini);
        AcquireStringValue(result, output);
    }
    else
    {
        LoadStringA(State.Module->Text, IDS_REGISTRY_KEY, setting, MAX_SETTINGS_VALUE_LENGTH);

        HKEY key = NULL;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, setting, REG_OPTION_NON_VOLATILE, KEY_READ, &key) == ERROR_SUCCESS)
        {
            DWORD type = REG_NONE;
            CHAR output[MAX_SETTINGS_DATA_VALUE_LENGTH];
            DWORD length = MAX_SETTINGS_DATA_VALUE_LENGTH;

            if (RegQueryValueExA(key, name.Value, NULL, &type, (BYTE*)output, &length) == ERROR_SUCCESS)
            {
                RegCloseKey(key);

                AcquireStringValue(result, output);

                ReleaseStringValue(&name);
                ReleaseStringValue(&value);

                return result;
            }
        }

        RegCloseKey(key);

        AcquireStringValue(result, &value);
    }

    ReleaseStringValue(&name);
    ReleaseStringValue(&value);

    return result;
}

// 0x004013f0
S32 AcquireSettingsValue(STRINGVALUE name, S32 value)
{
    CHAR input[MAX_SETTINGS_VALUE_LENGTH];
    LoadStringA(State.Module->Text, IDS_GAME, input, MAX_SETTINGS_VALUE_LENGTH);

    if (State.IsIniActive)
    {
        CONST S32 result = GetPrivateProfileIntA(input, name.Value, value, State.App->Ini);

        ReleaseStringValue(&name);

        return result;
    }

    STRINGVALUE val;
    AcquireStringValue(&val, INVALID_SETTINGS_STRING_VALUE);

    STRINGVALUE nm;
    AcquireStringValue(&nm, &name);

    STRINGVALUE setting;
    STRINGVALUEPTR actual = AcquireSettingsValue(&setting, nm, val);

    CHAR output[MAX_SETTINGS_OUTPUT_VALUE_LENGTH];
    strcpy(output, actual->Value);

    ReleaseStringValue(&setting);

    if (strncmp(output, INVALID_SETTINGS_STRING_VALUE, MAX_INVALID_SETTINGS_STRING_VALUE_LENGTH) == 0)
    {
        ReleaseStringValue(&name);

        return value;
    }

    ReleaseStringValue(&name);

    return atoi(output);
}

// 0x00401620
// 0x00401810
BOOL AcquireRendererSettingsValue(VOID)
{
    STRINGVALUE setting;
    AcquireSettingsValue(&setting, IDS_VIDEO_MODE);

    CONST S32 mode = AcquireSettingsValue(setting, INVALID_RENDERER_VIDEO_MODE_VALUE);

    if (mode == INVALID_RENDERER_VIDEO_MODE_VALUE) { return FALSE; }

    if (mode != RendererVideoMode || (IsRendererVideoModeActive && mode == RENDERER_VIDEO_MODE_800x600))
    {
        if (!IsRendererVideoModeActive) { RendererVideoMode = RENDERER_VIDEO_MODE_1024x768; }
        else if (mode != RENDERER_VIDEO_MODE_800x600) { RendererVideoMode = mode; }

        if (State.Renderer.State != NULL) { State.Renderer.State->Actions.ReleaseDirectX(); }

        ReleaseRenderStateModule();

        State.Renderer.State = NULL;
        State.Module->Renderer = NULL;

        // Draw Mode
        {
            STRINGVALUE value;
            AcquireStringValue(&value, "undefined");

            STRINGVALUE configuration;
            AcquireSettingsValue(&configuration, IDS_DRAW_MODE_INDEX, RendererVideoMode);

            STRINGVALUE setting;
            STRINGVALUEPTR actual = AcquireSettingsValue(&setting, configuration, value);

            CHAR output[MAX_SETTINGS_OUTPUT_VALUE_LENGTH];
            strcpy(output, actual->Value);

            ReleaseStringValue(&setting);

            if (!InitializeRendererStateModule(output)) { return FALSE; }
        }

        // Full Screen
        {
            STRINGVALUE configuration;
            AcquireSettingsValue(&configuration, IDS_FULL_SCREEN);

            CONST BOOL fullscreen = (BOOL)AcquireSettingsValue(configuration, TRUE);

            if (!State.Renderer.State->Actions.InitializeDirectX(State.Window->HWND, fullscreen)) { return FALSE; }
        }

        State.Module->Renderer = State.Renderer.State;
        IsRendererVideoModeActive = !IsRendererVideoModeActive;
    }

    return TRUE;
}