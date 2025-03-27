/* File : list1.c */
/* Deskripsi : Body ADT Linked list yang hanya dikenali First(L) */
/* Dibuat oleh : Ade Chandra Nugraha */
/* Tanggal : 24-10-2001 */
#include <limits.h>
#include <stdlib.h>
#include "list1.h"

/********** BODY SUB PROGRAM ***********/

/**** Predikat untuk test keadaan LIST ****/
boolean ListEmpty(List L)
/* Mengirim true jika List Kosong */
{
    return (First(L) == Nil);
}

/**** Konstruktor/Kreator List Kosong ****/
void CreateList(List *L)
/* IS : L sembarang */
/* FS : Terbentuk List Kosong */
{
    First(*L) = Nil;
}

/**** Manajemen Memory ****/

address Alokasi(infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address != Nil, */
/* dan misalnya menghasilkan P, maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    P = (address)malloc(sizeof(ElmtList));
    if (P != Nil) /* Alokasi berhasil */
    {
        Info(P) = X;
        Next(P) = Nil;
    }
    return (P);
}

void DeAlokasi(address P)
/* IS : P terdefinisi */
/* FS : P dikembalikan ke sistem */
/* Melakukan dealokasi / pengembalian address P ke system */
{
    if (P != Nil)
    {
        free(P);
    }
}

/**** Pencarian sebuah elemen List ****/

address Search(List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address elemen tsb. */
/* Jika tidak ada, mengirimkan Nil */
/* Menggunakan variabel bertype boolean */
{
    /* Kamus Lokal */
    address P;
    boolean found = false;
    /* algoritma */
    P = First(L);
    while ((P != Nil) && (!found))
    {
        if (Info(P) == X)
        {
            found = true;
        }
        else
        {
            P = Next(P);
        }
    } /* P = Nil atau Ketemu */
    return (P);
}

boolean FSearch(List L, address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    /* Kamus Lokal */
    boolean found = false;
    address PSearch;
    /* Algortima */
    PSearch = First(L);
    while ((PSearch != Nil) && (!found))
    {
        if (PSearch == P)
        {
            found = true;
        }
        else
        {
            PSearch = Next(PSearch);
        }
    } /* PSearch = Nil atau Ketemu */
    return (found);
}

address SearchPrec(List L, infotype X)
/* Mengirimkan address elemen sebelum elemen yang nilainya = X */
/* Mencari apakah ada elemen list dengan Info(P) = X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec) = P dan Info(P) = X */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec = Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
    /* Kamus Lokal */
    address Prec, P;
    boolean found = false;
    /* Algoritma */
    Prec = Nil;
    P = First(L);
    while ((P != Nil) && (!found))
    {
        if (Info(P) == X)
        {
            found = true;
        }
        else
        {
            Prec = P;
            P = Next(P);
        }
    } /* P = Nil atau Ketemu */
    if (found)
    {
        return (Prec);
    }
    else
    {
        return (Nil);
    }
}

/**** PRIMITIF BERDASARKAN NILAI ****/

/**** Penambahan Elemen ****/
void InsVFirst(List *L, infotype X)
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    /* Kamus Lokal */
    address P;
    /* Aloritma */
    P = Alokasi(X);
    if (P != Nil)
    {
        InsertFirst(&(*L), P);
    }
}

void InsVLast(List *L, infotype X)
/* IS : L mungkin Kosong */
/* FS : melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir (elemen terakhir adalah yang baru) */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal IS = FS */
{
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    P = Alokasi(X);
    if (P != Nil)
    {
        InsertLast(&(*L), P);
    }
}

/**** Penghapusan Elemen ****/

void DelVFirst(List *L, infotype *X)
/* IS : L TIDAK Kosong */
/* FS : Elemen pertama List dihapus, nilai info disimpan ke X */
/* dan alamat elemen pertama di dealokasi */
{
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    P = First(*L);
    *X = Info(P);
    First(*L) = Next(First(*L));
    DeAlokasi(P);
}

