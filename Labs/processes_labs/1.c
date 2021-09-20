#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){
	int f=fork();
	if (f<0){
		perror("Unable to create the first copy.");
		exit(1);
}
	if(f==0){
		int f2 = fork();
		if(f2 < 0){		
			perror("Unable to create the second copy.");
			exit(2);
		}
		if(f2==0){
			printf("C3 only pid: %d parent: %d\n", getpid(), getppid());
			exit(0);
		}
		wait(0);
		printf("Only in C1 pid: %d parent: %d\n", getpid(), getppid());
		exit(0);	
	}
	wait(0);
	printf("Process id: %d Parent id: %d\n", getpid(), getppid());
	return 0;
}
