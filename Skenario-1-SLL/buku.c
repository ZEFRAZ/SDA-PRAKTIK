#include "buku.h"
#include "borrower.h"

void createBuku(bukuAddress *b) {
    *b = (bukuAddress)malloc(sizeof(struct buku));
    (*b)->next = NULL;
}

void infoBuku(bukuAddress *b, char judul[], int stok) {
    strncpy((*b)->judul, judul, MAX_JUDUL-1);
    (*b)->judul[MAX_JUDUL-1] = '\0';
    (*b)->stok = stok;
}

void addBuku(bukuAddress newBuku) {
    if (newBuku == NULL) return;
    
    // Jika list kosong
    extern bukuAddress listBuku;
    if (listBuku == NULL) {
        listBuku = newBuku;
        return;
    }
    
    // Cari posisi terakhir
    bukuAddress current = listBuku;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Tambahkan buku baru
    current->next = newBuku;
}

void deleteBuku(bukuAddress *head, bukuAddress target) {
    if (*head == NULL || target == NULL) return;

    if (*head == target) {
        *head = target->next;
        free(target);
        return;
    }

    bukuAddress current = *head;
    while (current != NULL && current->next != target) {
        current = current->next;
    }

    if (current != NULL) {
        current->next = target->next;
        free(target);
    }
}

void clearAllBuku(bukuAddress *head) {
    while (*head != NULL) {
        bukuAddress temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

bukuAddress findBuku(bukuAddress head, char judul[]) {
    bukuAddress current = head;
    while (current != NULL) {
        if (strcmp(current->judul, judul) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
