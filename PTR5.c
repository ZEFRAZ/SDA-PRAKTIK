/* --------------------------------------------------------------------------------------------- */ 
/* File Program : PTR5.CPP */ 
/* Deskripsi : pointer ke type dasar, mendeklarasikan & alokasi variabel dinamik */ 
/* --------------------------------------------------------------------------------------------- */ 

#include <stdlib.h> 
#include <stdio.h> 

int main() 
{ 
    /* Kamus Data (deklarasi, inisialisasi nilai variabel)*/ 
    int i = 5, j;  // Mendeklarasikan variabel i dengan nilai 5 dan j tanpa inisialisasi
    char c = 'X';  // Mendeklarasikan variabel karakter dengan nilai 'X'
    
    // Alokasi memori dinamis menggunakan malloc()
    int *Ptri = (int *) malloc(4);  // Pointer Ptri dialokasikan sebesar 4 byte (untuk menyimpan int)
    int *Ptrj = (int *) malloc(sizeof(int)); // Pointer Ptrj dialokasikan dengan ukuran int
    float *fx = (float *) malloc(sizeof(float)); // Pointer fx dialokasikan untuk menyimpan float
    
    int A[5]; // Mendeklarasikan array A berisi 5 elemen integer
    float f = 7.23; // Variabel float dengan nilai 7.23

    /* Program utama */
    *Ptri = 8;  // Menyimpan nilai 8 pada alamat yang ditunjuk oleh Ptri
    *Ptrj = 0;  // Menyimpan nilai 0 pada alamat yang ditunjuk oleh Ptrj
    *fx = 3;    // Menyimpan nilai 3 pada alamat yang ditunjuk oleh fx

    // Mencetak alamat dan nilai variabel
    printf("Alamat i = %x \n", &i);
    printf("Nilai i = %d \n", i);
    printf("Ukuran int = %d byte\n\n", sizeof(int));

    printf("Alamat j = %x \n", &j);
    printf("Nilai j = %d \n", j); // Karena j belum diinisialisasi, nilainya bisa acak

    printf("Alamat c = %x \n", &c);
    printf("Nilai c = %c \n", c);
    printf("Ukuran char = %d byte\n\n", sizeof(char));

    // Informasi tentang pointer Ptri
    printf("Alamat Ptri = %x \n", &Ptri);
    printf("Isi var Ptri = %x \n", Ptri); // Alamat yang ditunjuk oleh Ptri
    printf("Nilai yang ditunjuk oleh Ptri = %d \n", *Ptri); // Nilai yang disimpan pada alamat tersebut (8)
    printf("Ukuran pointer int = %d byte\n\n", sizeof(int *));

    // Informasi tentang pointer Ptrj
    printf("Alamat Ptrj = %x \n", &Ptrj);
    printf("Isi var Ptrj = %x \n", Ptrj); // Alamat yang ditunjuk oleh Ptrj
    printf("Nilai yang ditunjuk oleh Ptrj = %d \n", *Ptrj); // Nilai yang ditunjuk Ptrj (0)

    Ptrj = Ptri; // Ptrj sekarang menunjuk ke alamat yang sama dengan Ptri
    printf("Isi var Ptrj sekarang = %x \n", Ptrj); // Alamat yang ditunjuk Ptrj (sama dengan Ptri)
    printf("Nilai yang ditunjuk oleh Ptrj sekarang = %d \n", *Ptrj); // Nilai yang ditunjuk Ptrj (8)

    // Informasi tentang array A
    printf("Alamat A = %x \n", &A);
    printf("Isi var A = %x \n", A[0]); // A[0] belum diinisialisasi, bisa bernilai acak
    printf("Ukuran array A = %d byte\n\n", sizeof(A));

    // Informasi tentang variabel float f
    printf("Alamat f = %x \n", &f);
    printf("Nilai f = %f \n", f);
    printf("Ukuran float = %d byte\n\n", sizeof(float));

    return 0; 
}

