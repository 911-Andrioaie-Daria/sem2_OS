#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int pr=0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* a){
	int nr =*(int*)a;
	int is_prime = 1, d;
	for(d=2; d<=nr/2 && is_prime == 1; d++){
		if(nr%d == 0)
			is_prime = 0;
		
	}
	if(is_prime == 1){
		pthread_mutex_lock(&mtx);
		pr++;
		pthread_mutex_unlock(&mtx);
	}


	return NULL;
}


int main(){
	int *arr =(int*)malloc(100*sizeof(int));
	int n = 0, nr;
	printf("Enter a number:\n");
	scanf("%d", &nr);
	while(nr!=-1){
		arr[n]=nr;
		n++;
		printf("Enter a number:\n");
        	scanf("%d", &nr);
	}

	pthread_t t[n];
	int i;
	for(i=0; i<n; i++){
		if(pthread_create(&t[i], NULL, thread, &arr[i])!=0){
			perror("Cannot create thread");
			exit(1);
		}	
	}
	for(i=0; i<n; i++){
                if(pthread_join(t[i], NULL)!=0){
                        perror("Cannot join thread");
                        exit(1);
                }
        }

	pthread_mutex_destroy(&mtx);
	free(arr);
	printf("There are %d prime numbers.\n", pr);
	return 0;

}
