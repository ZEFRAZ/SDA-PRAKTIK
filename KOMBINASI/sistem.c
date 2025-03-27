#include <stdio.h>
#include <stdlib.h>
#include "sistem.h"
#include "list1.h"
#include "boolean.h"
#include "queue.h"
#include "stack.h"
#include "tampilan.h"

/* Fungsi untuk mendapatkan input integer yang valid */
int getValidInt(const char *prompt, int min, int max) {
    int value;
    int result;
    while (1) {
        printf("%s", prompt);
        fflush(stdout);
        result = scanf("%d", &value);
        if (result == 1 && value >= min && value <= max) {
            break;
        } else {
            printf("Input tidak valid. Masukkan angka antara %d dan %d.\n", min, max);
            while (getchar() != '\n');  // Bersihkan input buffer
        }
    }
    return value;
}

/* Fungsi bantu: menghitung jumlah elemen dalam List */
int countList(List L) {
    int count = 0;
    address p = First(L);
    while (p != Nil) {
        count++;
        p = Next(p);
    }
    return count;
}

/* Menampilkan status antrean setiap loket */
void displayAllQueues(List loket[], int jumlahLoket) {
    int i;
    printf("\n=== STATUS ANTREAN SETIAP LOKET ===\n");
    for (i = 0; i < jumlahLoket; i++) {
        printf("Loket %d: ", i + 1);
        printQueue(loket[i]);
        printf("\n");
    }
}

/* Proses pembelian tiket */
void processPurchase(List *loket, List *tiketTerjual, List loketArray[], int jumlahLoket) {
    int id;
    if (!dequeueQueue(loket, &id)) {
        displayMessage("Antrean di loket tersebut kosong!");
        return;
    }
    InsVLast(tiketTerjual, id);
    printf("\nPembelian tiket berhasil diproses.\n");
    displayAllQueues(loketArray, jumlahLoket);
    printf("Tiket Terjual: ");
    PrintInfo(*tiketTerjual);
}

/* Membatalkan transaksi terakhir */
void cancelTransaction(List *tiketTerjual, List *riwayatBatal) {
    int id;
    if (ListEmpty(*tiketTerjual)) {
        displayMessage("Tidak ada transaksi untuk dibatalkan (tiket terjual kosong)!");
        return;
    }
    DelVLast(tiketTerjual, &id);
    pushStack(riwayatBatal, id);
    printf("\nTiket ID-%d dibatalkan dan dicatat di riwayat.\n", id);
    printf("Tiket Terjual Saat Ini: ");
    PrintInfo(*tiketTerjual);
}

