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

#pragma once

#include <BinFile.hxx>

BINFILEPTR CLASSCALL BinFileActivate(BINFILEPTR self);
BINFILEPTR CLASSCALL BinFileDispose(BINFILEPTR self);
BINFILEPTR CLASSCALL BinFileRelease(BINFILEPTR self, CONST OBJECTRELEASETYPE mode);

BOOL CLASSCALL BinFileIsActive(BINFILEPTR self);
BOOL CLASSCALL BinFileOpen(BINFILEPTR self, LPCSTR name, U32 type);
VOID CLASSCALL BinFileClose(BINFILEPTR self);
U32 CLASSCALL BinFileRead(BINFILEPTR self, LPVOID content, U32 size);
U32 CLASSCALL BinFileWrite(BINFILEPTR self, LPVOID content, U32 size);
BOOL CLASSCALL BinFileFlush(BINFILEPTR self);
S32 CLASSCALL BinFileSetPointer(BINFILEPTR self, S32 distance, U32 method);
S32 CLASSCALL BinFileGetPointer(BINFILEPTR self);
S32 CLASSCALL BinFileGetSize(BINFILEPTR self);
BINFILEFOLDERPTR CLASSCALL BinFileGetFolder(BINFILEPTR self);

EXTERN BINFILEFOLDER BinFileFolderState;

VOID ActivateBinFileFolder();

BINFILEPTR CLASSCALL BinFileFolderGetFile(BINFILEFOLDERPTR self);
BINFILEFINDERPTR CLASSCALL BinFileFolderGetFileFinder(BINFILEFOLDERPTR self);
BOOL CLASSCALL BinFileFolderCreateFolder(BINFILEFOLDERPTR self, LPCSTR name);

BINFILEFINDERPTR CLASSCALL BinFileFinderActivate(BINFILEFINDERPTR self);
BINFILEFINDERPTR CLASSCALL BinFileFinderRelease(BINFILEFINDERPTR self, CONST OBJECTRELEASETYPE mode);
BINFILEFINDERPTR CLASSCALL BinFileFinderDispose(BINFILEFINDERPTR self);

BOOL CLASSCALL BinFileFinderOpen(BINFILEFINDERPTR self, LPCSTR path);
VOID CLASSCALL BinFileFinderClose(BINFILEFINDERPTR self);
BOOL CLASSCALL BinFileFinderNext(BINFILEFINDERPTR self);
LPCSTR CLASSCALL BinFileFinderGetName(BINFILEFINDERPTR self);
DWORD CLASSCALL BinFileFinderGetAttributes(BINFILEFINDERPTR self);
DWORD CLASSCALL BinFileFinderGetSize(BINFILEFINDERPTR self);
