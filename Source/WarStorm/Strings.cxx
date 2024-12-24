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

#include "Strings.hxx"

#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_STRING_LENGTH 64

// 0x00401100
STRINGVALUEPTR CLASSCALL AcquireStringValue(STRINGVALUEPTR self, STRINGVALUEPTR value)
{
    self->Value = (LPSTR)malloc(strlen(value->Value) + 1);

    strcpy(self->Value, value->Value);

    return self;
}

// 0x00401000
VOID AcquireStringValue(STRINGVALUEPTR self, LPCSTR format, ...)
{
    CHAR value[DEFAULT_STRING_LENGTH];

    va_list args;
    va_start(args, format);
    vsprintf(value, format, args);
    va_end(args);

    self->Value = (LPSTR)malloc(strlen(value) + 1);

    strcpy(self->Value, value);
}

// 0x00401150
VOID CLASSCALL ReleaseStringValue(STRINGVALUEPTR self)
{
    if (self->Value != NULL) { free(self->Value); }
}