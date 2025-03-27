#include "queue.h"
#include <stdio.h>

void initQueue(List *q) {
    CreateList(q);
}

void enqueueQueue(List *q, int value) {
    InsVLast(q, value);
}

boolean dequeueQueue(List *q, int *value) {
    if (ListEmpty(*q))
        return false;
    DelVFirst(q, value);
    return true;
}

void printQueue(List q) {
    PrintInfo(q);
}

