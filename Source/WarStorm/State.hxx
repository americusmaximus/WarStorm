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

#pragma once

#include "App.hxx"
#include "Sound.hxx"
#include "Window.hxx"

typedef struct StateContainer
{
    BOOL                                IsIniActive;    // 0x00411260

    struct
    {
        HMODULE                         Module;         // 0x00411264
        RENDERERMODULESTATECONTAINERPTR State;          // 0x00411268
    } Renderer;

    MODULEPTR                           Module;         // 0x004113c0

    struct
    {
        HMODULE                         Handle;         // 0x004113ec
    } Text;

    APPPTR                              App;            // 0x004113f0

    SOUNDPTR                            Sound;          // 0x004113f8

    struct
    {
        ACTIONHANDLERPTR                Activate;       // 0x00411400
        ACTIONHANDLERPTR                Initialize;     // 0x00411404
        ACTIONHANDLERPTR                Action;         // 0x00411408
        ACTIONHANDLERPTR                Release;        // 0x0041140c
        ACTIONHANDLERPTR                Message;        // 0x00411410

        ACTIONHANDLERPTR                Active;         // 0x00411414
    } Actions;

    WINDOWPTR                           Window;         // 0x00411418

    struct
    {
        LPSTR                           All;            // 0x0041141c
        LPSTR*                          Args;           // 0x00411420
        U32                             Count;          // 0x00411424
    } Arguments;

    LOGGERPTR                           Logger;         // 0x00411428
} STATECONTAINER, * STATECONTAINERPTR;

EXTERN STATECONTAINER State;