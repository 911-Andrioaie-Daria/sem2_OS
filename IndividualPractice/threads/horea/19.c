// 19. Write a C program that receives any number of strings as command line arguments. The program creates two child processes, which inherit the parent's command line arguments (ie. no need to send the arguments via pipe/fifo to the children for this problem). Each child process creates a thread for each of the command line arguments. Each thread created by the first child will extract the vowels from its argument and will append them to a string shared among the threads. Each thread created by the second child process will extract the digits from its argument and will add them to a sum shared among the threads. Both child processes wait for their respective threads to finish and send the result to the parent via pipe. The parent displays the results.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

pthread_mutex_t mtx_d = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx_v = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
	char* vowels;
	int *index;
	char* argument;
}data_v;

typedef struct{
	int *sum;
	char* argument;	
}data_d;

void* thread_v(void *a){
	
	data_v data = *(data_v*)a;

	char v[] = "aeiouAEIOU";
	int i;
	for(i=0; i<strlen(data.argument); i++){
		if(strchr(v,data.argument[i])){
			pthread_mutex_lock(&mtx_v);
			data.vowels[*data.index] = data.argument[i];
			*data.index = *data.index +1;
			pthread_mutex_unlock(&mtx_v);
		}
	}

	free(a);
	return NULL;
}

void* thread_d(void *a){
	data_d data = *(data_d*)a;
	char v[] = "0123456789";
	int i;
	for(i=0; i<strlen(data.argument); i++){
		if(strchr(v, data.argument[i])){

			char digit[2];
			digit[0] = data.argument[i];
			int d = atoi(digit);
			pthread_mutex_lock(&mtx_d);
			*data.sum = *data.sum + d;
			pthread_mutex_unlock(&mtx_d);
		}	
	}

	free(a);
        return NULL;
}

int main(int argc, char** argv){
	int c1p[2], c2p[2];

	if(argc == 1){
		perror("Please provide some arguments");
		exit(1);
	}
	if(pipe(c1p)<0){
                perror("Error on pipe");
                exit(1);
        }

	if(pipe(c2p)<0){
		perror("Error on pipe");
		exit(1);
	}

	int f1 = fork();
	if(f1 == 0){ /// Child 1
		close(c2p[0]); close(c2p[1]);
		close(c1p[0]);
		pthread_t t[argc-1];
		int i;
				
		char* vowels_string = (char*)malloc(100*sizeof(char));
		int* v_index = (int*)malloc(sizeof(int));
		*v_index = 0;

		for(i=1; i<argc; i++){
			data_v *v = (data_v*)malloc(sizeof(data_v));
			v->vowels = vowels_string;
			v->index = v_index;
			v->argument = argv[i];
			if(pthread_create(&t[i-1], NULL, thread_v, v)!=0){
				perror("Cannot create thread");
				exit(1);
			}
		}		

		for(i=1; i<argc; i++){
                        if(pthread_join(t[i-1], NULL)!=0){
                                perror("Cannot join thread");
                                exit(1);
                        }
                }
        //	printf("Vowels: %s\n", vowels_string);
    		
		if(write(c1p[1], v_index, sizeof(int))<0){
			perror("Child 1 cannot write");
			exit(1);
		}

		if(write(c1p[1], vowels_string, (*v_index)*sizeof(char))<0){
                        perror("Child 1 cannot write");
                        exit(1);
                }


		free(vowels_string);
		free(v_index);
		close(c1p[1]);
		exit(0);
	}	
	
	int f2 = fork();
        if(f2 == 0){ /// Child 2
		close(c1p[0]); close(c1p[1]); close(c2p[0]);

		int* sum_of_digits = (int*)malloc(sizeof(int));
		*sum_of_digits = 0;
		
		pthread_t t[argc-1];

		int i;
		for(i=1; i<argc; i++){
			data_d* d = (data_d*)malloc(sizeof(data_d));
			d->argument = argv[i];
			d->sum = sum_of_digits;
			if(pthread_create(&t[i-1], NULL, thread_d, d)!=0){
				perror("Cannot create thread");
				exit(1);

			}			
		}
		for(i=1; i<argc; i++){
                        if(pthread_join(t[i-1], NULL)!=0){
                                perror("Cannot join thread");
                                exit(1);

                        }
                }

		if(write(c2p[1], sum_of_digits, sizeof(int))<0){
			perror("Child cannot write");
			exit(1);
		}

		free(sum_of_digits);

                exit(0);
        }

	/// Parent

	close(c1p[1]); close(c2p[1]);
	wait(0); wait(0);

	int length = 0;

	if(read(c1p[0], &length, sizeof(int))<0){
                        perror("Parent cannot read");
                        exit(1);
        }
	
	char *result = (char*)malloc(length*sizeof(char));

	if(read(c1p[0], result, length*sizeof(char))<0){
                        perror("Parent cannot read");
                        exit(1);
        }

	printf("Vowels received from child: %s\n", result);
	free(result);	
	close(c1p[0]);

	int sum;
	if(read(c2p[0], &sum, sizeof(int))<0){
		perror("Parent cannot read");
		exit(1);
	}
	printf("Sum received from child %d.\n", sum);
	close(c2p[0]);
	return 0;
}
