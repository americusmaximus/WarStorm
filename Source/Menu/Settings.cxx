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

#include "Settings.hxx"
#include "State.hxx"

#include <..\Text\Resources.hxx>

#include <stdio.h>

#define MAX_SETTINGS_VALUE_LENGTH           64
#define MAX_SETTINGS_OUTPUT_VALUE_LENGTH    512

// 0x100173c0
VOID AcquireSettingsValue(STRINGVALUEPTR result, CONST U32 indx, ...)
{
    CHAR setting[MAX_SETTINGS_VALUE_LENGTH];
    LoadStringA(State.Module->Text, indx, setting, MAX_SETTINGS_VALUE_LENGTH);

    CHAR output[MAX_SETTINGS_OUTPUT_VALUE_LENGTH];

    va_list args;
    va_start(args, indx);
    vsprintf(output, setting, args);
    va_end(args);

    result->Value = (LPSTR)malloc(strlen(output) + 1);

    strcpy(result->Value, output);
}