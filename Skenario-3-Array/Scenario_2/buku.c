#include "buku.h"
#include "borrower.h"
#include "menu.h"

void initBuku(buku bukuArray[], int *jumlahBuku) {
    *jumlahBuku = 0;
    int i;
    for(i = 0; i < getMaxBuku(); i++) {
        bukuArray[i].peminjamAktif = NULL;
        bukuArray[i].stok = 0;
        bukuArray[i].judul[0] = '\0';
    }
}

void tambahBuku(buku bukuArray[], int *jumlahBuku, char judul[], int stok) {
    if (*jumlahBuku >= getMaxBuku()) {
        printf("Error: Kapasitas buku penuh! (Maksimum %d buku)\n", getMaxBuku());
        return;
    }

    // Cek apakah buku sudah ada
    int i;
    for(i = 0; i < *jumlahBuku; i++) {
        if(strcmp(bukuArray[i].judul, judul) == 0) {
            bukuArray[i].stok += stok;
            printf("Stok buku \"%s\" ditambahkan menjadi %d.\n", judul, bukuArray[i].stok);
            return;
        }
    }

    // Tambah buku baru
    strncpy(bukuArray[*jumlahBuku].judul, judul, 99);
    bukuArray[*jumlahBuku].judul[99] = '\0';
    bukuArray[*jumlahBuku].stok = (stok > 0) ? stok : 0;
    bukuArray[*jumlahBuku].peminjamAktif = NULL;
    (*jumlahBuku)++;
}

void hapusBuku(buku bukuArray[], int *jumlahBuku, int index) {
    if (index < 0 || index >= *jumlahBuku) {
        printf("Error: Index buku tidak valid!\n");
        return;
    }

    // Hapus peminjam aktif
    clearAllBorrower(&(bukuArray[index].peminjamAktif));

    // Geser semua elemen setelah index yang dihapus
    int i;
    for(i = index; i < *jumlahBuku - 1; i++) {
        bukuArray[i] = bukuArray[i + 1];
    }

    (*jumlahBuku)--;
}

void clearAllBuku(buku bukuArray[], int *jumlahBuku) {
    int i;
    for(i = 0; i < *jumlahBuku; i++) {
        clearAllBorrower(&(bukuArray[i].peminjamAktif));
    }
    *jumlahBuku = 0;
}

