#include "stats.h"
#include "citydata.h"
#include "list1.h"
#include <stdio.h>

void displayStats(void) {
    int totalNames = 0;
    int i;
    for (i = 0; i < cityCount; i++) {
        totalNames += NbElmt(cityArray[i].nameList);
    }
    printf("Total kota: %d\n", cityCount);
    printf("Total nama: %d\n", totalNames);
    printf("Jumlah nama per kota:\n");
    for (i = 0; i < cityCount; i++) {
        printf("  - %s : %d\n", cityArray[i].cityName, NbElmt(cityArray[i].nameList));
    }
}

