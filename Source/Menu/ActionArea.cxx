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

#include "ActionArea.hxx"

ACTIONAREASTATEMODULECONTAINER ActionAreaState;

// 0x10075580
ACTIONAREAPTR AcquireActionArea(U32 action)
{
    ACTIONAREAPTR item = ActionAreaState.Items;

    while (item != NULL)
    {
        if (item->Action == action) { return item; }

        item = item->Next;
    }

    return item;
}

// 0x100755a0
VOID EnqueueActionArea(ACTIONAREAPTR area)
{
    ACTIONAREAPTR current = ActionAreaState.Items;
    ACTIONAREAPTR next = NULL;

    while (current != NULL)
    {
        ACTIONAREAPTR self = current;
        current = self;

        if (self->Priority < area->Priority) { break; }

        current = self->Next;
        next = self;
    };

    area->Next = current;

    if (next == NULL) { ActionAreaState.Items = area; return; }

    next->Next = area;
}

// 0x100755e0
VOID DequeueActionArea(ACTIONAREAPTR area)
{
    ACTIONAREAPTR current = ActionAreaState.Items;
    ACTIONAREAPTR next = NULL;

    if (current != NULL)
    {
        ACTIONAREAPTR value = current;

        while (value != area)
        {
            current = value->Next;
            next = value;

            if (value->Next == NULL) { return; }

            value = current;
        }

        if (next == NULL) { ActionAreaState.Items = value->Next; return; }

        next->Next = value->Next;
    }
}


// 0x100754e0
VOID CLASSCALL ReleaseActionArea(ACTIONAREAPTR self)
{
    ACTIONAREAPTR current = ActionAreaState.Items;
    ACTIONAREAPTR next = NULL;

    if (current != NULL)
    {
        ACTIONAREAPTR value = NULL;

        do
        {
            value = current;

            if (value == self)
            {
                if (next == NULL) { ActionAreaState.Items = self->Next; }
                else { next->Next = self->Next; }
            }

            current = value->Next;
            next = value;

        } while (value->Next != NULL);
    }
}