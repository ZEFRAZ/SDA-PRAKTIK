#include "antrian.h"

// Variabel global
bukuAddress listBuku = NULL;
borrowerAddress queueHead = NULL;
borrowerAddress activeBorrowers = NULL;

boolean isEmpty(borrowerAddress head) {
	return (head == NULL);
}

void printQueueForBook(bukuAddress b);  // Forward declaration

void printStatusBuku(bukuAddress b) {
    if (b == NULL) return;
    
    printf("\nBuku: %s (Stok: %d)\n", b->judul, b->stok);
    printf("Antrian peminjam:\n");
    
    borrowerAddress p = queueHead;
    boolean adaAntrian = false;
    
    while (p != NULL) {
        if (p->targetBuku == b) {
            adaAntrian = true;
            printf("- %s (%s)\n", p->nama, 
                   p->prioritas == DOSEN ? "Dosen" :
                   p->prioritas == MAHASISWA ? "Mahasiswa" : "Umum");
        }
        p = p->next;
    }
    
    if (!adaAntrian) {
        printf("(Tidak ada antrian)\n");
    }
    
    printf("Peminjam aktif:\n");
    p = activeBorrowers;
    boolean adaPeminjam = false;
    
    while (p != NULL) {
        if (p->targetBuku == b) {
            adaPeminjam = true;
            printf("- %s (%s)\n", p->nama, 
                   p->prioritas == DOSEN ? "Dosen" :
                   p->prioritas == MAHASISWA ? "Mahasiswa" : "Umum");
        }
        p = p->next;
    }
    
    if (!adaPeminjam) {
        printf("(Tidak ada peminjam aktif)\n");
    }
}

void printQueueForBook(bukuAddress b) {
    if (b == NULL) return;
    
    borrowerAddress current = queueHead;
    printf("Antrian untuk buku '%s':\n", b->judul);
    boolean adaAntrian = false;
    
    while (current != NULL) {
        if (current->targetBuku == b) {
            adaAntrian = true;
            printf("- %s (Prioritas: %d)\n", 
                   current->nama, current->prioritas);
        }
        current = current->next;
    }
    
    if (!adaAntrian) {
        printf("(Tidak ada antrian)\n");
    }
}

void printList(bukuAddress b) {
	if (b == NULL) {
		printf("Tidak ada buku dalam daftar.\n");
		return;
	}

	while (b != NULL) {
		printStatusBuku(b);
		b = b->next;
	}
}

void masukAntrian(borrowerAddress *head, borrowerAddress newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    borrowerAddress current = *head;
    borrowerAddress prev = NULL;

    // Find insertion point based on priority
    while (current != NULL && current->prioritas <= newNode->prioritas) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        newNode->next = *head;
        *head = newNode;
    } else {
        newNode->next = current;
        prev->next = newNode;
    }
}

void hapusPeminjam(bukuAddress buku, char namaPeminjam[]) {
	if (queueHead == NULL || buku == NULL) return;

	// Cari peminjam pertama untuk buku ini
	borrowerAddress current = queueHead;
	borrowerAddress prev = NULL;
	boolean found = false;

	while (current != NULL) {
		if (current->targetBuku == buku) {
			found = true;
			strcpy(namaPeminjam, current->nama);
			
			// Hapus dari antrian
			if (prev == NULL) {
				queueHead = current->next;
			} else {
				prev->next = current->next;
			}
			
			// Kurangi stok buku
			buku->stok--;
			
			// Pindahkan ke peminjam aktif dengan prioritas asli
			current->next = activeBorrowers;
			activeBorrowers = current;
			
			printf("\nPeminjaman berhasil!\n");
			printf("Peminjam: %s\n", current->nama);
			printf("Buku: %s\n", buku->judul);
			printf("Stok tersisa: %d\n", buku->stok);
			return;
		}
		prev = current;
		current = current->next;
	}

	if (!found) {
		printf("\nTidak ada peminjam dalam antrian untuk buku ini.\n");
	}
}

void hapusPeminjamTertentu(borrowerAddress *head, char namaTerhapus[], bukuAddress targetBuku) {
	if (*head == NULL) {
		printf("Antrian kosong.\n");
		return;
	}

	printf("Status sebelum pembatalan:\n");
	printStatusBuku(targetBuku);

	borrowerAddress current = *head;
	borrowerAddress prev = NULL;

	while (current != NULL && (strcmp(current->nama, namaTerhapus) != 0 || current->targetBuku != targetBuku)) {
		prev = current;
		current = current->next;
	}

	if (current == NULL) {
		printf("\nPeminjam \"%s\" tidak ditemukan untuk buku \"%s\".\n", namaTerhapus, targetBuku->judul);
		return;
	}

	if (prev == NULL) {
		*head = current->next;
	} else {
		prev->next = current->next;
	}

	free(current);
	printf("\nStatus setelah pembatalan:\n");
	printStatusBuku(targetBuku);
}

int jumlahElemen(borrowerAddress p) {
	int count = 0;
	while (p != NULL) {
		count++;
		p = p->next;
	}
	return count;
}

