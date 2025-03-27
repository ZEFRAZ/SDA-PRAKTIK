#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data Mahasiswa
typedef struct {
    char nama[50];
    int nilaiUTS;
} Mahasiswa;

// Struktur Node pada linked list
typedef struct tElmtList *address;
typedef struct tElmtList {
    Mahasiswa info;
    address next;
} ElmtList;

// Struktur List
typedef struct {
    address First;
} List;

// Fungsi untuk membuat dan menghapus list
void CreateList(List *L);
void DeleteList(List *L);       // Hapus list dan tampilkan pesan penghapusan
void DeleteListSilent(List *L); // Hapus list tanpa menampilkan pesan

// Validator
int IsEmpty(List L);

// Fungsi untuk membuat node (alokasi memori) dan mengisi node dengan data
void Create_Node(address *P);
void Fill_Node(address P, char *nama, int nilaiUTS);

// Fungsi penyisipan data ke list
void InsertAscending(List *L, Mahasiswa m);
void InsertDescendingByNilai(List *L, Mahasiswa m);

// Fungsi utilitas untuk menampilkan, menghitung, menyalin, dan menghapus duplikat
void PrintList(List L);
int CountElements(List L);
void CopyList(List *L1, List *L2, int threshold);
void RemoveDuplicates(List *L);

#endif // MAHASISWA_H

