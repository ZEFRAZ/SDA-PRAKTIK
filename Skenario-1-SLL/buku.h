#ifndef BUKU_H
#define BUKU_H

#include "types.h"

// Function declarations
void createBuku(bukuAddress *b);
void infoBuku(bukuAddress *b, char judul[], int stok);
void addBuku(bukuAddress newBuku);
void deleteBuku(bukuAddress *head, bukuAddress target);
void clearAllBuku(bukuAddress *head);
bukuAddress findBuku(bukuAddress head, char judul[]);

#endif