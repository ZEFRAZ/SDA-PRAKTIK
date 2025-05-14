#include "menu.h"
#include "stack.h"

static bukuAddress listBuku = NULL;
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
        printf("\n\n===== MENU PERPUSTAKAAN DOUBLY LINKED LIST =====\n");
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
                    newBuku->prev = NULL;
                    if (listBuku != NULL) {
                        listBuku->prev = newBuku;
                    }
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

                // Cek apakah nama sudah ada dalam antrian buku ini
                borrowerAddress existingBorrower = temp->firstQueue;
                boolean nameExists = false;

                while (existingBorrower != NULL) {
                    if (strcmp(existingBorrower->nama, nama) == 0) {
                        nameExists = true;
                        break;
                    }
                    existingBorrower = existingBorrower->next;
                }

                // Cek juga di peminjam aktif
                existingBorrower = temp->peminjamAktif;
                while (existingBorrower != NULL) {
                    if (strcmp(existingBorrower->nama, nama) == 0) {
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
                createBorrower(&newBorrower);
                infoBorrower(&newBorrower, nama, prioritas);

                masukAntrian(temp, newBorrower);
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
                    if (temp->firstQueue != NULL) {
                        hasQueuedBorrowers = true;
                        break;
                    }
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
                if (current->firstQueue == NULL) {
                    printf("Tidak ada antrian pada buku \"%s\".\n", current->judul);
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Ambil nama yang di-pop dan simpan prioritas asli *sebelum* hapus
                char namaTerhapus[100];
                int prioritasAsli = current->firstQueue->prioritas;  // << simpan dulu
                hapusPeminjam(&current, namaTerhapus);

                if (strcmp(namaTerhapus, "-") != 0) {
                    current->stok--;

                    // Tambahkan ke peminjam aktif (prioritas jadi PEMINJAM_AKTIF = 0)
                    borrowerAddress newBorrower;
                    createBorrower(&newBorrower);
                    infoBorrower(&newBorrower, namaTerhapus, PEMINJAM_AKTIF);
                    if (current->peminjamAktif == NULL) {
                        current->peminjamAktif = newBorrower;
                    } else {
                        borrowerAddress last = current->peminjamAktif;
                        while (last->next != NULL) last = last->next;
                        last->next = newBorrower;
                    }

                    // Push aktivitas dengan prioritas *asli* yang tadi disimpan
                    pushAktivitas(&aktivitasTop,
                                "peminjaman",
                                current->judul,
                                namaTerhapus,
                                prioritasAsli);

                    printf("\"%s\" berhasil meminjam buku \"%s\".\n",
                        namaTerhapus, current->judul);
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
                bukuAddress temp = listBuku;
                while (temp != NULL) {
                    if (temp->peminjamAktif != NULL) {
                        hasActiveBorrowers = true;
                        break;
                    }
                    temp = temp->next;
                }

                if (!hasActiveBorrowers) {
                    printf("Tidak ada peminjam aktif saat ini!\n");
                    printf("Silakan proses peminjaman buku terlebih dahulu.\n");
                    pressEnterToContinue();
                    break;
                }

                // Continue with existing return book logic
                // Tampilkan daftar buku
                printf("Daftar Buku:\n");
                temp = listBuku;
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

                if (temp->peminjamAktif == NULL) {
                    printf("Tidak ada peminjam aktif untuk buku \"%s\".\n", temp->judul);
                    break;
                }

                // Tampilkan daftar peminjam aktif
                printf("Daftar Peminjam Aktif untuk Buku \"%s\":\n", temp->judul);
                borrowerAddress current = temp->peminjamAktif;
                index = 1;
                while (current != NULL) {
                    printf("%d. %s\n", index, current->nama);
                    current = current->next;
                    index++;
                }

                // Pilih peminjam untuk mengembalikan buku
                int pilihanPeminjam = input_int("Pilih nomor peminjam yang akan mengembalikan buku: ", 1, index - 1);

                // Cari peminjam berdasarkan nomor urut
                current = temp->peminjamAktif;
                index = 1;
                while (current != NULL && index < pilihanPeminjam) {
                    current = current->next;
                    index++;
                }

                if (current == NULL) {
                    printf("Peminjam tidak valid.\n");
                    break;
                }

                // Proses pengembalian buku
                char namaPeminjam[50];
                strcpy(namaPeminjam, current->nama);  // Simpan nama sebelum menghapus
                printf("Peminjam \"%s\" telah mengembalikan buku \"%s\".\n", namaPeminjam, temp->judul);
                temp->stok++;

                // Hapus peminjam dari daftar peminjam aktif
                if (current == temp->peminjamAktif) {
                    temp->peminjamAktif = current->next;
                } else {
                    borrowerAddress prev = NULL;
                    borrowerAddress curr = temp->peminjamAktif;
                    while (curr != NULL && curr != current) {
                        prev = curr;
                        curr = curr->next;
                    }
                    if (curr != NULL) {
                        prev->next = curr->next;
                    }
                }
                free(current);

                // Simpan aktivitas
                pushAktivitas(&aktivitasTop, "pengembalian", temp->judul, namaPeminjam, 0);
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
                boolean hasQueuedBorrowers = false;
                bukuAddress temp = listBuku;
                while (temp != NULL) {
                    if (temp->firstQueue != NULL) {
                        hasQueuedBorrowers = true;
                        break;
                    }
                    temp = temp->next;
                }

                if (!hasQueuedBorrowers) {
                    printf("Tidak ada antrian peminjam yang dapat dibatalkan!\n");
                    printf("Silakan tambahkan peminjam ke antrian terlebih dahulu.\n");
                    pressEnterToContinue();
                    break;
                }

                // Continue with existing queue cancellation logic
                // Tampilkan daftar buku
                printf("\nDaftar Buku:\n");
                temp = listBuku;
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

                if (temp->firstQueue == NULL) {
                    printf("Tidak ada antrian pada buku \"%s\".\n", temp->judul);
                    pressEnterToContinue();
                    clearScreen();
                    break;
                }

                // Tampilkan daftar peminjam dalam antrian
                printf("\nDaftar Peminjam dalam Antrian untuk Buku \"%s\":\n", temp->judul);
                borrowerAddress current = temp->firstQueue;
                index = 1;
                while (current != NULL) {
                    printf("%d. %s\n", index++, current->nama);
                    current = current->next;
                }

                // Pilih peminjam yang akan dibatalkan
                int pilihanPeminjam = input_int("Pilih nomor peminjam yang akan dibatalkan: ", 1, index - 1);

                // Cari dan hapus peminjam yang dipilih
                char namaTerhapus[50];
                current = temp->firstQueue;
                borrowerAddress prev = NULL;
                for (i = 1; i < pilihanPeminjam; i++) {
                    prev = current;
                    current = current->next;
                }
                strcpy(namaTerhapus, current->nama);
                
                hapusPeminjamTertentu(&temp, namaTerhapus, &temp->firstQueue);
                printf("Peminjam \"%s\" telah dibatalkan dari antrian buku \"%s\".\n", namaTerhapus, temp->judul);
                
                pressEnterToContinue();
                clearScreen();
                break;
            }
            case 7: { // Peminjam Buku Aktif
                bukuAddress temp = listBuku;
                boolean adaPeminjamAktif = false;

                while (temp != NULL) {
                    if (temp->peminjamAktif != NULL) {
                        if (!adaPeminjamAktif) {
                            printf("\nDaftar Peminjam Buku Aktif:\n");
                            adaPeminjamAktif = true;
                        }
                        
                        printf("\n - Buku \"%s\" Sedang Dipinjam Oleh:\n", temp->judul);
                        borrowerAddress current = temp->peminjamAktif;
                        int index = 1;
                        
                        while (current != NULL && current->nama[0] != '\0') {
                            printf("%d. %s\n", index, current->nama);
                            current = current->next;
                            index++;
                        }
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
            case 10:
                clearScreen();
                runTestScenario(&listBuku, &aktivitasTop);
                clearScreen();
                break;
            case 0: { // Keluar
                clearAllBuku(&listBuku);
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

