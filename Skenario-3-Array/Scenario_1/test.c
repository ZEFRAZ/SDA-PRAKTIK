#include "test.h"
#include "menu.h"
#include "stack.h"

static void pressEnterToContinue() {
    printf("\nTekan Enter untuk melanjutkan...");
    fflush(stdout);
    getchar();
}

static void tampilkanStatusBuku(buku bukuArray[], int index) {
    printf("\nStatus Buku \"%s\":\n", bukuArray[index].judul);
    printf("- Stok: %d\n", bukuArray[index].stok);
    
    printf("- Antrian: ");
    borrowerAddress current = bukuArray[index].firstQueue;
    if (current == NULL) {
        printf("(kosong)\n");
    } else {
        while (current != NULL) {
            printf("-> \"%s\" ", current->nama);
            current = current->next;
        }
        printf("\n");
    }
    
    printf("- Peminjam aktif: ");
    current = bukuArray[index].peminjamAktif;
    if (current == NULL) {
        printf("(kosong)\n");
    } else {
        while (current != NULL) {
            printf("-> \"%s\" ", current->nama);
            current = current->next;
        }
        printf("\n");
    }
}

void runTestScenario(buku bukuArray[], int *jumlahBuku, aktivitasStack *aktivitasTop) {
    printf("=== MENJALANKAN TEST SKENARIO ===\n\n");

    // a) 2 X insert elemen "Buku1" dan "Buku2" di list Buku dimana stok buku masing masing 1
    printf("a) Menambah buku-buku:\n");
    tambahBuku(bukuArray, jumlahBuku, "Buku1", 1);
    printf("- Menambah buku \"Buku1\" dengan stok 1\n");
    tampilkanStatusBuku(bukuArray, 0);
    printf("\n");
    
    tambahBuku(bukuArray, jumlahBuku, "Buku2", 1);
    printf("- Menambah buku \"Buku2\" dengan stok 1\n");
    tampilkanStatusBuku(bukuArray, 1);
    printf("\n");

    // b) 1 X insert elemen "Anggota1" sebagai mahasiswa di list peminjaman "Buku1"
    printf("b) Menambah peminjam ke antrian Buku1:\n");
    borrowerAddress anggota1;
    createBorrower(&anggota1);
    infoBorrower(&anggota1, "Anggota1", MAHASISWA);
    masukAntrian(&bukuArray[0], anggota1);
    printf("- Menambah peminjam \"Anggota1\" (Mahasiswa) ke antrian buku \"Buku1\"\n");
    tampilkanStatusBuku(bukuArray, 0);
    printf("\n");

    // c) 1 X insert elemen "Dosen1" sebagai dosen di list peminjaman "Buku1"
    printf("c) Menambah peminjam ke antrian Buku1:\n");
    borrowerAddress dosen1;
    createBorrower(&dosen1);
    infoBorrower(&dosen1, "Dosen1", DOSEN);
    masukAntrian(&bukuArray[0], dosen1);
    printf("- Menambah peminjam \"Dosen1\" (Dosen) ke antrian buku \"Buku1\"\n");
    tampilkanStatusBuku(bukuArray, 0);
    printf("\n");

    // d) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku1"
    printf("d) Menambah peminjam ke antrian Buku1:\n");
    borrowerAddress umum1;
    createBorrower(&umum1);
    infoBorrower(&umum1, "Umum1", UMUM);
    masukAntrian(&bukuArray[0], umum1);
    printf("- Menambah peminjam \"Umum1\" (Umum) ke antrian buku \"Buku1\"\n");
    tampilkanStatusBuku(bukuArray, 0);
    printf("\n");

    // e) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku2"
    printf("e) Menambah peminjam ke antrian Buku2:\n");
    borrowerAddress umum1_buku2;
    createBorrower(&umum1_buku2);
    infoBorrower(&umum1_buku2, "Umum1", UMUM);
    masukAntrian(&bukuArray[1], umum1_buku2);
    printf("- Menambah peminjam \"Umum1\" (Umum) ke antrian buku \"Buku2\"\n");
    tampilkanStatusBuku(bukuArray, 1);
    printf("\n");

    // f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman
    printf("f) Memproses peminjaman Buku1:\n");
    printf("Status sebelum peminjaman:\n");
    tampilkanStatusBuku(bukuArray, 0);
    
    char namaTerhapus[100];
    hapusPeminjam(&bukuArray[0], namaTerhapus);
    bukuArray[0].stok--;
    
    // Tambahkan ke peminjam aktif
    borrowerAddress peminjamAktif;
    createBorrower(&peminjamAktif);
    infoBorrower(&peminjamAktif, namaTerhapus, DOSEN);
    bukuArray[0].peminjamAktif = peminjamAktif;
    
    printf("\n- Peminjam \"%s\" meminjam buku \"Buku1\"\n", namaTerhapus);
    
    printf("\nStatus setelah peminjaman:\n");
    tampilkanStatusBuku(bukuArray, 0);
    printf("\n");

    // g) Proses pengembalian "Buku1" oleh "Dosen1"
    printf("g) Memproses pengembalian Buku1:\n");
    printf("Status sebelum pengembalian:\n");
    tampilkanStatusBuku(bukuArray, 0);
    
    printf("\n- Peminjam \"Dosen1\" mengembalikan buku \"Buku1\"\n");
    bukuArray[0].stok++;
    
    // Hapus dari peminjam aktif
    borrowerAddress current = bukuArray[0].peminjamAktif;
    if (current != NULL) {
        bukuArray[0].peminjamAktif = current->next;
        free(current);
    }
    
    printf("\nStatus setelah pengembalian:\n");
    tampilkanStatusBuku(bukuArray, 0);
    printf("\n");

    // h) Elemen "Umum1" melakukan pembatalan aktivitas peminjaman buku
    printf("h) Membatalkan aktivitas peminjaman Buku2 oleh Umum1:\n");
    printf("Status sebelum pembatalan:\n");
    tampilkanStatusBuku(bukuArray, 1);
    
    // Tambahkan aktivitas pembatalan ke stack
    pushAktivitas(aktivitasTop, "BATAL", "Buku2", "Umum1", UMUM);
    
    // Hapus peminjam dari antrian
    borrowerAddress currentQueue = bukuArray[1].firstQueue;
    borrowerAddress prev = NULL;
    
    while (currentQueue != NULL) {
        if (strcmp(currentQueue->nama, "Umum1") == 0) {
            if (prev == NULL) {
                bukuArray[1].firstQueue = currentQueue->next;
            } else {
                prev->next = currentQueue->next;
            }
            free(currentQueue);
            break;
        }
        prev = currentQueue;
        currentQueue = currentQueue->next;
    }
    
    printf("\nStatus setelah pembatalan:\n");
    tampilkanStatusBuku(bukuArray, 1);
    printf("\n");

    printf("=== TEST SKENARIO SELESAI ===\n");
    pressEnterToContinue();
}

