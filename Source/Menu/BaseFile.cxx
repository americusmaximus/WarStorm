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

#include <stdio.h>
#include <stdlib.h>

#define MAX_BASEFILE_STRING_LENGTH    512

// 0x10090a88
STATIC BASEFILESELF BaseFileSelf =
{
    BaseFileRelease,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    BaseFileGetString,
    BaseFileSetString,
    NULL
};

// 0x10091280
STATIC BASEFILEFINDERSELF BaseFileFinderSelf =
{
    BaseFileFinderRelease,
    NULL,
    BaseFileFinderClose,
    NULL,
    NULL,
    NULL,
    NULL
};

// 0x1002bbc0
BASEFILEPTR CLASSCALL BaseFileRelease(BASEFILEPTR self, CONST OBJECTRELEASETYPE mode)
{
    if (mode & OBJECTRELEASETYPE_ALLOCATED) { free(self); }

    return self;
}

// 0x10074830
U32 CLASSCALL BaseFileGetString(BASEFILEPTR self, LPSTR content, U32 length)
{
    CONST U32 size = self->Self->Read(self, content, length - 1);

    if (size == 0) { return INVALID_FILE_STRING_LENGTH; }

    U32 actual = length;

    U32 count = 0;
    while (count < size)
    {
        if (content[count] == '\r') { actual = content[count + 1] == '\n'; break; }
        if (content[count] == '\n') { actual = content[count + 1] == '\r'; break; }

        count = count + 1;
    }

    if (count != length)
    {
        content[count] = NULL;

        CONST U32 offset = actual - size + 1 + count;

        if (offset != 0) { self->Self->SetPointer(self, offset, FILE_CURRENT); }

        return count;
    }

    content[length - 1] = NULL;

    return length - 1;
}

// 0x100748d0
U32 BaseFileSetString(BASEFILEPTR self, LPSTR format, ...)
{
    CHAR buffer[MAX_BASEFILE_STRING_LENGTH];

    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    CONST U32 length = strlen(buffer);

    self->Self->Write(self, buffer, length);

    return length;
}

// 0x10074960
BASEFILEFINDERPTR CLASSCALL BaseFileFinderRelease(BASEFILEFINDERPTR self, CONST OBJECTRELEASETYPE mode)
{
    BaseFileFinderDispose(self);

    if (mode & OBJECTRELEASETYPE_ALLOCATED) { free(self); }

    return self;
}

// 0x10074940
BASEFILEFINDERPTR CLASSCALL BaseFileFinderDispose(BASEFILEFINDERPTR self)
{
    return self;
}

// 0x10074950
VOID CLASSCALL BaseFileFinderClose(BASEFILEFINDERPTR self)
{

}
