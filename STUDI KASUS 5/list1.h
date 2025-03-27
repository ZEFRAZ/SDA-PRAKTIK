#ifndef list1_H
#define list1_H

#include "boolean.h"
#include <stdio.h>
#include <string.h>
#define Nil NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) (L).First

typedef char infotype[50];
typedef struct tElmtList *address;
typedef struct tElmtList {
    infotype info;
    address next;
} ElmtList;

typedef struct {
    address First;
} List;

/* Prototipe fungsi-fungsi ADT linked list */
void CreateList(List *L);
address Alokasi(infotype X);
void DeAlokasi(address P);
address Search(List L, infotype X);
address SearchPrec(List L, infotype X);
void InsVLast(List *L, infotype X);
void InsertLast(List *L, address P);
void DelP(List *L, infotype X);
void PrintInfo(List L);
int NbElmt(List L);
void DelAll(List *L);

#endif

