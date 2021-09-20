// 5. Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte dintr-un fişier de tip text două numere întregi pe care le trimite prin pipe procesului copil, iar procesul copil returnează prin pipe suma lor.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int n, m, sum;
	
	FILE* f = fopen("bota.txt", "r");

	 if(f < 0){
                perror("Cannot open file");
                exit(1);
        }

	int a2b = open("a2b", O_WRONLY);
	int b2a = open("b2a", O_RDONLY);

	if(a2b < 0){
		perror("Cannot open fifo");
		exit(1);
	}
	if(b2a < 0){
                perror("Cannot open fifo");
                exit(1);
        }	

	fscanf(f, "%d", &n);
	fscanf(f, "%d", &m);
	fclose(f);

	if(write(a2b, &n, sizeof(int))<0){
		perror("Cannot write to fifo");
                exit(2);
	}
	
	if(write(a2b, &m, sizeof(int))<0){
                perror("Cannot write to fifo");
                exit(2);
        }

	if(read(b2a, &sum, sizeof(int))<0){
                perror("Cannot read from fifo");
                exit(3);
        }
		
	printf("The sum of the numbers %d and %d is %d.\n", n, m, sum);
	close(a2b);
	close(b2a);

	return 0;
}
