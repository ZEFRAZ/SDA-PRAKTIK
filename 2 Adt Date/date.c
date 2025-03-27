/* File        : date.c */
/* Deskripsi   : Unit untuk keperluan ADT Date */

/***************************/
/*  BODY PRIMITIF DATE     */
/***************************/

#include <stdio.h>
#include <math.h>
#include "date.h"

/*********** Operasi Primitif ************/
/* Constructor Membentuk sebuah DATE, dengan nilai default adalah 01/01/1900 */
void CreateDate (date * D){
	SetTgl (01, &(* D));
	SetBln (01, &(* D));
	SetThn (1900, &(* D));
}

/******* Selector komponen **********/
/* Mengambil bagian Tgl dari date */
int GetTgl (date D){
	return(D.Tgl);
}

/* Mengambil bagian Bln dari date */
int GetBln (date D){
	return(D.Bln);
}

/* Mengambil bagian Thn dari date */
int GetThn (date D){
	return(D.Thn);
}


/****** Pengubah komponen ******/
/* Memberi nilai untuk Tgl */
void SetTgl (int NewTgl, date * D){
	(* D).Tgl = NewTgl;
}

/* Memberi nilai untuk Bln */
void SetBln (int NewBln, date * D){
	(* D).Bln = NewBln;
}

/* Memberi nilai untuk Thn */
void SetThn (int NewThn, date * D){
	(* D).Thn = NewThn;
}


/****** Kelompok Interaksi dengan I/O device, BACA/TULIS ******/
/* Membentuk DATE dari iTgl, iBln dan iThn yang dibaca dari keyboard */
void ReadDate (date * D){
	printf("Masukkan Tanggal: ");
	scanf("%d", &((* D).Tgl));
	printf("Masukkan Bulan: ");
	scanf("%d", &((* D).Bln));
	printf("Masukkan Tahun: ");
	scanf("%d", &((* D).Thn));
	if (! isValid(* D)){
		printf("Tanggal yang anda inputkan tidak valid! Tanggal akan direset ulang!\n");
		ReadDate(&(* D));
	}
}

/* Memeriksa apakah suatu tanggal valid, yaitu dengan memperhatikan batas akhir per bulan */
boolean isValid(date D){
	if ((GetThn(D) < 1900)||(GetThn(D) > 30000)||(GetBln(D) < 1) ||(GetBln(D) > 12)||(GetTgl(D) < 1)||(GetTgl(D) > getEndDate(D)))
		return (false);
	else
		return (true);
}

/* Print nilai D dengan format dd/mm/yyyy */
void PrintObj (date D){
	printf ("%d/%d/%d\n", GetTgl(D), GetBln(D), GetThn(D));
}

/****** Operator Relasional ******/
/* Memeriksa apakah suatu tanggal adalah kabisat; Dipakai untuk bulan == 2 saja
Harusnya kabisat adalah thn yang habis dibagi 4, atau habis dibagi 100 dan 400, tapi implementasinya seringkali hanya menggunakan 4 sebagai pembagi */
boolean isKabisat (date D){
    return ((GetThn(D) % 400 == 0) || (GetThn(D) % 4 == 0 && GetThn(D) % 100 != 0));
}

/***** Predikat lain *******/
/* Memberikan tanggal terakhir dari sebuah bulan */
int getEndDate (date D){
	if ((GetBln(D) == 1) || (GetBln(D) == 3) || (GetBln(D) == 5) || (GetBln(D) == 7) || (GetBln(D) == 8) || (GetBln(D) == 10) || (GetBln(D) == 12)) {
		return (31);
	} else if ((GetBln(D) == 4) || (GetBln(D) == 6) || (GetBln(D) == 9) || (GetBln(D) == 11)) {
		return (30);
	} else {
		return (isKabisat(D) ? 29 : 28);
	}
}

/* Menampilkan tanggal sebelumnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal sebelumnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika jan, thn-1 */
void DateBefore (date D){
	if (GetTgl(D) == 1){
		if (GetBln(D) == 1) 
		{
			SetTgl(31, &D);
			SetBln(12, &D);
			SetThn(GetThn(D) - 1, &D); 
		} else {
			SetBln(GetBln(D) - 1, &D);
			if (GetBln(D) == 2) { // CEK jika Tahun Kabisat atau bukan 
				if ((GetThn(D) % 4 != 0) || ((GetThn(D) % 100 == 0) && (GetThn(D) % 400 != 0))) {
					SetTgl(29, &D); // Tahun kabisat 
				} else {
					SetTgl(28, &D); // bukan tahun kabisat
				}
			} else if (GetBln(D) == 4 || GetBln(D) == 6 || GetBln(D) == 9 || GetBln(D) == 11) {
				SetTgl(30, &D); // Bulan April, Juni, September, November	
			} else SetTgl(31, &D); // Bulan lainnya
		}
	} else {
		SetTgl(GetTgl(D) - 1, &D); //jika bukan tanggal 1 berkurang satu
	}
	printf("\n	Adalah tanggal: %d/%d/%d\n", GetTgl(D), GetBln(D), GetThn(D));
}

/* Menampilkan tanggal berikutnya dari sebuah Date
	I.S = Tanggal tertentu diketahui
	F.S = Tanggal berikutnya diketahui
	Hal yang perlu diketahui : Batas akhir tiap bulan dan jika des, thn+1 */
void NextDate (date D){
	int DayAkhir = getEndDate(D);
	
	if (GetTgl(D) == DayAkhir) { // Jika Tanggal Terakhir 
		SetTgl(1, &D); 
		if (GetBln(D) == 12){ //Jika Bulan Desember
			SetBln(1, &D); //Menjadi Bulan Januari
			SetThn(GetThn(D) + 1, &D); //Tahun Bertambah
		} else SetBln(GetBln(D) + 1, &D); // Selain Bulan Desember
	} else SetTgl(GetTgl(D) + 1, &D); // Selain tanggal terakhir 
	printf("\nAdalah tanggal: %d/%d/%d\n", GetTgl(D), GetBln(D), GetThn(D));
}

/* Menampilkan selisih dua tanggal
	I.S = 2 buah Tanggal tertentu diketahui
	F.S = Tampil selisih dua buah tanggal
	Asumsi : 1 tahun = 365 hari */
void DifferenceDate (date D1, date D2){
	int totalHariD1 = 0, totalHariD2 = 0, i;
    int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

    // Hitung total hari untuk D1
    totalHariD1 += (GetThn(D1) - 1900) * 365; // Hitung hari dari tahun
    for (i = 0; i < GetBln(D1) - 1; i++) { // Hitung hari dari bulan sebelumnya
        totalHariD1 += daysPerMonth[i];
    }
    totalHariD1 += GetTgl(D1); // Tambahkan hari dalam bulan sekarang

    // Hitung total hari untuk D2
    totalHariD2 += (GetThn(D2) - 1900) * 365;
    for (i = 0; i < GetBln(D2) - 1; i++) {
        totalHariD2 += daysPerMonth[i];
    }
    totalHariD2 += GetTgl(D2);

    // Cetak selisih hari absolut
    printf("\nadalah: %d hari\n", abs(totalHariD1 - totalHariD2));
}

void printJudul() {
	printf("==================== Program ADT DATE ====================\n");
}

void printGaris() {
	printf("----------------------------------------------------------\n");
}
