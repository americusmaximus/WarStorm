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

#include "Strings.hxx"

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_STRING_BUFFER_LENGTH 512

#define UNIITEM(x, indx) ((BYTE)((LPBYTE)x)[indx])

// 0x1002bbe0
STRINGVALUEPTR AcquireStringValue(STRINGVALUEPTR self, LPCSTR format, ...)
{
    CHAR value[DEFAULT_STRING_BUFFER_LENGTH];

    va_list args;
    va_start(args, format);
    vsprintf(value, format, args);
    va_end(args);

    self->Value = (LPSTR)malloc(strlen(value) + 1);

    strcpy(self->Value, value);

    return self;
}

// 0x1002bd30
VOID CLASSCALL ReleaseStringValue(STRINGVALUEPTR self)
{
    if (self->Value != NULL) { free(self->Value); }
}

U32 AcquireCharacterLength(LPSTR value);

// 0x10078030
LPSTR AcquireNextString(LPSTR value)
{
    return (LPSTR)((ADDR)value + AcquireCharacterLength(value));
}

// 0x10078080
U32 AcquireUnicode(LPCSTR value)
{
    if (!(UNIITEM(value, 0) & 0x80)) { return (U32)UNIITEM(value, 0); }

    if ((UNIITEM(value, 0) & 0xE0) == 0xC0)
    {
        return (((U32)UNIITEM(value, 0) & 0x1F) << 6) | ((U32)UNIITEM(value, 1) & 0x3F);
    }

    if ((UNIITEM(value, 0) & 0xF0) == 0xE0)
    {
        return (((U32)UNIITEM(value, 0) & 0x0F) << 12)
            | (((U32)UNIITEM(value, 1) & 0x3F) << 6) | ((U32)UNIITEM(value, 2) & 0x3F);
    }

    if ((UNIITEM(value, 0) & 0xF8) == 0xF0)
    {
        return (((U32)UNIITEM(value, 0) & 0x0F) << 18) | (((U32)UNIITEM(value, 1) & 0x3F) << 12)
            | (((U32)UNIITEM(value, 2) & 0x3F) << 6) | ((U32)UNIITEM(value, 3) & 0x3F);
    }

    return NULL;
}

// 0x10078110
U32 AcquireCharacterLength(LPSTR value)
{
    CONST BYTE c = (BYTE)value[0];

    if ((c & 0x80) == 0x00) { return 1; }
    if ((c & 0xE0) == 0xC0) { return 2; }
    if ((c & 0xF0) == 0xE0) { return 3; }

    return ((c & 0xF8) != 0xF0) ? 1 : 4;
}

// 0x100783c0
U32 AcquireAnsiString(LPSTR result, U32 length, LPCSTR value, S32 limit)
{
    S32 indx = 0;
    LPSTR current = (LPSTR)value;
    LPWSTR items = (LPWSTR)alloca((length * sizeof(WCHAR) + 3) & 0xFFFFFFFC);

    if (length >= 0)
    {
        while (limit < 1 || ((ADDR)current - (ADDR)value) < limit)
        {
            CONST U32 item = AcquireUnicode(current);

            items[indx] = (WCHAR)item;
            indx = indx + 1;

            if ((limit < 0 && item == NULL) || length <= indx) { break; }

            current = AcquireNextString(current);
        }
    }

    CONST CHAR unknown = '?';
    return WideCharToMultiByte(CP_ACP,
        WC_COMPOSITECHECK | WC_DEFAULTCHAR | WC_DISCARDNS, items, indx, result, length, &unknown, NULL);
}
