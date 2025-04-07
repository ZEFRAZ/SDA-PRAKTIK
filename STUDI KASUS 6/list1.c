#include "list1.h"
#include <stdlib.h>

static boolean ListEmpty(List L) {
    return (L.First == Nil);
}

static void DelFirst(List *L, address *P) {
    *P = L->First;
    if (*P != Nil) {
        L->First = Next(*P);
        if (L->First != Nil) {
            L->First->prev = Nil;
        }
    }
}

void CreateList(List *L) {
    L->First = Nil;
}

address Alokasi(infotype X) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P == Nil) {
        fprintf(stderr, "Error: gagal mengalokasikan memori untuk node nama.\n");
        return Nil;
    }
    strcpy(Info(P), X);
    Next(P) = Nil;
    Prev(P) = Nil;
    return P;
}

void DeAlokasi(address P) {
    if (P != Nil) {
        free(P);
    }
}

address Search(List L, infotype X) {
    address P = L.First;
    while (P != Nil) {
        if (strcmp(Info(P), X) == 0)
            return P;
        P = Next(P);
    }
    return Nil;
}

address SearchPrec(List L, infotype X) {
    address P = L.First;
    while (P != Nil) {
        if (Next(P) != Nil && strcmp(Info(Next(P)), X) == 0)
            return P;
        P = Next(P);
    }
    return Nil;
}

void InsVLast(List *L, infotype X) {
    address P = Alokasi(X);
    if (P != Nil) {
        InsertLast(L, P);
    }
}

void InsertLast(List *L, address P) {
    if (L->First == Nil) {
        L->First = P;
    } else {
        address Last = L->First;
        while (Next(Last) != Nil) {
            Last = Next(Last);
        }
        Next(Last) = P;
        Prev(P) = Last;
    }
}

void DelP(List *L, infotype X) {
    address P = Search(*L, X);
    if (P != Nil) {
        if (P == L->First) {
            DelFirst(L, &P);
        } else {
            address prec = Prev(P);
            if (Next(P) != Nil) {
                Next(prec) = Next(P);
                Prev(Next(P)) = prec;
            } else {
                Next(prec) = Nil;
            }
        }
        DeAlokasi(P);
    }
}

void PrintInfo(List L) {
    if (L.First == Nil) {
        printf("List Kosong\n");
    } else {
        address P = L.First;
        while (P != Nil) {
            printf("%s ", Info(P));
            P = Next(P);
        }
        printf("\n");
    }
}

int NbElmt(List L) {
    int count = 0;
    address P = L.First;
    while (P != Nil) {
        count++;
        P = Next(P);
    }
    return count;
}

void DelAll(List *L) {
    address P;
    while (!ListEmpty(*L)) {
        DelFirst(L, &P);
        DeAlokasi(P);
    }
}

