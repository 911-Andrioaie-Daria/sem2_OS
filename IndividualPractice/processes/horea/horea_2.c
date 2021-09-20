// 2. Create a C program that generates N random integers (N given at the command line). It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	if(argc < 2){
		fprintf(stderr, "Provide a number.\n");
		exit(1);
	}
	
	int N, p2c[2], c2p[2], i;
	N = atoi(argv[1]);
	pipe(p2c); 
	pipe(c2p);
	
	int f = fork();
	if( f == -1){
		perror("Error on fork ");
		exit(2);
	}
	else if( f == 0){ /// child
		close(p2c[1]); close(c2p[0]);

		/// get the numbers from the pipe
		float average;
		int sum, number;
		for(i=0; i<N; i++){
			if(read(p2c[0], &number, sizeof(int)) <= 0){
				perror("Error on reading number:");
				close(p2c[0]); close(c2p[1]);
				exit(6);
			}
			printf("%d\n", number);
			sum += number;	
		}
		average = (float)sum/N;
		if(write(c2p[1], &average, sizeof(float))<=0){
			perror("Error on writing result");
			close(p2c[0]); close(c2p[1]);
			exit(5);
		}	
		
		close(p2c[0]); close(c2p[1]);
		exit(0);	
	}

	// parent
	close(p2c[0]); close(c2p[1]);

	// send the numbers via pipe.
	for(i=0; i<N; i++){
		int number = rand()%101;
		if(write(p2c[1], &number, sizeof(int))<=0){
			perror("Error on writing number:");
			close(p2c[1]); close(c2p[0]);
			exit(4);
		}
	}
	close(p2c[1]);	
	wait(0);   // wait for the child to process them

	float average;
	if(read(c2p[0], &average, sizeof(float))<= 0){
		perror("Error on reading result");
		exit(3);
	}
	close(c2p[0]);

	printf("The average is %f.\n", average);
	
	return 0;
}
