#include <stdio.h>
#include <pthread.h>

void* fa(void *a){
	int i;
	for(i=0;i<10;i++)
		printf("A: %d\n", i);
	return NULL;
}

void* fb(void *a){
	int i;
	for(i=0;i<10;i++)
		printf("B: %d\n", i);
	return NULL;
}

int main(int argc, char** argv){
	int i;
	pthread_t ta, tb;
	
	pthread_create(&ta, NULL, fa, NULL);
	pthread_create(&tb, NULL, fb, NULL);	

	for(i=0;i<10;i++){
		printf("M: %d\n", i);
	}	

	pthread_join(ta, NULL); /// wait for the specific thread to finish execution. it is mandatory to wait for threads.
	pthread_join(tb, NULL);

	return 0;
}
