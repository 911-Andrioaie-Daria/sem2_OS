#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int *arr, current=0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* a){
	int id = *(int*)a;

	int b, c, db=0, dc = 0, copy_b, copy_c;
	b = rand()%300;
	copy_b = b;
	c = rand()%300;
	copy_c = c;

	printf("Thread %d generated %d and %d.\n", id, b, c);

	while(copy_b){
		db++;
		copy_b /= 10;
	}
	while(copy_c){
                dc++;
                copy_c /= 10;
        }
	
	if(db == 3 && dc == 3){
		pthread_mutex_lock(&mtx);
		arr[current] = b;
		arr[current+1] = c;
		current += 2;
		pthread_mutex_unlock(&mtx);
	}

	free(a);
	return NULL;
}

int main(int argc, char** argv){
	if(argc < 2){
		perror("Please provide an argument");
		exit(1);
	}

	int i;
	int n = atoi(argv[1]);
	arr = (int*)malloc(2*n*sizeof(int));

	pthread_t t[n];
	for(i=0; i<n; i++){
		int *v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, thread, v)!=0){
			perror("Cannot create thread");
			exit(2);
		}
	}

	for(i=0; i<n; i++){
                if(pthread_join(t[i], NULL)!=0){
                        perror("Cannot join thread");
                        exit(3);
                }
        }

	pthread_mutex_destroy(&mtx);
	
	printf("The numbers in the array are: ");
	for(i = 0; i< current; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	
	free(arr);
	return 0;
}
