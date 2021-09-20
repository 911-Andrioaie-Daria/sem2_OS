// 6. Create two processes A and B. A generates a random number n between 50 and 200. If it is even, it sends it to B, if it is odd it sends n+1 to B. B receives the number and divides it by 2 and sends it back to A. The process repeats until n is smaller than 5. The processes will print the value of n at each step.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(){
	int a2b[2], b2a[2];

	pipe(a2b); pipe(b2a);

	int fa = fork();
	if( fa == -1){
		perror("Error on fork");
		exit(1);
	}

	/// child A	
	else if (fa == 0){
		close(a2b[0]); close(b2a[1]);
		int n = rand()%151 + 50;
		while(n>=5){
			if(n%2 == 1)
				n = n+1;
			if(write(a2b[1], &n, sizeof(int))<=0){
				perror("A cannot write to B.");
				exit(2);
			}
			printf("A sends %d.\n", n);
			
			if(read(b2a[0], &n, sizeof(int))<=0){
                                perror("A cannot read from B.");
                                exit(3);
                        }
			printf("A received %d.\n", n);
		}	
		close(a2b[1]); close(b2a[0]);
		exit(0);
	}
	
	int fb = fork();
        if( fb == -1){
                perror("Error on fork");
                exit(1);
        }

        /// child B
        else if (fb == 0){
                close(a2b[1]); close(b2a[0]);
		int n;
                while(1){
                        if(read(a2b[0], &n, sizeof(int))<=0){
                                perror("B cannot read from A.");
                                exit(4);
                        }
                        printf("B received %d.\n", n);
			n /= 2;
                        if(write(b2a[1], &n, sizeof(int))<=0){
                                perror("B cannot write to A.");
                                exit(5);
                        }
			printf("B sends %d.\n", n);

                }


                close(a2b[0]); close(b2a[1]);
                exit(0);
        }

	close(a2b[1]); close(b2a[0]);
        close(a2b[0]); close(b2a[1]);
	wait(0); wait(0);	

	return 0;
}
