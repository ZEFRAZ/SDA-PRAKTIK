/*---------------------------------------------------------------------------*/ 
/* File        : PTR20.cpp                									 */ 
/* Deskripsi   : contoh pendefinisian struct dan pointer ke struct 			 */ 
/* Dibuat oleh : Tim Dosen SDP                								 */			
/* Tanggal     : 13-09-2001                									 */ 
/*---------------------------------------------------------------------------*/ 
#include <stdlib.h>
#include <stdio.h>

int main() 
{ 
    /* kamus */ 
    /* cara 3 : INI yang membuat TYPE baru */ 
    typedef struct { 
        float x; 
        float y; 
    } Point;   
    Point *P2;  
    /* nama type */ 
    /* deklarasi pointer ke struct */ 
    Point *P3 = (Point *) malloc(sizeof(Point)); /* deklarasi alokasi */ 
    
    /* program */ 
    /* Cara 1 : mengacu elemen pointer ke struct */ 
    printf("Titik P2, dengan P2->x dan P2->y : \n"); 
    P2 = (Point *) malloc(sizeof(Point));   
    P2->x = 9.12;   
    P2->y = 2.567; 
    /* Isi nilai komponen */ 
    printf("P2.x = %f \nP2.y = %f \n", P2->x, P2->y); 
    
    /* Alokasi */ 
    /* Cara 2 : Perhatikanlah tanda kurung, lihat prioritas () dibuku TC */ 
    (*P3).x = 0.5;  
    /* Mendefinisikan isi */ 
    (*P3).y = 10.5; 
    printf("P3.x = %f \nP3.y = %f \n", (*P3).x, (*P3).y); 
    
    return 0; 
}

