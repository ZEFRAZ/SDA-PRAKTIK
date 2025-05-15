#include "borrower.h"

void createBorrower(borrowerAddress *p, bukuAddress targetBuku) {
    *p = (borrowerAddress)malloc(sizeof(struct borrower));
    (*p)->targetBuku = targetBuku;
    (*p)->next = NULL;
}

void infoBorrower(borrowerAddress *p, char nama[], Prioritas prioritas) {
    strncpy((*p)->nama, nama, MAX_NAMA-1);
    (*p)->nama[MAX_NAMA-1] = '\0';
    (*p)->prioritas = prioritas;
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
    while (*head != NULL) {
        borrowerAddress temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
