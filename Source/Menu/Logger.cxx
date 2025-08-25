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

#include "Logger.hxx"
#include "State.hxx"

#define MAX_LOG_MESSAGE_LENGTH  512

VOID CLASSCALL LogMessage(LOGGERPTR self, LPCSTR message);
VOID CLASSCALL LogMessage(LOGGERPTR self, LPCSTR format, va_list args);
VOID CLASSCALL SendLogMessage(LOGGERPTR self, LPCSTR message);

// 0x10001cb0
VOID LogMessage(LPCSTR format, ...)
{
    if (State.Logger != NULL)
    {
        va_list args;
        va_start(args, format);

        LogMessage(State.Logger, format, args);

        va_end(args);
    }
}

// 0x10076500
VOID CLASSCALL LogMessage(LOGGERPTR self, LPCSTR format, va_list args)
{
    CHAR message[MAX_LOG_MESSAGE_LENGTH];

    wvsprintfA(message, format, args);

    LogMessage(self, message);
}

// 0x100764a0
VOID CLASSCALL LogMessage(LOGGERPTR self, LPCSTR message)
{
    if (WaitForSingleObject(self->Mutex, 5000) != WAIT_OBJECT_0) { return; }

    if (self->Self->IsActive(self))
    {
        self->Self->Write(self, message, strlen(message));
    }

    OutputDebugStringA(message);

    SendLogMessage(self, message);

    ReleaseMutex(self->Mutex);
}

// 0x10076440
VOID CLASSCALL SendLogMessage(LOGGERPTR self, LPCSTR message)
{
    if (self->HWND != NULL)
    {
        LRESULT result = LB_OKAY;
        while ((result = SendMessageA(self->HWND, LB_ADDSTRING, 0, (LPARAM)message)) == LB_ERR)
        {
            if (SendMessageA(self->HWND, LB_DELETESTRING, 0, 0) == LB_ERR) { return; }
        }

        SendMessageA(self->HWND, LB_SETCURSEL, result, 0);
    }
}