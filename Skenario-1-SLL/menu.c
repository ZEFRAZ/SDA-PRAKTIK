#include "menu.h"
#include "stack.h"

// Referensi dari antrian.c, bukan redefinisi
extern bukuAddress listBuku;
static aktivitasStack aktivitasTop = NULL;

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

// Fungsi untuk membersihkan semua data
static void clearAllData() {
    // Hapus semua buku
    clearAllBuku(&listBuku);
    listBuku = NULL;
    
    // Hapus semua peminjam
    clearAllBorrower(&queueHead);
    clearAllBorrower(&activeBorrowers);
    
    // Hapus semua aktivitas
    while (aktivitasTop != NULL) {
        popAktivitas(&aktivitasTop);
    }
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

boolean isBookExists(bukuAddress b, const char* judul) {
    while (b != NULL) {
        if (strcmp(b->judul, judul) == 0) {
            return true;
        }
        b = b->next;
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

    do {
        clearScreen();
        printf("\n\n===== MENU PERPUSTAKAAN SINGLE LINKED LIST =====\n");
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

                bukuAddress temp = listBuku;
                while (temp != NULL && strcmp(temp->judul, judul) != 0) {
                    temp = temp->next;
                }

                if (temp != NULL) {
                    temp->stok += stok;
                    printf("Stok buku \"%s\" ditambahkan menjadi %d.\n", judul, temp->stok);
                } else {
                    bukuAddress newBuku;
                    createBuku(&newBuku);
                    infoBuku(&newBuku, judul, stok);

                    newBuku->next = listBuku;
                    listBuku = newBuku;
                    printf("Buku \"%s\" ditambahkan dengan stok %d.\n", judul, stok);

                    // Simpan aktivitas
                    pushAktivitas(&aktivitasTop, "tambah_buku", judul, "-", stok);
                }
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 2: { // Tambah Peminjam ke Antrian Buku
                if (listBuku == NULL) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                bukuAddress temp = listBuku;
                int index = 1;
                while (temp != NULL) {
                    printf("%d. %s (Stok: %d)\n", index, temp->judul, temp->stok);
                    temp = temp->next;
                    index++;
                }

                // Pilih buku berdasarkan nomor
                int pilihan = input_int("Pilih nomor buku untuk menambahkan peminjam: ", 1, index - 1);

                // Cari buku berdasarkan nomor
                temp = listBuku;
                index = 1;
                while (temp != NULL && index < pilihan) {
                    temp = temp->next;
                    index++;
                }

                if (temp == NULL) {
                    printf("Buku tidak valid.\n");
                    break;
                }

                // Tambahkan peminjam ke antrian buku
                char nama[50];
                input_string(nama, sizeof(nama), "Masukkan Nama Peminjam: ");

                // Cek apakah nama sudah ada dalam antrian
                borrowerAddress existingBorrower = queueHead;
                boolean nameExists = false;

                while (existingBorrower != NULL) {
                    if (existingBorrower->targetBuku == temp && 
                        strcmp(existingBorrower->nama, nama) == 0) {
                        nameExists = true;
                        break;
                    }
                    existingBorrower = existingBorrower->next;
                }

                // Cek juga di peminjam aktif
                existingBorrower = activeBorrowers;
                while (existingBorrower != NULL) {
                    if (existingBorrower->targetBuku == temp && 
                        strcmp(existingBorrower->nama, nama) == 0) {
                        nameExists = true;
                        break;
                    }
                    existingBorrower = existingBorrower->next;
                }

                if (nameExists) {
                    printf("Peminjam dengan nama \"%s\" sudah ada dalam antrian atau sedang meminjam buku ini.\n", nama);
                    pressEnterToContinue();
                    clearScreen();
                    break;
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
                createBorrower(&newBorrower, temp);
                infoBorrower(&newBorrower, nama, prioritas);

                masukAntrian(&queueHead, newBorrower);
                printf("Peminjam \"%s\" berhasil ditambahkan ke antrian buku \"%s\".\n", nama, temp->judul);

                // Simpan aktivitas
                pushAktivitas(&aktivitasTop, "tambah_peminjam", temp->judul, nama, prioritas);
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 3: { // Tampilkan Daftar Buku dan Antrian
                if (listBuku == NULL) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                printf("\nDaftar Buku dan Antrian Peminjam:");
                printList(listBuku);
                printf("\n");
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 4: { // Proses Peminjaman Buku
                if (listBuku == NULL) {
                    printf("Tidak ada buku dalam daftar.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Cek ada antrian peminjam
                boolean hasQueuedBorrowers = false;
                bukuAddress temp = listBuku;
                while (temp != NULL) {
                    borrowerAddress current = queueHead;
                    while (current != NULL) {
                        if (current->targetBuku == temp) {
                            hasQueuedBorrowers = true;
                            break;
                        }
                        current = current->next;
                    }
                    if (hasQueuedBorrowers) break;
                    temp = temp->next;
                }

                if (!hasQueuedBorrowers) {
                    printf("Tidak ada antrian peminjam buku saat ini!\n");
                    printf("Silakan tambahkan peminjam ke antrian terlebih dahulu.\n");
                    pressEnterToContinue();
                    break;
                }

                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                bukuAddress current = listBuku;
                int index = 1;
                while (current != NULL) {
                    printf("%d. %s (Stok: %d)\n", index, current->judul, current->stok);
                    current = current->next;
                    index++;
                }

                int pilihan = input_int("Pilih nomor buku untuk proses peminjaman: ", 1, index - 1);

                current = listBuku;
                int i;
                for (i = 1; i < pilihan && current != NULL; i++) {
                    current = current->next;
                }

                if (current == NULL) {
                    printf("Buku tidak ditemukan.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                if (current->stok <= 0) {
                    printf("Maaf, stok buku \"%s\" sedang habis.\n", current->judul);
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Cek apakah ada antrian untuk buku ini
                boolean hasQueue = false;
                borrowerAddress queueCurrent = queueHead;
                while (queueCurrent != NULL) {
                    if (queueCurrent->targetBuku == current) {
                        hasQueue = true;
                        break;
                    }
                    queueCurrent = queueCurrent->next;
                }

                if (!hasQueue) {
                    printf("Tidak ada antrian pada buku \"%s\".\n", current->judul);
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Ambil nama yang di-pop dan simpan prioritas asli
                char namaTerhapus[100] = "";
                int prioritasAsli = -1;
                borrowerAddress firstInQueue = queueHead;
                while (firstInQueue != NULL) {
                    if (firstInQueue->targetBuku == current) {
                        prioritasAsli = firstInQueue->prioritas;
                        break;
                    }
                    firstInQueue = firstInQueue->next;
                }

                hapusPeminjam(current, namaTerhapus);

                if (strlen(namaTerhapus) > 0) {
                    // Push aktivitas dengan prioritas asli yang tadi disimpan
                    pushAktivitas(&aktivitasTop,
                                "peminjaman",
                                current->judul,
                                namaTerhapus,
                                prioritasAsli);
                }

                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 5: { // Pengembalian Buku
                if (listBuku == NULL) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Check if there are any active borrowers
                boolean hasActiveBorrowers = false;
                borrowerAddress activeTemp = activeBorrowers;
                while (activeTemp != NULL) {
                    hasActiveBorrowers = true;
                    break;
                }

                if (!hasActiveBorrowers) {
                    printf("Tidak ada peminjam aktif saat ini!\n");
                    printf("Silakan proses peminjaman buku terlebih dahulu.\n");
                    pressEnterToContinue();
                    break;
                }

                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                bukuAddress temp = listBuku;
                int index = 1;
                while (temp != NULL) {
                    printf("%d. %s (Stok: %d)\n", index, temp->judul, temp->stok);
                    temp = temp->next;
                    index++;
                }

                // Pilih buku berdasarkan nomor
                int pilihan = input_int("Pilih nomor buku untuk pengembalian: ", 1, index - 1);

                // Cari buku berdasarkan nomor
                temp = listBuku;
                index = 1;
                while (temp != NULL && index < pilihan) {
                    temp = temp->next;
                    index++;
                }

                if (temp == NULL) {
                    printf("Buku tidak valid.\n");
                    break;
                }

                // Cari peminjam aktif untuk buku ini
                borrowerAddress current = activeBorrowers;
                boolean hasBorrowers = false;
                printf("Daftar Peminjam Aktif untuk Buku \"%s\":\n", temp->judul);
                index = 1;
                
                while (current != NULL) {
                    if (current->targetBuku == temp) {
                        printf("%d. %s\n", index++, current->nama);
                        hasBorrowers = true;
                    }
                    current = current->next;
                }

                if (!hasBorrowers) {
                    printf("Tidak ada peminjam aktif untuk buku \"%s\".\n", temp->judul);
                    break;
                }

                // Pilih peminjam untuk mengembalikan buku
                int pilihanPeminjam = input_int("Pilih nomor peminjam yang akan mengembalikan buku: ", 1, index - 1);

                // Cari peminjam berdasarkan nomor urut
                current = activeBorrowers;
                index = 1;
                int currentIndex = 1;
                
                while (current != NULL) {
                    if (current->targetBuku == temp) {
                        if (currentIndex == pilihanPeminjam) {
                            break;
                        }
                        currentIndex++;
                    }
                    current = current->next;
                }

                if (current == NULL) {
                    printf("Peminjam tidak valid.\n");
                    break;
                }

                // Proses pengembalian buku
                char namaPeminjam[50];
                strcpy(namaPeminjam, current->nama);
                int prioritasAsli = current->prioritas;  // Simpan prioritas asli

                // Hapus dari daftar peminjam aktif
                if (current == activeBorrowers) {
                    activeBorrowers = current->next;
                } else {
                    borrowerAddress prev = activeBorrowers;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    prev->next = current->next;
                }

                free(current);
                temp->stok++;
                printf("Peminjam \"%s\" telah mengembalikan buku \"%s\".\n", namaPeminjam, temp->judul);

                // Simpan aktivitas dengan prioritas asli
                pushAktivitas(&aktivitasTop, "pengembalian", temp->judul, namaPeminjam, prioritasAsli);
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 6: { // Batalkan Antrian
                if (listBuku == NULL) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Check if there are any queued borrowers
                if (queueHead == NULL) {
                    printf("Tidak ada antrian peminjam yang dapat dibatalkan!\n");
                    printf("Silakan tambahkan peminjam ke antrian terlebih dahulu.\n");
                    pressEnterToContinue();
                    break;
                }

                // Tampilkan daftar buku
                printf("\nDaftar Buku:\n");
                bukuAddress temp = listBuku;
                int index = 1;
                while (temp != NULL) {
                    printf("%d. %s\n", index++, temp->judul);
                    temp = temp->next;
                }

                // Pilih buku
                int pilihan = input_int("Pilih nomor buku: ", 1, index - 1);

                // Cari buku yang dipilih
                temp = listBuku;
                int i;
                for (i = 1; i < pilihan; i++) {
                    temp = temp->next;
                }

                // Cek apakah ada antrian untuk buku ini
                boolean hasQueue = false;
                borrowerAddress queueCurrent = queueHead;
                while (queueCurrent != NULL) {
                    if (queueCurrent->targetBuku == temp) {
                        hasQueue = true;
                        break;
                    }
                    queueCurrent = queueCurrent->next;
                }

                if (!hasQueue) {
                    printf("Tidak ada antrian pada buku \"%s\".\n", temp->judul);
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Tampilkan daftar peminjam dalam antrian untuk buku ini
                printf("\nDaftar Peminjam dalam Antrian untuk Buku \"%s\":\n", temp->judul);
                borrowerAddress current = queueHead;
                index = 1;
                while (current != NULL) {
                    if (current->targetBuku == temp) {
                        printf("%d. %s\n", index++, current->nama);
                    }
                    current = current->next;
                }

                // Pilih peminjam yang akan dibatalkan
                int pilihanPeminjam = input_int("Pilih nomor peminjam yang akan dibatalkan: ", 1, index - 1);

                // Cari dan hapus peminjam yang dipilih
                char namaTerhapus[50];
                current = queueHead;
                int currentIndex = 1;
                
                while (current != NULL) {
                    if (current->targetBuku == temp) {
                        if (currentIndex == pilihanPeminjam) {
                            strcpy(namaTerhapus, current->nama);
                            hapusPeminjamTertentu(&queueHead, namaTerhapus, temp);
                            printf("Peminjam \"%s\" telah dibatalkan dari antrian buku \"%s\".\n", 
                                   namaTerhapus, temp->judul);
                            break;
                        }
                        currentIndex++;
                    }
                    current = current->next;
                }
                
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 7: { // Peminjam Buku Aktif
                bukuAddress temp = listBuku;
                boolean adaPeminjamAktif = false;

                // Tampilkan peminjam aktif berdasarkan buku
                while (temp != NULL) {
                    boolean bukuIniAdaPeminjam = false;
                    borrowerAddress current = activeBorrowers;
                    
                    // Cek peminjam aktif untuk buku ini
                    while (current != NULL) {
                        if (current->targetBuku == temp) {
                            if (!bukuIniAdaPeminjam) {
                                if (!adaPeminjamAktif) {
                                    printf("\nDaftar Peminjam Buku Aktif:\n");
                                    adaPeminjamAktif = true;
                                }
                                printf("\n - Buku \"%s\" Sedang Dipinjam Oleh:\n", temp->judul);
                                bukuIniAdaPeminjam = true;
                            }
                            printf("   * %s\n", current->nama);
                        }
                        current = current->next;
                    }
                    temp = temp->next;
                }

                if (!adaPeminjamAktif) {
                    printf("\nTidak ada buku yang sedang dipinjam.\n");
                }
                
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 8: { // Hapus Buku
                if (listBuku == NULL) {
                    printf("\nBelum ada buku yang tersedia dalam sistem.\n");
                    printf("Silakan tambahkan buku terlebih dahulu menggunakan opsi 1.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                bukuAddress temp = listBuku;
                int index = 1;
                while (temp != NULL) {
                    printf("%d. %s (Stok: %d)\n", index, temp->judul, temp->stok);
                    temp = temp->next;
                    index++;
                }

                // Pilih buku berdasarkan nomor
                int pilihan = input_int("Pilih nomor buku yang akan dihapus: ", 1, index - 1);

                // Cari buku berdasarkan nomor
                temp = listBuku;
                index = 1;
                while (temp != NULL && index < pilihan) {
                    temp = temp->next;
                    index++;
                }

                if (temp == NULL) {
                    printf("Buku tidak valid.\n");
                    break;
                }

                // Hapus semua peminjam yang mengantri untuk buku ini
                borrowerAddress current = queueHead;
                borrowerAddress prev = NULL;
                while (current != NULL) {
                    borrowerAddress next = current->next;
                    if (current->targetBuku == temp) {
                        if (prev == NULL) {
                            queueHead = next;
                        } else {
                            prev->next = next;
                        }
                        free(current);
                    } else {
                        prev = current;
                    }
                    current = next;
                }

                // Hapus semua peminjam aktif untuk buku ini
                current = activeBorrowers;
                prev = NULL;
                while (current != NULL) {
                    borrowerAddress next = current->next;
                    if (current->targetBuku == temp) {
                        if (prev == NULL) {
                            activeBorrowers = next;
                        } else {
                            prev->next = next;
                        }
                        free(current);
                    } else {
                        prev = current;
                    }
                    current = next;
                }

                // Hapus buku
                printf("Buku \"%s\" telah dihapus dari daftar.\n", temp->judul);
                deleteBuku(&listBuku, temp);

                // Simpan aktivitas
                pushAktivitas(&aktivitasTop, "hapus_buku", temp->judul, "-", 0);
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 9: { // Batalkan Aktivitas Terakhir
                if (aktivitasTop == NULL) {
                    printf("\nTidak ada aktivitas yang dapat dibatalkan.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Periksa jika aktivitas terakhir adalah peminjaman atau pengembalian
                if (strcmp(aktivitasTop->jenis, "peminjaman") != 0 && 
                    strcmp(aktivitasTop->jenis, "pengembalian") != 0) {
                    printf("\nHanya aktivitas peminjaman dan pengembalian yang dapat dibatalkan.\n");
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                undoAktivitas(&aktivitasTop, &listBuku);
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 10: { // Jalankan Test Scenario
                clearScreen();
                
                // Tampilkan pesan peringatan dan konfirmasi
                printf("\n===== PERINGATAN TEST SCENARIO =====\n\n");
                printf("Test scenario akan menghapus semua data yang ada dan menjalankan skenario pengujian.\n");
                printf("Semua buku, antrian, dan data peminjam akan dihapus.\n\n");
                
                printf("Pilihan:\n");
                printf("1. Lanjutkan dan hapus semua data\n");
                printf("2. Kembali ke menu utama\n");
                
                int pilihan = input_int("Pilihan Anda: ", 1, 2);
                
                if (pilihan == 1) {
                    // Bersihkan semua data
                    clearAllData();
                    
                    // Jalankan test scenario
                    runTestScenario(&listBuku, &aktivitasTop);
                } else {
                    printf("\nTest scenario dibatalkan. Kembali ke menu utama.\n");
                    pressEnterToContinue();
                }
                
                clearScreen();
                break;
            }
            case 0: { // Keluar
                clearAllBuku(&listBuku);
                clearAllBorrower(&queueHead);
                clearAllBorrower(&activeBorrowers);
                while (aktivitasTop != NULL) {
                    popAktivitas(&aktivitasTop);
                }
                printf("\nKeluar dari program.\n");
                printf("TERIMA KASIH SUDAH DATANG DI PERPUSTAKAAN KAMI.....\n");
                break;
            }
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (opsi != 0);
}


