// Scrieti 2 programe C, A si B. Programul A va citi numere intregi de la tastatura si le va scrie intr un fifo. 
// Programul B va crea 2 procese P1 si P2. P1 va citi numerele din fifo ul mentionat anterior si va calcula suma acestora. Suma va fi transmisa printr-un pipe procesului P2 care va afisa pe ecran divizorii acesteia.
// Numele fifo ului va fi dat ca argument in linia de comanda in ambele programe. Programul A va crea fifo ul si programul B va sterge fifo ul.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv){

	if(argc != 2){
		fprintf(stderr, "Please provide exacly one argument.\n");
		exit(1);
	}

	char* path = argv[1];	
	int m = mkfifo(path, 0600);
	if(m != 0){
		perror("Cannot create fifo");
		exit(2);
	}

	int a2b = open(path, O_WRONLY);

	if(a2b < 0){
                perror("Cannot open fifo");
                exit(2);
        }

	int n, i;
	printf("Enter a number:\n");
	scanf("%d", &n);

	if(write(a2b, &n, sizeof(int))<0){
		 perror("A cannot write");
                exit(3);
	}

	int* a = (int*)malloc(n*sizeof(int));

	for(i=0; i<n; i++){
		printf("Enter number:\n");
		scanf("%d", a+i);	
	}
	 if(write(a2b, a, n*sizeof(int))<0){
                 perror("A cannot write");
                exit(3);
        }

	close(a2b);
	free(a);	

	return 0;
}
