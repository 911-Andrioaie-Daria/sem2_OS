#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>


#define N 5
int v=0;
int c=0;
pthread_mutex_t mtxv = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtxc = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* a){
	char p = *(char*)a;
	char* vowels = "aeiouAEIOU";
	if(strchr(vowels, p)){
		pthread_mutex_lock(&mtxv);
		v++;
		pthread_mutex_unlock(&mtxv);
	}
	else if(isalpha(p)){
		printf("%c is a consonant.\n", c);
		pthread_mutex_lock(&mtxc);
                c++;
                pthread_mutex_unlock(&mtxc);
	}		
	
	return NULL;
}

int main(){
	int i;
	char empty;
	char* s = (char*)malloc(N*sizeof(char));
	for(i=0; i<N; i++){
		printf("Enter character:\n");
		scanf("%c", &s[i]);
		scanf("%c", &empty);
	}

	pthread_t t[N];

	for(i=0; i<N; i++){
		if(pthread_create(&t[i], NULL, thread, &s[i])!=0){
			perror("Cannot create thread");
			exit(1);
		}
	}
	for(i=0; i<N; i++){
                if(pthread_join(t[i], NULL)!=0){
                        perror("Cannot join thread");
                        exit(2);
                }
        }

	free(s);

	printf("There are %d vowels and %d consonants.\n", v, c);
	pthread_mutex_destroy(&mtxv);
	pthread_mutex_destroy(&mtxc);
	return 0;
}
