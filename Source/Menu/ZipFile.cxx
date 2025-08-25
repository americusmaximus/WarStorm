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
#include "Strings.hxx"
#include "ZipFile.hxx"

#include <stdlib.h>

#define ALIGN_BUFFER_SIZE(X)    (X & 0xFFFFFFFE)

#define MIN_BUFFER_SIZE             0x2000
#define MIN_BUFFER_SIZE_THRESHOLD   0x4000

// 0x100913bc
STATIC ZIPFILESELF ZipFileSelf =
{
    ZipFileRelease,
    ZipFileIsActive,
    ZipFileOpen,
    ZipFileClose,
    ZipFileRead,
    ZipFileWrite,
    ZipFileFlush,
    ZipFileSetPointer,
    ZipFileGetPointer,
    ZipFileGetSize,
    (ZIPFILEGETSTRINGACTION)BaseFileGetString,
    (ZIPFILESETSTRINGACTION)BaseFileSetString,
    ZipFileGetFolder
};

// 0x100913b0
STATIC ZIPFILEFOLDERSELF ZipFileFolderSelf =
{
    ZipFileFolderGetFile,
    ZipFileFolderGetFileFinder,
    ZipFileFolderCreateFolder
};

// 0x100e93e4
ZIPFILEFOLDER ZipFileFolderState;

// 0x100913fc
STATIC ZIPWRITERSELF ZipWriterSelf =
{
    ZipWriterRelease,
    (ZIPWRITERISACTIOVEACTION)ZipFileIsActive,
    ZipWriterOpen,
    ZipWriterClose,
    ZipWriterRead,
    ZipWriterWrite,
    ZipWriterFlush,
    ZipWriterSetPointer,
    ZipWriterGetPointer,
    ZipWriterGetSize,
    (ZIPWRITERGETSTRINGACTION)BaseFileGetString,
    (ZIPWRITERSETSTRINGACTION)BaseFileSetString,
    ZipFileWriterGetFolder
};

// 0x100e93e0
ZIPWRITERFOLDER ZipWriterFolderState;

// 0x100913f0
STATIC ZIPWRITERFOLDERSELF ZipWriterFolderSelf =
{
    ZipWriterFolderGetFile,
    ZipWriterFolderGetFileFinder,
    (ZIPWRITERFOLDERCREATEFOLDERACTION)ZipFileFolderCreateFolder
};

// 0x10078f50
ZIPFILEPTR CLASSCALL ZipFileActivate(ZIPFILEPTR self)
{
    self->Self = &ZipFileSelf;
    self->Value = NULL;

    return self;
}

// 0x10078f70
ZIPFILEPTR CLASSCALL ZipFileRelease(ZIPFILEPTR self, CONST OBJECTRELEASETYPE mode)
{
    ZipFileDispose(self);

    if (mode & OBJECTRELEASETYPE_ALLOCATED) { free(self); }

    return self;
}

// 0x10078f90
ZIPFILEPTR CLASSCALL ZipFileDispose(ZIPFILEPTR self)
{
    ZipFileClose(self);

    return self;
}

// 0x100751c0
BOOL CLASSCALL ZipFileIsActive(ZIPFILEPTR self)
{
    return self->Value != NULL;
}

// 0x10078fe0
BOOL CLASSCALL ZipFileOpen(ZIPFILEPTR self, LPSTR name, U32 type)
{
    self->Self->Close(self);

    CHAR path[MAX_FILE_NAME_LENGTH];
    AcquireAnsiString(path, MAX_FILE_NAME_LENGTH, name, -1);

    LPCSTR mode = (type & FILEOPENTYPE_ACTION_MASK) == FILEOPENTYPE_READ ? "rb"
        : ((type & FILEOPENTYPE_ACTION_MASK) == FILEOPENTYPE_CREATE ? "wb" : "" /* TODO Correct Value ?*/);

    self->Value = gzopen(path, mode);

    if (self->Value == NULL
        && (type & FILEOPENTYPE_ACTION_MASK) == FILEOPENTYPE_CREATE && (type & FILEOPENTYPE_DIRECTORY))
    {
        LPSTR separator = strrchr(path, '\\');
        if (separator != NULL)
        {
            separator[0] = NULL;

            ZIPFILEFOLDERPTR folder = self->Self->GetFolder(self);
            folder->Self->CreateFolder(folder, path);

            separator[0] = '\\';

            self->Value = gzopen(path, mode);
        }
    }

    return self->Value != NULL;
}

