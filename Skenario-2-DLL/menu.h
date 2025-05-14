#ifndef MENU_H
#define MENU_H

#include "antrian.h"

void displayMenu();
boolean isBorrowerExists(borrowerAddress p, const char* nama);
boolean isBookExists(bukuAddress b, const char* judul);

#endif
