/* ----------------------------------------------------- */ 
/* File Program : PTR6.CPP                               
/* Deskripsi : pointer yang menunjuk ke array  */ 
/* ---------------------------------------------------- */ 
#include <stdio.h>

int main() { 
    /* Kamus Data (deklarasi, inisialisasi nilai variabel)*/ 
    static int tgl_lahir[] = {18, 6, 1989}; // Mendeklarasikan array statis dengan tiga elemen
    int *ptgl; // Mendeklarasikan pointer ke integer
    ptgl = tgl_lahir; // Pointer menunjuk ke alamat awal array tgl_lahir

    // Menampilkan seluruh elemen array tgl_lahir menggunakan while
    printf("Nilai yang ditunjuk oleh ptgl:\n");
    
    int i = 0; // Inisialisasi indeks
    while (i < 3) { // Loop berjalan selama i kurang dari jumlah elemen array (3)
        printf("Elemen ke-%d: %d\n", i, *(ptgl + i)); // Mengakses elemen array melalui pointer
        i++; // Increment indeks untuk berpindah ke elemen berikutnya
    }

    return 0; 
}

/* STUDI KASUS : */ 

/* Eksekusi dan pahami maksud program ini (tulis tujuan program ini) */ 
/* Modifikasi program tersebut agar bisa menampilkan seluruh elemen array tgl_lahir !*/ 
