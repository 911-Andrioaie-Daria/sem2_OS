// 5. Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte dintr-un fişier de tip text două numere întregi pe care le trimite prin pipe procesului copil, iar procesul copil returnează prin pipe suma lor.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int p2c[2], c2p[2], a;
	FILE* f;

	pipe(p2c); pipe(c2p);

	f = fopen("bota.txt", "r");
	
	if(f < 0){
		perror("Error on openning the file");
                exit(1);

	}

	a = fork();
	if( a == -1){
		perror("Error on fork");
		fclose(f);
		exit(1);
	}
	else if (a == 0){
		close(p2c[1]); close(c2p[0]);
	
		int n, m, sum;

       		 if(read(p2c[0], &n, sizeof(int))<=0){
               		 perror("Child cannot read");
               		 close(p2c[0]); close(c2p[1]);
               		 exit(3);
       		 }
		
       		 if(read(p2c[0], &m, sizeof(int))<=0){
               	 	 perror("Child cannot read");
               		 close(p2c[0]); close(c2p[1]);
              		  exit(3);
       		 }
		
		sum = n+m;
	
       		 if(write(c2p[1], &sum, sizeof(int))<=0){
               		 perror("Child cannot write");
               		 close(p2c[0]); close(c2p[1]);
               		 exit(3);
        	}
		
		close(p2c[0]); close(c2p[1]);
		exit(0);
	}
	
	close(p2c[0]); close(c2p[1]);

	int n=0, m=0, sum;
	fscanf(f, "%d", &n);
	fscanf(f, "%d", &m);
	fclose(f);
	if(write(p2c[1], &n, sizeof(int))<=0){
		perror("Parent cannot write");
		close(p2c[1]); close(c2p[0]);
		exit(2);
	}
	
	if(write(p2c[1], &m, sizeof(int))<=0){
                perror("Parent cannot write");
                close(p2c[1]); close(c2p[0]);
                exit(2);
        }	
	
	wait(0);	

	if(read(c2p[0], &sum, sizeof(int))<=0){
                perror("Parent cannot read");
                close(p2c[1]); close(c2p[0]);
                exit(2);
        }

	printf("The sum of %d and %d is %d.\n", n, m, sum);

	close(p2c[1]); close(c2p[0]);	
	
	return 0;
}
