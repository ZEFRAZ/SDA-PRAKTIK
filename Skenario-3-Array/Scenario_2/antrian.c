#include "antrian.h"

// Inisialisasi antrian global
borrowerAddress firstQueue = NULL;

boolean isEmpty() {
    return (firstQueue == NULL);
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
        
        // Cari peminjam yang menunjuk ke buku ini
        borrowerAddress p = firstQueue;
        boolean adaAntrian = false;
        
        while (p != NULL) {
            if (p->targetBuku == &bukuArray[i]) {
                adaAntrian = true;
                if (p->prioritas == DOSEN) {
                    printf(" -> \"%s\" [DOSEN] ", p->nama);
                } else if (p->prioritas == MAHASISWA) {
                    printf(" -> \"%s\" [MAHASISWA] ", p->nama);
                } else if (p->prioritas == UMUM) {
                    printf(" -> \"%s\" [MASYARAKAT UMUM] ", p->nama);
                } else {
                    printf(" -> \"%s\" [ANOMALI] ", p->nama);
                }
            }
            p = p->next;
        }
        
        if (!adaAntrian) {
            printf(" -> (Tidak Ada Antrian!)");
        }
    }
}

void masukAntrian(borrowerAddress Pnew, buku *targetBuku) {
    if (Pnew == NULL || targetBuku == NULL) return;

    // Set target buku untuk peminjam baru
    setBorrowTarget(Pnew, targetBuku);

    borrowerAddress current = firstQueue;
    borrowerAddress prev = NULL;

    // Cari posisi yang tepat berdasarkan prioritas
    while (current != NULL && current->targetBuku == targetBuku && 
           current->prioritas <= Pnew->prioritas) {
        prev = current;
        current = current->next;
    }

    // Masukkan ke antrian
    if (prev == NULL) {
        Pnew->next = firstQueue;
        firstQueue = Pnew;
    } else {
        Pnew->next = current;
        prev->next = Pnew;
    }
}

void hapusPeminjam(char namaTerhapus[], buku *targetBuku) {
    if (firstQueue == NULL) {
        strcpy(namaTerhapus, "-");
        return;
    }

    borrowerAddress current = firstQueue;
    borrowerAddress prev = NULL;
    
    // Cari peminjam dengan prioritas tertinggi untuk buku tersebut
    while (current != NULL) {
        if (current->targetBuku == targetBuku) {
            strcpy(namaTerhapus, current->nama);
            
            if (prev == NULL) {
                firstQueue = current->next;
            } else {
                prev->next = current->next;
            }
            
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
    
    strcpy(namaTerhapus, "-");
}

void hapusPeminjamTertentu(char namaTerhapus[], borrowerAddress *p) {
    if (firstQueue == NULL) {
        printf("Antrian kosong.\n");
        return;
    }

    borrowerAddress current = firstQueue;
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
        firstQueue = current->next;
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