void DelVLast(List *L, infotype *X)
/* IS : L TIDAK Kosong */
/* FS : Elemen terakhir list dihapus : nilai info disimpan pada X */
/* dan alamat elemen terakhir di dealokasi */
{
    /* Kamus Lokal */
    address PDel;
    /* Algoritma */
    PDel = First(*L);
    DelLast(&(*L), &PDel);
    (*X) = Info(PDel);
    DeAlokasi(PDel);
}

/**** PRIMITIF BERDASARKAN ALAMAT ****/

/**** Penambahan elemen berdasarkan alamat ****/
void InsertFirst(List *L, address P)
/* IS : L sembarang, P sudah dialokasi */
/* FS : menambahkan elemen ber-address P sebagai elemen pertama */
{
    Next(P) = First(*L);
    First(*L) = P;
}

void InsertAfter(List *L, address P, address Prec)
/* IS : Prec pastilah elemen List dan bukan elemen terakhir */
/* P sudah dialokasi */
/* FS : Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

void InsertLast(List *L, address P)
/* IS : L sembarang, P sudah dialokasi */
/* FS : P ditambahkan sebagai elemen terakhir yang baru */
{
    /* Kamus Lokal */
    address Last;
    /* Algoritma */
    if (First(*L) != Nil)
    {
        Last = First(*L);
        while (Next(Last) != Nil)
        {
            Last = Next(Last);
        }
        Next(Last) = P;
    }
    else
    {
        First(*L) = P;
    }
}

/**** Penghapusan sebuah elemen ****/

void DelFirst(List *L, address *P)
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen pertama list sebelum penghapusan */
/* elemen list berkurang satu (mungkin menjadi kosong) */
/* First elemen yang baru adalah suksessor elemen pertama yang lama */

{
    *P = First(*L);
    First(*L) = Next(First(*L));
}

void DelP(List *L, infotype X)
/* IS : L sembarang */
/* FS : Jika ada elemen list beraddress P, dengan Info(P) = X */
/* Maka P dihapus dari list dan di dealokasi */
/* Jika tidak ada elemen list dengan Info(P) = X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    /* Kamus Lokal */
    address P, Prec;
    boolean found = false;
    /* Algoritma */
    Prec = Nil;
    P = First(*L);
    while ((P != Nil) && (!found))
    {
        if (Info(P) == X)
        {
            found = true;
        }
        else
        {
            Prec = P;
            P = Next(P);
        }
    } /* P = Nil Atau Ketemu */
    if (found)
    {
        if (Prec == Nil && Next(P) == Nil) /* Hanya 1 elemen */
        {
            First(*L) = Nil;
        }
        else if (Prec == Nil) /* Ketemu di elemen 1*/
        {
            First(*L) = Next(P);
        }
        else /* Ketemu di elemen list yang ditengah/akhir */
        {
            Next(Prec) = Next(P);
        }
        Next(P) = Nil;
        DeAlokasi(P);
    }
}

void DelLast(List *L, address *P)
/* IS : L TIDAK kosong */
/* FS : P adalah alamat elemen terakhir list sebelum penghapusan */
/* Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last elemen baru adalah predesessor elemen terakhir yang lama, jika ada */
{
    /* Kamus Lokal */
    address Prec;
    /* Algoritma */
    *P = First(*L);
    Prec = Nil;
    while (Next(*P) != Nil)
    {
        Prec = *P;
        *P = Next(*P);
    }
    if (Prec == Nil) /* Hanya 1 elemen */
    {
        First(*L) = Nil;
    }

    else /* List Lebih dari 1 elemen */
    {
        Next(Prec) = Nil;
    }
}

void DelAfter(List *L, address *Pdel, address Prec)
/* IS : L TIDAK Kosong, Prec adalah anggota List */
/* FS : menghapus Next(Prec): Pdel adalah alamat elemen list yang dihapus */
{
    *Pdel = Next(Prec);
    if (Pdel != Nil)
    {
        Next(Prec) = Next(*Pdel);
        Next(*Pdel) = Nil;
    }
}

