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

#include "Module.hxx"
#include "State.hxx"

#include <Mathematics.Basic.hxx>

using namespace Mathematics;

// 0x00402ce0
VOID AcquireStartArguments(LPCSTR value)
{
    U32 count = 0;
    U32 length = 0;

    LPCSTR actual = value == NULL ? State.Window->Args : value;

    AcquireStartArguments(actual, NULL, NULL, &count, &length);

    State.Arguments.All = (LPSTR)malloc(length);
    State.Arguments.Args = (LPSTR*)malloc(count * sizeof(LPSTR));

    AcquireStartArguments(actual, State.Arguments.Args, State.Arguments.All, &count, &length);

    State.Arguments.Count = count;
}

// 0x00402d60
VOID AcquireStartArguments(LPCSTR value, LPSTR* args, LPSTR values, U32* count, U32* length)
{
    BOOL start = FALSE;
    BOOL end = FALSE;

    *length = 0;
    *count = 0;

    if (value == NULL) { return; }

    while (*value != NULL)
    {
        // Skip spaces and tabs.
        for (; *value == ' ' || *value == '\t'; value = value + 1) {}

        if (*value == NULL) { break; }

        if (args != NULL)
        {
            *args = values;
            args = args + 1;
        }

        *count = *count + 1;

        while (TRUE)
        {
            U32 slashes = 0;
            BOOL append = TRUE;
            CHAR current = *value;

            // Count contiguous slashes.
            while (current == '\\')
            {
                value = value + 1;
                slashes = slashes + 1;
                current = *value;
            }

            if (*value == '\"')
            {
                if ((slashes & 1) == 0)
                {
                    if (start && value[1] == '\"')
                    {
                        value = value + 1;
                    }
                    else { append = FALSE; }

                    start = !end;
                    end = start;
                }

                slashes = slashes >> 1;
            }

            for (; slashes != 0; slashes = slashes - 1)
            {
                if (values != NULL)
                {
                    *values = '\\';
                    values = values + 1;
                }

                *length = *length + 1;
            }

            current = *value;

            if (current == NULL || (!start && (current == ' ' || current == '\t'))) { break; }

            if (append)
            {
                if (values != NULL)
                {
                    *values = current;
                    values = values + 1;
                }

                *length = *length + 1;
            }

            value = value + 1;
        }

        if (values != NULL)
        {
            *values = NULL;
            values = values + 1;
        }

        *length = *length + 1;
    }
}

// 0x00402e90
// NOTE. Contains additional checks for better startup arguments parsing.
BOOL AcquireStartArguments(LPCSTR name, LPSTR value, CONST U32 length)
{
    for (U32 x = 0; x < State.Arguments.Count; x++)
    {
        LPSTR current = strrchr(State.Arguments.Args[x], '=');

        if (current != NULL)
        {
            CONST ADDR size = (ADDR)current - (ADDR)State.Arguments.Args[x];

            if (size != 0 && strnicmp(State.Arguments.Args[x], name, size) == 0)
            {
                current++;

                strncpy(value, current, Min<size_t>(length, strlen(current) + 1));

                return TRUE;
            }
        }
    }

    return FALSE;
}

// 0x00402e60
VOID ReleaseStartArguments(VOID)
{
    if (State.Arguments.Args != NULL) { free(State.Arguments.Args); }
    if (State.Arguments.All != NULL) { free(State.Arguments.All); }
}

// 0x00401160
VOID AcquireIniFileState(VOID)
{
    State.IsIniActive = GetPrivateProfileIntA("debug", "useinifile", FALSE, State.App->Ini);
}