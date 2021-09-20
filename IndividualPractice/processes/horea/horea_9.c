// 9. Using PIPE channels create and implement the following scenario: Process A reads N integer numbers from the keyboard and sends them another process named B. Process B will add a random number, between 2 and 5, to each received number from process A and will send them to another process named C. The process C will add all the received numbers and will send the result back to process A. All processes will print a debug message before sending and after receiving a number.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
int main(int argc, char** argv){
	if(argc != 2){
		fprintf(stderr, "Enter exactly one argument.\n");
		exit(1);
	}
	
	int n = atoi(argv[1]);
	int a2b[2], b2c[2], c2a[2];
	pipe(a2b); pipe(b2c); pipe(c2a);
	
	int fa = fork();
	if(fa == -1){
		perror("Error on fork");
		exit(2);
	}

	///process A
	else if(fa == 0){
		close(a2b[0]); close(c2a[1]);
		close(b2c[0]); close(b2c[1]);

		/// send numbers to B
		int i;
		for(i=0; i<n; i++){
			int nr =0;
			if(scanf("%d", &nr) < 0){
				perror("A cannot read.");
				close(a2b[1]); close(c2a[0]);
				exit(3);
			}
			printf("A sends %d.\n", nr);

			if(write(a2b[1], &nr, sizeof(int))<0){
				perror("A cannot send to B.");
                         	close(a2b[1]); close(c2a[0]);
			        exit(4);
			}
		}		
		close(a2b[1]);
		
		int sum;		

		if(read(c2a[0], &sum, sizeof(int))<0){
			 perror("A cannot read from C.");
                	 close(c2a[0]); 
		         exit(5);
		}
		printf("A received the sum %d\n", sum);
		
		close(c2a[0]);
	}

	int fb = fork();
        if(fb == -1){
                perror("Error on fork");
                exit(2);
        }

        // process B
        else if(fb == 0){
                close(a2b[1]); close(b2c[0]);
                close(c2a[0]); close(c2a[1]);

		int i;
                for(i=0; i<n; i++){
                        int nr =0;
                        if(read(a2b[0], &nr, sizeof(int)) < 0){
                                perror("B cannot read.");
                                close(a2b[0]); close(b2c[1]);
                                exit(3);
                        }

                        printf("B received %d.\n", nr);
			nr = nr + rand()%4 + 2;

                        if(write(b2c[1], &nr, sizeof(int))<0){
                                perror("B cannot send to C.");
                                close(a2b[0]); close(b2c[1]);
                                exit(4);
                        }
			printf("B sends %d.\n", nr);
                }


                close(a2b[0]); close(b2c[1]);
        }


	int fc = fork();
        if(fc == -1){
                perror("Error on fork");
                exit(2);
        }

        // process C
        else if(fc == 0){
                close(c2a[0]); close(b2c[1]);
                close(a2b[0]); close(a2b[1]);

		int i, sum=0;
                for(i=0; i<n; i++){
                        int nr =0;
                        if(read(b2c[0], &nr, sizeof(int)) < 0){
                                perror("B cannot read.");
                                close(c2a[1]); close(b2c[0]);
                                exit(3);
                        }

                        printf("C received %d.\n", nr);
                        sum += nr;
                }
		close(b2c[0]);
		if(write(c2a[1], &sum, sizeof(int))<0){
			perror("C cannot write to A");
			close(c2a[1]);
			exit(4);
		}

                close(c2a[1]);
        }

	wait(0); wait(0); wait(0);


	

	return 0;
}

