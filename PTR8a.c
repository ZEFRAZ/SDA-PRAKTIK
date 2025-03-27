/* -------------------------------------------------------------------------------- */ 
/* File Program : PTR8a.CPP                                               
*/ 
/* (Pointer dan String bagian ke-2)                                 
*/ 
/* Deskripsi : menukar isi dua buah string TANPA pemakaian pointer */ 
/* ------------------------------------------------------------------------------- */ 
#include <stdio.h>  // Untuk fungsi input/output seperti printf dan puts
#include <string.h> // Untuk fungsi manipulasi string seperti strcpy
#define PANJANG 20  // Mendefinisikan ukuran maksimum array karakter

int main() 
{ 
    /* Kamus Data (deklarasi, inisialisasi nilai variabel)*/ 
    char nama1[PANJANG] = "DEWI SARTIKA";         // Array karakter untuk nama pertama
    char nama2[PANJANG] = "SULTAN HASANUDDIN";    // Array karakter untuk nama kedua
    char namaX[PANJANG];                          // Variabel sementara untuk membantu pertukaran

    // Menampilkan nilai awal dari kedua string
    puts("Nama semula : "); 
    printf("Nama 1 --> %s\n", nama1); // Menampilkan isi nama1
    printf("Nama 2 --> %s\n", nama2); // Menampilkan isi nama2

    /* Pertukaran string */ 
    strcpy(namaX, nama1); // Menyalin isi nama1 ke namaX (variabel sementara)
    strcpy(nama1, nama2); // Menyalin isi nama2 ke nama1
    strcpy(nama2, namaX); // Menyalin isi namaX (yang berisi nama1) ke nama2

    // Menampilkan nilai string setelah pertukaran
    puts("Nama sekarang : "); 
    printf("Nama 1 --> %s\n", nama1); // Menampilkan isi nama1 setelah pertukaran
    printf("Nama 2 --> %s\n", nama2); // Menampilkan isi nama2 setelah pertukaran

    return 0; // Program selesai
}
