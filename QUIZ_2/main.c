#include "LinkedList.h"

int main() {
    LinkedList L;
    createList(&L);

    // Contoh penggunaan fungsi dasar sesuai spesifikasi pseudocode

    printf("1) Masukkan bilangan 7 sebagai elemen pertama:\n");
    insertFirst(&L, 7); // Expected: Linked List: 7 -> NULL

    printf("\n2) Masukkan bilangan 11 sebagai elemen kedua:\n");
    insertLast(&L, 11); // Expected: Linked List: 7 -> 11 -> NULL

    printf("\n3) Masukkan bilangan 9 di antara bilangan 7 dan 11:\n");
    insertAfter(&L, 9, 7); // Expected: Linked List: 7 -> 9 -> 11 -> NULL

    printf("\n4) Masukkan bilangan 5 di awal list:\n");
    insertFirst(&L, 5); // Expected: Linked List: 5 -> 7 -> 9 -> 11 -> NULL

    printf("\n5) Masukkan bilangan 13 di akhir list:\n");
    insertLast(&L, 13); // Expected: Linked List: 5 -> 7 -> 9 -> 11 -> 13 -> NULL

    printf("\n6) Hapus elemen terakhir (bilangan 13):\n");
    deleteLast(&L); // Expected: Linked List: 5 -> 7 -> 9 -> 11 -> NULL

    printf("\n7) Hapus bilangan 7 pada list:\n");
    deleteNode(&L, 7); // Expected: Linked List: 5 -> 9 -> 11 -> NULL

    printf("\n8) Hapus elemen pertama (bilangan 5):\n");
    deleteFirst(&L); // Expected: Linked List: 9 -> 11 -> NULL

    printf("\n9) Hapus semua bilangan ganjil:\n");
    deleteAllOdd(&L); // Expected: Linked List: (semua elemen ganjil dihapus; tersisa elemen genap atau list kosong)

    // =================== FUNGSI TAMBAHAN ===================

    // Menambahkan beberapa elemen untuk demonstrasi fungsi tambahan
    printf("\nMenambahkan beberapa elemen untuk fungsi tambahan sesuai di buku:\n");
    insertLast(&L, 10); // List: 10 -> ...
    insertLast(&L, 20); // List: 10 -> 20 -> ...
    insertLast(&L, 30); // List: 10 -> 20 -> 30 -> ...
    insertLast(&L, 20); // List: 10 -> 20 -> 30 -> 20 -> ...

    // 1. searchValue
    printf("\nCari nilai 20 di list:\n");
    if (searchValue(L, 20))
        printf("Nilai 20 ditemukan di dalam list.\n");
    else
        printf("Nilai 20 tidak ditemukan di dalam list.\n");

    // 2. modifyFirst
    printf("\nUbah nilai elemen pertama menjadi 99:\n");
    modifyFirst(&L, 99); // Expected: elemen pertama berubah menjadi 99

    // 3. modifyLast
    printf("\nUbah nilai elemen terakhir menjadi 77:\n");
    modifyLast(&L, 77); // Expected: elemen terakhir berubah menjadi 77

    // 4. modifyBetween
    printf("\nUbah nilai 20 menjadi 88 (kemunculan pertama):\n");
    modifyBetween(&L, 20, 88); // Expected: kemunculan pertama nilai 20 berubah menjadi 88

    // 5. countValue
    printf("\nHitung banyaknya kemunculan nilai 77:\n");
    int cnt = countValue(L, 77);
    printf("Nilai 77 muncul sebanyak %d kali.\n", cnt);

    // 6. sumAll
    printf("\nJumlahkan seluruh nilai di list:\n");
    int total = sumAll(L);
    printf("Total penjumlahan elemen = %d\n", total);

    // 7. swapValue
    printf("\nSwap nilai 88 dan 30:\n");
    swapValue(&L, 88, 30); // Expected: nilai 88 dan 30 ditukar

    return 0;
}

