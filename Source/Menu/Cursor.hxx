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

#include "BinAsset.hxx"

#include <Renderer.Basic.hxx>

typedef struct Cursor
{
    ANIMATIONSPRITEHEADERPTR    Animation;
    PIXEL* Palette;
    U32                         Width;
    U32                         Height;
    PIXEL* Pixels;
} CURSOR, * CURSORPTR;

typedef struct CursorStateModuleContainer
{
    CURSOR  Cursor; // TODO

    S32     X;      // 0x100b5f2c
    S32     Y;      // 0x100b5f30
    BOOL    IsLeft; // 0x100b5f34
    BOOL    IsRight;// 0x100b5f38
} CURSORSTATEMODULECONTAINER, * CURSORSTATEMODULECONTAINERPTR;

EXTERN CURSORSTATEMODULECONTAINER CursorState;

VOID CursorMessageHandler(U32 action);
VOID SelectCursorCoordinates(S32 ox, S32 oy, S32 nx, S32 ny);