/**** PROSES SEMUA ELEMEN LIST ****/

void PrintInfo(List L)
/* IS : L mungkin kosong */
/* FS : Jika List tidak kosong, semua info yang disimpan pada elemen list */
/* diprint. Jika list kosong, hanya menuliskan "List Kosong" */
{
    /* Kamus Lokal */
    address P;
    /* Algoritma */
    if (First(L) == Nil)
    {
        printf("List Kosong .... \a\n");
    }
    else /* List memiliki elemen */
    {
        P = First(L);
        for (;;)
        {
            if (P == Nil)
            {
                printf("\n");
                break;
            }
            else /* Belum berada di akhir List */
            {
                printf("%d ", Info(P));
                P = Next(P);
            }
        }
    }
}

int NbElmt(List L)
/* Mengirimkan banyaknya elemen list, mengirimkan 0 jika list kosong */
{
    /* Kamus Lokal */
    int Jml = 0;
    address P;
    /* Algoritma */
    if (First(L) != Nil)
    {
        P = First(L);

        for (;;)
        {
            if (P == Nil)
            {
                break;
            }
            else /* Belum berada di akhir List */
            {
                Jml++;
                P = Next(P);
            }
        } /* P = Nil */
    }
    return (Jml);
}

infotype Max(List L)
/* Mengirimkan nilai Info(P) yang maksimum */
{
    /* Kamus Lokal */
    int Maks = INT_MIN;
    address P;
    /* Algoritma */
    if (First(L) != Nil)
    {
        P = First(L);
        for (;;)
        {
            if (P == Nil)
            {
                break;
            }
            else /* Belum berada di akhir List */
            {
                if (Maks < Info(P))
                {
                    Maks = Info(P);
                }
                P = Next(P);
            }
        } /* P = Nil */
    }
    return (Maks);
}

address AdrMax(List L)
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
{
    /* Kamus Lokal */
    address P;
    infotype X;
    /* Algoritma */
    X = Max(L);
    if (X != INT_MIN)
    {
        P = Search(L, X);
    }
    else
    {
        P = Nil;
    }
    return (P);
}

infotype Min(List L)
/* Mengirimkan nilai Info(P) yang minimum */
{
    /* Kamus Lokal */
    int Minimal = INT_MAX;
    address P;

    /* Algoritma */
    if (First(L) != Nil)
    {
        P = First(L);
        for (;;)
        {
            if (P == Nil)
            {
                break;
            }
            else /* Belum berada di akhir List */
            {
                if (Minimal > Info(P))
                {
                    Minimal = Info(P);
                }
                P = Next(P);
            }
        } /* P = Nil */
    }
    return (Minimal);
}

address AdrMin(List L)
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
{
    /* Kamus Lokal */
    address P;
    infotype X;
    /* Algoritma */
    X = Min(L);
    if (X != INT_MAX)
    {
        P = Search(L, X);
    }
    else
    {
        P = Nil;
    }
    return (P);
}

infotype Average(List L)
/* Mengirimkan nilai rata-rata Info(P) */
{
    /* Kamus lokal */
    int Jml = 0;
    int Acc = 0;
    address P;
    /* Algoritma */
    if (First(L) != Nil)
    {
        P = First(L);
        for (;;)
        {
            if (P == Nil)
            {
                break;
            }
            else /* Belum berada di akhir List */
            {
                Acc = Acc + Info(P);
                Jml++;
                P = Next(P);
            }
        } /* P = Nil */
    }
    if (Jml > 0)
    {
        Jml = (int)Acc / Jml;
    }
    return (Jml);
}

/***************************************/
/******* PROSES TERHADAP LIST ********/
/***************************************/

