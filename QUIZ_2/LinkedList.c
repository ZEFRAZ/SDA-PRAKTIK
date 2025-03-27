#include "LinkedList.h"

// =================== FUNGSI/PROSEDUR DASAR LINKED LIST ===================

// Membuat list kosong (inisialisasi)
void createList(LinkedList *L) {
    L->First = NULL;
}

// Mengecek apakah list kosong
bool isEmpty(LinkedList L) {
    return (L.First == NULL);
}

// Alokasi memori untuk node baru dengan nilai X
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

// Insert elemen di awal list
void insertFirst(LinkedList *L, infotype X) {
    address P = allocate(X);
    if (P != NULL) {
        P->next = L->First;
        L->First = P;
        printList(*L);
    }
}

// Insert elemen di akhir list
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
    printList(*L);
}

// Insert elemen X setelah elemen yang bernilai Y
void insertAfter(LinkedList *L, infotype X, infotype Y) {
    address P = allocate(X);
    if (P == NULL) return;
    
    address temp = L->First;
    // Cari node dengan info == Y
    while (temp != NULL && temp->info != Y)
        temp = temp->next;
    
    if (temp != NULL) {
        P->next = temp->next;
        temp->next = P;
        printList(*L);
    } else {
        printf("ERROR: Elemen %d tidak ditemukan, insertAfter ditolak!\n", Y);
        free(P);
    }
}

// Hapus elemen pertama
void deleteFirst(LinkedList *L) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, deleteFirst ditolak!\n");
        return;
    }
    address P = L->First;
    L->First = P->next;
    free(P);
    printList(*L);
}

// Hapus elemen terakhir
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
    printList(*L);
}

// Hapus elemen dengan nilai X
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
        printList(*L);
    } else {
        printf("ERROR: Elemen %d tidak ditemukan, deleteNode ditolak!\n", X);
    }
}

// Hapus semua elemen bilangan ganjil
void deleteAllOdd(LinkedList *L) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, deleteAllOdd ditolak!\n");
        return;
    }
    address P = L->First, prev = NULL, temp;
    while (P != NULL) {
        if (P->info % 2 != 0) { // Jika nilai ganjil
            temp = P;
            if (prev == NULL)
                L->First = P->next;
            else
                prev->next = P->next;
            P = P->next;
            free(temp);
        } else {
            prev = P;
            P = P->next;
        }
    }
    printList(*L);
}

// Cetak isi list
void printList(LinkedList L) {
    address P = L.First;
    printf("Linked List: ");
    while (P != NULL) {
        printf("%d -> ", P->info);
        P = P->next;
    }
    printf("NULL\n");
}

// =================== FUNGSI/PROSEDUR TAMBAHAN ===================

// 1. Cari apakah nilai X ada di dalam list
bool searchValue(LinkedList L, infotype X) {
    address p = L.First;
    while (p != NULL) {
        if (p->info == X)
            return true;
        p = p->next;
    }
    return false;
}

// 2. Ubah nilai elemen pertama menjadi newVal
void modifyFirst(LinkedList *L, infotype newVal) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, modifyFirst ditolak!\n");
        return;
    }
    L->First->info = newVal;
    printList(*L);
}

// 3. Ubah nilai elemen terakhir menjadi newVal
void modifyLast(LinkedList *L, infotype newVal) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, modifyLast ditolak!\n");
        return;
    }
    address p = L->First;
    while (p->next != NULL)
        p = p->next;
    p->info = newVal;
    printList(*L);
}

// 4. Ubah nilai kemunculan pertama oldVal menjadi newVal
bool modifyBetween(LinkedList *L, infotype oldVal, infotype newVal) {
    if (isEmpty(*L)) {
        printf("ERROR: List kosong, modifyBetween ditolak!\n");
        return false;
    }
    address p = L->First;
    while (p != NULL && p->info != oldVal)
        p = p->next;
    if (p == NULL) {
        printf("ERROR: Elemen %d tidak ditemukan, modifyBetween ditolak!\n", oldVal);
        return false;
    }
    p->info = newVal;
    printList(*L);
    return true;
}

// 5. Hitung jumlah kemunculan nilai X dalam list
int countValue(LinkedList L, infotype X) {
    address p = L.First;
    int count = 0;
    while (p != NULL) {
        if (p->info == X)
            count++;
        p = p->next;
    }
    return count;
}

// 6. Jumlahkan seluruh nilai dalam list
int sumAll(LinkedList L) {
    address p = L.First;
    int sum = 0;
    while (p != NULL) {
        sum += p->info;
        p = p->next;
    }
    return sum;
}

// 7. Tukar isi (info) dari dua node yang memiliki nilai val1 dan val2
bool swapValue(LinkedList *L, infotype val1, infotype val2) {
    if (val1 == val2) {
        printf("Kedua nilai sama, swap tidak diperlukan.\n");
        return false;
    }
    address p1 = NULL, p2 = NULL;
    address p = L->First;
    // Cari node yang memiliki nilai val1 dan val2
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
    // Tukar isi
    infotype temp = p1->info;
    p1->info = p2->info;
    p2->info = temp;
    printList(*L);
    return true;
}

