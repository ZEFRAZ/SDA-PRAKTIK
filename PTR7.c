/* ----------------------------------------------------------- */ 
/* File Program : PTR7.CPP                 
/* (Pointer dan String bagian ke-1)                       
*/ 
 
/* Deskripsi : pointer yang menunjuk ke data string */ 
/* ---------------------------------------------------------- */ 
#include <stdio.h>

int main()
{
    /* Deklarasi pointer ke string */
    
	char *pkota = "BANDUNG"; // Pointer menunjuk ke string konstan "BANDUNG"
    

    puts(pkota); // Menampilkan string yang ditunjuk oleh pointer pkota
	pkota[0] = 'b';
    return 0;
}
/* STUDI KASUS : */ 
/* Apa perbedaan deklarasi variabel char *pkota='BANDUNG'; dengan char kota[]='BANDUNG'  ? 
*/ 
