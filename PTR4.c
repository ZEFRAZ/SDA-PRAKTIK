/* --------------------------------------------------------- */ 
/* File Program : PTR4.CPP       */ 
/* Contoh pemakaian pointer      */ 
/* --------------------------------------------------------- */ 
 
#include <stdio.h> 
 
int main() 

{ // Deklarasi variabel integer z dan s, serta pointer pz dan ps
 int z, s, *pz, *ps; 
 
 z = 20; 
 s = 30; 
 // pointer pz menunjuk ke alamat variabel z
 pz = &z; 
 // pointer ps menunjuk ke alamat variabel s
 ps = &s; 
 // nilai yang ditunjuk oleh pz (z) dijumlahkan dengan nilai yang ditunjuk oleh ps (s), 
 // lalu hasilnya disimpan kembali ke z
 *pz = *pz + *ps; 
 
 // Menampilkan nilai z dan s
 printf("z  = %d, s  =  %d\n", z , s); 
 
 return 0;
}
