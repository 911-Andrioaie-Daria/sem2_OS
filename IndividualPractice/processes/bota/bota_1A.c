// 1. Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte de la tastatură un număr natural şi îl trimite prin pipe procesului copil, iar procesul copil verifică şi afişează dacă acest număr este par sau impar.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	int n;
	int a2b = open("a2b", O_WRONLY);
	if(a2b < 0){
		perror("Cannot open fifo");
		exit(1);
	}
	
	do{
		printf("Enter a natural number: \n");
		scanf("%d", &n);
	}while(n<0);
	
	if(write(a2b, &n, sizeof(int))<=0){
		 perror("Cannot write");
		close(a2b);
                exit(2);
	}
	close(a2b);
	return 0;
}
