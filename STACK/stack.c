#include <stdio.h>
#include "stack.h"

// Inisialisasi Stack menggunakan Linked List
void initStack(Stack *s) {
    createList(&s->list);
}

// Mengecek apakah Stack kosong (Menggunakan isEmpty dari linkedlist.c)
bool isStackEmpty(Stack *s) {
    return isEmpty(s->list);
}

// Push ke Stack (Menggunakan insertFirst dari linkedlist.c)
void push(Stack *s, infotype value) {
    insertFirst(&s->list, value);
}

// Pop dari Stack (Menggunakan deleteFirst dari linkedlist.c)
infotype pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack kosong!\n");
        return -1; // Nilai error jika stack kosong
    }
    infotype value = s->list.First->info;
    deleteFirst(&s->list);
    return value;
}

// Menampilkan isi Stack (Menggunakan printList dari linkedlist.c)
void printStack(Stack *s) {
    printList(s->list);
}

// Fungsi untuk mengonversi bilangan desimal ke biner
void convertToBinary(int num) {
    Stack s;
    initStack(&s);

    printf("Proses konversi:\n");

    while (num > 0) {
        int remainder = num % 2;
        printf("%d / 2 = %d, sisa = %d (dimasukkan ke stack)\n", num, num / 2, remainder);
        push(&s, remainder);
        printStack(&s);
        num /= 2;
    }

    printf("\nMembaca stack untuk mendapatkan bilangan biner:\n");
    printf("Bilangan Biner: ");

    while (!isStackEmpty(&s)) {
        printf("%d", pop(&s));
    }
    printf("\n");
}

