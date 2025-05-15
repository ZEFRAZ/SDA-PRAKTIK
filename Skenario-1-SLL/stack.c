#include "stack.h"

void pushAktivitas(aktivitasStack* top, char jenis[], char judulBuku[], char namaPeminjam[], int prioritas) {
    aktivitasStack newNode = (aktivitasStack)malloc(sizeof(struct aktivitas));
    if (newNode == NULL) return;
    
    strncpy(newNode->jenis, jenis, sizeof(newNode->jenis)-1);
    strncpy(newNode->judulBuku, judulBuku, sizeof(newNode->judulBuku)-1);
    strncpy(newNode->namaPeminjam, namaPeminjam, sizeof(newNode->namaPeminjam)-1);
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
        borrowerAddress current = activeBorrowers;
        borrowerAddress prev = NULL;
        
        while (current != NULL) {
            if (strcmp(current->nama, temp->namaPeminjam) == 0 && 
                current->targetBuku == buku) {
                // Buat node baru untuk dikembalikan ke antrian
                borrowerAddress newBorrower;
                createBorrower(&newBorrower, buku);
                infoBorrower(&newBorrower, temp->namaPeminjam, temp->prioritas);
                
                // Masukkan kembali ke antrian dengan prioritas asli
                masukAntrian(&queueHead, newBorrower);
                
                // Hapus dari peminjam aktif
                if (prev == NULL) {
                    activeBorrowers = current->next;
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
    // UNDO aktivitas pengembalian
    else if (strcmp(temp->jenis, "pengembalian") == 0) {
        // Cari di antrian
        borrowerAddress current = queueHead;
        borrowerAddress prev = NULL;
        boolean found = false;
        
        // Cari peminjam di antrian
        while (current != NULL) {
            if (strcmp(current->nama, temp->namaPeminjam) == 0 && 
                current->targetBuku == buku) {
                found = true;
                break;
            }
            prev = current;
            current = current->next;
        }
        
        // Jika peminjam ditemukan di antrian, hapus dari antrian
        if (found) {
            if (prev == NULL) {
                queueHead = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
        }
        
        // Kembalikan ke peminjam aktif dengan prioritas asli
        borrowerAddress newBorrower;
        createBorrower(&newBorrower, buku);
        infoBorrower(&newBorrower, temp->namaPeminjam, temp->prioritas);  // Gunakan prioritas asli
        
        // Tambahkan ke peminjam aktif
        newBorrower->next = activeBorrowers;
        activeBorrowers = newBorrower;
        buku->stok--;  // Kurangi stok karena buku dianggap belum dikembalikan
        
        printf("Undo: Pengembalian \"%s\" oleh \"%s\" dibatalkan.\n",
               temp->judulBuku, temp->namaPeminjam);
    }

    // Hapus aktivitas dari stack
    popAktivitas(top);
}
