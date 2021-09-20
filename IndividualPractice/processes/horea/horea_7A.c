// 7. Create two processes A and B. A creates a shared memory segment. A then keeps reading strings from the standard input and places whatever it reads in the shared memory segment(replacing previous data). Process B, on each run, reads the data from the shared memory segment and counts the number of vowels. Process A, upon receiving a SIGINT, deletes the shared memory segment.
//

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int shmid;
char* p;

void f(int sgn){
	p[0]='x';
	
	sleep(1);	

	shmdt(p);
//	free(p);
	shmctl(shmid, IPC_RMID, NULL);	
	exit(0);
}

/// process A
int main(){
	signal(SIGINT, f);
	shmid = shmget(2854, 1000*sizeof(char), IPC_CREAT | 0600);
	
	p = shmat(shmid, 0, 0);

	while(1){
		char* s = malloc(1000);
		scanf("%s", s);
		strcpy(p+1, s);
		free(s);
	}
	return 0;
}
