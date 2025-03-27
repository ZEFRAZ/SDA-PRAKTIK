#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teller.h"

// Membuat sistem teller dengan n teller dan mengisi nama teller secara otomatis (nomor)
void CreateTellerSystem(TellerSystem *ts, int n) {
    ts->numTellers = n;
    ts->tellers = (Teller *)malloc(n * sizeof(Teller));
    int i;
    for (i = 0; i < n; i++) {
        ts->tellers[i].currentNumber = 0;
        ts->tellers[i].customersServed = 0;
        CreateQueue(&(ts->tellers[i].queue));
        // Isi nama teller dengan nomor (misal "1", "2", dll)
        sprintf(ts->tellers[i].name, "%d", i + 1);
    }
}

// Menambahkan teller baru (tidak lagi digunakan karena nama diassign otomatis)
boolean AddTeller(TellerSystem *ts, char *name, int index) {
    if (index < 0 || index >= ts->numTellers) {
        return false;
    }
    // Jika menggunakan input nama, cek duplikasi (tidak dipakai di sini)
    if (IsTellerNameExists(*ts, name)) {
        return false;
    }
    strcpy(ts->tellers[index].name, name);
    return true;
}

boolean IsTellerNameExists(TellerSystem ts, char *name) {
    int i;
    for (i = 0; i < ts.numTellers; i++) {
        if (strcmp(ts.tellers[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

int FindTeller(TellerSystem ts, char *name) {
    int i;
    for (i = 0; i < ts.numTellers; i++) {
        if (strcmp(ts.tellers[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Mengambil nomor antrian untuk teller tertentu
int TakeQueueNumber(TellerSystem *ts, int tellerIndex) {
    if (tellerIndex < 0 || tellerIndex >= ts->numTellers) {
        return -1;
    }
    Teller *t = &(ts->tellers[tellerIndex]);
    t->currentNumber++;
    enqueue(&(t->queue), t->currentNumber);
    return t->currentNumber;
}

// Memproses antrian pada teller tertentu
boolean ProcessQueue(TellerSystem *ts, int tellerIndex) {
    if (tellerIndex < 0 || tellerIndex >= ts->numTellers) {
        return false;
    }
    Teller *t = &(ts->tellers[tellerIndex]);
    if (isEmpty(t->queue)) {
        return false;
    }
    dequeue(&(t->queue));
    t->customersServed++;
    return true;
}

// Menampilkan status teller tertentu
void DisplayTeller(Teller t) {
    printf("\n---------------------------\n");
    printf("Teller: %s\n", t.name);
    printf("Jumlah pelanggan dilayani: %d\n", t.customersServed);
    printf("Antrian saat ini: ");
    displayQueue(t.queue);
    printf("---------------------------\n");
}

// Menampilkan status semua teller
void DisplayAllTellers(TellerSystem ts) {
    printf("\n=== Status Semua Teller ===\n");
    int i;
    for (i = 0; i < ts.numTellers; i++) {
        printf("\n[Teller %s]\n", ts.tellers[i].name);
        DisplayTeller(ts.tellers[i]);
    }
}

void CleanupTellerSystem(TellerSystem *ts) {
    free(ts->tellers);
    ts->numTellers = 0;
}

