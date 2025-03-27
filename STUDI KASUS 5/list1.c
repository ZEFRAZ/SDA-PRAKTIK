#include "list1.h"
#include <stdlib.h>

/* Fungsi-fungsi privat (tidak di-ekspos) */
static boolean ListEmpty(List L)
{
    return (First(L) == Nil);
}

static void DelFirst(List *L, address *P)
{
    *P = First(*L);
    if (*P != Nil)
    {
        First(*L) = Next(First(*L));
    }
}

void CreateList(List *L)
{
    First(*L) = Nil;
}

address Alokasi(infotype X)
{
    address P = (address)malloc(sizeof(ElmtList));
    if (P != Nil)
    {
        strcpy(Info(P), X);
        Next(P) = Nil;
    }
    return P;
}

void DeAlokasi(address P)
{
    if (P != Nil)
    {
        free(P);
    }
}

address Search(List L, infotype X)
{
    address P = First(L);
    while (P != Nil)
    {
        if (strcmp(Info(P), X) == 0)
        {
            return P;
        }
        P = Next(P);
    }
    return Nil;
}

address SearchPrec(List L, infotype X)
{
    address Prec = Nil;
    address P = First(L);
    while (P != Nil)
    {
        if (strcmp(Info(P), X) == 0)
        {
            return Prec;
        }
        Prec = P;
        P = Next(P);
    }
    return Nil;
}

void InsVLast(List *L, infotype X)
{
    address P = Alokasi(X);
    if (P != Nil)
    {
        InsertLast(L, P);
    }
}

void InsertLast(List *L, address P)
{
    if (First(*L) == Nil)
    {
        First(*L) = P;
    }
    else
    {
        address Last = First(*L);
        while (Next(Last) != Nil)
        {
            Last = Next(Last);
        }
        Next(Last) = P;
    }
}

void DelP(List *L, infotype X)
{
    address P = Search(*L, X);
    if (P != Nil)
    {
        if (P == First(*L))
        {
            DelFirst(L, &P);
        }
        else
        {
            address Prec = SearchPrec(*L, X);
            Next(Prec) = Next(P);
        }
        DeAlokasi(P);
    }
}

void PrintInfo(List L)
{
    if (First(L) == Nil)
    {
        printf("List Kosong\n");
    }
    else
    {
        address P = First(L);
        while (P != Nil)
        {
            printf("%s ", Info(P));
            P = Next(P);
        }
        printf("\n");
    }
}

int NbElmt(List L)
{
    int count = 0;
    address P = First(L);
    while (P != Nil)
    {
        count++;
        P = Next(P);
    }
    return count;
}

void DelAll(List *L)
{
    address P;
    while (!ListEmpty(*L))
    {
        DelFirst(L, &P);
        DeAlokasi(P);
    }
}

