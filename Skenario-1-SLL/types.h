#ifndef TYPES_H
#define TYPES_H

#include "boolean.h"

#define MAX_NAMA 50
#define MAX_JUDUL 100

typedef enum {
    DOSEN = 1,
    MAHASISWA = 2,
    UMUM = 3,
    PEMINJAM_AKTIF = 4
} Prioritas;

// Forward declarations
struct buku;
struct borrower;
struct aktivitas;

typedef struct buku* bukuAddress;
typedef struct borrower* borrowerAddress;
typedef struct aktivitas* aktivitasStack;

// Struktur untuk buku
struct buku {
    char judul[MAX_JUDUL];
    int stok;
    struct buku *next;
};

// Struktur untuk peminjam
struct borrower {
    char nama[MAX_NAMA];
    Prioritas prioritas;
    bukuAddress targetBuku;
    struct borrower* next;
};

// Struktur untuk aktivitas (stack)
struct aktivitas {
    char jenis[20];
    char judulBuku[MAX_JUDUL];
    char namaPeminjam[MAX_NAMA];
    int prioritas;
    struct aktivitas* next;
};

#endif