void printQueue(borrowerAddress queue) {
	if (queue == NULL) {
		printf("(Antrian Kosong)\n");
		return;
	}

	borrowerAddress current = queue;
	int no = 1;
	while (current != NULL) {
		printf("%d. %s (", no++, current->nama);
		switch(current->prioritas) {
			case DOSEN: printf("DOSEN"); break;
			case MAHASISWA: printf("MAHASISWA"); break;
			case UMUM: printf("MASYARAKAT UMUM"); break;
			case PEMINJAM_AKTIF: printf("PEMINJAM AKTIF"); break;
			default: printf("UNKNOWN"); break;
		}
		printf(") - Buku: %s\n", current->targetBuku->judul);
		current = current->next;
	}
}

void tampilkanSemuaAntrian() {
	borrowerAddress p = queueHead;
	if (p == NULL) {
		printf("\nTidak ada antrian peminjaman.\n");
		return;
	}

	printf("\nDaftar Antrian Peminjaman:\n");
	while (p != NULL) {
		printf("- \"%s\" mengantri untuk buku \"%s\" (", p->nama, p->targetBuku->judul);
		switch(p->prioritas) {
			case DOSEN: printf("DOSEN"); break;
			case MAHASISWA: printf("MAHASISWA"); break;
			case UMUM: printf("MASYARAKAT UMUM"); break;
			default: printf("UNKNOWN"); break;
		}
		printf(")\n");
		p = p->next;
	}
}

void tampilkanPeminjamAktif() {
	borrowerAddress p = activeBorrowers;
	if (p == NULL) {
		printf("\nTidak ada peminjam aktif.\n");
		return;
	}

	printf("\nDaftar Peminjam Aktif:\n");
	while (p != NULL) {
		printf("- \"%s\" meminjam buku \"%s\"\n", p->nama, p->targetBuku->judul);
		p = p->next;
	}
}

void kembalikanBuku(borrowerAddress *head, bukuAddress buku) {
	if (*head == NULL || buku == NULL) return;

	// Cari peminjam aktif untuk buku ini
	borrowerAddress current = *head;
	borrowerAddress prev = NULL;
	char namaPeminjam[50];
	boolean found = false;

	while (current != NULL) {
		if (current->targetBuku == buku) {
			found = true;
			strcpy(namaPeminjam, current->nama);
			
			// Hapus dari peminjam aktif
			if (prev == NULL) {
				*head = current->next;
			} else {
				prev->next = current->next;
			}
			
			// Tambah stok buku
			buku->stok++;
			
			printf("\nPengembalian berhasil!\n");
			printf("Peminjam: %s\n", namaPeminjam);
			printf("Buku: %s\n", buku->judul);
			printf("Stok tersisa: %d\n", buku->stok);
			
			// Proses peminjam berikutnya jika ada
			if (queueHead != NULL) {
				borrowerAddress nextBorrower = queueHead;
				while (nextBorrower != NULL) {
					if (nextBorrower->targetBuku == buku) {
						char temp[MAX_NAMA] = "";
						hapusPeminjam(buku, temp);
						break;
					}
					nextBorrower = nextBorrower->next;
				}
			}
			return;
		}
		prev = current;
		current = current->next;
	}

	if (!found) {
		printf("\nTidak ada peminjam aktif untuk buku ini.\n");
	}
}

void printDaftarPeminjam(bukuAddress b) {
	if (b == NULL) {
		printf("Error: Buku tidak ditemukan.\n");
		return;
	}

	printf("Daftar Peminjam:\n");
	borrowerAddress p = queueHead;
	int no = 1;
	boolean adaPeminjam = false;
	
	while (p != NULL) {
		if (p->targetBuku == b) {
			adaPeminjam = true;
			printf("%d. %s (", no++, p->nama);
			switch(p->prioritas) {
				case DOSEN: printf("DOSEN"); break;
				case MAHASISWA: printf("MAHASISWA"); break;
				case UMUM: printf("MASYARAKAT UMUM"); break;
				default: printf("UNKNOWN"); break;
			}
			printf(")\n");
		}
		p = p->next;
	}

	if (!adaPeminjam) {
		printf("(Tidak ada peminjam dalam antrian)\n");
	}
}

void batalkanPeminjaman(borrowerAddress *head, bukuAddress buku, char namaPeminjam[]) {
	if (*head == NULL || buku == NULL) return;

	// Cari peminjam di antrian
	borrowerAddress current = *head;
	borrowerAddress prev = NULL;
	boolean found = false;

	while (current != NULL) {
		if (current->targetBuku == buku && strcmp(current->nama, namaPeminjam) == 0) {
			found = true;
			
			// Hapus dari antrian
			if (prev == NULL) {
				*head = current->next;
			} else {
				prev->next = current->next;
			}
			
			printf("\nPembatalan berhasil!\n");
			printf("Peminjam: %s\n", namaPeminjam);
			printf("Buku: %s\n", buku->judul);
			
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}

	if (!found) {
		printf("\nPeminjam %s tidak ditemukan dalam antrian buku %s.\n", namaPeminjam, buku->judul);
	}
}

void printAllBuku() {
	bukuAddress current = listBuku;
	while (current != NULL) {
		printStatusBuku(current);
		current = current->next;
	}
}
