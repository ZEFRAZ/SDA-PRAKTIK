/* --------------------------------------------------------- */ 
/* File Program : PTR2.CPP       */ 
/* Contoh pemakaian pointer yang salah   */ 
/* Tujuan : mengetahui panjang dan posisi variabel di memory */ 
/* --------------------------------------------------------- */ 
 
#include <stdio.h> 
 
int main() {
 
// deklarasi variabel tunggal bertipe pointer untuk float
 float *pu;  
// deklarasi variabel tunggal bertipe float
 float nu; 
// deklarasi dan pengisian variabel tunggal bertipe integer
 int u  = 1234; 
 
// Pengisian pu dengan alamat dari u 
// Ada Kesalahan: 'pu' bertipe float*, tetapi diberikan alamat variabel int
 pu = &u;
// Pengisian nu dengan nilai yang ditunjuk oleh pu, 
// Ada kesalahan: 'pu' mengacu pada alamat int, tetapi disimpan ke variabel float
 nu = *pu; 
 
 // Menampilkan nilai u
 printf("u  = %d\n", u); 
 // Menampilkan nilai nu
 printf("nu = %f\n", nu); 
 
 return 0;
}
