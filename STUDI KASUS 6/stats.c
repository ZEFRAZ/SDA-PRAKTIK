#include "stats.h"
#include "citylist.h"
#include "list1.h"
#include <stdio.h>

void displayStats(void) {
    int totalNames = 0;
    CityAddress p = cityList.head;
    while (p != NULL) {
        totalNames += NbElmt(p->data.nameList);
        p = p->next;
    }
    printf("Total kota: %d\n", cityList.size);
    printf("Total nama: %d\n", totalNames);
    printf("Jumlah nama per kota:\n");
    p = cityList.head;
    while (p != NULL) {
        printf("  - %s : %d\n", p->data.cityName, NbElmt(p->data.nameList));
        p = p->next;
    }
}

