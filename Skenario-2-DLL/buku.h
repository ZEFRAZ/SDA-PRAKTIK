#ifndef BUKU_H
#define BUKU_H

#include "boolean.h"
#include "types.h"

typedef struct buku {
    char judul[100];
    int stok;
    struct borrower *firstQueue;
    struct borrower *peminjamAktif;
    struct buku *next;
    struct buku *prev;
} buku;

typedef buku* bukuAddress;

void createBuku(bukuAddress *b);
void infoBuku(bukuAddress *b, char judul[], int stok);
void deleteBuku(bukuAddress *head, bukuAddress target);
void clearAllBuku(bukuAddress *head);

#endif
