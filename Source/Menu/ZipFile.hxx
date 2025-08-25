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

#include <ZipFile.hxx>

ZIPFILEPTR CLASSCALL ZipFileActivate(ZIPFILEPTR self);
ZIPFILEPTR CLASSCALL ZipFileDispose(ZIPFILEPTR self);
ZIPFILEPTR CLASSCALL ZipFileRelease(ZIPFILEPTR self, CONST OBJECTRELEASETYPE mode);

BOOL CLASSCALL ZipFileIsActive(ZIPFILEPTR self);
BOOL CLASSCALL ZipFileOpen(ZIPFILEPTR self, LPSTR name, U32 type);
VOID CLASSCALL ZipFileClose(ZIPFILEPTR self);
U32 CLASSCALL ZipFileRead(ZIPFILEPTR self, LPVOID content, U32 size);
U32 CLASSCALL ZipFileWrite(ZIPFILEPTR self, LPVOID content, U32 size);
BOOL CLASSCALL ZipFileFlush(ZIPFILEPTR self);
S32 CLASSCALL ZipFileSetPointer(ZIPFILEPTR self, S32 distance, U32 method);
S32 CLASSCALL ZipFileGetPointer(ZIPFILEPTR self);
S32 CLASSCALL ZipFileGetSize(ZIPFILEPTR self);
ZIPFILEFOLDERPTR CLASSCALL ZipFileGetFolder(ZIPFILEPTR self);

EXTERN ZIPFILEFOLDER ZipFileFolderState;

VOID ActivateZipFileFolder();

ZIPFILEPTR CLASSCALL ZipFileFolderGetFile(ZIPFILEFOLDERPTR self);
ZIPFILEFINDERPTR CLASSCALL ZipFileFolderGetFileFinder(ZIPFILEFOLDERPTR self);
BOOL CLASSCALL ZipFileFolderCreateFolder(ZIPFILEFOLDERPTR self, LPCSTR name);

ZIPWRITERPTR CLASSCALL ZipWriterActivate(ZIPWRITERPTR self);
ZIPWRITERPTR CLASSCALL ZipWriterDispose(ZIPWRITERPTR self);
ZIPWRITERPTR CLASSCALL ZipWriterRelease(ZIPWRITERPTR self, CONST OBJECTRELEASETYPE mode);

BOOL CLASSCALL ZipWriterOpen(ZIPWRITERPTR self, LPSTR name, U32 type);
VOID CLASSCALL ZipWriterClose(ZIPWRITERPTR self);
U32 CLASSCALL ZipWriterRead(ZIPWRITERPTR self, LPVOID content, U32 size);
U32 CLASSCALL ZipWriterWrite(ZIPWRITERPTR self, LPVOID content, U32 size);
S32 CLASSCALL ZipWriterFlush(ZIPWRITERPTR self);
S32 CLASSCALL ZipWriterSetPointer(ZIPWRITERPTR self, S32 distance, U32 method);
S32 CLASSCALL ZipWriterGetPointer(ZIPWRITERPTR self);
S32 CLASSCALL ZipWriterGetSize(ZIPWRITERPTR self);
ZIPWRITERFOLDERPTR CLASSCALL ZipFileWriterGetFolder(ZIPWRITERPTR self);

S32 CLASSCALL ZipWriterSetPosition(ZIPWRITERPTR self, S32 pointer);
VOID CLASSCALL ZipWriterClearBuffer(ZIPWRITERPTR self, U32 pointer);
VOID CLASSCALL ZipWriterResizeBuffer(ZIPWRITERPTR self, U32 pointer);
VOID CLASSCALL ZipWriterCopyBuffer(ZIPWRITERPTR self, LPVOID content, U32 size);

EXTERN ZIPWRITERFOLDER ZipWriterFolderState;

VOID ActivateZipWriterFolder();

ZIPWRITERPTR CLASSCALL ZipWriterFolderGetFile(ZIPWRITERFOLDERPTR self);
ZIPWRITERFINDERPTR CLASSCALL ZipWriterFolderGetFileFinder(ZIPWRITERFOLDERPTR self);
