#include <stdio.h>
#include "queue.h"

void CreateQueue(Queue *q) {
    CreateList(&(q->L));
}

boolean isEmpty(Queue q) {
    return ListEmpty(q.L);
}

int length(Queue q) {
    return NbElmt(q.L);
}

// Menambahkan elemen ke dalam queue
void enqueue(Queue *q, int val) {
    InsVLast(&(q->L), val);
}

// Menghapus elemen dari queue
int dequeue(Queue *q) {
    infotype val;
    DelVFirst(&(q->L), &val);
    return val;
}

// Mengirim elemen pertama dari queue
int front(Queue q) {
    return Info(First(q.L));
}

// Menampilkan isi queue dengan tanda panah untuk urutan
void displayQueue(Queue q) {
    if (isEmpty(q)) {
        printf("Queue kosong\n");
    } else {
        printf("");
        address P = First(q.L);
        while (P != Nil) {
            printf("%d <- ", Info(P));
            P = Next(P);
        }
        printf("END\n");
    }
}

