/* --------------------------------------------------------------------------------------------------------- */ 
/* File Program : PTR17.CPP                               
/* Deskripsi   : Array dengan def type:mengisi dg assignment, menulis     
*/  
/* --------------------------------------------------------------------------------------------------------- */ 
#include <stdlib.h> 
#include <stdio.h>

int main() 
{ 
    /* kamus */ 
    /* Definisi tabel integer */ 
    typedef struct { 
        int *T;   // Pointer ke array integer
        int N;    // Ukuran efektif array
    } tabint; 

    tabint MyTab; // Deklarasi variabel MyTab bertipe tabint
    int i; 

    /* program */ 
    printf("Tentukan ukuran tabel, maks 10 = "); 
    scanf("%d", &(MyTab.N)); // Membaca ukuran array dari pengguna

    MyTab.T = (int *) malloc (MyTab.N * sizeof(int)); // Alokasi memori untuk array

    /* isi dengan assignment */ 
    for (i = 0; i < MyTab.N; i++) { 
        *(MyTab.T + i) = i; // Mengisi array dengan nilai i
        printf("i = %d MyTab.T = %d \n", i, *(MyTab.T + i)); // Menampilkan nilai array
    } 

    return 0; 
}
