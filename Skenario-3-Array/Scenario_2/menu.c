#include "menu.h"
#include "stack.h"
#include "antrian.h"

static buku *bukuArray = NULL;  // Pointer ke array buku yang akan dialokasikan secara dinamis
static int jumlahBuku = 0;
static int maxBuku = 0;  // Variabel untuk menyimpan ukuran maksimum array
static aktivitasStack aktivitasTop = NULL;

void setMaxBuku(int max) {
    maxBuku = max;
    // Alokasi memori untuk array buku
    bukuArray = (buku*)malloc(max * sizeof(buku));
    if (bukuArray == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk array buku.\n");
        printf("Silakan coba dengan ukuran yang lebih kecil.\n");
        exit(1);
    }
    // Inisialisasi array
    initBuku(bukuArray, &jumlahBuku);
}

int getMaxBuku() {
    return maxBuku;
}

static void input_string(char *buffer, size_t size, const char *prompt) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

static int input_int(const char *prompt, int min, int max) {
    int value;
    do {
        printf("%s", prompt);
        while (scanf("%d", &value) != 1) {
            printf("Input tidak valid! Masukkan angka antara %d-%d: ", min, max);
            while (getchar() != '\n');
        }
        while (getchar() != '\n');
        
        if (value < min || value > max) {
            printf("Pilih nomor antara %d-%d!\n", min, max);
        }
    } while (value < min || value > max);
    return value;
}

boolean isBorrowerExists(borrowerAddress p, const char* nama) {
    while (p != NULL) {
        if (strcmp(p->nama, nama) == 0) {
            return true;
        }
        p = p->next;
    }
    return false;
}

