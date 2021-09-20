#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define T 5
#define N 10
void* f(void *a){
	int i;
	for(i=0;i<N;i++)
		printf("%d: %d\n", *(int*)a, i);
	free(a);
	return NULL;
}


int main(int argc, char** argv){
	int i;
	int *a;
	pthread_t t[T];
	
	for(i=0; i<T; i++){
		a = (int*)malloc(sizeof(int));  /// every thread has a new pointer.
		*a = i;
		pthread_create(&t[i], NULL, f,(void*)a);
	}
	for(i=0; i<T; i++){
	pthread_join(t[i], NULL); /// wait for the specific thread to finish execution. it is mandatory to wait for threads.
	}
	return 0;
}
