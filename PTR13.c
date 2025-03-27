/* ------------------------------------------------------------------------------------------------------------------ */ 
/* File        : PTR13.cpp          */ 
/* Deskripsi   : Pointer ke function (Procedure dengan parameter input/output sebagai parameter) */ 
/*       Melakukan offset terhadap tabel tergantung fungsi f     */ 
/* ------------------------------------------------------------------------------------------------------------------ */ 
 
#include <stdio.h>
#include <stdlib.h>

int N;
enum MyType { 
    bulat, karakter 
};

/* Prototype fungsi */
void succI (int *i);
void predI (int *i);
void succC (char *c);
void predC (char *c);

/* Fungsi untuk mencetak tabel */
void printtab (void *T, enum MyType Ty);

/* Prosedur geser */
void geserInt (int *TT, void (*f) (int *));
void geserChar (char *TT, void (*f) (char *));

/* Program Utama */
int main() { 
    int *MyTabInt;
    char *MyTabC;
    int i;

    N = 10;
    MyTabInt = (int *) malloc (N * sizeof(int));
    MyTabC = (char *) malloc (N * sizeof(char));

    /* Inisialisasi array */
    for (i = 0; i < N; i++) { 
        MyTabInt[i] = i; 
        MyTabC[i] = 'Z'; 
    }

    printf("Isi tabel dalam main sebelum pemanggilan : \n");
    printf(" Tabel integer \n");
    printtab(MyTabInt, bulat);
    printf("\nTabel karakter \n");
    printtab(MyTabC, karakter);
    printf("\n");

    /* Pakai geser dengan parameter succ */
    printf("Geser dengan succ \n");
    geserInt(MyTabInt, succI);
    geserChar(MyTabC, succC);

    printf("dalam main \n");
    printf("Tabel integer \n");
    printtab(MyTabInt, bulat);
    printf("\nTabel karakter \n");
    printtab(MyTabC, karakter);
    printf("\n");

    free(MyTabInt);
    free(MyTabC);
    return 0;
}

/* Body Function */
void succI (int *i) { *i = *i + 1; }
void predI (int *i) { *i = *i - 1; }
void succC (char *c) { *c = *c + 1; }
void predC (char *c) { *c = *c - 1; }

/* Prosedur geser */
void geserInt (int *TT, void (*f) (int *)) { 
    int i;
    printf(" dalam geser \n");
    for (i = 0; i < N; i++) { 
        f(&TT[i]);
        printf(" %d ", TT[i]); 
    }
    printf("\n");
}

void geserChar (char *TT, void (*f) (char *)) { 
    int i;
    printf(" dalam geser \n");
    for (i = 0; i < N; i++) { 
        f(&TT[i]);
        printf(" %c ", TT[i]); 
    }
    printf("\n");
}

/* Fungsi print */
void printtab (void *T, enum MyType Ty) { 
    int i;
    if (Ty == bulat) {
        for (i = 0; i < N; i++) {
            printf("%d ", *((int *)T + i));
        }
    } else {
        for (i = 0; i < N; i++) {
            printf("%c ", *((char *)T + i));
        }
    }
}

