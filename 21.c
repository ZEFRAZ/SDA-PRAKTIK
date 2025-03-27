/*----------------------------------------------------------------------------*/ 
/* File    	   : PTR21.cpp      
/* Deskripsi   : contoh deklarasi list dan pemakaian makro  
/* Dibuat oleh : Tim Dosen SDP      
/* Tanggal     : 13-09-2001      
/*----------------------------------------------------------------------------*/ 
#include <stdio.h>
#include <stdlib.h>

#define Nil NULL
#define info(P) ((P)->info)
#define next(P) ((P)->next)

/* Definisi tipe data untuk elemen linked list */
typedef int infotype;
typedef struct tElmtList *address;
typedef struct tElmtList {
    infotype info;
    address next;
} ElmtList;

int main() {
    /* Kamus */
    address First;
    address P, Q;

    /* Create list kosong */
    First = Nil;

    /* Alokasi, insert as first elemen (nilai 10) */
    P = (address) malloc(sizeof(ElmtList));
    info(P) = 10;
    next(P) = Nil;
    First = P;

    /* Alokasi, insert as first elemen (nilai 20) */
    Q = (address) malloc(sizeof(ElmtList));
    info(Q) = 20;
    next(Q) = Nil;   // Inisialisasi pointer next Q
    next(Q) = First; // Hubungkan Q ke list yang ada
    First = Q;       // Update First menjadi Q

    /* Alokasi, insert as first elemen (nilai 30) */
    P = (address) malloc(sizeof(ElmtList));
    info(P) = 30;
    next(P) = Nil;   // Inisialisasi pointer next P
    next(P) = First; // Hubungkan P ke list yang ada
    First = P;       // Update First menjadi P

    /* Menampilkan nilai elemen ketiga (30 -> 20 -> 10) */
    printf("%d\n", info(next(next(First))));

    return 0;
}
