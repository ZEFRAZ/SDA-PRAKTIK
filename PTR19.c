/* --------------------------------------------------------------------------------------------------------- */ 
/* File Program : PTR19.CPP                               
/* Deskripsi   : Maksud program sama dengan PTR18.cpp. Cari perbedaannnya!   
*/ 
/* --------------------------------------------------------------------------------------------------------- */ 
#include <stdlib.h> 
#include <stdio.h>

/* Definisi tabel integer */ 
typedef struct { 
    int *tab;  // Pointer ke array integer (dinamis)
    int N;     // Ukuran efektif array
} tabint; 

/* Prototype */ 
void incTab (tabint *T);  // Fungsi untuk menambah setiap elemen array
void printTab (tabint T); // Fungsi untuk mencetak isi array

int main() 
{  
    /* kamus */ 
    tabint T; // Deklarasi variabel T bertipe tabint
    int i; 

    /* program */ 
    T.tab = (int *) malloc (3 * sizeof(int)); // Alokasi memori untuk array dinamis
    T.N = 3; // Mengatur ukuran efektif array

    printf("Isi dan print tabel untuk indeks 1..3 \n"); 

    /* isi dari pembacaan */ 
    for (i = 0; i < T.N; i++) { 
        printf("Input tabel ke -[%d] = ", i); 
        scanf ("%d", &(T.tab[i])); // Membaca nilai dari pengguna
    } 

    printTab(T); /* Print : perhatikan passing parameter by value */ 
    incTab (&T); /* Increment : perhatikan passing parameter by reference */ 
    printTab (T); 

    return 0; 
} 

/* Body prototype */ 
void incTab(tabint *T)   
/* Increment setiap elemen tabel */ 
{   
    /* Kamus lokal */ 
    int i; 

    /* Program */ 
    for (i = 0; i < (*T).N; i++) 
    {  
        (*T).tab[i] = (*T).tab[i] + 1; // Menambah setiap elemen array
    } 
} 

void printTab(tabint T)  
{ 
    /* Kamus lokal */ 
    int i; 

    /* Print setiap elemen tabel */ 
    for (i = 0; i < T.N; i++) 
    {  
        printf("T[%d] = %d \n", i, T.tab[i]); // Mencetak setiap elemen array
    } 
}
