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

#pragma once

#include "Basic.hxx"

#include <ControlCommand.hxx>

#define MAX_CONTROL_COMMAND_ITEMS_COUNT 256

typedef struct ControlCommandStateModuleContainer
{
    CONTROLCOMMAND  Items[MAX_CONTROL_COMMAND_ITEMS_COUNT]; // 0x100b5f3c
    S32             WriteIndex;                             // 0x100b6f3c
    S32             ReadIndex;                              // TODO
} CONTROLCOMMANDSTATEMODULECONTAINER, * CONTROLCOMMANDSTATEMODULECONTAINERPTR;

EXTERN CONTROLCOMMANDSTATEMODULECONTAINER CommandControlState;

BOOL DequeueControlCommand(U32 command);
BOOL DequeueControlCommand(CONTROLCOMMANDPTR command, BOOL remove);
CONTROLCOMMANDPTR DequeueControlCommand(BOOL remove);
VOID EnqueueControlCommand(U32 command, U32 action, U32 param1, U32 param2);