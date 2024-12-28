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

#pragma once

#include "Basic.hxx"
#include "Native.Basic.hxx"

#define DEFAULT_ACTION_HANDLER_PRIORITY     0x10000000

typedef BOOL(*ACTIONHANDLERLAMBDA)(VOID);
typedef BOOL(*WINDOWACTIONHANDLERLAMBDA)(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, LRESULT* result);

#define INVOKEACTIONHANDLERLAMBDA(ACTION) ((ACTIONHANDLERLAMBDA)ACTION)()
#define INVOKEWINDOWACTIONHANDLERLAMBDA(ACTION, WND, MSG, WP, LP, RESULT) ((WINDOWACTIONHANDLERLAMBDA)ACTION)(WND, MSG, WP, LP, RESULT)

struct ActionHandler;
typedef struct ActionHandler ACTIONHANDLER, * ACTIONHANDLERPTR;

struct ActionHandler
{
    LPVOID              Action;
    U32                 Priority;
    ACTIONHANDLERPTR    Next;
};

#define INITIALIZEACTIONHANDLER(H, A)                                                               \
    if (A != NULL) {                                                                                \
        ACTIONHANDLERPTR handler = ALLOCATE(ACTIONHANDLER);                                         \
        if (handler != NULL) {                                                                      \
            InitializeActionHandler(handler, H, DEFAULT_ACTION_HANDLER_PRIORITY, A);                \
        }                                                                                           \
    }

VOID CLASSCALL InitializeActionHandler(ACTIONHANDLERPTR self, ACTIONHANDLERPTR* destination, CONST U32 priority, ACTIONHANDLERLAMBDA action);