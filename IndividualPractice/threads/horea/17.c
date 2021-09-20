// 17. Write a C program that creates 2^N threads that race to the finish (N is a command line argument). The threads must pass through N checkpoint. The checkpoint with number X will allow half as many threads to pass simultaneously than checkpoint number X - 1 (N >= X >=1). Checkpoint 0 (the first one) will allow 2^(N-1) to pass simultaneously through it. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t *semaphores;
int n;

void* runner(void* a){
	int id = *(int*)a;
	int i;

	for(i =0; i<n; i++){
		sem_wait(&semaphores[i]);
		printf("%d passed through checkpoint %d.\n", id, i);
		int time = rand()%900000 + 100000;
                usleep(time);
		sem_post(&semaphores[i]);
	}		
	printf("%d finished.\n", id);
	free(a);	
	return NULL;
}

int main(int argc, char** argv){
	if(argc < 2){
		perror("Please provide an argument");
		exit(1);
	}
	n = atoi(argv[1]);	
	
	int p=1, i;
	for(i=0; i<n; i++)
		p *= 2;

	semaphores = (sem_t*)malloc(n*sizeof(sem_t));

	int cp = p/2;
	for(i = 0; i<n; i++){
		sem_init(&semaphores[i], 0, cp);
		cp /= 2;
	}
	
	pthread_t t[p];
	
	for(i=0; i<p; i++){
		int *a = (int*)malloc(sizeof(int));
		*a = i;
		if(pthread_create(&t[i], NULL, runner, a) != 0){
			perror("Cannot create thread");
			exit(1);
		}
	}	

	for(i=0; i<p; i++){
       		pthread_join(t[i], NULL);	
	}

	for(i=0; i<n; i++)
		sem_destroy(&semaphores[i]);		
			
	return 0;
}
