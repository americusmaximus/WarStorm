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
#include "BinAsset.hxx"
#include "Logger.hxx"

#include <stdlib.h>

// 0x100035e0
BINASSETPTR CLASSCALL ActivateBinAsset(BINASSETPTR self)
{
    self->Content = NULL;
    self->IsCollection = FALSE;
    self->Name = NULL;
    self->IsImage = FALSE;

    return self;
}

// 0x10003610
BOOL CLASSCALL InitializeBinAsset(BINASSETPTR self, LPCSTR name, CONST BOOL load)
{
    if (load) { self->Name = name; }

    if (name != NULL && !load)
    {
        self->Name = name;

        return TRUE;
    }

    LogMessage("Loading %s\n", self->Name);

    AcquireAssetContent(self->Name, (LPVOID*)&self->Content, 0);

    if (self->IsImage)
    {
        LogMessage("Adjusting %s\n", self->Name);

        AdjustBinAssetImage(self);
    }

    self->Name = NULL;

    return TRUE;
}

// 0x100035f0
VOID CLASSCALL DisposeBinAsset(BINASSETPTR self)
{
    if (self->Content != NULL)
    {
        free(self->Content);

        self->Content = NULL;
    }
}
