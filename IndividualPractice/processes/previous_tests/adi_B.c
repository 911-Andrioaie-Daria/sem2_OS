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

	int f2s[2];
	pipe(f2s);

	int f1 = fork();
	if(f1 == -1){
		perror("Error on fork");
		exit(2);
	}
	else if (f1 == 0){
		close(f2s[0]);
       		 char* path = argv[1];
		 int a2b = open(path, O_RDONLY);

		if(a2b < 0){
			perror("Cannot open fifo");
			exit(2);
		}

       		 int n, i, s=0;

	        if(read(a2b, &n, sizeof(int))<0){
        	         perror("B cannot read");
        	        exit(3);
       		 }

      		int* a = (int*)malloc(n*sizeof(int));

        	 if(read(a2b, a, n*sizeof(int))<0){
                	 perror("B cannot read");
               		 free(a);
			 exit(3);
       		 }	
		
		for(i =0; i<n; i++)
			s+=a[i];

    		 close(a2b);
		 unlink(path);
       		 free(a);
		
		if(write(f2s[1], &s, sizeof(int))<0){
			perror("Child cannot write");
                        exit(2);

		}
		close(f2s[1]);
		exit(0);
	}

	int f2 = fork();
        if(f2 == -1){
                perror("Error on fork");
                exit(2);
        }
        else if (f2 == 0){
		close(f2s[1]);

		int s, d;
		if(read(f2s[0], &s, sizeof(int))<0){
			perror("Child cannot read");
			exit(2);
		}
		close(f2s[0]);

		printf("The divisors of the sum %d are:\n", s);

		for(d=1; d<=s; d++)
			if(s%d == 0)
			printf("%d ", d);
		printf("\n");

		exit(0);
	}

	close(f2s[1]); close(f2s[0]);
	wait(0); wait(0);
	return 0;
}

	

