#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* fast(void* a){
	int idx;
	idx = (int)pthread_self();
	printf("Thread %d started.\n", idx);
	int r;
	r = rand()%2+1;
	sleep(r);
	printf("Thread %d phase 1 is done.\n", idx);

	pthread_mutex_lock(&mtx); /// mutex is locked.
	pthread_cond_wait(&cond, &mtx); /// unlocking the mutex. it adds the thread                                        /// in the queue
	
	printf("Thread %d starting phase 2.\n", idx);
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

void* slow(void* a){
	int idx;
        idx = (int)pthread_self();
        printf("Slower thread %d started.\n", idx);
 
	int r;
	r = rand()%2+3;
        sleep(r);
        printf("Thread %d phase 1 is done.\n", idx);
 
	pthread_cond_broadcast(&cond);
	printf("Thread %d phase 2 is done.\n", idx);

 
	return NULL;
}

int main(){
	pthread_t t[N];

	int i;
	for(i=0; i<N-1; i++){
		if(pthread_create(&t[i], NULL, fast, NULL)!=0){
			perror("Cannot create thread");
			exit(1);	
		}
	}
	if(pthread_create(&t[N-1], NULL, slow, NULL)!=0){
                perror("Cannot create thread");
                exit(2);
                }

	for(i=0; i<N; i++){
                if(pthread_join(t[i], NULL)!=0){
                        perror("Cannot join thread");
                        exit(1);
                }
        }
	return 0;
}
