#include "menu.h"
#include <stdio.h>

void showMenu(void) {
    printf("\n=== MENU ===\n");
    printf("1. Tambah Kota\n");
    printf("2. Hapus Kota\n");
    printf("3. Tambah Nama ke Kota\n");
    printf("4. Hapus Nama dari Kota\n");
    printf("5. Tampilkan Semua Data\n");
    printf("6. Tampilkan Data per Kota\n");
    printf("7. Tampilkan Statistik Data\n");
    printf("8. Keluar\n");
    printf("Pilihan Anda: ");
}

int getChoice(void) {
    int choice;
    scanf("%d", &choice);
    getchar();
    return choice;
}

