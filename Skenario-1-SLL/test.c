#include "test.h"
#include "antrian.h"

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
    // Hapus semua buku
    clearAllBuku(listBuku);
    *listBuku = NULL;
    
    // Hapus semua peminjam
    clearAllBorrower(&queueHead);
    clearAllBorrower(&activeBorrowers);
    
    // Hapus semua aktivitas
    while (*aktivitasTop != NULL) {
        popAktivitas(aktivitasTop);
    }
}

void runTestScenario(bukuAddress *listBuku, aktivitasStack *aktivitasTop) {
    printf("\n=== MENJALANKAN TEST SKENARIO ===\n\n");

    // Test a: Menambahkan Buku1 dan Buku2
    printf("Test a: Menambahkan Buku1 dan Buku2\n");
    bukuAddress buku1, buku2;
    createBuku(&buku1);
    createBuku(&buku2);
    infoBuku(&buku1, "Buku1", 1);
    infoBuku(&buku2, "Buku2", 1);
    
    // Tambahkan ke daftar buku
    addBuku(buku1);
    addBuku(buku2);
    
    printf("\nPenambahan Buku: BERHASIL\n");
    printf("\nStatus awal buku:\n");
    printAllBuku();

    // Test b: Menambah Anggota1 (Mahasiswa) ke antrian Buku1
    printf("\nTest b: Menambah Anggota1 (Mahasiswa) ke antrian Buku1\n");
    borrowerAddress anggota1;
    createBorrower(&anggota1, buku1);
    infoBorrower(&anggota1, "Anggota1", MAHASISWA);
    masukAntrian(&queueHead, anggota1);
    printf("\nAntrian Buku1 sekarang:\n");
    printQueueForBook(buku1);

    // Test c: Menambah Dosen1 (Dosen) ke antrian Buku1
    printf("\nTest c: Menambah Dosen1 (Dosen) ke antrian Buku1\n");
    borrowerAddress dosen1;
    createBorrower(&dosen1, buku1);
    infoBorrower(&dosen1, "Dosen1", DOSEN);
    masukAntrian(&queueHead, dosen1);
    printf("\nAntrian Buku1 sekarang:\n");
    printQueueForBook(buku1);

    // Test d: Menambah Umum1 (Masyarakat Umum) ke antrian Buku1
    printf("\nTest d: Menambah Umum1 (Masyarakat Umum) ke antrian Buku1\n");
    borrowerAddress umum1;
    createBorrower(&umum1, buku1);
    infoBorrower(&umum1, "Umum1", UMUM);
    masukAntrian(&queueHead, umum1);
    printf("\nAntrian Buku1 sekarang:\n");
    printQueueForBook(buku1);

    // Test e: Menambah Umum1 (Masyarakat Umum) ke antrian Buku2
    printf("\nTest e: Menambah Umum1 (Masyarakat Umum) ke antrian Buku2\n");
    borrowerAddress umum2;
    createBorrower(&umum2, buku2);
    infoBorrower(&umum2, "Umum1", UMUM);
    masukAntrian(&queueHead, umum2);
    printf("\nAntrian Buku2 sekarang:\n");
    printQueueForBook(buku2);

    // Test f: Proses peminjaman Buku1
    printf("\nTest f: Proses peminjaman Buku1\n");
    printf("Status sebelum peminjaman:\n");
    printAllBuku();
    char namaPeminjam[MAX_NAMA] = "";
    hapusPeminjam(buku1, namaPeminjam);
    printf("\nStatus setelah peminjaman:\n");
    printAllBuku();

    // Test g: Pengembalian Buku1 oleh Dosen1
    printf("\nTest g: Pengembalian Buku1 oleh Dosen1\n");
    printf("Status sebelum pengembalian:\n");
    printAllBuku();
    kembalikanBuku(&activeBorrowers, buku1);
    printf("\nStatus setelah pengembalian:\n");
    printAllBuku();

    // Test h: Pembatalan peminjaman Buku2 oleh Umum1
    printf("\nTest h: Pembatalan peminjaman Buku2 oleh Umum1\n");
    printf("Status sebelum pembatalan:\n");
    printAllBuku();
    batalkanPeminjaman(&queueHead, buku2, "Umum1");
    printf("\nStatus setelah pembatalan:\n");
    printAllBuku();

    printf("\n=== Status Akhir Setelah Semua Test ===\n");
    printAllBuku();
    printf("\n=== TEST SKENARIO SELESAI ===\n");
    
    pressEnterToContinue();
}

