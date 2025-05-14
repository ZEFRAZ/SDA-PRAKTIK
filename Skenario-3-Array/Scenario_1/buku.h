#ifndef BUKU_H
#define BUKU_H

#include "boolean.h"
#include "types.h"

typedef struct buku {
    char judul[100];
    int stok;
    struct borrower *firstQueue;
    struct borrower *peminjamAktif;
} buku;

// Fungsi untuk menginisialisasi array buku
void initBuku(buku bukuArray[], int *jumlahBuku);

// Fungsi untuk menambah buku baru
void tambahBuku(buku bukuArray[], int *jumlahBuku, char judul[], int stok);

// Fungsi untuk menghapus buku
void hapusBuku(buku bukuArray[], int *jumlahBuku, int index);

// Fungsi untuk membersihkan semua buku
void clearAllBuku(buku bukuArray[], int *jumlahBuku);

#endif