void DelAll(List *L)
/* Delete semua elemen list dan alamat elemen di dealokasi */
{
    /* Kamus Lokal */
    address PDel;
    /* Algoritma */
    PDel = First(*L);
    while (PDel != Nil)
    {
        DelFirst(&(*L), &PDel);
        DeAlokasi(PDel);
        PDel = First(*L);
    }
}

void InversList(List *L)
/* IS : L sembarang */
/* FS : Elemen List dibalik : elemen terakhir menjadi elemen pertama, dst */
/* Membalik elemen list, tanpa melakukan alokasi / dealokasi */
{
    /* Kamus Lokal */
    address P, PNew;
    List Temp;
    /* Algoritma */
    CreateList(&Temp);
    P = First(*L);
    while (P != Nil)
    {
        PNew = P;
        P = Next(P);
        First(*L) = P;
        Next(PNew) = Nil;
        InsertFirst(&Temp, PNew);
    } /* P = Nil */
    First(*L) = First(Temp);
}

List FInversList(List L)
/* Mengirimkan list baru, hasil invers dari L */
{
    /* Kamus Lokal */
    int Jml;
    List Temp;
    infotype X;
    boolean gagal = false;
    address P;
    /* Algoritma */
    CreateList(&Temp);
    P = First(L);
    while ((P != Nil) && (!gagal))
    {
        Jml = NbElmt(Temp);
        X = Info(P);
        InsVFirst(&Temp, X);
        if (Jml != NbElmt(Temp))
        {
            P = Next(P);
        }
        else /* Gagal Alokasi */
        {
            gagal = true;
        }
    } /* P = nil atau Gagal Alokasi */
    if (gagal)
    {
        DelAll(&Temp);
    }
    return (Temp);
}

void CopyList(List L1, List *L2)
/* IS : L1 sembarang */
/* FS : L2 = l1 */
/* L1 dan L2 "menunjuk" ke list yang sama, Tidak ada alokasi / dealokasi */
{
    CreateList(&(*L2));
    First(*L2) = First(L1);
}

List FCopyList(List L)
/* Mengirimkan List yang merupakan salinan L */
{
    /* Kamus Lokal */
    int Jml;
    infotype X;
    List Temp;
    boolean gagal = false;
    address P;
    /* Algoritma */
    CreateList(&Temp);
    P = First(L);
    while ((P != Nil) && (!gagal))
    {
        Jml = NbElmt(Temp);
        X = Info(P);
        InsVLast(&Temp, X);
        if (Jml != NbElmt(Temp))
        {
            P = Next(P);
        }
        else /* Gagal Alokasi */
        {
            gagal = true;
        }
    } /* P = nil atau Gagal Alokasi */
    if (gagal)
    {
        DelAll(&Temp);
    }
    return (Temp);
}

void CpAlokList(List Lin, List *Lout)
/* IS : Lin Sembarang */
/* FS : Jika semua alokasi berhasi, maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout = Nil dan semua elemen yang */
/* terlanjur di alokasi, maka didealokasikan */
/* Dengan melakukan alokasi elemen */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */
{
    /* Kamus Lokal */
    boolean berhasil = true;
    address P, PNew;
    infotype X;
    /* algoritma */
    CreateList(&(*Lout));
    P = First(Lin);

    while ((P != Nil) && (berhasil))
    {
        X = Info(P);
        PNew = Alokasi(X);
        if (PNew != Nil) /* Alokasi berhasil */
        {
            InsertLast(&(*Lout), PNew);
            P = Next(P);
        }
        else /* Alokasi Gagal */
        {
            berhasil = false;
        }
    } /* P = nil atau Gagal Alokasi */
    if (!berhasil)
    {
        DelAll(&(*Lout));
    }
}

