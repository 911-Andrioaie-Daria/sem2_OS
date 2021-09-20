#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define T 500
#define N 10000

int n = 0;
pthread_mutex_t m;

void* f(void *a){
	int i;
	for(i=0;i<N;i++){
		pthread_mutex_lock(&m);
		n++;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}


int main(int argc, char** argv){
	long long i;
	pthread_t t[T];

	pthread_mutex_init(&m, NULL);	
	for(i=0; i<T; i++){
		pthread_create(&t[i], NULL, f, (void*)i);
	}
	for(i=0; i<T; i++){
		pthread_join(t[i], NULL); /// wait for the specific thread to finish execution. it is mandatory to wait for threads.
	}
	pthread_mutex_destroy(&m);
	printf("%d\n", n);
	return 0;
}
