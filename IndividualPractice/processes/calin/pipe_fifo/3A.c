// . Implement a program that creates 2 child processes A and B, which communicate using FIFO.
// Process A sends to process B a number 70>n>10; process B receives this number, subtracts 4 and sends it to process A;
// process A reads the number from B, decreases the number by 1 and sends it to B... and so on, until the number n has 1 digit.
// (Fifo created in the command line using mkfifo)


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	int fa = fork();
	if(fa == -1){
		perror("Error on fork");
		exit(1);
	}
	else if(fa == 0){
		int a2b = open("a2b", O_WRONLY);
		int b2a = open("b2a", O_RDONLY);

		if(a2b < 0){
			 perror("Error on opening fifo");
               		 exit(2);
		}
		 if(b2a < 0){
                         perror("Error on opening fifo");
                         exit(2);
                }
		int n = rand()%61 + 10;
		while(n > 9){
			if(write(a2b, &n, sizeof(int))<=0){
				perror("A cannot write");
				exit(3);
			}
			printf("A sends %d\n", n);	
			
			if(read(b2a, &n, sizeof(int))<=0){
				 perror("A cannot read");
                                exit(4);
			}

			printf("A receives %d\n", n);
			n--;
		}	
	
		close(a2b); close(b2a);
		exit(0);
	}


	int fb = fork();
        if(fb == -1){
                perror("Error on fork");
                exit(1);
        }
        else if(fb == 0){
		int a2b = open("a2b", O_RDONLY);
                int b2a = open("b2a", O_WRONLY);

		 if(a2b < 0){
                         perror("Error on opening fifo");
                         exit(2);
                }
                 if(b2a < 0){
                         perror("Error on opening fifo");
                         exit(2);
                }

		 while(1){
			int k, n;
                        k = read(a2b, &n, sizeof(int));
			if(k<0){
                                perror("B cannot read");
                                exit(3);
                        }
			else if (k == 0){
				printf("Game is over.\n");
				break;
			}
			printf("B receives %d\n", n);			

			n -= 4;
                        if(write(b2a, &n, sizeof(int))<=0){
                                 perror("A cannot write");
                                exit(4);
                        }
      			printf("B sends %d\n", n);
                }


                close(a2b); close(b2a);
		exit(0);

        }
	
	wait(0); wait(0);

	return 0;
}
