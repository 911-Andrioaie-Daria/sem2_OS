//  Write a C program that reads a number N and creates 2 threads. One of the threads will generate an even number and will append it to an array that is passed as a parameter to the thread. The other thread will do the same, but using odd numbers. Implement a synchronization between the two threads so that they alternate in appending numbers to the array, until they reach the maximum length N.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int n;
pthread_mutex_t oddmtx, evenmtx;

void* odd(void* a){
	int* arr = (int*)a;

	int i = 0;
	while(i<n){
		pthread_mutex_lock(&oddmtx);
		int n = rand()%100+1;
		if(n%2 == 0)
			n++;
		arr[i] = n;			
		i += 2;
		pthread_mutex_unlock(&evenmtx);
	}
	pthread_mutex_unlock(&evenmtx);
	return NULL;
}

void* even(void* a){
	
	int* arr = (int*)a;

        int i = 1;
        while(i<n){
                pthread_mutex_lock(&evenmtx);
 		int n = rand()%100 + 1;
		if(n%2 == 1)
			n--;
                arr[i] = n;
                i += 2;
                pthread_mutex_unlock(&oddmtx);
        }
	pthread_mutex_unlock(&oddmtx);
        return NULL;
}


int main(){
	do{
		printf("Enter a natural number:\n");
		scanf("%d", &n);
	}while(n<=0);

	int *arr = (int*)malloc(n*sizeof(int));

	pthread_t o, e;
	pthread_mutex_init(&oddmtx, NULL);
	pthread_mutex_init(&evenmtx, NULL);
	
	pthread_mutex_lock(&evenmtx);

	if(pthread_create(&o, NULL, odd, arr) != 0){
		perror("Cannot create thread");
		exit(1);
	}
	if(pthread_create(&e, NULL, even, arr) != 0){
                perror("Cannot create thread");
                exit(1);
        }

	pthread_join(o, NULL);
	pthread_join(e, NULL);

	pthread_mutex_destroy(&oddmtx);
	pthread_mutex_destroy(&evenmtx);	

	int i;
	for(i = 0; i<n; i++){
		printf("%d ", arr[i]);
	}

	printf("\n");
	free(arr);

	return 0;
}
