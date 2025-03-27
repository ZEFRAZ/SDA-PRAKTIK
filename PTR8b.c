/* ------------------------------------------------------------------------------------------------- */ 
/* File Program : PTR8b.CPP                                        
/* (Pointer dan String bagian ke-2)                          
/* Deskripsi : menukar isi dua buah string yang ditunjuk oleh pointer     
*/ 
 
/* PERHATIKAN! Bila dibandingkan dengan program PTR8A.cpp, maka dengan */ 
/* pointer, penyalinan isi array tidak perlu dilakukan. Sehingga bisa menghemat waktu eksekusi.   */                             
/* ---------------------------------------------------------------------------------------------- */ 
#include <stdio.h> 
int main() 
{ 
/* Kamus Data (deklarasi, inisialisasi nilai variabel)*/ 

	// Pointer nama1 menunjuk ke string "DEWI SARTIKA"
	char *nama1 = "DEWI SARTIKA"; 
	// Pointer nama2 menunjuk ke string "SULTAN HASANUDDIN"
	char *nama2 = "SULTAN HASANUDDIN"; 
	// Pointer sementara untuk pertukaran nilai
	char *namaX; 
	
	// Menampilkan nilai awal dari kedua pointer
	puts("Nama semula : "); 
	printf("Nama 1 --> %s\n", nama1); 
	printf("Nama 2 --> %s\n", nama2); 
	
	/* Penukaran string yang ditunjuk oleh pointer nama1 dan nama2 */ 
	namaX = nama1; // Simpan alamat yang ditunjuk oleh nama1 ke namaX
	nama1 = nama2; // Ubah nama1 agar menunjuk ke alamat string yang ditunjuk oleh nama2
	nama2 = namaX; // Ubah nama2 agar menunjuk ke alamat string yang disimpan di namaX
	
	// Menampilkan nilai setelah pertukaran pointer
	puts("Nama sekarang : "); 
	printf("Nama 1 --> %s\n", nama1); 
	printf("Nama 2 --> %s\n", nama2); 
	return 0; 
} 
