/* -------------------------------------------------- */ 
/* File Program : PTR9.CPP                           
*/ 
/* Deskripsi : pointer yang menunjuk pointer */ 
/* -------------------------------------------------- */ 
#include <stdio.h> 
int main() 
{ 
/* Kamus Data (deklarasi, inisialisasi nilai variabel)*/ 
int var_x = 273; 
int *ptr1;  /* ptr1 adl pointer yang menunjuk ke objek bertipe integer */ 
			/* (Boleh disebut pointer integer saja) */ 
int **ptr2; /* ptr2 adl pointer yang menunjuk ke pointer yang menunjuk */ 
			/* ke objek bertipe integer (Boleh disebut : pointer menunjuk ke pointer integer saja) */ 
			
// Pointer ptr1 diisi dengan alamat variabel var_x
ptr1 = &var_x; 
// Pointer ptr2 diisi dengan alamat pointer ptr1
ptr2 = &ptr1; 

/* Mengakses nilai var_x melalui ptr1 dan ptr2 */ 

// Mengambil nilai dari alamat yang ditunjuk ptr1 (273)
printf("Nilai var_x = %d\n", *ptr1); 

// Mengambil nilai dari alamat yang ditunjuk oleh ptr2 (273)
printf("Nilai var_x = %d\n", **ptr2); 
return 0; 
} 