void Konkat(List L1, List L2, List *L3)
/* IS : L1 dan L2 sembarang */
/* FS : L1 dan L2 tetap, L3 adalah hasil konkatenansi L1 dan L2 */
/* Jika semua alokasi berhasil , maka L3 adalah hasil konkatenasi */
/* Jika ada alokasi gagal, semua elemen yang sudah di alokasi harus */
/* di dealokasi dan L3 = Nil */
/* Konkatenasi dua buah list : L1 dan L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang "baru". Jika ada alokasi yang */
/* GAGAL, maka L3 harus bernilai nil dan semua elemen yang pernah di */
/* alokasi didealokasi */
{
    /* Kamus Lokal */
    boolean L1_ada = false;
    boolean gagal = false;
    infotype X;
    address P, PNew;
    /* Algoritma */
    if (!ListEmpty(*L3))
    {
        DelAll(&(*L3));
    }
    if (!ListEmpty(L1))
    {
        L1_ada = true;
        CpAlokList(L1, &(*L3));
        if (First(*L3) == Nil) /* Gagal Alokasi */
        {
            gagal = true;
        }
    }
    if (!ListEmpty(L2) && (!gagal))
    {
        if (L1_ada)
        {
            P = First(L2);
            while ((P != Nil) && (!gagal))
            {
                X = Info(P);
                PNew = Alokasi(X);
                if (PNew != Nil) /* Alokasi berhasil */
                {
                    InsertLast(&(*L3), PNew);
                    P = Next(P);
                }
                else /* Alokasi Gagal */
                {
                    gagal = false;
                }

            } /* P = nil atau Gagal Alokasi */
        }
        else
        {
            CpAlokList(L2, &(*L3));
            if (First(*L3) == Nil) /* Gagal Alokasi */
            {
                gagal = true;
            }
        }
    }
    if (gagal)
    {
        DelAll(&(*L3));
    }
}

void Konkat1(List *L1, List *L2, List *L3)
/* IS : L1 dan L2 sembarang */
/* FS : L1 dan L2 kosong, L3 adalah hasil konkatenansi L1 dan L2 */
/* Konkatenasi dua buah List L1 dan L2; menghasilkan L3 yang baru */
/* (dengan elemen List L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong */
/* Tidak ada alokasi / dealokasi pada procedure ini */
{
    /* Kamus Lokal */
    address P, P_L3;
    /* algoritma */
    if (!ListEmpty(*L3))
    {
        DelAll(&(*L3));
    }
    if (!ListEmpty(*L1))
    {
        First(*L3) = First(*L1);
        First(*L1) = Nil;
    }
    if (!ListEmpty(*L2))
    {
        P = First(*L2);
        InsertLast(&(*L3), P);
        First(*L2) = Nil;
    }
}

void PecahList(List *L1, List *L2, List L)
/* IS : L mungkin kosong */
/* FS : berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah : untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil , maka separuh adalah NbElmt (L) div 2 */
{
    /* Kamus Lokal */
    int Jml, i;
    address P;
    boolean gagal = false;
    infotype X;
    /* algoritma */
    if (First(L) != Nil) /* L tidak kosong */
    {
        CreateList(&(*L1));
        P = First(L);
        i = 1;

        while ((i <= NbElmt(L) / 2) && (!gagal))
        {
            Jml = NbElmt(*L1);
            X = Info(P);
            InsVLast(&(*L1), X);
            if (Jml != NbElmt(*L1))
            {
                P = Next(P);
                i++;
            }
            else /* Alokasi Gagal */
            {
                gagal = true;
            }
        } /* Sudah setengah jml elemen L atau gagal Alokasi */
        if (!gagal)
        {
            CreateList(&(*L2));
            while ((P != Nil) && (!gagal))
            {
                Jml = NbElmt(*L2);
                X = Info(P);
                InsVLast(&(*L2), X);
                if (Jml != NbElmt(*L2))
                {
                    P = Next(P);
                }
                else /* Alokasi Gagal */
                {
                    gagal = true;
                }
            } /* P = Nil untuk List L atau Gagal alokasi */
        }
        if (gagal)
        {
            DelAll(&(*L1));
            DelAll(&(*L2));
        }
    }
}
