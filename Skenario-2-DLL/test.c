#include "test.h"

static void pressEnterToContinue() {
    printf("\nTekan Enter untuk melanjutkan...");
    fflush(stdout);
    getchar();
}

static void displayTestResult(const char* testName, boolean success) {
    printf("\n%s: %s\n", testName, success ? "BERHASIL" : "GAGAL");
}

// Fungsi untuk membersihkan semua data sebelum test
static void clearAllData(bukuAddress *listBuku, aktivitasStack *aktivitasTop) {
    // Hapus semua buku dan antrian
    clearAllBuku(listBuku);
    *listBuku = NULL;
    
    // Hapus semua aktivitas
    while (*aktivitasTop != NULL) {
        popAktivitas(aktivitasTop);
    }
}

void runTestScenario(bukuAddress *listBuku, aktivitasStack *aktivitasTop) {
    printf("\n=== MENJALANKAN TEST SKENARIO ===\n");
    
    // Cek apakah ada data manual
    if (*listBuku != NULL) {
        printf("\nPERHATIAN: Ada data yang sudah ditambahkan sebelumnya.\n");
        printf("1. Lanjutkan dan hapus semua data yang ada\n");
        printf("2. Batalkan test skenario\n");
        
        int pilihan;
        do {
            printf("Pilihan Anda (1/2): ");
            scanf("%d", &pilihan);
            while (getchar() != '\n'); // Clear input buffer
        } while (pilihan != 1 && pilihan != 2);
        
        if (pilihan == 2) {
            printf("\nTest skenario dibatalkan.\n");
            pressEnterToContinue();
            return;
        }
        
        // Jika pilihan 1, lanjutkan dengan menghapus data
        clearAllData(listBuku, aktivitasTop);
    }
    
    boolean success = true;
    bukuAddress buku;
    borrowerAddress peminjam;
    char namaTerhapus[50];

    // Test 1: Menambah Buku1 dan Buku2
    printf("\nTest 1: Menambahkan Buku1 dan Buku2\n");
    createBuku(&buku);
    infoBuku(&buku, "Buku1", 1);
    buku->next = *listBuku;
    if(*listBuku) (*listBuku)->prev = buku;
    *listBuku = buku;

    createBuku(&buku);
    infoBuku(&buku, "Buku2", 1);
    buku->next = *listBuku;
    if(*listBuku) (*listBuku)->prev = buku;
    *listBuku = buku;

    displayTestResult("Penambahan Buku", *listBuku != NULL);

    // Test 2: Menambah Anggota1 sebagai mahasiswa ke antrian Buku1
    printf("\nTest 2: Menambah Anggota1 ke antrian Buku1\n");
    buku = *listBuku;
    while(buku && strcmp(buku->judul, "Buku1") != 0) buku = buku->next;
    
    if(buku) {
        createBorrower(&peminjam);
        infoBorrower(&peminjam, "Anggota1", MAHASISWA);
        masukAntrian(buku, peminjam);
        pushAktivitas(aktivitasTop, "tambah_peminjam", "Buku1", "Anggota1", MAHASISWA);
        printf("\nAntrian Buku1 sekarang:\n");
        printQueue(buku->firstQueue);
    }

    // Test 3: Menambah Dosen1 ke antrian Buku1
    printf("\nTest 3: Menambah Dosen1 ke antrian Buku1\n");
    createBorrower(&peminjam);
    infoBorrower(&peminjam, "Dosen1", DOSEN);
    masukAntrian(buku, peminjam);
    pushAktivitas(aktivitasTop, "tambah_peminjam", "Buku1", "Dosen1", DOSEN);
    printf("\nAntrian Buku1 sekarang:\n");
    printQueue(buku->firstQueue);

    // Test 4: Menambah Umum1 ke antrian Buku1
    printf("\nTest 4: Menambah Umum1 ke antrian Buku1\n");
    createBorrower(&peminjam);
    infoBorrower(&peminjam, "Umum1", UMUM);
    masukAntrian(buku, peminjam);
    pushAktivitas(aktivitasTop, "tambah_peminjam", "Buku1", "Umum1", UMUM);
    printf("\nAntrian Buku1 sekarang:\n");
    printQueue(buku->firstQueue);

    // Test 5: Menambah Umum1 ke antrian Buku2
    printf("\nTest 5: Menambah Umum1 ke antrian Buku2\n");
    buku = *listBuku;
    while (buku && strcmp(buku->judul, "Buku2") != 0) buku = buku->next;

    if (buku) {
        createBorrower(&peminjam);
        infoBorrower(&peminjam, "Umum1", UMUM);
        masukAntrian(buku, peminjam);
        pushAktivitas(aktivitasTop, "tambah_peminjam", "Buku2", "Umum1", UMUM);
        printf("\nAntrian Buku2 sekarang:\n");
        printQueue(buku->firstQueue);
    }

    // Test 6: Proses peminjaman Buku1
    printf("\nTest 6: Proses peminjaman Buku1\n");
    buku = *listBuku;
    while(buku && strcmp(buku->judul, "Buku1") != 0) buku = buku->next;
    
    if(buku) {
        hapusPeminjam(&buku, namaTerhapus);
        if(strcmp(namaTerhapus, "Dosen1") == 0) {
            buku->stok--;
            createBorrower(&peminjam);
            infoBorrower(&peminjam, namaTerhapus, PEMINJAM_AKTIF);
            buku->peminjamAktif = peminjam;
            pushAktivitas(aktivitasTop, "peminjaman", "Buku1", namaTerhapus, DOSEN);
            printf("Peminjam yang mendapat buku: %s\n", namaTerhapus);
            displayTestResult("Peminjaman oleh Dosen1", true);
        } else {
            displayTestResult("Peminjaman oleh Dosen1", false);
        }
    }

    // Test 7: Pengembalian Buku1
    printf("\nTest 7: Pengembalian Buku1 oleh Dosen1\n");
    buku = *listBuku;
    while (buku && strcmp(buku->judul, "Buku1") != 0) buku = buku->next;

    if (buku) {
        // Hapus dari peminjam aktif
        if (buku->peminjamAktif) {
            free(buku->peminjamAktif);
            buku->peminjamAktif = NULL;
            buku->stok++;
            pushAktivitas(aktivitasTop, "pengembalian", "Buku1", "Dosen1", DOSEN);
        }

        // Proses peminjaman berikutnya
        if (buku->firstQueue) {
            hapusPeminjam(&buku, namaTerhapus);
            if(strcmp(namaTerhapus, "Anggota1") == 0) {
                buku->stok--;
                createBorrower(&peminjam);
                infoBorrower(&peminjam, namaTerhapus, PEMINJAM_AKTIF);
                buku->peminjamAktif = peminjam;
                pushAktivitas(aktivitasTop, "peminjaman", "Buku1", namaTerhapus, MAHASISWA);
                printf("Peminjam berikutnya: %s\n", namaTerhapus);
                displayTestResult("Anggota1 menjadi peminjam berikutnya", true);
            } else {
                displayTestResult("Anggota1 menjadi peminjam berikutnya", false);
            }
        }

        printf("\nAntrian Buku1 setelah pengembalian:\n");
        printQueue(buku->firstQueue);
    }

    // Test 8: Pembatalan peminjaman Buku2
    printf("\nTest 8: Pembatalan peminjaman Buku2 oleh Umum1\n");
    printf("\nStatus Sebelum Pembatalan:\n");
    printList(*listBuku);

    boolean pembatalanBerhasil = false;
    if (*aktivitasTop != NULL) {
        // Hapus Umum1 dari antrian Buku2
        buku = *listBuku;
        while (buku && strcmp(buku->judul, "Buku2") != 0) buku = buku->next;
        
        if (buku) {
            borrowerAddress current = buku->firstQueue;
            borrowerAddress prev = NULL;
            
            while (current != NULL) {
                if (strcmp(current->nama, "Umum1") == 0) {
                    if (prev == NULL) {
                        buku->firstQueue = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    free(current);
                    pembatalanBerhasil = true;
                    break;
                }
                prev = current;
                current = current->next;
            }
        }

        printf("\nStatus Setelah Pembatalan:\n");
        printList(*listBuku);
    }

    displayTestResult("Pembatalan peminjaman Umum1 dari Buku2", pembatalanBerhasil);

    printf("\n=== Status Akhir Setelah Semua Test ===\n");
    printList(*listBuku);
    
    printf("\n=== TEST SKENARIO SELESAI ===\n");
    pressEnterToContinue();
    
    // Bersihkan data setelah test selesai
    clearAllData(listBuku, aktivitasTop);
}
