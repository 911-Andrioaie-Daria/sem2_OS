#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* slow(void* a){

	printf("Slow started.\n");
	int x = rand()%6+5;
	sleep(x);
	printf("Slow finished phase 1.\n");
	
	printf("Slow finished phase 2.\n");
	pthread_cond_signal(&cond);
	return NULL;
}

void* fast(void* a){
	printf("Fast started.\n");
        int x = rand()%2+2;
        sleep(x);
	printf("Fast finished phase 1.\n");
	pthread_mutex_lock(&mtx);

	printf("Fast is waiting....\n");
	pthread_cond_wait(&cond, &mtx);
	printf("Fast finished phase 2.\n");
	pthread_mutex_unlock(&mtx);
	return NULL;
}


int main(){
	pthread_t s, f;

	if(pthread_create(&s, NULL, slow, NULL)!=0){
		perror("Cannot create thread");
		exit(1);
	}

	if(pthread_create(&f, NULL, fast, NULL)!=0){
                perror("Cannot create thread");
                exit(1);
        }

	pthread_join(s, NULL);
	pthread_join(f, NULL);
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mtx);
	return 0;
}
