// 2. Write a program that creates 4 threads and had 3 global variables v5, v2, v3.
// Each thread generates a random number and:
// - if the number is multiple of 2 increments v2
// - if the number is multiple of 3, increments v3
// - if the number is multiple of 5 increments v5
//
// The number can be a multiple of more numbers (ex. for 10 we will increment both V2 and V5)
//
// Threads print the generated numbers and stop when 30 numbers have been generated.
//
// The main program prints the 3 global variables.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int v2 = 0, v3 = 0, v5 = 0, count = 0;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx5 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtxc = PTHREAD_MUTEX_INITIALIZER;



void* increment(void* a){
	int id = *(int*)a;
	while(1){
		pthread_mutex_lock(&mtxc);
		if(count >= 30){
			pthread_mutex_unlock(&mtxc);
			break;
		}
		int n = rand()%100;

		printf("%d generated %d.\n", id, n);
		count++;
		pthread_mutex_unlock(&mtxc);

		if(n%2==0){
			pthread_mutex_lock(&mtx2);
			v2++;
			pthread_mutex_unlock(&mtx2);
		}
		if(n%3==0){
                        pthread_mutex_lock(&mtx3);
                        v3++;
                        pthread_mutex_unlock(&mtx3);
                }
		if(n%5==0){
                        pthread_mutex_lock(&mtx5);
                        v5++;
                        pthread_mutex_unlock(&mtx5);
                }		
	}


	free(a);
	return NULL;
}

int main(){
	int i;
	pthread_t t[4];

	for(i=0; i<4; i++){
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, increment, v)!=0){
			perror("Cannot create thread");
			exit(1);
		}
	}

	for(i=0; i<4; i++){
                if(pthread_join(t[i], NULL)!=0){
                        perror("Cannot join thread");
                        exit(2);
                }
        }

	pthread_mutex_destroy(&mtx2);
	pthread_mutex_destroy(&mtx3);
	pthread_mutex_destroy(&mtx5);
	pthread_mutex_destroy(&mtxc);

	printf("Count is %d.\n", count);
	printf("The are %d numbers divisible by 2, %d numbers divisible by 3 and %d numbers divisible by 5.\n", v2, v3, v5);

	return 0;
	
}
