//1. Create a C program that runs a bash command received as a command line argument and prints the execution time.

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv){
	struct timeval t0, t1;
	double duration;	
	int status;

	if(argc < 2){
		fprintf(stderr, "Provide some arguments.\n");
//		perror("Provide some arguments.\n");
		exit(1);
	}
	gettimeofday(&t0, NULL);
	int f = fork();
	if( f == 0){ // child
		execvp(argv[1], argv+1);
		exit(2);	
	}
	else if ( f == -1){
		perror("Error on fork");
		exit(3);
	} 
	wait(&status);
	gettimeofday(&t1, NULL);
	duration = t1.tv_sec - t0.tv_sec;
	printf("Duration is %lf seconds.\n", duration);	

	return WEXITSTATUS(status);
}
