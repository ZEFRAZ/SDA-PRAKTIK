#include "stack.h"
#include <stdio.h>

void initStack(List *s) {
    CreateList(s);
}

void pushStack(List *s, int value) {
    InsVFirst(s, value);
}

boolean popStack(List *s, int *value) {
    if (ListEmpty(*s))
        return false;
    DelVFirst(s, value);
    return true;
}

void printStack(List s) {
    PrintInfo(s);
}

