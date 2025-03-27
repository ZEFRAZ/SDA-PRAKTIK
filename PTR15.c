/* ---------------------------------------------------------------------------------------------------------------- */ 
/* File Program : PTR15.CPP                                        
*/ 
/* Deskripsi   : Array of string : Pendefinisian dan pengaksesan. Perhatikanlah permasalahannya */ 
/* ---------------------------------------------------------------------------------------------------------------- */ 
#include <stdio.h>  // Library untuk input/output
#include <stdlib.h> // Library untuk alokasi memori dinamis

int main() 
{ 
    /* kamus */ 
    /* Definisi array yang elemennya string, statik dan sekaligus mengisi */ 
    static char *s[3] = {"the", "time", "is"};  // Array of string statis

    /* Definisi array yang elemennya string, dinamik */ 
    char *(*TabStr);  // Pointer ke array of string dinamis
    int i;  // Variabel indeks

    /* program */ 
    for (i=0; i < 3; i++) {   // Cetak isi array statis
        printf("%s\n", s[i]); 
    } 

    /* Alokasi TabStr sebanyak 3 */ 
    TabStr = (char **) malloc (3 * sizeof(char *));  // Alokasi memori untuk array of string dinamis

    for (i=0; i < 3; i++) { 
        /* Alokasi string yang merupakan elemen tabel */ 
        *(TabStr + i) = (char *) malloc (5 * sizeof(char));  // Alokasi memori untuk setiap string
        printf("\nInput Str[%d], maksimum 5 karakter : ", i); 
        scanf("%5s", *(TabStr+i));  // Input string dari pengguna
        /* Mengisi nilai string */ 
        printf("\n Nilai Str[%d] : %5s\n ", i, *(TabStr + i));  // Cetak string yang diinput
    } 

    return 0;  // Akhir program
}
