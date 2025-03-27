 
/* --------------------------------------------------------- */ 
/* File Program : PTR3.CPP        */ 
/* Contoh pengubahan isi suatu variabel melalui pointer   */ 
/* Tujuan : Menggunakan type data pointer dan manipulasinya  */ 
/* --------------------------------------------------------- */ 
 
#include <stdio.h> 
 
int main() 
{
 // Mendeklarasikan variabel `d` bertipe float dan pointer `pd` yang menunjuk ke float
 float d, *pd; 
 
 // Menginisialisasi variabel `d` dengan nilai 54.5
 d  = 54.5; 
 
 // Mencetak nilai awal dari `d`
 printf("Isi d semula  = %g\n", d); 
 
 // Pointer `pd` diarahkan ke alamat variabel `d`
 pd  = &d; 
 // Mengubah nilai `d` melalui pointer `pd`, sekarang `d = 54.5 + 10 = 64.5`
 *pd = *pd + 10; 
 
 // Mencetak nilai `d` setelah diubah melalui pointer
 printf("Isi d kini    = %g\n", d); 
 
 return 0; 
}
