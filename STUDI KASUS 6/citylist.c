#include "citylist.h"
#include <stdlib.h>

CityList cityList = { NULL, NULL, 0 };

CityAddress findCity(const char* cityName) {
    CityAddress p = cityList.head;
    while (p != NULL) {
       if (strcmp(p->data.cityName, cityName) == 0)
         return p;
       p = p->next;
    }
    return NULL;
}

int addCity(const char* cityName) {
    if (findCity(cityName) != NULL) {
        printf("Kota '%s' sudah terdaftar!\n", cityName);
        return 0;
    }
    CityAddress newNode = (CityAddress)malloc(sizeof(CityNode));
    if (newNode == NULL) {
       fprintf(stderr, "Error: gagal mengalokasikan memori untuk kota baru.\n");
       return 0;
    }
    strncpy(newNode->data.cityName, cityName, MAX_CITY_NAME);
    newNode->data.cityName[MAX_CITY_NAME - 1] = '\0';
    CreateList(&newNode->data.nameList);
    newNode->next = NULL;
    newNode->prev = NULL;
    
    // Tambahkan node di akhir linked list kota
    if (cityList.head == NULL) {
       cityList.head = newNode;
       cityList.tail = newNode;
    } else {
       cityList.tail->next = newNode;
       newNode->prev = cityList.tail;
       cityList.tail = newNode;
    }
    cityList.size++;
    return 1;
}

int deleteCity(const char* cityName) {
    CityAddress p = findCity(cityName);
    if (p == NULL)
       return 0;
    
    DelAll(&p->data.nameList);
    
    if (p->prev != NULL)
       p->prev->next = p->next;
    else
       cityList.head = p->next;
    
    if (p->next != NULL)
       p->next->prev = p->prev;
    else
       cityList.tail = p->prev;
    
    free(p);
    cityList.size--;
    return 1;
}

int addNameToCity(const char* cityName, const char* name) {
    CityAddress p = findCity(cityName);
    if (p == NULL)
       return 0;
    InsVLast(&p->data.nameList, (char *)name);
    return 1;
}

int deleteNameFromCity(const char* cityName, const char* name) {
    CityAddress p = findCity(cityName);
    if (p == NULL)
       return 0;
    DelP(&p->data.nameList, (char *)name);
    return 1;
}

void displayAllCities(void) {
    if (cityList.head == NULL) {
        printf("Belum ada data kota.\n");
        return;
    }
    printf("\n=== DAFTAR KOTA DAN NAMA ===\n");
    int idx = 1;
    CityAddress p = cityList.head;
    while (p != NULL) {
        printf("%d. Kota: %s\n", idx, p->data.cityName);
        if (p->data.nameList.First == NULL) {
            printf("   (Belum ada nama yang terdaftar)\n");
        } else {
            printf("   Nama:\n");
            address q = p->data.nameList.First;
            while (q != NULL) {
                printf("        -> %s\n", Info(q));
                q = Next(q);
            }
        }
        printf("\n");
        idx++;
        p = p->next;
    }
}

void displayCity(const char* cityName) {
    CityAddress p = findCity(cityName);
    if (p == NULL) {
        printf("Kota '%s' tidak ditemukan.\n", cityName);
        return;
    }
    printf("\n=== DATA KOTA ===\n");
    printf("Kota: %s\n", p->data.cityName);
    if (p->data.nameList.First == NULL) {
        printf("   (Belum ada nama yang terdaftar)\n");
    } else {
        printf("   Nama:\n");
        address q = p->data.nameList.First;
        while (q != NULL) {
            printf("        -> %s\n", Info(q));
            q = Next(q);
        }
    }
    printf("\n");
}

