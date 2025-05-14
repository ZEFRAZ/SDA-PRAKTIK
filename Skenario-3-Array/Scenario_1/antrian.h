#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "boolean.h"
#include "buku.h"
#include "borrower.h"

boolean isEmpty(buku bukuArray[], int index);
void printList(buku bukuArray[], int jumlahBuku);
void masukAntrian(buku *b, borrowerAddress Pnew);
void hapusPeminjam(buku *b, char namaTerhapus[]);
void hapusPeminjamTertentu(buku *b, char namaTerhapus[], borrowerAddress *p);
int jumlahElemen(borrowerAddress p);
void printQueue(borrowerAddress queue);

#endif

