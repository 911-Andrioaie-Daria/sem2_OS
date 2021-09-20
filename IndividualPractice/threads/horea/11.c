// 11. Write a program that receives strings of characters as command line arguments. For each string the program creates a thread which calculates the number of digits, the number of leters and the number of special characters (anything other than a letter or digit). The main program waits for the threads to terminate and prints the total results (total number of digits, letters and special characters across all the received command line arguments) and terminates. Use efficient synchronization. Do not use global variables.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	int *letters;
	int *digits;
	int *specials;
	char* string;
	pthread_mutex_t *mtx;
} data;


void* thread(void* a){
	data* args = (data*)a;	
	int l=0, d = 0, s = 0, i;
	char *str = args->string;
	for(i=0; i<strlen(str); i++){
		if(isalpha(str[i]))
			l++;
		else if (isdigit(str[i]))
			d++;
		else
			s++;

	}
	pthread_mutex_lock(args->mtx);
	*(args->letters) += l;
	*(args->digits) += d;
	*(args->specials) += s;
	pthread_mutex_unlock(args->mtx);
	free(str);
	return NULL;
}

int main(int argc, char** argv){

	if(argc == 1){
		perror("Please provide at least one argument");
		exit(1);
	}
	pthread_t t[argc-1];	

	data *args = (data*)malloc((argc-1)*sizeof(data));
	int* letters = (int*)malloc(sizeof(int));
	int* digits = (int*)malloc(sizeof(int));
	int* specials = (int*)malloc(sizeof(int));
	pthread_mutex_t *mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));


	int i;

	for(i = 1; i< argc; i++){
		args[i-1].letters = letters;
		args[i-1].digits = digits;
		args[i-1].specials = specials;
		args[i-1].mtx = mutex;
		pthread_mutex_init(args[i-1].mtx, NULL);


		int l = strlen(argv[i]);
		args[i-1].string = (char*)malloc(l*sizeof(char));
		strcpy(args[i-1].string, argv[i]);
		pthread_create(&t[i-1], NULL, thread, &args[i-1]);
	}

	for(i = 0; i<argc-1; i++){
		pthread_join(t[i], NULL);
	}

	printf("There are %d letters, %d digits and %d special characters.\n", *letters, *digits, *specials);

	pthread_mutex_destroy(mutex);
	free(mutex);
	free(letters);
	free(digits);
	free(specials);
	free(args);
	return 0;
}
