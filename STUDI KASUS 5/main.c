#include "citydata.h"
#include <stdio.h>

int main(void) {
    int choice;
    char cityName[MAX_CITY_NAME];
    char personName[50];
    
    /* Inisialisasi awal: tambahkan beberapa kota default */
    addCity("Averia");
	addCity("Brivana");
	addCity("Cendralis");
	addCity("Draventhia");
	addCity("Eldoria");
	
	/* Tambahkan beberapa nama*/
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
    
    do {
        showMenu();
        choice = getChoice();
        switch (choice) {
            case 1:
                printf("Masukkan nama kota yang ingin ditambah: ");
                fgets(cityName, sizeof(cityName), stdin);
                cityName[strcspn(cityName, "\n")] = '\0';
                if (addCity(cityName)) {
                    printf("Kota '%s' berhasil ditambahkan.\n", cityName);
                }
                break;
            case 2:
                printf("Masukkan nama kota yang ingin dihapus: ");
                fgets(cityName, sizeof(cityName), stdin);
                cityName[strcspn(cityName, "\n")] = '\0';
                if (deleteCity(cityName)) {
                    printf("Kota '%s' beserta data namanya berhasil dihapus.\n", cityName);
                } else {
                    printf("Kota '%s' tidak ditemukan.\n", cityName);
                }
                break;
            case 3:
                printf("Masukkan nama kota: ");
                fgets(cityName, sizeof(cityName), stdin);
                cityName[strcspn(cityName, "\n")] = '\0';
                printf("Masukkan nama yang ingin ditambahkan: ");
                fgets(personName, sizeof(personName), stdin);
                personName[strcspn(personName, "\n")] = '\0';
                if (addNameToCity(cityName, personName)) {
                    printf("Nama '%s' berhasil ditambahkan ke kota '%s'.\n", personName, cityName);
                } else {
                    printf("Kota '%s' tidak ditemukan.\n", cityName);
                }
                break;
            case 4:
                printf("Masukkan nama kota: ");
                fgets(cityName, sizeof(cityName), stdin);
                cityName[strcspn(cityName, "\n")] = '\0';
                printf("Masukkan nama yang ingin dihapus: ");
                fgets(personName, sizeof(personName), stdin);
                personName[strcspn(personName, "\n")] = '\0';
                if (deleteNameFromCity(cityName, personName)) {
                    printf("Nama '%s' berhasil dihapus dari kota '%s'.\n", personName, cityName);
                } else {
                    printf("Data nama '%s' atau kota '%s' tidak ditemukan.\n", personName, cityName);
                }
                break;
            case 5:
                displayAllCities();
                break;
            case 6:
                printf("Masukkan nama kota: ");
                fgets(cityName, sizeof(cityName), stdin);
                cityName[strcspn(cityName, "\n")] = '\0';
                displayCity(cityName);
                break;
            case 7:
                displayStats();
                break;
            case 8:
                printf("Terima kasih, program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                break;
        }
    } while (choice != 8);
    
    return 0;
}

