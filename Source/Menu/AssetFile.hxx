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

#include "Objects.hxx"

#include <AssetFile.hxx>

ASSETFILEPTR CLASSCALL ActivateAssetFile(ASSETFILEPTR self);
ASSETFILEPTR CLASSCALL DisposeAssetFile(ASSETFILEPTR self);
ASSETFILEPTR CLASSCALL ReleaseAssetFile(ASSETFILEPTR self, CONST OBJECTRELEASETYPE mode);
BOOL CLASSCALL IsAssetFileActive(ASSETFILEPTR self);
BOOL CLASSCALL OpenAssetFile(ASSETFILEPTR self, LPCSTR name);
S32 CLASSCALL AcquireAssetFileOffset(ASSETFILEPTR self);
S32 CLASSCALL AcquireAssetFileSize(ASSETFILEPTR self);
S32 CLASSCALL AcquireAssetFileString(ASSETFILEPTR self, LPSTR content, CONST U32 length);
S32 CLASSCALL SelectAssetFileOffset(ASSETFILEPTR self, LONG distance, DWORD method);
U32 CLASSCALL AssetFileUnk05(ASSETFILEPTR self); // TODO
U32 CLASSCALL AssetFileUnk06(ASSETFILEPTR self); // TODO
VOID CLASSCALL CloseAssetFile(ASSETFILEPTR self);

BFH AcquireAssetFileIndex(LPCSTR name);
BOOL IsAssetFileActive(CONST BFH indx);
BOOL OpenAssetFile(CONST BFH indx);;