// stack.h
#ifndef STACK_H
#define STACK_H
#include "boolean.h"
#include "buku.h"
#include "borrower.h"

typedef struct aktivitas {
    char jenis[20];
    char judulBuku[100];
    char namaPeminjam[50];
    int prioritas;
    struct aktivitas* next;
} aktivitas;

typedef aktivitas* aktivitasStack;

void pushAktivitas(aktivitasStack* top, char jenis[], char judulBuku[], char namaPeminjam[], int prioritas);
void popAktivitas(aktivitasStack* top);
void undoAktivitas(aktivitasStack* top, bukuAddress* listBuku);

#endif
