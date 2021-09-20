#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 50
sem_t lane2, lane4;
pthread_barrier_t bar, bar2, bar4;

void* car(void* a){
	int id = *(int*)a;
	int lane = id%2;

	printf("Car %d is on lane %d\n", id, lane);
	pthread_barrier_wait(&bar);
	if(lane == 0){
		sem_wait(&lane4);
		printf("Car %d from lane 4 passed the intersection.\n", id);
		//pthread_barrier_wait(&bar4);
		sem_post(&lane2);
	}
	else{
		sem_wait(&lane2);
		printf("Car %d from lane 2 passed the intersection.\n", id);
         //	pthread_barrier_wait(&bar2);
	        sem_post(&lane4);
	}
	free(a);
	return NULL;
}

int main(){
	pthread_t t[100];
	sem_init(&lane4, 0, 8);
	sem_init(&lane2, 0, 3);
	pthread_barrier_init(&bar, NULL, N);
	pthread_barrier_init(&bar2, NULL, 3);
	pthread_barrier_init(&bar4, NULL, 8);

	int i;
	for(i=0; i<N; i++){
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, car, v)!=0){
			perror("Cannot create thread");
			exit(1);
		}
		
	}
	for(i = 0; i<N; i++)
		pthread_join(t[i], NULL);

	sem_destroy(&lane4);
	sem_destroy(&lane2);
	pthread_barrier_destroy(&bar);
	pthread_barrier_destroy(&bar2);
	pthread_barrier_destroy(&bar4);
	return 0;
}
