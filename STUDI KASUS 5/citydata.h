#ifndef CITYDATA_H
#define CITYDATA_H

#include "list1.h"
#include "menu.h"
#include "stats.h"

#define MAX_CITY 15
#define MAX_CITY_NAME 50

typedef struct {
    char cityName[MAX_CITY_NAME];
    List nameList;  /* List untuk menyimpan nama-nama */
} City;

/* Deklarasi variabel global (definisi ada di citydata.c) */
extern City cityArray[MAX_CITY];
extern int cityCount;

/* Prototipe fungsi untuk operasi data kota dan daftar nama */
int findCityIndex(const char* cityName);
int addCity(const char* cityName);
int deleteCity(const char* cityName);
int addNameToCity(const char* cityName, const char* name);
int deleteNameFromCity(const char* cityName, const char* name);
void displayAllCities(void);
void displayCity(const char* cityName);

#endif

