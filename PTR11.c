/* ----------------------------------------------------------------------------- */ 
/* File        : PTR11.cpp                  */ 
/* Deskripsi   : Pointer ke function (Function sebagai parameter)     */ 
/*            Melakukan offset terhadap tabel tergantung fungsi f */ 
/* ----------------------------------------------------------------------------- */ 

#include <stdio.h> 
/* Kamus Global */ 
 int N;    /* ukuran efektif */ 
 
/* Prototype, fungsi yang diberikan sebagai parameter aktual */ 
// Fungsi untuk menambah 1 pada nilai i
int succ (int i);  /* succ -> singkatan dari suksessor */ 
// Fungsi untuk mengurangi 1 pada nilai i
int pred (int i);  /* pred -> singkatan dari predesessor */ 
 
/* Prosedur dengan parameter sebuah fungsi */ 
// Prosedur untuk menggeser nilai dalam array sesuai fungsi f
void geser (int *TT, int (*f) (int)); 
 
/* Program Utama */ 
int main() 
{ 
	/* kamus lokal */ 
	 int MyTab[10]; 
	 int i; 
 
	/* program */ 
	 N = 10; 
	 for (i = 0; i < N; i++) 
	 { 
	  MyTab[i] = i; 
	 } 
 printf("Isi tabel dalam main sebelum pemanggilan : \n"); 
 for (i = 0; i < N; i++) 
 { 
  printf(" %d ", MyTab[i]); 
 } 
 printf("\n"); 
 
 /* Pakai geser dengan parameter succ */ 
 printf("Geser dengan succ \n"); 
 geser (MyTab, succ); 
 printf(" dalam main \n"); 
 for (i = 0; i < N; i++)  
{ 
  printf(" %d ", MyTab[i]); 
 } 
printf("\n"); 
 
 /* Pakai geser dengan parameter pred */ 
 printf("Geser dengan pred \n"); 
 geser (MyTab, pred); 
 printf(" dalam main setelah aplikasi pred \n"); 
    for (i = 0; i < N; i++) 
 { 
  printf(" %d ", MyTab[i]); 
 } 
    printf("\n"); 
 return 0; 
} 
 
/* Body Function */ 
int succ (int i) 
{ 
 return (i+1); 
} 

/* Fungsi untuk mengurangi 1 dari nilai i */ 
int pred (int i) 
{ 
 return (i-1); 
} 
 
/* Prosedur untuk menggeser nilai dalam array sesuai fungsi f */
void geser (int *TT, int (*f) (int)) 
{ 
 int i; 
 
/* Iterasi melalui array dan menerapkan fungsi f */
 printf(" dalam geser \n"); 
 for (i = 0; i < N; i++) { 
  	TT[i] = f (TT[i]); 		// Mengubah nilai sesuai fungsi f
  	printf(" %d ", TT[i]); 
  } 
  printf("\n"); 
}

 
