#include "antrian.h"

boolean isEmpty(bukuAddress *b, borrowerAddress p){
	return (*b == NULL || p == NULL);
}

void printList(buku *b) {
    if (b == NULL) {
        printf("Tidak ada buku dalam daftar.\n");
        return;
    }

    while (b != NULL) {
        printf("\n<-> | Judul Buku: \"%s\" | (Stok: %d) | ", b->judul, b->stok);
        borrower *p = b->firstQueue;
        while (p != NULL) {
            if (p->prioritas == 1) {
                printf(" -> \"%s\" [DOSEN] ", p->nama);
            } else if (p->prioritas == 2) {
                printf(" -> \"%s\" [MAHASISWA] ", p->nama);
            } else if (p->prioritas == 3) {
                printf(" -> \"%s\" [MASYARAKAT UMUM] ", p->nama);
            } else {
                printf(" -> \"%s\" [ANOMALI] ", p->nama);
            }
            p = p->next;
        }
        if (b->firstQueue == NULL) {
            printf(" -> (Tidak Ada Antrian!)");
        }
        b = b->next;
    }
}

void masukAntrian(bukuAddress b, borrowerAddress Pnew) {
    if (b == NULL || Pnew == NULL) return;

    // Jika antrian kosong atau prioritas Pnew lebih tinggi dari head
    if (b->firstQueue == NULL || Pnew->prioritas < b->firstQueue->prioritas) {
        Pnew->next = b->firstQueue;
        b->firstQueue = Pnew;
        return;
    }

    // Cari posisi yang tepat berdasarkan prioritas
    borrowerAddress current = b->firstQueue;
    while (current->next != NULL && current->next->prioritas <= Pnew->prioritas) {
        current = current->next;
    }

    // Sisipkan Pnew
    Pnew->next = current->next;
    current->next = Pnew;
}

void hapusPeminjam(bukuAddress *b, char namaTerhapus[]) {
    if (*b == NULL || (*b)->firstQueue == NULL) {
        strcpy(namaTerhapus, "-");
        return;
    }

    borrowerAddress current = (*b)->firstQueue;
    strcpy(namaTerhapus, current->nama);
    
    (*b)->firstQueue = current->next;
    free(current);
}

void hapusPeminjamTertentu(bukuAddress *b, char namaTerhapus[], borrowerAddress *p) {
    if (*b == NULL || *p == NULL) {
        printf("Buku atau antrian tidak valid.\n");
        return;
    }

    borrowerAddress current = *p;
    borrowerAddress prev = NULL;

    while (current != NULL && strcmp(current->nama, namaTerhapus) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Peminjam \"%s\" tidak ditemukan.\n", namaTerhapus);
        return;
    }

    if (prev == NULL) {
        (*b)->firstQueue = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

int jumlahElemen(borrowerAddress p){
	int count = 0;
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

void printQueue(borrowerAddress queue) {
    printf("Daftar Peminjam:\n");
    if(queue == NULL) {
        printf("(Tidak ada peminjam)\n");
        return;
    }

    borrowerAddress current = queue;
    int no = 1;
    while(current != NULL) {
        printf("%d. %s (", no++, current->nama);
        switch(current->prioritas) {
            case DOSEN: printf("DOSEN"); break;
            case MAHASISWA: printf("MAHASISWA"); break;
            case UMUM: printf("MASYARAKAT UMUM"); break;
            default: printf("UNKNOWN"); break;
        }
        printf(")\n");
        current = current->next;
    }
}
