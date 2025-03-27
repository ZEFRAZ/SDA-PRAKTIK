#include <stdio.h>
#include <stdlib.h>
#include "list1.h"
#include "boolean.h"
#include "queue.h"
#include "stack.h"
#include "tampilan.h"
#include "sistem.h"

#define MAX_LOKET 10  

int main(void) {
    /* Meminta jumlah loket */
    int jumlahLoket = getValidInt("Masukkan jumlah loket yang ingin dibuka (1 - 10): ", 1, MAX_LOKET);

    /* Inisialisasi array loket */
    List loket[MAX_LOKET];
    int i;
    for (i = 0; i < jumlahLoket; i++) {
        CreateList(&loket[i]);
    }

    /* Inisialisasi daftar tiket terjual dan riwayat pembatalan */
    List tiketTerjual, riwayatBatal;
    CreateList(&tiketTerjual);
    CreateList(&riwayatBatal);

    int idCounter = 1;
    int choice;
    static int currentLoket = 0;  // Untuk round-robin proses pembelian antar loket

    do {
        displayMainMenu();
        choice = getValidInt("", 1, 4);  // Validasi input menu antara 1 dan 4

        switch (choice) {
            case 1: {
                /* Tambah Pembeli ke Loket dengan antrean terpendek */
                int index = 0;
                int minCount = countList(loket[0]);
                for (i = 1; i < jumlahLoket; i++) {
                    int cnt = countList(loket[i]);
                    if (cnt < minCount) {
                        minCount = cnt;
                        index = i;
                    }
                }
                int id = idCounter++;
                enqueueQueue(&loket[index], id);
                printf("\nPembeli dengan Tiket ID-%d masuk ke Loket %d.\n", id, index + 1);
                break;
            }
            case 2: {
                /* Proses Pembelian: mencari loket dengan antrean non-kosong */
                int loketPilihan = -1;
                int j;
                for (j = 0; j < jumlahLoket; j++) {
                    int index = (currentLoket + j) % jumlahLoket;
                    if (countList(loket[index]) > 0) {
                        loketPilihan = index;
                        currentLoket = (index + 1) % jumlahLoket;
                        break;
                    }
                }
                if (loketPilihan == -1) {
                    displayMessage("Tidak ada pembeli di antrean di semua loket.");
                } else {
                    processPurchase(&loket[loketPilihan], &tiketTerjual, loket, jumlahLoket);
                }
                break;
            }
            case 3:
                /* Batalkan transaksi terakhir */
                cancelTransaction(&tiketTerjual, &riwayatBatal);
                break;
            case 4:
                /* Keluar dari program */
                displayMessage("Program selesai.");
                break;
            default:
                displayMessage("Pilihan tidak valid!");
        }
    } while (choice != 4);
	
	for (i = 0; i < jumlahLoket; i++) {
        DelAll(&loket[i]);
    }
    DelAll(&tiketTerjual);
    DelAll(&riwayatBatal);
    
    return 0;
}

