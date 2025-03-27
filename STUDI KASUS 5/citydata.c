#include "citydata.h"

/* Definisi variabel global */
City cityArray[MAX_CITY];
int cityCount = 0;

/* Mencari indeks kota berdasarkan nama */
int findCityIndex(const char* cityName) {
    int i;
    for (i = 0; i < cityCount; i++) {
        if (strcmp(cityArray[i].cityName, cityName) == 0) {
            return i;
        }
    }
    return -1;
}

/* Menambah kota baru */
int addCity(const char* cityName) {
    if (findCityIndex(cityName) != -1) {
        printf("Kota '%s' sudah terdaftar!\n", cityName);
        return 0;
    }
    if (cityCount < MAX_CITY) {
        strcpy(cityArray[cityCount].cityName, cityName);
        CreateList(&cityArray[cityCount].nameList);
        cityCount++;
        return 1;
    } else {
        printf("Array kota sudah penuh!\n");
        return 0;
    }
}

/* Menghapus kota beserta seluruh daftar nama di dalamnya */
int deleteCity(const char* cityName) {
    int idx, i;
    idx = findCityIndex(cityName);
    if (idx == -1) {
        return 0;
    }
    /* Hapus seluruh daftar nama di kota tersebut */
    DelAll(&cityArray[idx].nameList);
    /* Geser elemen array untuk mengisi "lubang" */
    for (i = idx; i < cityCount - 1; i++) {
        cityArray[i] = cityArray[i + 1];
    }
    cityCount--;
    return 1;
}

/* Menambah nama ke dalam daftar nama pada kota tertentu */
int addNameToCity(const char* cityName, const char* name) {
    int idx;
    idx = findCityIndex(cityName);
    if (idx == -1) {
        return 0;
    }
    /* Menggunakan fungsi InsVLast dari list1.c/h, lakukan cast dari const char* ke char* */
    InsVLast(&cityArray[idx].nameList, (char *)name);
    return 1;
}

/* Menghapus nama dari daftar nama pada kota tertentu */
int deleteNameFromCity(const char* cityName, const char* name) {
    int idx;
    idx = findCityIndex(cityName);
    if (idx == -1) {
        return 0;
    }
    /* Menggunakan fungsi DelP dari list1.c/h, lakukan cast dari const char* ke char* */
    DelP(&cityArray[idx].nameList, (char *)name);
    return 1;
}

/* Fungsi untuk mencetak daftar nama dengan format custom: "   -> nama" */
void PrintInfoCustom(List L) {
    address P = First(L);
    if (P == Nil) {
        printf("   (Belum ada nama yang terdaftar)\n");
        return;
    }
    printf("   Nama:\n");
    while (P != Nil) {
        printf("        -> %s\n", Info(P));
        P = Next(P);
    }
}

/* Menampilkan semua kota beserta daftar nama masing-masing */
void displayAllCities(void) {
    int i;
    if (cityCount == 0) {
        printf("Belum ada data kota.\n");
        return;
    }
    printf("\n=== DAFTAR KOTA DAN NAMA ===\n");
    for (i = 0; i < cityCount; i++) {
        printf("%d. Kota: %s\n", i + 1, cityArray[i].cityName);
        PrintInfoCustom(cityArray[i].nameList);
        printf("\n");
    }
}

/* Menampilkan data untuk satu kota tertentu */
void displayCity(const char* cityName) {
    int idx;
    idx = findCityIndex(cityName);
    if (idx == -1) {
        printf("Kota '%s' tidak ditemukan.\n", cityName);
        return;
    }
    printf("\n=== DATA KOTA ===\n");
    printf("Kota: %s\n", cityArray[idx].cityName);
    PrintInfoCustom(cityArray[idx].nameList);
    printf("\n");
}

