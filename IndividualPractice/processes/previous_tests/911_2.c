#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int n,i, count;
	do{
		printf("Enter n: \n");
		scanf("%d", &n);
	}while(n<=0);

	int* a = (int*)malloc(n*sizeof(int));
	//int a[n];
	for(i = 0; i<n;i++){
		printf("Enter number: \n");
		scanf("%d", a+i);
	}
	
	int a2b = open("a2b", O_WRONLY);
	if(a2b < 0){
		perror("Cannot open fifo");
		free(a);
		exit(1);
	}
	if(write(a2b, &n, sizeof(int))<0){
		perror("A cannot write");
		close(a2b);
		free(a);
		exit(2);
	}
	if(write(a2b, a, n*sizeof(int))<0){
                perror("A cannot write");
        	close(a2b); 
	        free(a);
                exit(2);
        }
	
	close(a2b);
	free(a);

	int b2a = open("b2a", O_RDONLY);
	if(a2b < 0){
                perror("Cannot open fifo");
                exit(1);
        }
	if(read(b2a, &count, sizeof(int))<0){
		perror("A cannot read");
        	close(b2a);
	        exit(2);
	}


	close(a2b);
	printf("There are %d numbers not divisible by 3.\n", count);
	return 0;

}
