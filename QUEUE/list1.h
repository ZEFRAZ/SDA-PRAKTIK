/* File : list1.h */
/* Deskripsi : ADT list berkait dengan representasi fisik pointer */
/* Representasi address dengan pointer */
/* InfoType adalah integer */
/* Dibuat oleh : Ade Chandra Nugraha, Tanggal : 24-10-2001 */
#ifndef list1_H
#define list1_H
#include "boolean.h"
#include <stdio.h>
#define Nil NULL
#define Info(P) (P)->info
#define Next(P) (P)->next
#define First(L) (L).First
typedef int infotype;
typedef struct tElmtList *address;
typedef struct tElmtList
{
    infotype info;
    address next;
} ElmtList;
/* Definisi list : */
/* List kosong ===> First(L) = Nil */
/* Setiap elemen dengan address P dapat diacu info(P) dan Next(P); */
/* Elemen terakhir list ===> Jika addressnya Last maka Next(Last) = Nil */
typedef struct
{
    address First;
} List;
/*********** PROTOTYPE ****************/

/**** Predikat untuk test keadaan LIST ****/

boolean ListEmpty(List L);
/* Mengirim true jika List Kosong */

/**** Konstruktor/Kreator List Kosong ****/

void CreateList(List *L);
/* IS : L sembarang */
/* FS : Terbentuk List Kosong */
/**** Manajemen Memory ****/

address Alokasi(infotype X);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address != Nil, */
/* dan misalnya menghasilkan P, maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DeAlokasi(address P);
/* IS : P terdefinisi */
/* FS : P dikembalikan ke sistem */
/* Melakukan dealokasi / pengembalian address P ke system */

/**** Pencarian sebuah elemen List ****/

address Search(List L, infotype X);
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address elemen tsb. */
/* Jika tidak ada, mengirimkan Nil */

boolean FSearch(List L, address P);
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */

address SearchPrec(List L, infotype X);
/* Mengirimkan address elemen sebelum elemen yang nilainya = X */
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec) = P dan Info(P) = X */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec = Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */

/**** PRIMITIF BERDASARKAN NILAI ****/

/**** Penambahan Elemen ****/

void InsVFirst(List *L, infotype X);
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void InsVLast(List *L, infotype X);
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir (elemen terakhir adalah yang baru) */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal IS = FS */

/**** Penghapusan Elemen ****/

void DelVFirst(List *L, infotype *X);
/* IS : L TIDAK Kosong */
/* FS : Elemen pertama List dihapus, nilai info disimpan ke X */
/* dan alamat elemen pertama di dealokasi */

void DelVLast(List *L, infotype *X);
/* IS : L TIDAK Kosong */
/* FS : Elemen terakhir list dihapus : nilai info disimpan pada X */
/* dan alamat elemen terakhir di dealokasi */
/**** PRIMITIF BERDASARKAN ALAMAT ****/
/**** Penambahan elemen berdasarkan alamat ****/

void InsertFirst(List *L, address P);
/* IS : L sembarang, P sudah dialokasi */
/* FS : menambahkan elemen ber-address P sebagai elemen pertama */

void InsertAfter(List *L, address P, address Prec);
/* IS : Prec pastilah elemen List dan bukan elemen terakhir */
/* P sudah dialokasi */
/* FS : Insert P sebagai elemen sesudah elemen beralamat Prec */

void InsertLast(List *L, address P);
/* IS : L sembarang, P sudah dialokasi */
/* FS : P ditambahkan sebagai elemen terakhir yang baru */

/****Penghapusan sebuah elemen ****/

void DelFirst(List *L, address *P);
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen pertama list sebelum penghapusan */
/* elemen list berkurang satu (mungkin menjadi kosong) */
/* First elemen yang baru adalah suksessor elemen pertama yang lama */

void DelP(List *L, infotype X);
/* IS : L sembarang */
/* FS : Jika ada elemen list beraddress P, dengan Info(P) = X */
/* Maka P dihapus dari list dan di dealokasi */
/* Jika tidak ada elemen list dengan Info(P) = X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

void DelLast(List *L, address *P);
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen terakhir list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last elemen baru adalah predesessor elemen terakhir yang lama, jika ada */

void DelAfter(List *L, address *Pdel, address Prec);
/* IS : L TIDAK Kosong, Prec adalah anggota List */
/* FS : menghapus Next(Prec): Pdel adalah alamat elemen list yang dihapus */

/**** PROSES SEMUA ELEMEN LIST ****/

void PrintInfo(List L);
/* IS : L mungkin kosong */
/* FS : Jika List tidak kosong, semua info yang disimpan pada elemen list */
/* diprint. Jika list kosong, hanya menuliskan "List Kosong" */

int NbElmt(List L);
/* Mengirimkan banyaknya elemen list, mengirimkan 0 jika list kosong */

infotype Max(List L);
/* Mengirimkan nilai Info(P) yang maksimum */

address AdrMax(List L);
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */

infotype Min(List L);
/* Mengirimkan nilai Info(P) yang minimum */

address AdrMin(List L);
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */

infotype Average(List L);
/* Mengirimkan nilai rata-rata Info(P) */

/***************************************/
/******* PROSES TERHADAP LIST ********/
/***************************************/
void DelAll(List *L);
/* Delete semua elemen list dan alamat elemen di dealokasi */

void InversList(List *L);
/* IS : L sembarang */
/* FS : Elemen List dibalik : elemen terakhir menjadi elemen pertama, dst */
/* Membalik elemen list, tanpa melakukan alokasi / dealokasi */

List FInversList(List L);
/* Mengirimkan list baru, hasil invers dari L */

void CopyList(List L1, List *L2);
/* IS : L1 sembarang */
/* FS : L2 = l1 */
/* L1 dan L2 "menunjuk" ke list yang sama, Tidak ada alokasi / dealokasi */

List FCopyList(List L);
/* Mengirimkan List yang merupakan salinan L */

void CpAlokList(List Lin, List *Lout);
/* IS : Lin Sembarang */
/* FS : Jika semua alokasi berhasi, maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout = Nil dan semua elemen yang */
/* terlanjur di alokasi, maka didealokasikan */
/* Dengan melakukan alokasi elemen */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */

void Konkat(List L1, List L2, List *L3);
/* IS : L1 dan L2 sembarang */
/* FS : L1 dan L2 tetap, L3 adalah hasil konkatenansi L1 dan L2 */
/* Jika semua alokasi berhasil , maka L3 adalah hasil konkatenasi */
/* Jika ada alokasi gagal, semua elemen yang sudah di alokasi harus */
/* di dealokasi dan L3 = Nil */
/* Konkatenasi dua buah list : L1 dan L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang "baru". Jika ada alokasi yang */
/* GAGAL, maka L3 harus bernilai nil dan semua elemen yang pernah di */
/* alokasi didealokasi */

void Konkat1(List *L1, List *L2, List *L3);
/* IS : L1 dan L2 sembarang */
/* FS : L1 dan L2 kosong, L3 adalah hasil konkatenansi L1 dan L2 */
/* Konkatenasi dua buah List L1 dan L2; menghasilkan L3 yang baru */
/* (dengan elemen List L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong */
/* Tidak ada alokasi / dealokasi pada procedure ini */

void PecahList(List *L1, List *L2, List L);
/* IS : L mungkin kosong */
/* FS : berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah : untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil , maka separuh adalah NbElmt (L) div 2 */

#endif
