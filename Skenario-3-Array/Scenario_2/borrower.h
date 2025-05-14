#ifndef BORROWER_H
#define BORROWER_H

#include "boolean.h"
#include "types.h"

typedef struct buku buku;  // Forward declaration

typedef struct borrower {
    char nama[50];
    Prioritas prioritas;
    struct borrower* next;
    buku* targetBuku;  // Pointer ke buku yang ingin dipinjam
} borrower;

typedef borrower* borrowerAddress;

void createBorrower(borrowerAddress *p);
void infoBorrower(borrowerAddress *p, char nama[], Prioritas prioritas);
void setBorrowTarget(borrowerAddress p, buku *targetBuku);
borrowerAddress searchBorrower(borrowerAddress p, char nama[]);
void clearAllBorrower(borrowerAddress *head);

#endif

