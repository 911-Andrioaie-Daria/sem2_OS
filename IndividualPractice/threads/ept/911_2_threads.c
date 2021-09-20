#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_barrier_t bar;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int G = 0;

void* thread(void *a){
	int id = *(int*)a;
	int A = rand()%10 + 1;
	pthread_mutex_lock(&mtx);
 	printf("Thread %d added %d to %d and it is now %d.\n", id, A, G, G+A);
	G += A;
	pthread_mutex_unlock(&mtx);

	printf("Thread %d waiting ...\n", id);	
	pthread_barrier_wait(&bar);

	int B = rand()%6 + 10;
        pthread_mutex_lock(&mtx);
	if(G > B){
        	printf("Thread %d generated %d and subtracted from %d, which is now %d.\n", id, B, G, G-B);
        	G -= B;
	}
	else
		printf("Thread %d generated %d and didn't subtract from %d.\n", id, B, G);
        pthread_mutex_unlock(&mtx);


	free(a);
	return NULL;
}

int main(int argc, char** argv){
	if(argc == 1){
		perror("Please provide one argument");
		exit(1);
	}

	int N = atoi(argv[1]);

	pthread_barrier_init(&bar, NULL, N);
	pthread_t t[N];
	int i;
	for(i=0; i<N; i++){
		int* v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, thread, v)!=0){
			perror("Error on creating threads");
			exit(1);
		}
	}
	
	for(i=0; i<N; i++){
                if(pthread_join(t[i], NULL)!=0){
                        perror("Error on joining threads");
                        exit(1);
                }
        }
	printf("The value of G is %d.\n", G);

	return 0;
}
