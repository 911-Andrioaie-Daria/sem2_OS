// 1. Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte de la tastatură un număr natural şi îl trimite prin pipe procesului copil, iar procesul copil verifică şi afişează dacă acest număr este par sau impar.
//


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(){
	int p2c[2];

	pipe(p2c);

	int f = fork();
	if(f == -1){
		perror("Error on fork");
		exit(1);
	}
	else if(f==0){  // CHILD
		close(p2c[1]);	
		int n;
		if(read(p2c[0], &n, sizeof(int))<0){
			perror("Child cannot read");
        	       close(p2c[0]);
			 exit(2);
		}
		
		if(n%2 ==0)
			printf("The number %d is even.\n", n);
		else printf("The number %d is odd.\n", n);
	
		close(p2c[0]);
		exit(0);
	}

	// PARENT
	close(p2c[0]);
	int n;
	do{
		printf("Enter a natural number: \n");
		scanf("%d", &n);
	}while(n<0);
	
	if(write(p2c[1], &n, sizeof(int))<=0){
		 perror("Parent cannot write to child");
		 close(p2c[1]); 
               exit(2);
	}
	close(p2c[1]);
	wait(0);
	return 0;


}


