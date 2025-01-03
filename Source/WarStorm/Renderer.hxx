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

#include "Basic.hxx"

#define INVALID_RENDERER_VIDEO_MODE_VALUE (-1)
#define DEFAULT_RENDERER_VIDEO_MODE_VALUE (-100)

#define RENDERER_VIDEO_MODE_640x480         0
#define RENDERER_VIDEO_MODE_800x600         1
#define RENDERER_VIDEO_MODE_1024x768        2
#define RENDERER_VIDEO_MODE_COUNT           3

EXTERN S32  RendererVideoMode;
EXTERN BOOL IsRendererVideoModeActive;

BOOL InitializeRendererStateModule(LPCSTR file);
VOID ReleaseRenderStateModule(VOID);
