#ifndef QUEUE_H
#define QUEUE_H

#include "list1.h"
#include "boolean.h"

/* Inisialisasi queue (List) */
void initQueue(List *q);

/* Enqueue: tambahkan nilai di belakang */
void enqueueQueue(List *q, int value);

/* Dequeue: hapus nilai dari depan; kembalikan true jika berhasil */
boolean dequeueQueue(List *q, int *value);

/* Tampilkan queue menggunakan PrintInfo() */
void printQueue(List q);

#endif

