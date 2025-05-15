#ifndef BORROWER_H
#define BORROWER_H

#include "types.h"

// Function declarations
void createBorrower(borrowerAddress *p, bukuAddress targetBuku);
void infoBorrower(borrowerAddress *p, char nama[], Prioritas prioritas);
borrowerAddress searchBorrower(borrowerAddress p, char nama[]);
void clearAllBorrower(borrowerAddress *head);

#endif