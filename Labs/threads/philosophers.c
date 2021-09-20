#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int n=5;
pthread_mutex_t m[5];
pthread_mutex_t b = PTHREAD_MUTEX_INITIALIZER;

void* philosopher(void* a){
	int i = *(int*)a;
	printf("Philosopher %d started.\n", i);
	int l=i;
	int r=(i+1)%n;

	while(1){
		printf("Philosopher %d .....\n", i);
		pthread_mutex_lock(%m[l]);
		if(pthread_mutex_trylock(&m[r])==0){		
			printf("Philosopher %d eats!\n", i);
			sleep(rand()%3+2);
			pthread_mutex_unlock(&m[r]);
			pthread_mutex_unlock(&m[l]);
			printf("Philosopher %d releasing both forks.\n", i);
		}
		else{
			printf("Philosopher %d releasing left fork\n", i);
			pthread_mutex_unlock(&m[l]);
		}
		sleep(rand()%2+1);
	}
	free(a);
	return NULL;
}

int main(){
	int i;
	pthread_t phi[n];
	
	for(i=0;i<n;i++){
		pthread_mutex_init(&m[i], NULL);
	}

	for(i=0;i<n;i++){
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&phi[i], NULL, philosopher, v) < 0){
			perror("Cannot create thread");
			exit(1);
		}
	}
	for(i=0;i<n;i++);
		pthread_join(phi[i], NULL);
	return 0;
}
