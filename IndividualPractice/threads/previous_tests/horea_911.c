#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int *arr, counter=0, current_pos=0;
pthread_mutex_t mtx1, mtx2 = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* a){
	int n = *(int*)a;
	printf("Received %d.\n", n);

	if(n%2 == 0){
		pthread_mutex_lock(&mtx1);
		arr[current_pos] = n;
		current_pos++;
		pthread_mutex_unlock(&mtx1);
	}	
	else{
		pthread_mutex_lock(&mtx2);
		counter++;
		pthread_mutex_unlock(&mtx2);

	}
	free(a);
	return NULL;
}

int main(int argc, char** argv){
	if(argc == 1){
		perror("Please provide some arguments.");
		exit(1);
	}
	pthread_t t[argc-1];
	arr = (int*)malloc((argc-1)*sizeof(int));

	int i;
	for(i=1; i<argc; i++){
		int* nr = (int*)malloc(sizeof(int));
		*nr = atoi(argv[i]);
		if(pthread_create(&t[i-1], NULL, thread, nr)!=0){
			perror("Cannot create thread");
			exit(2);
		}
	}
	for(i=1; i<argc; i++){
                if(pthread_join(t[i-1], NULL)!=0){
                        perror("Cannot join thread");
                        exit(3);
                }
        }

	pthread_mutex_destroy(&mtx1);
	pthread_mutex_destroy(&mtx2);	

	printf("The numbers in the array are: ");
	for(i=0; i<current_pos; i++){
		printf("%d ", arr[i]);
	}	
	printf("\n");
	printf("The value of the counter is: %d.\n", counter);

	free(arr);

	return 0;
}
