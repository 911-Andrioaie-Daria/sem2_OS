//4. A C program receives command line args pairs of numbers, and creates for each pair a thread that checks is the two numbers are relatively prime (gcd=1), incrementing a global variable. The program prints at the end how many relatively prime pairs have been found and the respective pairs.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int count=0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
	int n;
	int m;
}pair;

void* checkpair(void* a){
	pair *p = (pair*)a;
	int n = p->n;
	int m = p->m;
	
	printf("Received %d and %d.\n", n, m);
	int gcd=0, i;
	for(i=1; i<=m && i<=n; i++){
		if(m%i ==0 && n%i ==0)
			gcd = i;
	}
	
	if(gcd == 1){
		pthread_mutex_lock(&mtx);
		count++;
		pthread_mutex_unlock(&mtx);
	}

	free(a);
	return NULL;
}

int main(int argc, char** argv){

	if(argc %2 == 0){
		perror("You need to provide an even number of arguments.");
		exit(2);	
	}

	pthread_t t[(argc-1)/2];
	int i;
	for(i=1; i<argc; i+=2){
		pair *p = (pair*)malloc(sizeof(pair));
		p->n = atoi(argv[i]);
		p->m = atoi(argv[i+1]);
		printf("Sending %d and %d.\n", p->n, p->m);
		if(pthread_create(&t[i/2], NULL, checkpair, p)!=0){
			perror("Cannot create thread");
			exit(1);
		}
	}
	
	for(i=1; i<argc; i+=2){
                if(pthread_join(t[i/2], NULL)!=0){
                        perror("Cannot join thread");
                        exit(3);
                }
        }

	pthread_mutex_destroy(&mtx);
	printf("There are %d pairs that are relatively prime.\n", count);	

	return 0;
}
