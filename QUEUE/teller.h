#ifndef TELLER_H
#define TELLER_H

#include "queue.h"
#include "boolean.h"

typedef struct {
    char name[50];        /* Nama teller (diisi otomatis dengan nomor) */
    Queue queue;          /* Antrian untuk teller ini */
    int currentNumber;    /* Nomor antrian terakhir */
    int customersServed;  /* Jumlah pelanggan yang telah dilayani */
} Teller;

typedef struct {
    Teller *tellers;     /* Array of tellers */
    int numTellers;      /* Jumlah teller */
} TellerSystem;

/* Konstruktor */
void CreateTellerSystem(TellerSystem *ts, int n);

/* Menambahkan teller baru (tidak digunakan karena nama diassign otomatis) */
boolean AddTeller(TellerSystem *ts, char *name, int index);

/* Operasi-operasi pada Teller */
int FindTeller(TellerSystem ts, char *name);
int TakeQueueNumber(TellerSystem *ts, int tellerIndex);
boolean ProcessQueue(TellerSystem *ts, int tellerIndex);
void DisplayAllTellers(TellerSystem ts);
void DisplayTeller(Teller t);
void CleanupTellerSystem(TellerSystem *ts);
boolean IsTellerNameExists(TellerSystem ts, char *name);

#endif

