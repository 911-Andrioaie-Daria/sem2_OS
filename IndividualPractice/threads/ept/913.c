#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv){
	if(argc == 1){
		perror("No arguments provided");
		exit(1);
	}	
	int N = atoi(argv[1]);
	int c1p[2], c2p[2];
	srand(time(NULL));

	if(pipe(c1p)!=0){
		perror("Error on pipe");
		exit(1);
	}	
	if(pipe(c2p)!=0){
                perror("Error on pipe");
                exit(1);
        }

	int f1 = fork();
	if(f1 == 0){ //child 1
		close(c2p[1]); close(c2p[0]); close(c1p[0]);
		
		int* fr = (int*)calloc(10,sizeof(int));	

		int i;
		for(i=0; i<N; i++){
			int d = rand()%400+100;
			printf("Child 1 generated %d.\n", d);
			while(d){
				fr[d%10]++;
				d /= 10;
			}
		}
		printf("Child 1 has the array: ");
		for(i=0; i<10; i++)
			printf("%d ", fr[i]);
		printf("\n");
			
		if(write(c1p[1], fr, 10*sizeof(int))<0){
			perror("Error on writing to parent");
			exit(1);
		}
		free(fr);
		close(c1p[1]);
		exit(0);
	}
	int f2 = fork();
        if(f2 == 0){ //child 2
		close(c1p[1]); close(c1p[0]); close(c2p[0]);

		int* fr = (int*)calloc(10,sizeof(int));
		int i;
                for(i=0; i<N; i++){
                        int d = rand()%500+500;
        		printf("Child 2 generated %d.\n", d); 
	                while(d){
                                fr[d%10]++;
                                d /= 10;
                        }
                }
        	printf("Child 2 has the array: ");
                for(i=0; i<10; i++)
                        printf("%d ", fr[i]);
                printf("\n"); 

   	        if(write(c2p[1], fr, 10*sizeof(int))<0){
                        perror("Error on writing to parent");
                        exit(1);
                }
                free(fr);


                close(c2p[1]);


                exit(0);
        }
	close(c1p[1]); close(c2p[1]);
	wait(0); wait(0);

	int fr1[10], fr2[10];
	if(read(c1p[0], fr1, 10*sizeof(int))<0){
		perror("Error on reading from child 1");
		exit(1);
	}	

	if(read(c2p[0], fr2, 10*sizeof(int))<0){
                perror("Error on reading from child 2");
                exit(1);
        }

	close(c1p[0]); close(c2p[0]);
	int i;
	for(i=0; i<10; i++){
		if(fr1[i] == fr2[i])
			printf("%d - equal\n", i);
		else if(fr1[i] > fr2[i])
			printf("%d - child 1\n", i);
		else
			printf("%d - child 2\n", i);
	}

	return 0;
}
