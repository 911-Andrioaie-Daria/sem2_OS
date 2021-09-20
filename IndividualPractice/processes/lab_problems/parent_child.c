#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	if(fork()==0){
		printf("I'm the fisrt child %d, my parent is %d\n", getpid(), getppid());
		if(fork()==0){
			printf("I'm the second child %d, my  parent is %d\n", getpid(), getppid());	
			exit(0);	
		}
		wait(0);
		exit(0);
	}
	wait(0);
	printf("I'm the original parent: %d, my parent is %d\n", getpid(), getppid());
	while(1);	
	return 0;
}
