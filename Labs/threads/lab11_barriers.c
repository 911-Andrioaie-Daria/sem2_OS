#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bar;

void* slow(void* a){

	printf("Slow %d started.\n", *(int*)a);
	int x = rand()%6+5;
	sleep(x);
	printf("Slow finished phase 1.\n");
	printf("Slow finished phase 2.\n");

	pthread_barrier_wait(&bar);
	pthread_mutex_unlock(&mtx);	

	free(a);
	return NULL;
}

void* fast(void* a){
	printf("Fast started.\n");
        int x = rand()%2+2;
        sleep(x);
	printf("Fast finished phase 1.\n");

	printf("Fast is waiting....\n");
	pthread_mutex_lock(&mtx);

	printf("Fast finished phase 2.\n");
	pthread_mutex_unlock(&mtx);
	return NULL;
}


int main(){
	pthread_t s, f;
	pthread_barrier_init(&bar, NULL, 5);
	int i;
	pthread_mutex_lock(&mtx);
	for(i=0; i<5; i++)
		pthread_mutex_unlock(&mtx);
	
	for(i = 0; i<5; i++){
		int *a = (int*)malloc(sizeof(int));
		*a = i;
	if(pthread_create(&s, NULL, slow, a)!=0){
		perror("Cannot create thread");
		exit(1);
	}
	}
	if(pthread_create(&f, NULL, fast, NULL)!=0){
                perror("Cannot create thread");
                exit(1);
        }
	for(i=0; i<5; i++)
		pthread_join(s, NULL);
	pthread_join(f, NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mtx);
	return 0;
}
