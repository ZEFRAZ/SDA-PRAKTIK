#include "citylist.h"
#include "menu.h"
#include "stats.h"
#include <stdio.h>
#include <string.h>

#define MAX_CITY_NAME 50

int selectCity(char *outName) {
    if (cityList.size == 0) {
        printf("Belum ada kota terdaftar.\n");
        return 0;
    }
    printf("Pilih kota:\n");
    CityAddress p = cityList.head;
    int idx = 1;
    while (p) {
        printf("  %d. %s\n", idx, p->data.cityName);
        p = p->next;
        idx++;
    }
    printf("Masukkan nomor kota: ");
    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice >= idx) {
        printf("Pilihan tidak valid.\n");
        getchar();
        return 0;
    }
    getchar();
    p = cityList.head;
    int i;
    for (i = 1; i < choice; i++) p = p->next;
    strcpy(outName, p->data.cityName);
    return 1;
}

int selectName(const char *cityName, char *outName) {
    CityAddress p = findCity(cityName);
    if (!p || p->data.nameList.First == NULL) {
        printf("Belum ada nama di kota %s.\n", cityName);
        return 0;
    }
    printf("Pilih nama di kota %s:\n", cityName);
    address q = p->data.nameList.First;
    int idx = 1;
    while (q) {
        printf("  %d. %s\n", idx, Info(q));
        q = Next(q);
        idx++;
    }
    printf("Masukkan nomor nama: ");
    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice >= idx) {
        printf("Pilihan tidak valid.\n");
        getchar();
        return 0;
    }
    getchar();
    q = p->data.nameList.First;
    int i;
    for (i = 1; i < choice; i++) q = Next(q);
    strcpy(outName, Info(q));
    return 1;
}

int main(void) {
    int choice;
    char cityName[MAX_CITY_NAME];
    char personName[50];

    // Inisialisasi data awal
    addCity("Averia");
    addCity("Brivana");
    addCity("Cendralis");
    addCity("Draventhia");
    addCity("Eldoria");

    addNameToCity("Averia", "Alden");
    addNameToCity("Averia", "Aurora");
    addNameToCity("Averia", "Asher");
    addNameToCity("Brivana", "Bastian");
    addNameToCity("Cendralis", "Callista");
    addNameToCity("Cendralis", "Cassius");
    addNameToCity("Eldoria", "Elara");
    addNameToCity("Eldoria", "Edric");
    addNameToCity("Eldoria", "Evangeline");
    addNameToCity("Eldoria", "Ezra");

    // Clear screen saat pertama kali
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    do {
    	printf("=====================================\n");
        printf("||     Jumlah kota saat ini: %d     || \n", cityList.size);
        printf("=====================================\n");

        showMenu();
        choice = getChoice();

        switch (choice) {
            case 1: // Tambah Kota
                printf("Masukkan nama kota baru: ");
                fgets(cityName, MAX_CITY_NAME, stdin);
                cityName[strcspn(cityName, "\n")] = '\0'; // hapus newline
                if (addCity(cityName))
                    printf("Kota '%s' berhasil ditambahkan.\n", cityName);
                else
                    printf("Kota '%s' sudah ada.\n", cityName);
                pauseAndClear();
                break;

            case 2: // Hapus Kota
                if (selectCity(cityName)) {
                    if (deleteCity(cityName))
                        printf("Kota '%s' berhasil dihapus.\n", cityName);
                    else
                        printf("Gagal menghapus kota '%s'.\n", cityName);
                }
                pauseAndClear();
                break;

            case 3: // Tambah Nama ke Kota
                if (selectCity(cityName)) {
                    printf("Masukkan nama orang: ");
                    fgets(personName, 50, stdin);
                    personName[strcspn(personName, "\n")] = '\0';
                    if (addNameToCity(cityName, personName))
                        printf("Nama '%s' berhasil ditambahkan ke kota '%s'.\n", personName, cityName);
                    else
                        printf("Gagal menambahkan nama.\n");
                }
                pauseAndClear();
                break;

            case 4: // Hapus Nama dari Kota
                if (selectCity(cityName)) {
                    if (selectName(cityName, personName)) {
                        if (deleteNameFromCity(cityName, personName))
                            printf("Nama '%s' berhasil dihapus dari kota '%s'.\n", personName, cityName);
                        else
                            printf("Gagal menghapus nama.\n");
                    }
                }
                pauseAndClear();
                break;

            case 5: // Tampilkan Semua Kota
                displayAllCities();
                pauseAndClear();
                break;

            case 6: // Tampilkan Data per Kota
                if (selectCity(cityName)) {
                    displayCity(cityName);
                }
                pauseAndClear();
                break;

            case 7: // Statistik Global
                displayStats();
                pauseAndClear();
                break;

            case 8: // Keluar
                printf("Terima kasih telah menggunakan program ini.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
                pauseAndClear();
                break;
        }
    } while (choice != 8);

    return 0;
}

