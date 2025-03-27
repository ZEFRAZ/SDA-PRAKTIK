#include <stdio.h>
#include <stdlib.h>
#include "teller.h"

// Menampilkan menu pilihan
void displayMenu() {
    printf("\n========== Sistem Antrian Bank ==========\n");
    printf("1. Ambil Nomor Antrian\n");
    printf("2. Proses Antrian\n");
    printf("3. Tampilkan Status Teller\n");
    printf("4. Keluar\n");
    printf("===========================================\n");
    printf("Pilih opsi (1-4): ");
}

int main() {
    TellerSystem ts;
    int numTellers, choice, tellerNumber;
    
    // Input jumlah teller
    printf("Masukkan jumlah teller: ");
    scanf("%d", &numTellers);
    
    // Buat sistem teller (nama teller diisi secara otomatis dengan nomor)
    CreateTellerSystem(&ts, numTellers);
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: { // Ambil nomor antrian
                printf("\n--- Daftar Teller ---\n");
                DisplayAllTellers(ts);
                printf("\nPilih teller (masukkan nomor teller): ");
                scanf("%d", &tellerNumber);
                
                if (tellerNumber < 1 || tellerNumber > numTellers) {
                    printf("Teller tidak ditemukan!\n");
                } else {
                    int queueNumber = TakeQueueNumber(&ts, tellerNumber - 1);
                    printf("\nNomor antrian Anda: %d\n", queueNumber);
                    DisplayTeller(ts.tellers[tellerNumber - 1]);
                }
                break;
            }
            
            case 2: { // Proses antrian
                printf("\n--- Daftar Teller ---\n");
                DisplayAllTellers(ts);
                printf("\nPilih teller untuk memproses antrian (masukkan nomor teller): ");
                scanf("%d", &tellerNumber);
                
                if (tellerNumber < 1 || tellerNumber > numTellers) {
                    printf("Teller tidak ditemukan!\n");
                } else {
                    if (ProcessQueue(&ts, tellerNumber - 1)) {
                        printf("\nBerhasil memproses antrian.\n");
                    } else {
                        printf("\nTidak ada antrian untuk diproses!\n");
                    }
                    DisplayTeller(ts.tellers[tellerNumber - 1]);
                }
                break;
            }
            
            case 3: { // Tampilkan status teller
                DisplayAllTellers(ts);
                break;
            }
            
            case 4: { // Keluar
                printf("\nTerima kasih telah menggunakan Sistem Antrian Bank!\n");
                break;
            }
            
            default: {
                printf("\nOpsi tidak valid! Silakan pilih antara 1-4.\n");
                break;
            }
        }
    } while (choice != 4);
    
    // Bersihkan sistem teller
    CleanupTellerSystem(&ts);
    return 0;
}

