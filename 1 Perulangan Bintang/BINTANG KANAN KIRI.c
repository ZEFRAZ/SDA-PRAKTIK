#include <stdio.h>

int main(){
	int i, j, n;
	printf("Masukkan jumlah baris untuk segitiga rata kanan: ");
	scanf("%d", &n);
	i = 1;
	while(i <= n){
		j = 1;
		while(j <= n - i){
			printf(" ");
			j++;
		}
		j = 1;
		while(j <= i){
			printf("*");
			j++;
		}
		printf("\n");
		i++;
	}
	
	return 0;
}
