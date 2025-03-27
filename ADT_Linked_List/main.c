#include <stdio.h>
#include "mahasiswa.h"

int main() {
    List L1, L2;
    CreateList(&L1);
    CreateList(&L2);

    // Mengisi L1 dengan data mahasiswa (ascending berdasarkan nama)
    Mahasiswa m1 = {"Amira", 85};
    Mahasiswa m2 = {"Bobon", 75};
    Mahasiswa m3 = {"Cinda", 90};
    Mahasiswa m4 = {"Dono", 65};
    Mahasiswa m5 = {"Amira", 80}; // Duplikat nama

    InsertAscending(&L1, m1);
    InsertAscending(&L1, m2);
    InsertAscending(&L1, m3);
    InsertAscending(&L1, m4);
    InsertAscending(&L1, m5);

    printf("List L1 (Ascending berdasarkan Nama):\n");
    PrintList(L1);

    // Menampilkan L1 secara descending berdasarkan nilai
    printf("\nList L1 (Descending berdasarkan Nilai):\n");
    List L1Desc;
    CreateList(&L1Desc);
    address P = L1.First;
    while (P != NULL) {
        InsertDescendingByNilai(&L1Desc, P->info);
        P = P->next;
    }
    PrintList(L1Desc);
    // Hapus list sementara secara silent (tidak menampilkan pesan)
    DeleteListSilent(&L1Desc);

    // Menampilkan jumlah elemen di L1
    int jumlah = CountElements(L1);
    printf("\nJumlah mahasiswa List L1: %d\n", jumlah);

    // Menyalin elemen L1 ke L2 dengan nilai > 70
    CopyList(&L1, &L2, 70);
    printf("\nList L2 (Setelah menyalin elemen dengan nilai > 70):\n");
    PrintList(L2);

    // Menghapus duplikat pada L2
    RemoveDuplicates(&L2);
    printf("\nList L2 (Setelah menghapus duplikat nama):\n");
    PrintList(L2);

    // Menghapus L1 dan L2 dengan menampilkan pesan penghapusan
    printf("\n==== Menghapus List L1 ====\n");
    DeleteList(&L1);

    printf("\n==== Menghapus List L2 ====\n");
    DeleteList(&L2);

    return 0;
}

