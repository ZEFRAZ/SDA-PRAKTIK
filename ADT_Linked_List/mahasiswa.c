#include "mahasiswa.h"

// Membuat list kosong
void CreateList(List *L) {
    L->First = NULL;
}

// Menghapus list dan menampilkan pesan penghapusan tiap node
void DeleteList(List *L) {
    address P = L->First;
    while (P != NULL) {
        printf("Menghapus: %s dengan nilai %d\n", P->info.nama, P->info.nilaiUTS);
        address Q = P;
        P = P->next;
        free(Q);
    }
    L->First = NULL;
}

// Menghapus list tanpa menampilkan pesan (untuk list sementara)
void DeleteListSilent(List *L) {
    address P = L->First;
    while (P != NULL) {
        address Q = P;
        P = P->next;
        free(Q);
    }
    L->First = NULL;
}

// Mengecek apakah list kosong
int IsEmpty(List L) {
    return L.First == NULL;
}

// Mengalokasikan memori untuk node baru
void Create_Node(address *P) {
    *P = (address) malloc(sizeof(ElmtList));
}

// Mengisi node dengan data mahasiswa
void Fill_Node(address P, char *nama, int nilaiUTS) {
    if (P != NULL) {
        strcpy(P->info.nama, nama);
        P->info.nilaiUTS = nilaiUTS;
        P->next = NULL;
    }
}

// Menyisipkan data ke list secara ascending berdasarkan nama
void InsertAscending(List *L, Mahasiswa m) {
    address P;
    Create_Node(&P);
    if (P == NULL) {
        printf("Alokasi memori gagal\n");
        return;
    }
    Fill_Node(P, m.nama, m.nilaiUTS);
    if (IsEmpty(*L) || strcmp(m.nama, L->First->info.nama) < 0) {
        P->next = L->First;
        L->First = P;
    } else {
        address Q = L->First;
        while (Q->next != NULL && strcmp(Q->next->info.nama, m.nama) < 0) {
            Q = Q->next;
        }
        P->next = Q->next;
        Q->next = P;
    }
}

// Menyisipkan data ke list secara descending berdasarkan nilai
void InsertDescendingByNilai(List *L, Mahasiswa m) {
    address P;
    Create_Node(&P);
    if (P == NULL) {
        printf("Alokasi memori gagal\n");
        return;
    }
    Fill_Node(P, m.nama, m.nilaiUTS);
    if (IsEmpty(*L) || m.nilaiUTS > L->First->info.nilaiUTS) {
        P->next = L->First;
        L->First = P;
    } else {
        address Q = L->First;
        while (Q->next != NULL && Q->next->info.nilaiUTS > m.nilaiUTS) {
            Q = Q->next;
        }
        P->next = Q->next;
        Q->next = P;
    }
}

// Menampilkan isi list
void PrintList(List L) {
    address P = L.First;
    while (P != NULL) {
        printf("Nama: %s, Nilai UTS: %d\n", P->info.nama, P->info.nilaiUTS);
        P = P->next;
    }
}

// Menghitung jumlah elemen dalam list
int CountElements(List L) {
    int count = 0;
    address P = L.First;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

// Menyalin elemen dari L1 ke L2 jika nilaiUTS > threshold
void CopyList(List *L1, List *L2, int threshold) {
    address P = L1->First;
    while (P != NULL) {
        if (P->info.nilaiUTS > threshold) {
            InsertAscending(L2, P->info);
        }
        P = P->next;
    }
}

// Menghapus duplikat nama dari list (asumsi list terurut berdasarkan nama)
void RemoveDuplicates(List *L) {
    address P = L->First;
    while (P != NULL && P->next != NULL) {
        if (strcmp(P->info.nama, P->next->info.nama) == 0) {
            address Q = P->next;
            P->next = Q->next;
            free(Q);
        } else {
            P = P->next;
        }
    }
}

