#ifndef STACK_H
#define STACK_H

#include "list1.h"
#include "boolean.h"

/* Inisialisasi stack (List) */
void initStack(List *s);

/* Push: tambahkan nilai di depan */
void pushStack(List *s, int value);

/* Pop: hapus nilai dari depan; kembalikan true jika berhasil */
boolean popStack(List *s, int *value);

/* Tampilkan stack menggunakan PrintInfo() */
void printStack(List s);

#endif

