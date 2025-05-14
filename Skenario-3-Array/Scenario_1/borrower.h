#ifndef BORROWER_H
#define BORROWER_H

#include "boolean.h"
#include "types.h"

typedef struct borrower {
    char nama[50];
    Prioritas prioritas;
    struct borrower* next;
} borrower;

typedef borrower* borrowerAddress;

void createBorrower(borrowerAddress *p);
void infoBorrower(borrowerAddress *p, char nama[], Prioritas prioritas);
borrowerAddress searchBorrower(borrowerAddress p, char nama[]);
void clearAllBorrower(borrowerAddress *head);

#endif

