// 16. Write a C program that takes as command line arguments 2 numbers: N and M. The program will simulate a thread race that have to pass through M checkpoints. Through each checkpoint the threads must pass one at a time (no 2 threads can be inside the same checkpoint). Each thread that enters a checkpoint will wait between 100 and 200 milliseconds (usleep(100000) makes a thread or process wait for 100 milliseconds) and will print a message indicating the thread number and the checkpoint number, then it will exit the checkpoint. Ensure that no thread will try to pass through a checkpoint until all threads have been created.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t *mutexes;
int *m;
pthread_barrier_t bar;

void* runner(void *a){
	pthread_barrier_wait(&bar);
	int id = *(int*)a;
	
	int i;
	for(i=0; i<*m; i++){
		pthread_mutex_lock(&mutexes[i]);
		printf("%d passed through checkpoint %d\n", id+1, i+1);
		int time = rand()%100000 + 100000;
		usleep(time);
		pthread_mutex_unlock(&mutexes[i]);
	}
	
	printf("%d finished.\n", id);
	free(a);
	return NULL;
}

int main(int argc, char** argv){
	if(argc < 3){
		perror("Please provide 2 numbers");
		exit(1);
	}

	int *n =(int *)malloc(sizeof(int));
	m =(int *)malloc(sizeof(int));
	*n = atoi(argv[1]);
	*m = atoi(argv[2]);

	mutexes = (pthread_mutex_t*)malloc((*m)*sizeof(pthread_mutex_t));

	int i;

	for(i=0; i<*m; i++){
		pthread_mutex_init(&mutexes[i], NULL);
        }
	pthread_barrier_init(&bar, NULL, *n);

	pthread_t t[*n];
	for(i=0; i<*n; i++){
		int *id = (int*)malloc(sizeof(int));
		*id = i;
		if(pthread_create(&t[i], NULL, runner, id)!=0){
			perror("Cannot create thread");
			exit(2);
		}
	}
	for(i=0; i<*n; i++){
        	pthread_join(t[i], NULL);
	}

	for(i=0; i<*m; i++){
                pthread_mutex_destroy(&mutexes[i]);
        }
	pthread_barrier_destroy(&bar);

	free(n);
	free(m);
	free(mutexes);

	return 0;
}
