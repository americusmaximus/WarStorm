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

#include "BaseFile.hxx"
#include "BinFile.hxx"

#include <stdlib.h>

// 0x100912a8
STATIC BINFILESELF BinFileSelf =
{
    BinFileRelease,
    BinFileIsActive,
    BinFileOpen,
    BinFileClose,
    BinFileRead,
    BinFileWrite,
    BinFileFlush,
    BinFileSetPointer,
    BinFileGetPointer,
    BinFileGetSize,
    (BINFILEGETSTRINGACTION)BaseFileGetString,
    (BINFILESETSTRINGACTION)BaseFileSetString,
    BinFileGetFolder
};

// 0x1009129c
STATIC BINFILEFOLDERSELF BinFileFolderSelf =
{
    BinFileFolderGetFile,
    BinFileFolderGetFileFinder,
    BinFileFolderCreateFolder
};

// 0x100912dc
STATIC BINFILEFINDERSELF BinFileFinderSelf =
{
    BinFileFinderRelease,
    BinFileFinderOpen,
    BinFileFinderClose,
    BinFileFinderNext,
    BinFileFinderGetName,
    BinFileFinderGetAttributes,
    BinFileFinderGetSize
};

// 0x100b5f24
BINFILEFOLDER BinFileFolderState;

// 0x10074a60
BINFILEPTR CLASSCALL BinFileActivate(BINFILEPTR self)
{
    self->Self = &BinFileSelf;

    self->Value = (BFH)INVALID_BINFILE_VALUE;

    return self;
}

// 0x10074a80
BINFILEPTR CLASSCALL BinFileRelease(BINFILEPTR self, CONST OBJECTRELEASETYPE mode)
{
    BinFileDispose(self);

    if (mode & OBJECTRELEASETYPE_ALLOCATED) { free(self); }

    return self;
}

// 0x10077510
BINFILEPTR CLASSCALL BinFileDispose(BINFILEPTR self)
{
    BinFileClose(self);

    return self;
}

// 0x10074af0
BOOL CLASSCALL BinFileIsActive(BINFILEPTR self)
{
    return self->Value != (BFH)INVALID_BINFILE_VALUE;
}

// 0x10074b00
BOOL CLASSCALL BinFileOpen(BINFILEPTR self, LPCSTR name, U32 type)
{
    self->Self->Close(self);

    DWORD access = GENERIC_READ;
    DWORD mode = FILE_SHARE_READ;
    DWORD disposition = OPEN_EXISTING;

    switch (type & FILEOPENTYPE_ACTION_MASK)
    {
    case FILEOPENTYPE_READ:
    {
        access = GENERIC_READ;
        mode = FILE_SHARE_READ;
        disposition = OPEN_EXISTING;

        break;
    }
    case FILEOPENTYPE_WRITE:
    {
        access = GENERIC_READ | GENERIC_WRITE;
        mode = FILE_SHARE_READ;
        disposition = OPEN_EXISTING;

        break;
    }
    case FILEOPENTYPE_CREATE:
    {
        access = GENERIC_WRITE;
        mode = FILE_SHARE_READ;
        disposition = CREATE_ALWAYS;

        break;
    }
    case FILEOPENTYPE_CREATE | FILEOPENTYPE_WRITE:
    {
        access = GENERIC_WRITE;
        mode = FILE_SHARE_READ;
        disposition = OPEN_EXISTING;

        break;
    }
    }

    self->Value = (BFH)CreateFileA(name, access, mode, NULL, disposition, FILE_ATTRIBUTE_NORMAL, NULL);

    if (self->Value == (BFH)INVALID_BINFILE_VALUE)
    {
        if ((type & FILEOPENTYPE_ACTION_MASK) == FILEOPENTYPE_CREATE && (type & FILEOPENTYPE_DIRECTORY))
        {
            LPSTR separator = strrchr((LPSTR)name, '\\');
            if (separator != NULL)
            {
                separator[0] = NULL;

                BINFILEFOLDERPTR folder = self->Self->GetFolder(self);
                folder->Self->CreateFolder(folder, name);

                separator[0] = '\\';

                self->Value = (BFH)CreateFileA(name, access, mode, NULL, disposition, FILE_ATTRIBUTE_NORMAL, NULL);
            }
        }
    }

    return self->Value != INVALID_BINFILE_VALUE;
}

// 0x10074c20
VOID CLASSCALL BinFileClose(BINFILEPTR self)
{
    if (self->Self->IsActive(self))
    {
        CloseHandle(BINFILEHANDLE(self->Value));
        self->Value = (BFH)INVALID_BINFILE_VALUE;
    }
}

// 0x10074c40
U32 CLASSCALL BinFileRead(BINFILEPTR self, LPVOID content, U32 size)
{
    if (!self->Self->IsActive(self)) { return 0; }

    DWORD read = 0;
    ReadFile(BINFILEHANDLE(self->Value), content, size, &read, NULL);

    return read;
}

