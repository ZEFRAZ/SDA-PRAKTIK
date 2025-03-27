#ifndef SISTEM_H
#define SISTEM_H

#include "list1.h"

/* Mendapatkan input integer yang valid */
int getValidInt(const char *prompt, int min, int max);

/* Menghitung jumlah elemen dalam List */
int countList(List L);

/* Menampilkan status antrean untuk semua loket */
void displayAllQueues(List loket[], int jumlahLoket);

/* Proses pembelian tiket dari loket */
void processPurchase(List *loket, List *tiketTerjual, List loketArray[], int jumlahLoket);

/* Membatalkan transaksi terakhir */
void cancelTransaction(List *tiketTerjual, List *riwayatBatal);

#endif

