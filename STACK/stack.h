#ifndef STACK_H
#define STACK_H

#include "linkedlist.h"

// Struktur Stack menggunakan Linked List
typedef struct {
    LinkedList list; // Stack berbasis Linked List
} Stack;

// Fungsi Stack menggunakan fungsi Linked List
void initStack(Stack *s);
bool isStackEmpty(Stack *s);
void push(Stack *s, infotype value);
infotype pop(Stack *s);
void printStack(Stack *s);

// Deklarasi fungsi konversi (baru!)
void convertToBinary(int num);

#endif