// 0x100790b0
VOID CLASSCALL ZipFileClose(ZIPFILEPTR self)
{
    if (self->Self->IsActive(self))
    {
        gzclose(self->Value);
        self->Value = NULL;
    }
}

// 0x100790e0
U32 CLASSCALL ZipFileRead(ZIPFILEPTR self, LPVOID content, U32 size)
{
    if (!self->Self->IsActive(self)) { return 0; }

    return gzread(self->Value, content, size);
}

// 0x10079110
U32 CLASSCALL ZipFileWrite(ZIPFILEPTR self, LPVOID content, U32 size)
{
    if (!self->Self->IsActive(self)) { return 0; }

return gzwrite(self->Value, content, size);
}

// 0x10079140
BOOL CLASSCALL ZipFileFlush(ZIPFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return -1; }

    return gzflush(self->Value, Z_SYNC_FLUSH) == Z_OK;
}

// 0x10079170
S32 CLASSCALL ZipFileSetPointer(ZIPFILEPTR self, S32 distance, U32 method)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_OFFSET; }

    return (S32)gzseek(self->Value, distance, method);
}

// 0x100791c0
S32 CLASSCALL ZipFileGetPointer(ZIPFILEPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_OFFSET; }

    return (S32)gztell(self->Value);
}

// 0x100791b0
S32 CLASSCALL ZipFileGetSize(ZIPFILEPTR self)
{
    return self->Self->IsActive(self) ? 0 : INVALID_FILE_SIZE;
}

// 0x10078f60
ZIPFILEFOLDERPTR CLASSCALL ZipFileGetFolder(ZIPFILEPTR self)
{
    return &ZipFileFolderState;
}

// 0x10078ed0
// 0x10078ee0
VOID ActivateZipFileFolder()
{
    ZipFileFolderState.Self = &ZipFileFolderSelf;
}

// 0x10078ef0
ZIPFILEPTR CLASSCALL ZipFileFolderGetFile(ZIPFILEFOLDERPTR self)
{
    ZIPFILEPTR file = (ZIPFILEPTR)malloc(sizeof(ZIPFILE));

    return file != NULL ? ZipFileActivate(file) : NULL;
}

// 0x10077460
ZIPFILEFINDERPTR CLASSCALL ZipFileFolderGetFileFinder(ZIPFILEFOLDERPTR self)
{
    return NULL;
}

// 0x10079260
BOOL CLASSCALL ZipFileFolderCreateFolder(ZIPFILEFOLDERPTR self, LPCSTR name)
{
    CHAR path[MAX_FILE_NAME_LENGTH];
    AcquireAnsiString(path, MAX_FILE_NAME_LENGTH, name, -1);

    return CreateDirectoryA(path, NULL);
}

// 0x100792a0
ZIPWRITERPTR CLASSCALL ZipWriterActivate(ZIPWRITERPTR self)
{
    self->Self = &ZipWriterSelf;

    self->Value = NULL;
    self->Buffer = NULL;
    self->Current = 0;
    self->Size = 0;
    self->Length = 0;

    return self;
}

// 0x100792d0
ZIPWRITERPTR CLASSCALL ZipWriterRelease(ZIPWRITERPTR self, CONST OBJECTRELEASETYPE mode)
{
    ZipWriterDispose(self);

    if (mode & OBJECTRELEASETYPE_ALLOCATED) { free(self); }

    return self;
}

// 0x100792f0
ZIPWRITERPTR CLASSCALL ZipWriterDispose(ZIPWRITERPTR self)
{
    ZipWriterClose(self);

    free(self->Buffer);

    return self;
}

// 0x10079350
BOOL CLASSCALL ZipWriterOpen(ZIPWRITERPTR self, LPSTR name, U32 type)
{
    CHAR path[MAX_FILE_NAME_LENGTH];
    AcquireAnsiString(path, MAX_FILE_NAME_LENGTH, name, -1);

    self->Value = gzopen(path, "wb");

    if (self->Value == NULL
        && (type & FILEOPENTYPE_ACTION_MASK) == FILEOPENTYPE_CREATE && (type & FILEOPENTYPE_DIRECTORY))
    {
        LPSTR separator = strrchr(path, '\\');
        if (separator != NULL)
        {
            separator[0] = NULL;

            ZIPWRITERFOLDERPTR folder = self->Self->GetFolder(self);
            folder->Self->CreateFolder(folder, path);

            separator[0] = '\\';

            self->Value = gzopen(path, "wb");
        }
    }

    return self->Value != NULL;
}