boolean isBookExists(buku bukuArray[], int jumlahBuku, const char* judul) {
    int i;
    for(i = 0; i < jumlahBuku; i++) {
        if(strcmp(bukuArray[i].judul, judul) == 0) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk membersihkan layar
static void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk menunggu user menekan enter
static void pressEnterToContinue() {
    printf("\nTekan Enter untuk melanjutkan...");
    fflush(stdout);
    getchar();
}

void displayMenu() {
    int opsi;
    char judul[100];
    char nama[50];
    int i;

    // Minta input ukuran maksimum array
    printf("Masukkan jumlah maksimum buku yang dapat disimpan: ");
    int max;
    while (scanf("%d", &max) != 1 || max <= 0) {
        printf("Input tidak valid! Masukkan angka positif: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    
    // Set ukuran array
    setMaxBuku(max);
    printf("Array buku telah diinisialisasi dengan kapasitas %d buku.\n", maxBuku);
    pressEnterToContinue();
    clearScreen();

    do {
        clearScreen();
        printf("\n\n===== MENU PERPUSTAKAAN ARRAY OF STRUCT =====\n");
        printf("Kapasitas Maksimum Buku: %d\n", maxBuku);
        printf("Jumlah Buku Saat Ini: %d\n", jumlahBuku);
        printf("1. Tambah Buku\n");
        printf("2. Tambah Peminjam ke Antrian Buku\n");
        printf("3. Tampilkan Daftar Buku dan Antrian\n");
        printf("4. Proses Peminjaman Buku\n");
        printf("5. Pengembalian Buku\n");
        printf("6. Batalkan Antrian\n");
        printf("7. Peminjam Buku Aktif\n");
        printf("8. Hapus Buku\n");
        printf("9. Batalkan Aktivitas Terakhir Peminjam (peminjaman/pengembalian)\n");
        printf("10. Jalankan Test Scenario\n");
        printf("0. Keluar\n");

        opsi = input_int("Pilihan Anda: ", 0, 10);

        switch (opsi) {
            case 1: { // Tambah Buku
                input_string(judul, sizeof(judul), "Masukkan Judul Buku: ");
                int stok = input_int("Masukkan Stok Buku: ", 1, 1000);

                if (stok <= 0) {
                    printf("Stok harus lebih dari 0!\n");
                    break;
                }

                if (strlen(judul) == 0) {
                    printf("Judul buku tidak boleh kosong!\n");
                    break;
                }

                tambahBuku(bukuArray, &jumlahBuku, judul, stok);
                pushAktivitas(&aktivitasTop, "tambah_buku", judul, "-", stok);
                printf("\nBuku \"%s\" berhasil ditambahkan dengan stok %d.\n", judul, stok);
                
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 2: { // Tambah Peminjam ke Antrian Buku
                if (jumlahBuku == 0) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                for(i = 0; i < jumlahBuku; i++) {
                    printf("%d. %s (Stok: %d)\n", i+1, bukuArray[i].judul, bukuArray[i].stok);
                }

                int pilihan = input_int("Pilih nomor buku untuk menambahkan peminjam: ", 1, jumlahBuku);
                int index = pilihan - 1;

                // Tambahkan peminjam ke antrian buku
                input_string(nama, sizeof(nama), "Masukkan Nama Peminjam: ");

                // Cek apakah nama sudah ada dalam antrian global
                borrowerAddress existingBorrower = searchBorrower(firstQueue, nama);
                if (existingBorrower != NULL) {
                    printf("Peminjam dengan nama \"%s\" sudah ada dalam antrian.\n", nama);
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Cek di peminjam aktif
                existingBorrower = bukuArray[index].peminjamAktif;
                while (existingBorrower != NULL) {
                    if (strcmp(existingBorrower->nama, nama) == 0) {
                        printf("Peminjam \"%s\" sedang meminjam buku ini.\n", nama);
                        pressEnterToContinue();
                        clearScreen();
                        break;
                    }
                    existingBorrower = existingBorrower->next;
                }

                int prioritas = input_int("Masukkan Prioritas (1: Dosen, 2: Mahasiswa, 3: Umum): ", DOSEN, UMUM);
                if (prioritas == DOSEN) {
                    printf("Prioritas: Dosen\n");
                } else if (prioritas == MAHASISWA) {
                    printf("Prioritas: Mahasiswa\n");
                } else if (prioritas == UMUM) {
                    printf("Prioritas: Umum\n");
                }

                borrowerAddress newBorrower;
                createBorrower(&newBorrower);
                infoBorrower(&newBorrower, nama, prioritas);

                masukAntrian(newBorrower, &bukuArray[index]);
                printf("Peminjam \"%s\" berhasil ditambahkan ke antrian buku \"%s\".\n", 
                       nama, bukuArray[index].judul);

                pushAktivitas(&aktivitasTop, "tambah_peminjam", 
                             bukuArray[index].judul, nama, prioritas);
                
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 3: { // Tampilkan Daftar Buku dan Antrian
                if (jumlahBuku == 0) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                printList(bukuArray, jumlahBuku);
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 4: { // Proses Peminjaman Buku
                if (jumlahBuku == 0) {
                    printf("Tidak ada buku dalam daftar.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Cek ada antrian peminjam
                if (isEmpty(firstQueue)) {
                    printf("Tidak ada antrian peminjam.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                for(i = 0; i < jumlahBuku; i++) {
                    printf("%d. %s (Stok: %d)\n", i+1, bukuArray[i].judul, bukuArray[i].stok);
                }

                int pilihan = input_int("Pilih nomor buku untuk proses peminjaman: ", 1, jumlahBuku);
                int index = pilihan - 1;

                if (bukuArray[index].stok <= 0) {
                    printf("Maaf, stok buku \"%s\" sedang habis.\n", bukuArray[index].judul);
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Proses peminjaman
                char namaTerhapus[100];
                borrowerAddress peminjam = firstQueue;
                int prioritasAsli = 0;
                
                // Cari peminjam dan simpan prioritas aslinya
                while (peminjam != NULL) {
                    if (peminjam->targetBuku == &bukuArray[index]) {
                        prioritasAsli = peminjam->prioritas;
                        break;
                    }
                    peminjam = peminjam->next;
                }
                
                hapusPeminjam(namaTerhapus, &bukuArray[index]);

                if (strcmp(namaTerhapus, "-") != 0) {
                    bukuArray[index].stok--;

                    // Tambahkan ke peminjam aktif
                    borrowerAddress newBorrower;
                    createBorrower(&newBorrower);
                    infoBorrower(&newBorrower, namaTerhapus, PEMINJAM_AKTIF);
                    newBorrower->next = bukuArray[index].peminjamAktif;
                    bukuArray[index].peminjamAktif = newBorrower;

                    // Simpan aktivitas dengan prioritas asli
                    pushAktivitas(&aktivitasTop, "peminjaman",
                                bukuArray[index].judul,
                                namaTerhapus,
                                prioritasAsli);  // Gunakan prioritas asli

                    printf("\"%s\" berhasil meminjam buku \"%s\".\n",
                        namaTerhapus, bukuArray[index].judul);
                }

                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 5: { // Pengembalian Buku
                if (jumlahBuku == 0) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Check if there are any active borrowers
                boolean hasActiveBorrowers = false;
                for(i = 0; i < jumlahBuku; i++) {
                    if (bukuArray[i].peminjamAktif != NULL) {
                        hasActiveBorrowers = true;
                        break;
                    }
                }

                if (!hasActiveBorrowers) {
                    printf("Tidak ada peminjam aktif pada semua buku.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                for(i = 0; i < jumlahBuku; i++) {
                    printf("%d. %s (Stok: %d)\n", i+1, bukuArray[i].judul, bukuArray[i].stok);
                }

                // Pilih buku berdasarkan nomor
                int pilihan = input_int("Pilih nomor buku untuk pengembalian: ", 1, jumlahBuku);
                int index = pilihan - 1;

                if (bukuArray[index].peminjamAktif == NULL) {
                    printf("Tidak ada peminjam aktif untuk buku \"%s\".\n", bukuArray[index].judul);
                    break;
                }

                // Tampilkan daftar peminjam aktif
                printf("Daftar Peminjam Aktif untuk Buku \"%s\":\n", bukuArray[index].judul);
                borrowerAddress current = bukuArray[index].peminjamAktif;
                int indexPeminjam = 1;
                while (current != NULL) {
                    printf("%d. %s\n", indexPeminjam++, current->nama);
                    current = current->next;
                }

                // Pilih peminjam untuk mengembalikan buku
                int pilihanPeminjam = input_int("Pilih nomor peminjam yang akan mengembalikan buku: ", 1, indexPeminjam - 1);

                // Cari peminjam berdasarkan nomor urut
                current = bukuArray[index].peminjamAktif;
                indexPeminjam = 1;
                while (current != NULL && indexPeminjam < pilihanPeminjam) {
                    current = current->next;
                    indexPeminjam++;
                }

                if (current == NULL) {
                    printf("Peminjam tidak ditemukan.\n");
                    break;
                }

                char namaPeminjam[50];
                strcpy(namaPeminjam, current->nama);  // Simpan nama sebelum menghapus
                printf("Peminjam \"%s\" telah mengembalikan buku \"%s\".\n", namaPeminjam, bukuArray[index].judul);
                bukuArray[index].stok++;

                // Hapus dari peminjam aktif
                if (current == bukuArray[index].peminjamAktif) {
                    bukuArray[index].peminjamAktif = current->next;
                } else {
                    borrowerAddress temp = bukuArray[index].peminjamAktif;
                    while (temp != NULL && temp->next != current) {
                        temp = temp->next;
                    }
                    if (temp != NULL) {
                        temp->next = current->next;
                    }
                }
                free(current);

                // Simpan aktivitas
                pushAktivitas(&aktivitasTop, "pengembalian", bukuArray[index].judul, namaPeminjam, 0);
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 6: { // Batalkan Antrian
                if (isEmpty(firstQueue)) {
                    printf("Tidak ada antrian peminjam.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                printf("\nDaftar Antrian Peminjam:\n");
                printQueue(firstQueue);

                input_string(nama, sizeof(nama), "\nMasukkan nama peminjam yang akan dibatalkan: ");
                hapusPeminjamTertentu(nama, &firstQueue);
                
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 7: { // Peminjam Buku Aktif
                boolean adaPeminjamAktif = false;
                for(i = 0; i < jumlahBuku; i++) {
                    if (bukuArray[i].peminjamAktif != NULL) {
                        if (!adaPeminjamAktif) {
                            printf("\nDaftar Peminjam Buku Aktif:\n");
                            adaPeminjamAktif = true;
                        }
                        
                        printf("\n - Buku \"%s\" Sedang Dipinjam Oleh:\n", bukuArray[i].judul);
                        borrowerAddress current = bukuArray[i].peminjamAktif;
                        int indexPeminjam = 1;
                        
                        while (current != NULL && current->nama[0] != '\0') {
                            printf("%d. %s\n", indexPeminjam++, current->nama);
                            current = current->next;
                        }
                    }
                }

                if (!adaPeminjamAktif) {
                    printf("\nTidak ada buku yang sedang dipinjam.\n");
                }
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 8: { // Hapus Buku
                if (jumlahBuku == 0) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                for(i = 0; i < jumlahBuku; i++) {
                    printf("%d. %s (Stok: %d)\n", i+1, bukuArray[i].judul, bukuArray[i].stok);
                }

                // Pilih buku berdasarkan nomor
                int pilihan = input_int("Pilih nomor buku yang akan dihapus: ", 1, jumlahBuku);
                int index = pilihan - 1;

                // Hapus buku
                printf("Buku \"%s\" telah dihapus dari daftar.\n", bukuArray[index].judul);
                hapusBuku(bukuArray, &jumlahBuku, index);

                // Simpan aktivitas
                pushAktivitas(&aktivitasTop, "hapus_buku", bukuArray[index].judul, "-", 0);
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 9: { // Batalkan Aktivitas Terakhir
                if (aktivitasTop == NULL) {
                    printf("Tidak ada aktivitas yang dapat dibatalkan.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                undoAktivitas(&aktivitasTop, bukuArray, &jumlahBuku);
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 10: {
                // Validasi sebelum menjalankan test skenario
                if (jumlahBuku > 0) {
                    printf("\nPERHATIAN: Menjalankan test skenario akan menghapus semua data yang ada!\n");
                    printf("Apakah Anda yakin ingin melanjutkan? (y/n): ");
                    char konfirmasi;
                    scanf("%c", &konfirmasi);
                    getchar();
                    
                    if (konfirmasi != 'y' && konfirmasi != 'Y') {
                        printf("Test skenario dibatalkan.\n");
                        pressEnterToContinue();
                        clearScreen();
                        break;
                    }
                    
                    // Reset semua data
                    int i;
                    for (i = 0; i < jumlahBuku; i++) {
                        // Hapus peminjam aktif
                        borrowerAddress current = bukuArray[i].peminjamAktif;
                        while (current != NULL) {
                            borrowerAddress temp = current;
                            current = current->next;
                            free(temp);
                        }
                        bukuArray[i].peminjamAktif = NULL;
                    }
                    jumlahBuku = 0;

                    // Bersihkan antrian global
                    while (firstQueue != NULL) {
                        borrowerAddress temp = firstQueue;
                        firstQueue = firstQueue->next;
                        free(temp);
                    }
                }
                
                clearScreen();
                // Jalankan test skenario
                runTestScenario(bukuArray, &jumlahBuku, &aktivitasTop);
                
                // Hapus semua data skenario test setelah selesai
                for (i = 0; i < jumlahBuku; i++) {
                    // Hapus peminjam aktif
                    borrowerAddress current = bukuArray[i].peminjamAktif;
                    while (current != NULL) {
                        borrowerAddress temp = current;
                        current = current->next;
                        free(temp);
                    }
                    bukuArray[i].peminjamAktif = NULL;
                }
                jumlahBuku = 0;
                
                // Bersihkan antrian global
                while (firstQueue != NULL) {
                    borrowerAddress temp = firstQueue;
                    firstQueue = firstQueue->next;
                    free(temp);
                }
                
                // Hapus semua aktivitas dari stack
                while (aktivitasTop != NULL) {
                    popAktivitas(&aktivitasTop);
                }
                
                clearScreen();
                break;
            }
            case 0: { // Keluar
                clearAllBuku(bukuArray, &jumlahBuku);
                
                // Bersihkan antrian global
                while (firstQueue != NULL) {
                    borrowerAddress temp = firstQueue;
                    firstQueue = firstQueue->next;
                    free(temp);
                }
                
                while (aktivitasTop != NULL) {
                    popAktivitas(&aktivitasTop);
                }
                printf("Terima kasih telah menggunakan program ini.\n");
                break;
            }
        }
    } while (opsi != 0);

    // Free memori saat program selesai
    free(bukuArray);
}


