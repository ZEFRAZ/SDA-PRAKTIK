// stack.h
#ifndef STACK_H
#define STACK_H

#include "boolean.h"
#include "types.h"
#include "buku.h"
#include "borrower.h"
#include "antrian.h"

// Deklarasi extern untuk variabel global dari antrian.c
extern borrowerAddress queueHead;
extern borrowerAddress activeBorrowers;

void pushAktivitas(aktivitasStack* top, char jenis[], char judulBuku[], char namaPeminjam[], int prioritas);
void popAktivitas(aktivitasStack* top);
void undoAktivitas(aktivitasStack* top, bukuAddress* listBuku);

#endif

