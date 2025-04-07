#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

void showMenu(void) {
	printf("=====================================\n");
    printf("||--- MENU DAFTAR NAMA DAN KOTA ---||\n");
    printf("=====================================\n");

    printf("1. Tambah Kota\n");
    printf("2. Hapus Kota\n");
    printf("3. Tambah Nama ke Kota\n");
    printf("4. Hapus Nama dari Kota\n");
    printf("5. Tampilkan Semua Data\n");
    printf("6. Tampilkan Data per Kota\n");
    printf("7. Tampilkan Statistik Data\n");
    printf("8. Keluar\n");
    printf("=====================================\n");

    printf("Pilihan Anda: ");
}

int getChoice(void) {
    int choice;
    scanf("%d", &choice);
    getchar();  // buang newline
    return choice;
}

/* Tunggu Enter lalu clear screen */
void pauseAndClear(void) {
    printf("\nTekan ENTER untuk kembali ke menu...");
    getchar();  // tunggu enter
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

