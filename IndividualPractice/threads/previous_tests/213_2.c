#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int g, current_i = 0;
pthread_mutex_t mtxg = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtxi = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* a){
	int id = *(int*)a;

	while(1){
		pthread_mutex_lock(&mtxi);
		if(id != current_i){
			pthread_mutex_unlock(&mtxi);
		}
		else{
			if(current_i == 4){
                                current_i = 0;
                        }
                        else{
                                current_i++;
                        }

			if(g>0){
				int n = rand()%10;
				g -= n;
				printf("Thread %d decrements %d with %d and remains %d.\n", id, g+n, n, g);
				pthread_mutex_unlock(&mtxi);
			}
			else{
				pthread_mutex_unlock(&mtxi);
				break;
			}
		
		}
	}
	printf("");
	free(a);
	return NULL;
}


int main(){
	do{
		printf("Enter a natural number:\n");
		scanf("%d", &g);
	}while(g<0);

	pthread_t t[5];
	int i;
	for(i=0; i<5; i++){
		int* v = (int*)malloc(sizeof(int));
		*v = i;
		if(pthread_create(&t[i], NULL, thread, v)!=0){
			perror("Cannot create thread");
			exit(1);
		}
	}

	for(i=0; i<5; i++){
		if(pthread_join(t[i], NULL)!=0){
			perror("Cannot join thread");
			exit(2);
		}
	}

	pthread_mutex_destroy(&mtxg);
	pthread_mutex_destroy(&mtxi);
	return 0;	
}