// 0x10074c80
U32 CLASSCALL BinFileWrite(BINFILEPTR self, LPVOID content, U32 size)
{
    if (!self->Self->IsActive(self)) { return 0; }

    DWORD written = 0;
    WriteFile(BINFILEHANDLE(self->Value), content, size, &written, NULL);

    return written;
}

// 0x10074cc0
BOOL CLASSCALL BinFileFlush(BINFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return -1; }

    return FlushFileBuffers(BINFILEHANDLE(self->Value));
}

// 0x10074ce0
S32 CLASSCALL BinFileSetPointer(BINFILEPTR self, S32 distance, U32 method)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_OFFSET; }

    return SetFilePointer(BINFILEHANDLE(self->Value), distance, NULL, method);
}

// 0x10074d50
S32 CLASSCALL BinFileGetPointer(BINFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_OFFSET; }

    return SetFilePointer(BINFILEHANDLE(self->Value), 0, NULL, FILE_CURRENT);
}

// 0x10074d30
S32 CLASSCALL BinFileGetSize(BINFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_SIZE; }

    return GetFileSize(BINFILEHANDLE(self->Value), NULL);
}

// 0x10074a70
BINFILEFOLDERPTR CLASSCALL BinFileGetFolder(BINFILEPTR self)
{
    return &BinFileFolderState;
}

// 0x10074980
// 0x10074990
VOID ActivateBinFileFolder()
{
    BinFileFolderState.Self = &BinFileFolderSelf;
}

// 0x100749a0
BINFILEPTR CLASSCALL BinFileFolderGetFile(BINFILEFOLDERPTR self)
{
    BINFILEPTR file = (BINFILEPTR)malloc(sizeof(BINFILE));

    return file != NULL ? BinFileActivate(file) : NULL;
}

// 0x10074a00
BINFILEFINDERPTR CLASSCALL BinFileFolderGetFileFinder(BINFILEFOLDERPTR self)
{
    BINFILEFINDERPTR finder = (BINFILEFINDERPTR)malloc(sizeof(BINFILEFINDER));

    return finder != NULL ? BinFileFinderActivate(finder) : finder;
}

// 0x10074d80
BOOL CLASSCALL BinFileFolderCreateFolder(BINFILEFOLDERPTR self, LPCSTR name)
{
    return CreateDirectoryA(name, NULL);
}

// 0x10074a00
BINFILEFINDERPTR CLASSCALL BinFileFinderActivate(BINFILEFINDERPTR self)
{
    self->Self = &BinFileFinderSelf;

    self->Handle = INVALID_HANDLE_VALUE;
    self->IsActive = FALSE;

    return self;
}

// 0x10074db0
BINFILEFINDERPTR CLASSCALL BinFileFinderRelease(BINFILEFINDERPTR self, CONST OBJECTRELEASETYPE mode)
{
    BinFileFinderDispose(self);

    if (mode & OBJECTRELEASETYPE_ALLOCATED) { free(self); }

    return self;
}

// 0x100094f0
BINFILEFINDERPTR CLASSCALL BinFileFinderDispose(BINFILEFINDERPTR self)
{
    BaseFileFinderDispose((BASEFILEFINDERPTR)self);

    return self;
}

// 0x10074e30
BOOL CLASSCALL BinFileFinderOpen(BINFILEFINDERPTR self, LPCSTR path)
{
    self->Self->Close(self);

    self->Handle = FindFirstFileA(path, &self->Data);

    return self->Handle != INVALID_HANDLE_VALUE;
}

// 0x10074e60
VOID CLASSCALL BinFileFinderClose(BINFILEFINDERPTR self)
{
    if (self->Handle != INVALID_HANDLE_VALUE)
    {
        FindClose(self->Handle);

        self->IsActive = FALSE;
        self->Handle = INVALID_HANDLE_VALUE;
    }
}

// 0x10074e80
BOOL CLASSCALL BinFileFinderNext(BINFILEFINDERPTR self)
{
    if (!self->IsActive)
    {
        self->IsActive = FALSE;

        return TRUE;
    }

    return FindNextFileA(self->Handle, &self->Data);
}

// 0x10074eb0
LPCSTR CLASSCALL BinFileFinderGetName(BINFILEFINDERPTR self)
{
    return self->Data.cFileName;
}

// 0x10074ec0
DWORD CLASSCALL BinFileFinderGetAttributes(BINFILEFINDERPTR self)
{
    return self->Data.dwFileAttributes;
}

// 0x10074ed0
DWORD CLASSCALL BinFileFinderGetSize(BINFILEFINDERPTR self)
{
    return self->Data.nFileSizeLow;
}
