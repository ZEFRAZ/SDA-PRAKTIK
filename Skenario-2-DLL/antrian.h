#ifndef ANTRIAN_H
#define ANTRIAN_H

#include "boolean.h"
#include "buku.h"
#include "borrower.h"

boolean isEmpty(bukuAddress *b, borrowerAddress p);
void printList(buku *b);
void masukAntrian(bukuAddress b, borrowerAddress Pnew);
void hapusPeminjam(bukuAddress *b, char namaTerhapus[]);
void hapusPeminjamTertentu(bukuAddress *b, char namaTerhapus[], borrowerAddress *p);
int jumlahElemen(borrowerAddress p);
void printQueue(borrowerAddress queue);

#endif
