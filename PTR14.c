/* ---------------------------------------------------------------------------------------------- */ 
/* File Program : PTR14.CPP                                 
*/ 
/* Deskripsi : Array dinamis, dimana ukuran array ditentukan dari read keyboard */ 
/* ---------------------------------------------------------------------------------------------- */ 
#include <stdlib.h>  // Untuk fungsi malloc dan free
#include <stdio.h>   // Untuk fungsi printf dan scanf

int main() 
{ 
    /* Kamus Data (deklarasi, inisialisasi nilai variabel)*/ 
    int *tab; // Pointer ke array dinamis
    int N, i; // N adalah ukuran array, i adalah variabel iterasi

    /* program */ 
    printf("Contoh mengisi array dinamis berukuran 0..N : \n"); 
    printf("N = "); 
    scanf("%d", &N); // Membaca ukuran array dari pengguna

    printf("Alokasi setelah mengetahui ukuran array \n"); 
    tab = (int *) malloc((N+1) * sizeof(int)); // Mengalokasikan memori untuk array

    if (tab != NULL) // Jika alokasi berhasil
    { 
        for (i = 0; i <= N; i++) 
        { 
            printf("i=%d tab[i]=%d \n", i, *(tab + i)); // Menampilkan nilai awal array
        } 
        printf("Akhir program \n"); 

        /* dealloc */ 
        free(tab);  // Membebaskan memori yang dialokasikan
        return 0; 
    } 
    else // Jika alokasi gagal
    { 
        printf("Alokasi gagal ... \n"); 
        return 1; 
    } 
}
