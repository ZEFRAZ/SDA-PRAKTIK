#ifndef MENU_H
#define MENU_H

#include "antrian.h"

void displayMenu();
boolean isBorrowerExists(borrowerAddress p, const char* nama);
boolean isBookExists(buku bukuArray[], int jumlahBuku, const char* judul);
void setMaxBuku(int max);
int getMaxBuku();

#endif

