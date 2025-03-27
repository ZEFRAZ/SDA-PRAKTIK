/* Nama Program : mdate.c
	Deskripsi : Driver untuk menggunakan unit ADT Date
			yang ada di date.h dan date.c
*/

#include <stdio.h>
#include <conio.h>
#include "date.h"

/* P R O G R A M   U T A M A   */
int main(){
	date D1, D2, D3, D4;
	char lagi = 'y';

	/* Algoritma : Procedure yang isi bodynya call thd semua feature yang ada */
	for (;;){
		 //lakukan clear screen;
        system("cls");
		printJudul();
		
        //create date D1
		CreateDate (&D1);
		printf ("Hasil CreateDate (&D1), maka D1 bernilai: ");
		PrintObj (D1);
		printGaris();
		
		//lakukan set tanggal, bulan, dan tahun, simpan hasil ke var D2
		ReadDate(&D2);
		//tampilkan D2
		printGaris();
		printf ("\nSetelah perintah ReadDate(&D2), maka D2 bernilai: ");
		PrintObj(D2);
		printf("\nTahun %d %s tahun kabisat\n", GetThn(D2), isKabisat(D2) ? "adalah" : "bukan");
		printGaris();
		printf("\n");
		printf("Menggunakan Perintah DateBefore(D2), sebelum tanggal: %d/%d/%d\n", GetTgl(D2), GetBln(D2), GetThn(D2));
		DateBefore(D2);
		printf("\n");
		printf("Menggunakan Perintah NextDate(D2), setelah tanggal: %d/%d/%d\n", GetTgl(D2), GetBln(D2), GetThn(D2));
		NextDate(D2);
		printGaris();
		
		ReadDate(&D3);
		printf ("\nSetelah perintah ReadDate(&D3), maka D3 bernilai: ");
		PrintObj(D3);
		printf ("\nSetelah perintah DifferenceDate(D2, D3), selisih antara %d/%d/%d dan %d/%d/%d\n", GetTgl(D2), GetBln(D2), GetThn(D2), GetTgl(D3), GetBln(D3), GetThn(D3));
		DifferenceDate(D2, D3); // Menampilkan difference date D2 dan D3
		printGaris();

		printf("\nCoba lagi ? (y/t) ");
		lagi = getch();
		if (lagi == 't' || lagi == 'T')
    	break;
	}

	printf("\n\nTerima Kasih sudah menggunakan program ini!\n");
	printGaris();

	return 0;
}
