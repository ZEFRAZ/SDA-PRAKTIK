#include "stack.h"

void pushAktivitas(aktivitasStack* top, char jenis[], char judulBuku[], char namaPeminjam[], int prioritas) {
    aktivitasStack newNode = (aktivitasStack)malloc(sizeof(aktivitas));
    if (newNode == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk aktivitas.\n");
        exit(1);
    }
    strncpy(newNode->jenis, jenis, sizeof(newNode->jenis)-1);
    newNode->jenis[sizeof(newNode->jenis)-1] = '\0';

    strncpy(newNode->judulBuku, judulBuku, sizeof(newNode->judulBuku)-1);
    newNode->judulBuku[sizeof(newNode->judulBuku)-1] = '\0';
    
    strncpy(newNode->namaPeminjam, namaPeminjam, sizeof(newNode->namaPeminjam)-1);
    newNode->namaPeminjam[sizeof(newNode->namaPeminjam)-1] = '\0';

    newNode->prioritas = prioritas;
    newNode->next = *top;
    *top = newNode;
}

void popAktivitas(aktivitasStack* top) {
    if (*top == NULL) return;
    aktivitasStack temp = *top;
    *top = (*top)->next;
    free(temp);
}

void undoAktivitas(aktivitasStack* top, bukuAddress* listBuku) {
    if (*top == NULL) {
        printf("Tidak ada aktivitas yang bisa di-undo.\n");
        return;
    }

    aktivitasStack temp = *top;
    bukuAddress buku = *listBuku;

    // Cari buku yang sesuai
    while (buku != NULL && strcmp(buku->judul, temp->judulBuku) != 0) {
        buku = buku->next;
    }

    if (buku == NULL) {
        printf("Buku tidak ditemukan untuk aktivitas ini.\n");
        popAktivitas(top);
        return;
    }

    // UNDO aktivitas peminjaman
    if (strcmp(temp->jenis, "peminjaman") == 0) {
        // Hapus dari peminjam aktif
        if (buku->peminjamAktif != NULL) {
            borrowerAddress current = buku->peminjamAktif;
            borrowerAddress prev = NULL;
            
            while (current != NULL) {
                if (strcmp(current->nama, temp->namaPeminjam) == 0) {
                    // Buat node baru untuk dikembalikan ke antrian
                    borrowerAddress newBorrower;
                    createBorrower(&newBorrower);
                    infoBorrower(&newBorrower, temp->namaPeminjam, temp->prioritas);
                    
                    // Masukkan kembali ke antrian dengan prioritas asli
                    masukAntrian(buku, newBorrower);
                    
                    // Hapus dari peminjam aktif
                    if (prev == NULL) {
                        buku->peminjamAktif = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    
                    free(current);
                    buku->stok++;  // Kembalikan stok
                    printf("Undo: Peminjaman \"%s\" oleh \"%s\" dibatalkan.\n",
                           temp->judulBuku, temp->namaPeminjam);
                    break;
                }
                prev = current;
                current = current->next;
            }
        }
    }
    // UNDO aktivitas pengembalian
    else if (strcmp(temp->jenis, "pengembalian") == 0) {
        // Cari di antrian
        borrowerAddress current = buku->firstQueue;
        borrowerAddress prev = NULL;
        boolean found = false;
        
        // Cari peminjam di antrian
        while (current != NULL) {
            if (strcmp(current->nama, temp->namaPeminjam) == 0) {
                found = true;
                break;
            }
            prev = current;
            current = current->next;
        }
        
        // Jika peminjam ditemukan di antrian, hapus dari antrian
        if (found) {
            if (prev == NULL) {
                buku->firstQueue = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
        }
        
        // Kembalikan ke peminjam aktif
        borrowerAddress newBorrower;
        createBorrower(&newBorrower);
        infoBorrower(&newBorrower, temp->namaPeminjam, PEMINJAM_AKTIF);
        
        // Tambahkan ke peminjam aktif
        newBorrower->next = buku->peminjamAktif;
        buku->peminjamAktif = newBorrower;
        buku->stok--;  // Kurangi stok karena buku dianggap belum dikembalikan
        
        printf("Undo: Pengembalian \"%s\" oleh \"%s\" dibatalkan.\n",
               temp->judulBuku, temp->namaPeminjam);
    }

    // Hapus aktivitas dari stack
    popAktivitas(top);
}