// 0x10079410
VOID CLASSCALL ZipWriterClose(ZIPWRITERPTR self)
{
    if (self->Buffer != NULL)
    {
        CONST U32 length =
            self->Size <= self->Current ? self->Size : self->Current;

        gzwrite(self->Value, self->Buffer, length);

        self->Current = 0;
        self->Size = 0;
    }

    gzclose(self->Value);

    self->Value = NULL;
}

// 0x10077b20
U32 CLASSCALL ZipWriterRead(ZIPWRITERPTR self, LPVOID content, U32 size)
{
    return 0;
}

// 0x10079460
U32 CLASSCALL ZipWriterWrite(ZIPWRITERPTR self, LPVOID content, U32 size)
{
    if (!self->Self->IsActive(self)) { return 0; }

    ZipWriterCopyBuffer(self, content, size);

    return size;
}

// 0x100794e0
S32 CLASSCALL ZipWriterGetSize(ZIPWRITERPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_SIZE; }

    return self->Size;
}

// 0x100791b0
S32 CLASSCALL ZipWriterFlush(ZIPWRITERPTR self)
{
    return self->Self->IsActive(self) ? 0 : -1;
}

// 0x10079490
S32 CLASSCALL ZipWriterSetPointer(ZIPWRITERPTR self, S32 distance, U32 method)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_OFFSET; }

    switch (method)
    {
    case FILE_BEGIN: { ZipWriterSetPosition(self, distance); break; }
    case FILE_CURRENT: { ZipWriterSetPosition(self, distance + self->Current); break; }
    case FILE_END: { ZipWriterSetPosition(self, distance + self->Size); break; }
    }

    return self->Current;
}

// 0x10079500
S32 CLASSCALL ZipWriterGetPointer(ZIPWRITERPTR self)
{
    if (!self->Self->IsActive(self)) { return INVALID_FILE_OFFSET; }

    return self->Current;
}

// 0x100792c0
ZIPWRITERFOLDERPTR CLASSCALL ZipFileWriterGetFolder(ZIPWRITERPTR self)
{
    return &ZipWriterFolderState;
}

// 0x10079520
S32 CLASSCALL ZipWriterSetPosition(ZIPWRITERPTR self, S32 pointer)
{
    if (pointer < 0) { pointer = 0; }

    if (self->Size < pointer)
    {
        self->Current = self->Size;
        ZipWriterClearBuffer(self, pointer - self->Size);
    }

    self->Current = pointer;

    return self->Current;
}

// 0x10079550
VOID CLASSCALL ZipWriterResizeBuffer(ZIPWRITERPTR self, U32 size)
{
    if (self->Length < self->Current + size)
    {
        CONST U32 extra =
            (ALIGN_BUFFER_SIZE(size) < MIN_BUFFER_SIZE_THRESHOLD) ? MIN_BUFFER_SIZE : (size / 2);

        self->Length = self->Current + extra + size;
        self->Buffer = realloc(self->Buffer, self->Length);
    }
}

// 0x100795a0
VOID CLASSCALL ZipWriterClearBuffer(ZIPWRITERPTR self, U32 size)
{
    ZipWriterResizeBuffer(self, size);

    ZeroMemory((LPVOID)((ADDR)self->Buffer + self->Current), size);

    self->Current = self->Current + size;

    if (self->Size < self->Current) { self->Size = self->Current; }
}

// 0x100795f0
VOID CLASSCALL ZipWriterCopyBuffer(ZIPWRITERPTR self, LPVOID content, U32 size)
{
    ZipWriterResizeBuffer(self, size);

    CopyMemory((LPVOID)((ADDR)self->Buffer + self->Current), content, size);

    self->Current = self->Current + size;

    if (self->Size < self->Current) { self->Size = self->Current; }
}

// 0x100791f0
VOID ActivateZipWriterFolder()
{
    ZipWriterFolderState.Self = &ZipWriterFolderSelf;
}

// 0x10079200
ZIPWRITERPTR CLASSCALL ZipWriterFolderGetFile(ZIPWRITERFOLDERPTR self)
{
    ZIPWRITERPTR file = (ZIPWRITERPTR)malloc(sizeof(ZIPWRITER));

    return file != NULL ? ZipWriterActivate(file) : NULL;
}

// 0x10077460
ZIPWRITERFINDERPTR CLASSCALL ZipWriterFolderGetFileFinder(ZIPWRITERFOLDERPTR self)
{
    return NULL;
}
