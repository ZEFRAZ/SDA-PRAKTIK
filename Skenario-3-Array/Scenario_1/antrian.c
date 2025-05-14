#include "antrian.h"

boolean isEmpty(buku bukuArray[], int index) {
    return (index < 0 || bukuArray[index].firstQueue == NULL);
}

void printList(buku bukuArray[], int jumlahBuku) {
    if (jumlahBuku == 0) {
        printf("Tidak ada buku dalam daftar.\n");
        return;
    }
	int i;
    for(i = 0; i < jumlahBuku; i++) {
        printf("\n<-> | Judul Buku: \"%s\" | (Stok: %d) | ", 
               bukuArray[i].judul, bukuArray[i].stok);
        
        borrower *p = bukuArray[i].firstQueue;
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
        if (bukuArray[i].firstQueue == NULL) {
            printf(" -> (Tidak Ada Antrian!)");
        }
    }
}

void masukAntrian(buku *b, borrowerAddress Pnew) {
    if (b == NULL || Pnew == NULL) return;

    borrowerAddress current = b->firstQueue;
    borrowerAddress prev = NULL;

    while (current != NULL && current->prioritas <= Pnew->prioritas) {
        prev = current;
        current = current->next;
    }

    Pnew->next = current;
    
    if (prev != NULL) {
        prev->next = Pnew;
    } else {
        b->firstQueue = Pnew;
    }
}

void hapusPeminjam(buku *b, char namaTerhapus[]) {
    if (b == NULL || b->firstQueue == NULL) {
        strcpy(namaTerhapus, "-");
        return;
    }

    borrowerAddress current = b->firstQueue;
    strcpy(namaTerhapus, current->nama);
    
    b->firstQueue = current->next;
    free(current);
}

void hapusPeminjamTertentu(buku *b, char namaTerhapus[], borrowerAddress *p) {
    if (b == NULL || *p == NULL) {
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
        b->firstQueue = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

int jumlahElemen(borrowerAddress p) {
    int count = 0;
    while(p != NULL) {
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

