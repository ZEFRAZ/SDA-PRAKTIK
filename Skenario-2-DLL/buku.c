#include "buku.h"
#include "borrower.h"

void createBuku(bukuAddress *b) {
    *b = (bukuAddress)malloc(sizeof(buku));
    if (*b == NULL) {
        printf("Gagal mengalokasikan memori untuk buku.\n");
        exit(1); // Keluar dari program jika alokasi memori gagal
    }
    (*b)->prev = NULL;
    (*b)->next = NULL;
    (*b)->firstQueue = NULL;
    (*b)->peminjamAktif = NULL;
}

void infoBuku(bukuAddress *b, char judul[], int stok) {
    if(*b != NULL) {
        strncpy((*b)->judul, judul, 99);
        (*b)->judul[99] = '\0';  // Pastikan null-terminated
        (*b)->stok = (stok > 0) ? stok : 0;
    }
}

void deleteBuku(bukuAddress *head, bukuAddress target) {
    if (*head == NULL || target == NULL) return;

    // Hapus semua antrian dan peminjam aktif
    clearAllBorrower(&(target->firstQueue));
    clearAllBorrower(&(target->peminjamAktif));

    if (target->prev != NULL) {
        target->prev->next = target->next;
    } else {
        *head = target->next;
    }

    if (target->next != NULL) {
        target->next->prev = target->prev;
    }

    free(target);
    target = NULL;  // Hindari dangling pointer
}

void clearAllBuku(bukuAddress *head) {
    while (*head != NULL) {
        bukuAddress temp = *head;
        *head = (*head)->next;
        clearAllBorrower(&(temp->firstQueue));
        clearAllBorrower(&(temp->peminjamAktif));
        free(temp);
    }
}
