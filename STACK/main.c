#include <stdio.h>
#include "stack.h"

int main() {
    int num;
    printf("Masukkan bilangan desimal: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Bilangan harus positif!\n");
    } else {
        convertToBinary(num);
    }

    return 0;
    
}

