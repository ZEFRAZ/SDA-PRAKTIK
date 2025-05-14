#include "borrower.h"
#include "buku.h"

void createBorrower(borrowerAddress *p) {
    *p = (borrowerAddress)malloc(sizeof(borrower));
    if (*p == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk borrower.\n");
        exit(1);
    }
    (*p)->next = NULL;
    (*p)->targetBuku = NULL;  // Inisialisasi pointer buku
}

void infoBorrower(borrowerAddress *p, char nama[], Prioritas prioritas) {
    strcpy((*p)->nama, nama);
    (*p)->prioritas = prioritas;
    (*p)->next = NULL;
    (*p)->targetBuku = NULL;  // Inisialisasi pointer buku
}

void setBorrowTarget(borrowerAddress p, buku *targetBuku) {
    if (p != NULL) {
        p->targetBuku = targetBuku;
    }
}

borrowerAddress searchBorrower(borrowerAddress p, char nama[]) {
    while (p != NULL) {
        if (strcmp(p->nama, nama) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void clearAllBorrower(borrowerAddress *head) {
    if (head == NULL) return;
    
    borrowerAddress current = *head;
    while (current != NULL) {
        borrowerAddress temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

