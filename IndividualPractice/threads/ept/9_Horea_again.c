// 9. Using PIPE channels create and implement the following scenario:
// Process A reads N integer numbers from the keyboard and sends them another process named B. Process B will add a random number, between 2 and 5, to each received number from process A and will send them to another process named C. The process C will add all the received numbers and will send the result back to process A. All processes will print a debug message before sending and after receiving a number.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int a2b[2], b2c[2], c2a[2];
	if(pipe(a2b) != 0){
		perror("Error on pipe");
		exit(1);
	}
	if(pipe(b2c) != 0){
		perror("Error on pipe");
		exit(1);
	}
	if(pipe(c2a) != 0){
		perror("Error on pipe");
		exit(1);
	}

	int fa = fork();
	if(fa == 0){  /// process A
		close(b2c[0]); close(b2c[1]); close(a2b[0]); close(c2a[1]);
		int n, i;
		printf("Enter n:\n");
		scanf("%d",&n);

		if(write(a2b[1], &n, sizeof(int))<=0){
			perror("Error on writing to B");
			close(a2b[1]); close(c2a[0]);
			exit(1);
		}

		for(i=0; i<n; i++){
			int d;
			printf("Enter number:\n");
			scanf("%d",&d);
			if(write(a2b[1], &d, sizeof(int))<=0){
				perror("Error on writing to B");
				close(a2b[1]); close(c2a[0]);
				exit(1);
			}
		}
		int s;
		if(read(c2a[0], &s, sizeof(int))<=0){
			perror("Error on reading from C");
			close(a2b[1]); close(c2a[0]);
			exit(1);
		}
		printf("The sum is %d.\n",s);

		close(a2b[1]); close(c2a[0]);
		exit(0);
	}

	int fb = fork();
	if(fb == 0){  /// process B
		close(c2a[0]); close(c2a[1]); close(a2b[1]); close(b2c[0]);
		int i, n;

		if(read(a2b[0], &n, sizeof(int))<=0){
			perror("Error on reading from A");
			close(a2b[0]); close(b2c[1]);
			exit(1);
		}

		if(write(b2c[1], &n, sizeof(int))<=0){
			perror("Error on writing to C");
			close(a2b[0]); close(b2c[1]);
			exit(1);
		}

		for(i=0; i<n; i++){
			int d;
			if(read(a2b[0], &d, sizeof(int))<=0){
				perror("Error on reading from A");
				close(a2b[0]); close(b2c[1]);
				exit(1);
			}

			int r = rand()%4+2;
			d += r;

			printf("B generated %d and sends %d.\n", r, d);
			if(write(b2c[1], &d, sizeof(int))<=0){
				perror("Error on writing to C");
				close(a2b[0]); close(b2c[1]);
				exit(1);
			}
		}

		close(a2b[0]); close(b2c[1]);
		exit(0);
	}

	int fc = fork();
	if(fc == 0){  /// process C
		close(a2b[0]); close(a2b[1]); close(b2c[1]); close(c2a[0]);

		int i, n, s=0;

		if(read(b2c[0], &n, sizeof(int))<=0){
			perror("Error on reading from B");
			close(b2c[0]); close(c2a[1]);
			exit(1);
		}

		for(i=0; i<n; i++){
			int d;
			if(read(b2c[0], &d, sizeof(int))<=0){
				perror("Error on reading from B");
				close(b2c[0]); close(c2a[1]);
				exit(1);
			}

			s += d;

			printf("C received %d.\n",d);
		}

		if(write(c2a[1], &s, sizeof(int))<=0){
			perror("Error on writing to A");
			close(b2c[0]); close(c2a[1]);
			exit(1);
		}


		close(b2c[0]); close(c2a[1]);
		exit(0);
	}

	wait(0); wait(0); wait(0);

	return 0;
}
