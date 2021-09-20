// 12. Write a C program that receives integers as command line argument. The program will keep a frequency vector for all digits. The program will create a thread for each argument that counts the number of occurences of each digit and adds the result to the frequency vector. Use efficient synchronization.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int f[10];
pthread_mutex_t mtx;

void* thread (void* a){
	int n = *(int*)a;
	printf("%d\n", n);

	pthread_mutex_lock(&mtx);	
	while(n){
		f[n%10]++;
		n /= 10;
	}
	pthread_mutex_unlock(&mtx);
	free(a);
	return NULL;
}

int main(int argc, char** argv){
	if(argc == 1){
		perror("Please rovide at least one argument.");
		exit(1);
	}
	int i;
	pthread_t t[argc-1];
	pthread_mutex_init(&mtx, NULL);

	for(i=0; i<argc-1; i++){
		int *n = (int*)malloc(sizeof(int));
		*n = atoi(argv[i+1]);
		pthread_create(&t[i], NULL, thread, n);
	}

	for(i = 0; i<argc-1; i++){
		pthread_join(t[i], NULL);
	}
	pthread_mutex_destroy(&mtx);

	for(i = 0; i<=9; i++)
		printf("Digit %d appears %d times.\n", i, f[i]);
	
	
	return 0;
}
