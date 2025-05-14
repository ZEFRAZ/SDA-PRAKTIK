#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "boolean.h"
#include "buku.h"
#include "borrower.h"

// Deklarasi antrian global
extern borrowerAddress firstQueue;

boolean isEmpty();
void printList(buku bukuArray[], int jumlahBuku);
void masukAntrian(borrowerAddress Pnew, buku *targetBuku);
void hapusPeminjam(char namaTerhapus[], buku *targetBuku);
void hapusPeminjamTertentu(char namaTerhapus[], borrowerAddress *p);
int jumlahElemen(borrowerAddress p);
void printQueue(borrowerAddress queue);

#endif

