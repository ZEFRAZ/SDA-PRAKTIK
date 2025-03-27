#include "tampilan.h"
#include "list1.h"
#include <stdio.h>

void displayMainMenu(void) {
    printf("\n=== SISTEM PEMESANAN TIKET KONSER ===\n");
    printf("1. Tambah Antrean Pembeli Tiket Konser\n");
    printf("2. Proses Pembelian Tiket\n");
    printf("3. Batalkan Transaksi Terakhir (Tiket Terjual)\n");
    printf("4. Keluar\n");
    printf("Pilihan: ");
}

void displayMessage(const char *msg) {
    printf("%s\n", msg);
}

