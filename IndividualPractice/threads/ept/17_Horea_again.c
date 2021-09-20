//17. Write a C program that creates 2^N threads that race to the finish (N is a command line argument). The threads must pass through N checkpoint. The checkpoint with number X will allow half as many threads to pass simultaneously than checkpoint number X - 1 (N >= X >=1). Checkpoint 0 (the first one) will allow 2^(N-1) to pass simultaneously through it..

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t *sems;
int N;

void* thread(void* a){
	int id = *(int*)a;
	int i;
	for(i = 0; i<N; i++){
		sem_wait(&sems[i]);
		printf("Thread %d passed checkpoint %d.\n", id, i);
		sem_post(&sems[i]);	
	}	
	
	free(a);
	return NULL;
}

int main(int argc, char** argv){
	if(argc == 1){
		perror("Please provide one argument");
		exit(1);
	}
	N = atoi(argv[1]);
	int p=1, i;
	for(i=1; i<=N; i++)
		p *= 2;
	
	int cp = p;
	cp /= 2;
	pthread_t t[p];
	sems = (sem_t*)malloc(N*sizeof(sem_t));
	for(i=0; i<N; i++){
		sem_init(&sems[i], 0, cp);
		cp /= 2;
	}

	for(i=0; i<p; i++){
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, thread, v) != 0){
			perror("Error on creating thread");
			exit(1);
		}
	}
		
	for(i=0; i<p; i++){
                if(pthread_join(t[i], NULL) != 0){
                        perror("Error on joining thread");
                        exit(1);
                }
        }
	
	for(i=0; i<N; i++){
		sem_destroy(&sems[i]);
	}

	free(sems);
	return 0;
}
