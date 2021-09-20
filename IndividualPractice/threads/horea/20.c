// 20. Write a C program that creates N threads and one child process (N given as a command line argument). Each thread will receive a unique id from the parent. Each thread will generate two random numbers between 1 and 100 and will print them together with its own id. The threads will send their generated numbers to the child process via pipe. The child process will calculate the average of each pair of numbers received from a thread and will print it alongside the thread id. Use efficient synchronization.

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int t2c[2];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* thread(void *a){
	int id = *(int*)a;

	int n, m;
	n = rand()%100+1;
	m = rand()%100+1;

	printf("Thread %d generated %d and %d.\n", id, n, m);	

	pthread_mutex_lock(&mtx);
	if(write(t2c[1], &id, sizeof(int))<0){
		perror("Thread cannot write");
		exit(1);
	}

	if(write(t2c[1], &n, sizeof(int))<0){
		perror("Thread cannot write");
		exit(1);
	}

	if(write(t2c[1], &m, sizeof(int))<0){
		perror("Thread cannot write");
		exit(1);
	}

	pthread_mutex_unlock(&mtx);

	free(a);
	return NULL;
}

int main(int argc, char** argv){
	if(argc == 1){
		perror("Please provide an argument");
		exit(1);
	}

	if(pipe(t2c)!=0){
		perror("Error on pipe");
		exit(1);
	}
	int N = atoi(argv[1]);

	pthread_t t[N];
	int i;
	for(i=0; i<N; i++){
		int *v = (int*)malloc(sizeof(int));
		*v =i;
		if(pthread_create(&t[i], NULL, thread, v)!=0){
			perror("cannot create thread.");
			exit(1);
		}
	}

	for(i=0; i<N; i++){
		if(pthread_join(t[i], NULL)!=0){
			perror("cannot join thread.");
			exit(1);
		}
	}

	int f = fork();
	if(f == 0){
		close(t2c[1]);

		for(i=0; i<N; i++){
			int id, n, m;
			if(read(t2c[0], &id, sizeof(int))<0){
				perror("Child cannot read");
				exit(1);
			}
			if(read(t2c[0], &n, sizeof(int))<0){
                                perror("Child cannot read");
                                exit(1);
                        }
			if(read(t2c[0], &m, sizeof(int))<0){
                                perror("Child cannot read");
                                exit(1);
                        }

			float average =(float)(n+m)/2;
			printf("Child received %d and %d from %d and the average is %f.\n", n, m, id, average);

		}

		close(t2c[0]);
		exit(0);
	}	
	
	close(t2c[1]); close(t2c[0]);
	wait(0);
	return 0;
}
