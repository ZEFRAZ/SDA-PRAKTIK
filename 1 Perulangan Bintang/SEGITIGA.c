#include <stdio.h>
int main(void){
	int i, j, n;
	
	printf("Masukkan jumlah baris untuk piramida: ");
	scanf("%d", &n);
	
	i = 1;
	while(i <= n){
		j = 1;
		while(j <= 2*n-1){
			if(j >= n-(i-1) && j <= n+(i-1))
			{
				printf("*");
			}
			else
			{
				printf(" ");
			}
			j++;
		}
		printf("\n");
		i++;
	}
	return 0;
}
