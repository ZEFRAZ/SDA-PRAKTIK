/* ---------------------------------------------------------------------------------------------------------------- */ 
/* File Program : PTR16CPP                                        
*/ 
/* Deskripsi   : Array of string : Pendefinisian dan pengaksesan. Perhatikanlah permasalahannya */ 
/* Jelaskan perbedaannya dengan program PTR15.cpp!                                                                
*/ 
/* ---------------------------------------------------------------------------------------------------------------- */ 
#include <stdlib.h>  // Library untuk alokasi memori dinamis
#include <stdio.h>   // Library untuk input/output
#define STRING char* // Macro untuk menggantikan char* dengan STRING

int main() 
{ 
    /* kamus */ 
    /* Definisi array yang elemennya string, statik dan sekaligus mengisi */ 
    static STRING s[3] = {"the", "time", "is"};  // Array of string statis

    /* Definisi array yang elemennya string, dinamik */ 
    STRING (*TabStr);  // Pointer ke array of string dinamis
    int i;  // Variabel indeks

    /* program */ 
    /* Deklarasi array of string */ 
    for (i = 0; i < 3; i++) {  /* Print isi s */ 
        printf("%s\n", s[i]);  // Cetak isi array statis
    } 

    /* Alokasi TabStr sebanyak 3 */ 
    TabStr = (STRING *) malloc(3 * sizeof(STRING));  // Alokasi memori untuk array of string dinamis

    for (i = 0; i < 3; i++) { 
        /* Alokasi string yang merupakan elemen tabel */ 
        *(TabStr + i) = (STRING) malloc(5 * sizeof(char));  // Alokasi memori untuk setiap string
        printf("\nInput Str[%d], maksimum 5 karakter : ", i); 
        scanf("%5s", *(TabStr + i));  // Input string dari pengguna
        /* Mengisi nilai string */ 
        printf("\n Nilai Str[%d] : %5s\n ", i, *(TabStr + i));  // Cetak string yang diinput
    } 

    return 0;  // Akhir program
}
