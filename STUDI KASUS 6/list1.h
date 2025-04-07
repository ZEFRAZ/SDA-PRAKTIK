#ifndef LIST1_H
#define LIST1_H

#include "boolean.h"
#include <stdio.h>
#include <string.h>

#define Nil NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define Prev(P) (P)->prev

typedef char infotype[50];
typedef struct tElmtList *address;
typedef struct tElmtList {
    infotype info;
    address next;
    address prev;  // pointer ke node sebelumnya
} ElmtList;

typedef struct {
    address First;
} List;

/* Prototipe fungsi-fungsi double linked list */
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

