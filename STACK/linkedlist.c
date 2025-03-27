#include "LinkedList.h"

// =================== FUNGSI/PROSEDUR DASAR LINKED LIST ===================

// Membuat list kosong (inisialisasi) Digunakan dalam stack
void createList(LinkedList *L) {
    L->First = NULL;
}

// Mengecek apakah list kosong Digunakan dalam stack
boolean isEmpty(LinkedList L) {
    return (L.First == NULL);
}

// Alokasi memori untuk node baru dengan nilai X Digunakan dalam stack
address allocate(infotype X) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P != NULL) {
        P->info = X;    // Set data dengan nilai X
        P->next = NULL; // Inisialisasi pointer next dengan NULL
    } else {
        printf("ERROR: Alokasi memori gagal, insertion ditolak!\n");
    }
    return P;
}

// Insert elemen di awal list Digunakan dalam stack sebagai push()
void insertFirst(LinkedList *L, infotype X) {
    address P = allocate(X);
    if (P != NULL) {
        P->next = L->First;
        L->First = P;
    }
}

// Hapus elemen pertama Digunakan dalam stack sebagai pop()
void deleteFirst(LinkedList *L) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, deleteFirst ditolak!\n");
        return;
    }
    address P = L->First;
    L->First = P->next;
    free(P);
}

// Cetak isi list Digunakan dalam stack untuk menampilkan isi stack
void printList(LinkedList L) {
    address P = L.First;
    printf("Linked List: ");
    while (P != NULL) {
        printf("%d -> ", P->info);
        P = P->next;
    }
    printf("NULL\n");
}

// =================== FUNGSI LAIN (TIDAK DIGUNAKAN DI STACK) ===================

// Insert elemen di akhir list Tidak digunakan dalam stack, tapi tetap dipertahankan
void insertLast(LinkedList *L, infotype X) {
    address P = allocate(X);
    if (P == NULL) return;
    
    if (isEmpty(*L)) {
        L->First = P;
    } else {
        address temp = L->First;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = P;
    }
}

// Insert elemen X setelah elemen yang bernilai Y Tidak digunakan dalam stack
void insertAfter(LinkedList *L, infotype X, infotype Y) {
    address P = allocate(X);
    if (P == NULL) return;
    
    address temp = L->First;
    while (temp != NULL && temp->info != Y)
        temp = temp->next;
    
    if (temp != NULL) {
        P->next = temp->next;
        temp->next = P;
    } else {
        printf("ERROR: Elemen %d tidak ditemukan, insertAfter ditolak!\n", Y);
        free(P);
    }
}

// Hapus elemen terakhir Tidak digunakan dalam stack
void deleteLast(LinkedList *L) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, deleteLast ditolak!\n");
        return;
    }
    address P = L->First, prev = NULL;
    while (P->next != NULL) {
        prev = P;
        P = P->next;
    }
    if (prev == NULL)
        L->First = NULL;
    else
        prev->next = NULL;
    
    free(P);
}

// Hapus elemen dengan nilai X Tidak digunakan dalam stack
void deleteNode(LinkedList *L, infotype X) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, deleteNode(%d) ditolak!\n", X);
        return;
    }
    address P = L->First, prev = NULL;
    while (P != NULL && P->info != X) {
        prev = P;
        P = P->next;
    }
    if (P != NULL) {
        if (prev == NULL)
            L->First = P->next;
        else
            prev->next = P->next;
        free(P);
    } else {
        printf("ERROR: Elemen %d tidak ditemukan, deleteNode ditolak!\n", X);
    }
}

// =================== FUNGSI TAMBAHAN (TIDAK DIGUNAKAN DI STACK) ===================

// 1. Cari apakah nilai X ada di dalam list Tidak digunakan dalam stack
boolean searchValue(LinkedList L, infotype X) {
    address p = L.First;
    while (p != NULL) {
        if (p->info == X)
            return true;
        p = p->next;
    }
    return false;
}

// 2. Ubah nilai elemen pertama menjadi newVal Tidak digunakan dalam stack
void modifyFirst(LinkedList *L, infotype newVal) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, modifyFirst ditolak!\n");
        return;
    }
    L->First->info = newVal;
}

// 3. Ubah nilai elemen terakhir menjadi newVal Tidak digunakan dalam stack
void modifyLast(LinkedList *L, infotype newVal) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, modifyLast ditolak!\n");
        return;
    }
    address p = L->First;
    while (p->next != NULL)
        p = p->next;
    p->info = newVal;
}

// 4. Tukar isi (info) dari dua node yang memiliki nilai val1 dan val2 Tidak digunakan dalam stack
boolean swapValue(LinkedList *L, infotype val1, infotype val2) {
    if (val1 == val2) {
        printf("Kedua nilai sama, swap tidak diperlukan.\n");
        return false;
    }
    address p1 = NULL, p2 = NULL;
    address p = L->First;
    while (p != NULL) {
        if (p->info == val1 && p1 == NULL)
            p1 = p;
        else if (p->info == val2 && p2 == NULL)
            p2 = p;
        p = p->next;
    }
    if (p1 == NULL || p2 == NULL) {
        printf("ERROR: Elemen %d atau %d tidak ditemukan, swap ditolak!\n", val1, val2);
        return false;
    }
    infotype temp = p1->info;
    p1->info = p2->info;
    p2->info = temp;
    return true;
}

