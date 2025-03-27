/* --------------------------------------------------------- */ 
/* File Program : PTR1.CPP        */ 
/* Contoh pemakaian pointer       */ 
/* Tujuan : mengetahui panjang dan posisi variabel di memory */ 
/* --------------------------------------------------------- */ 
 
#include <stdio.h> 
 
int main() 
{ 
 // Deklarasi variabel integer x dan y
 int x, y; 
 // Deklarasi pointer px yang akan menunjuk ke variabel bertipe integer
 int *px; 
 // Menginisialisasi variabel x dengan nilai 87
 x = 87; 
 
 // Pointer px menyimpan address dari variabel x
 px = &x; 
 // Variable y diisi dengan nilai yang ditunjuk oleh pointer px (y = *px berarti berarti y = x)
 y = *px; 
 
 // Menampilkan address memori tempat variabel x disimpan
 printf("Alamat x = %p\n", &x); 
 // Menampilkan isi dari variabel x
 printf("Isi px   = %d\n", x); 
 // Menampilkan nilai yang ditunjuk oleh pointer px (yang merupakan nilai x)
 printf("Nilai yang ditunjuk oleh px = %d\n", *px); 
 // Menampilkan isi dari variabel y
 printf("Nilai y  = %d\n", y); 
 
 return 0; 
}
