#ifndef ANTRIAN_H
#define ANTRIAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// Global variables (extern)
extern bukuAddress listBuku;
extern borrowerAddress queueHead;
extern borrowerAddress activeBorrowers;

// Function declarations
boolean isEmpty(borrowerAddress head);
void printQueueForBook(bukuAddress b);
void printStatusBuku(bukuAddress b);
void printList(bukuAddress b);
void masukAntrian(borrowerAddress *head, borrowerAddress newNode);
void hapusPeminjam(bukuAddress buku, char namaPeminjam[]);
void hapusPeminjamTertentu(borrowerAddress *head, char namaTerhapus[], bukuAddress targetBuku);
void kembalikanBuku(borrowerAddress *head, bukuAddress buku);
void batalkanPeminjaman(borrowerAddress *head, bukuAddress buku, char namaPeminjam[]);
void printQueue(borrowerAddress queue);
void printAllBuku();
void clearAllBorrower(borrowerAddress *head);

#endif