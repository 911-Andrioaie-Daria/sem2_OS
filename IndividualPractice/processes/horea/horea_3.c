// 3. Write a C program that creates two child processes. The two child processes will alternate sending random integers between 1 and 10(inclusively) to one another until one of them sends the number 10. Print messages as the numbers are sent.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(){
	int a2b[2], b2a[2];	
	pipe(a2b); pipe(b2a);

	int f1 = fork();
	if( f1 == -1){
		perror("Cannot create fork.");
		exit(1);
	}
	
	/// CHILD A
	else if(f1 == 0){
		close(a2b[0]); close(b2a[1]);
		int n;
		srand(time(0));
		n = rand()%10 +1;
		if(write(a2b[1], &n, sizeof(int))<=0){
			perror("A cannot write to B");
			close(a2b[1]); close (b2a[0]);
			exit(1);
		}	
		printf("A sends %d.\n", n);	
		while(1){
			if(read(b2a[0], &n, sizeof(int))<=0){
				perror("A cannot read from B");
				close(a2b[1]); close (b2a[0]);
				exit(1);
			}
			printf("A received %d.\n", n);
			if(n==10){
				close(a2b[1]); close (b2a[0]);
				exit(0);	
			}			

			srand(time(0));
			n = rand()%10 +1;
			if(write(a2b[1], &n, sizeof(int))<=0){
				perror("A cannot write to B");
				close(a2b[1]); close (b2a[0]);
				exit(1);
			}	
			printf("A sends %d.\n", n);		
			
		}			

		exit(0);
	}

	int f2 = fork();

	if( f2 == -1){
		perror("Cannot create fork.");
		exit(1);
	}
	
	/// CHILD B
	else if(f2 == 0){
		close(b2a[0]); close(a2b[1]);
		int n;
		while(1){
			if(read(a2b[0], &n, sizeof(int))<=0){
				perror("B cannot read from A");
				close(b2a[1]); close(a2b[0]);
				exit(1);
			}
			printf("B received %d.\n", n);
			if(n==10){			
				close(b2a[1]); close(a2b[0]);
				exit(0);	
			}			
			srand(time(0));
			n = rand()%10 +1;
			if(write(b2a[1], &n, sizeof(int))<=0){
				perror("B cannot write to A");
				close(b2a[1]); close(a2b[0]);
				exit(1);
			}	
			printf("B sends %d.\n", n);		
			
		}			
		exit(0);
	}

	/// PARENT
	close(a2b[0]); close(a2b[1]);	
	close(b2a[0]); close(b2a[1]);	
	wait(0); wait(0);
	return 0;
}
