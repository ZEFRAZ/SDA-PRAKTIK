#include "stack.h"
#include "antrian.h"

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

void undoAktivitas(aktivitasStack* top, buku bukuArray[], int* jumlahBuku) {
    if (*top == NULL) {
        printf("Tidak ada aktivitas yang bisa di-undo.\n");
        return;
    }

    aktivitasStack temp = *top;
    *top = (*top)->next;

    // Cari buku yang sesuai
    int index = -1;
    int i;
    for(i = 0; i < *jumlahBuku; i++) {
        if(strcmp(bukuArray[i].judul, temp->judulBuku) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Buku tidak ditemukan untuk aktivitas ini.\n");
        free(temp);
        return;
    }

    // UNDO aktivitas peminjaman
    if (strcmp(temp->jenis, "peminjaman") == 0) {
        // Hapus dari peminjam aktif
        if (bukuArray[index].peminjamAktif != NULL) {
            borrowerAddress current = bukuArray[index].peminjamAktif;
            borrowerAddress prev = NULL;
            
            while (current != NULL) {
                if (strcmp(current->nama, temp->namaPeminjam) == 0) {
                    // Buat node baru untuk dikembalikan ke antrian
                    borrowerAddress newBorrower;
                    createBorrower(&newBorrower);
                    infoBorrower(&newBorrower, temp->namaPeminjam, temp->prioritas);
                    
                    // Masukkan kembali ke antrian dengan prioritas asli
                    masukAntrian(newBorrower, &bukuArray[index]);
                    
                    // Hapus dari peminjam aktif
                    if (prev == NULL) {
                        bukuArray[index].peminjamAktif = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    
                    free(current);
                    bukuArray[index].stok++;  // Kembalikan stok
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
        // Cari di antrian global
        borrowerAddress current = firstQueue;
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
                firstQueue = current->next;
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
        newBorrower->next = bukuArray[index].peminjamAktif;
        bukuArray[index].peminjamAktif = newBorrower;
        bukuArray[index].stok--;  // Kurangi stok karena buku dianggap belum dikembalikan
        
        printf("Undo: Pengembalian \"%s\" oleh \"%s\" dibatalkan.\n",
               temp->judulBuku, temp->namaPeminjam);
    }

    free(temp);
}
