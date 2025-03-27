#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Tipe data untuk informasi dalam node
typedef int infotype;

// Tipe data pointer untuk node
typedef struct tElmtlist *address;

// Struktur Node (elemen dari linked list)
typedef struct tElmtlist {
    infotype info;   // Data yang disimpan (bilangan)
    address next;    // Pointer ke node selanjutnya
} ElmtList;

// Struktur Linked List
typedef struct {
    address First;   // Pointer ke elemen pertama dalam list
} LinkedList;

// Prosedur & Fungsi Dasar Linked List
void createList(LinkedList *L);             // Inisialisasi list kosong
address allocate(infotype X);               // Alokasi node baru dengan data X
bool isEmpty(LinkedList L);                 // Cek apakah list kosong

void insertFirst(LinkedList *L, infotype X);  // Insert elemen X di awal list
void insertLast(LinkedList *L, infotype X);   // Insert elemen X di akhir list
void insertAfter(LinkedList *L, infotype X, infotype Y); // Insert elemen X setelah elemen Y

void deleteFirst(LinkedList *L);            // Hapus elemen pertama
void deleteLast(LinkedList *L);             // Hapus elemen terakhir
void deleteNode(LinkedList *L, infotype X);   // Hapus elemen dengan nilai X
void deleteAllOdd(LinkedList *L);           // Hapus semua elemen bilangan ganjil

void printList(LinkedList L);               // Tampilkan isi linked list

// Fungsi/Prosedur Tambahan
bool searchValue(LinkedList L, infotype X);     // Cari apakah nilai X ada di list
void modifyFirst(LinkedList *L, infotype newVal); // Ubah nilai elemen pertama menjadi newVal
void modifyLast(LinkedList *L, infotype newVal);  // Ubah nilai elemen terakhir menjadi newVal
bool modifyBetween(LinkedList *L, infotype oldVal, infotype newVal); // Ubah kemunculan pertama oldVal menjadi newVal
int countValue(LinkedList L, infotype X);         // Hitung jumlah kemunculan nilai X
int sumAll(LinkedList L);                         // Jumlahkan seluruh nilai dalam list
bool swapValue(LinkedList *L, infotype val1, infotype val2); // Tukar isi dua node yang memiliki nilai val1 dan val2

#endif

