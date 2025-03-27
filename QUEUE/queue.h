#ifndef QUEUE_H
#define QUEUE_H

#include "boolean.h"
#include "list1.h"

#define MAX_QUEUE 100
#define IDX_UNDEF -1
#define QUEUE_CAPACITY 100

typedef struct {
    List L;
} Queue;

/* Operasi Queue */
void CreateQueue(Queue *q);
boolean isEmpty(Queue q);
int length(Queue q);
void enqueue(Queue *q, int val);
int dequeue(Queue *q);
int front(Queue q);
void displayQueue(Queue q);

#endif

