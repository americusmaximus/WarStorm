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

#include "Window.hxx"

#include <App.hxx>

typedef struct StateModuleContainer
{
    APPPTR                          App;                            // 0x100b46c0

    struct
    {
        LPSTR                       All;                            // TODO
        LPSTR*                      Args;                           // TODO
        U32                         Count;                          // TODO
    } Arguments;

    BOOL IsIniActive;                                               // TODO

    MODULEPTR                       Module;                         // TODO
    RENDERERPTR                     Renderer;                       // TODO
    WINDOWPTR                       Window;                         // 0x100b71c8
    LOGGERPTR                       Logger;                         // 0x100b71cc

    CHAR                            Name[MAX_PLAYER_NAME_LENGTH];   // TODO
} STATEMODULECONTAINER, * STATEMODULECONTAINERPTR;

EXTERN STATEMODULECONTAINER State;