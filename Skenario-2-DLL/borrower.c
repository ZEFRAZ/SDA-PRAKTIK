#include "borrower.h"

void createBorrower(borrowerAddress *p) {
    *p = (borrowerAddress)malloc(sizeof(borrower));
    if (*p == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk borrower.\n");
        exit(1);
    }
    (*p)->next = NULL;
}

void infoBorrower(borrowerAddress *p, char nama[], Prioritas prioritas) {
    strcpy((*p)->nama, nama);
    (*p)->prioritas = prioritas;
    (*p)->next = NULL;
}

borrowerAddress searchBorrower(borrowerAddress p, char nama[]){
	while (p != NULL){
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
