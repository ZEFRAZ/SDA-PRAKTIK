#ifndef CITYLIST_H
#define CITYLIST_H

#include "list1.h"
#include "boolean.h"
#include <stdio.h>
#include <string.h>

#define MAX_CITY_NAME 50

typedef struct {
    char cityName[MAX_CITY_NAME];
    List nameList;  // double linked list untuk menyimpan nama-nama
} City;

typedef struct tCityNode *CityAddress;
typedef struct tCityNode {
    City data;
    CityAddress next;
    CityAddress prev;
} CityNode;

typedef struct {
    CityAddress head;
    CityAddress tail;
    int size;
} CityList;

/* Variabel global untuk data kota */
extern CityList cityList;

/* Prototipe fungsi operasi data kota dan daftar nama */
CityAddress findCity(const char* cityName);
int addCity(const char* cityName);
int deleteCity(const char* cityName);
int addNameToCity(const char* cityName, const char* name);
int deleteNameFromCity(const char* cityName, const char* name);
void displayAllCities(void);
void displayCity(const char* cityName);

#endif

