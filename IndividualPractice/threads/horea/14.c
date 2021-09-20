// 14. Create a C program that converts all lowecase letters from the command line arguments to uppercase letters and prints the result. Use a thread for each given argument.
 
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

void* convert(void* a){
	char* str = (char*)a;
	int i;
	for(i=0; i<strlen(str); i++)
		if(str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 'a' - 'A';

	return NULL;
}

int main(int argc, char** argv){
	if(argc == 1){
		perror("Please provide arguments");
		exit(1);
	}	
	pthread_t t[argc-1];
	int i;
	for(i = 0; i<argc-1; i++){
		if(pthread_create(&t[i], NULL, convert, argv[i+1]) != 0){
			perror("Cannot create thread");
			exit(2);
		}
	}

	for(i = 0; i<argc-1; i++){
                if(pthread_join(t[i], NULL) != 0){
                        perror("Cannot wait thread");
                        exit(3);
                }
        }
	
	for(i = 0; i<argc-1; i++){
		printf("%s ", argv[i+1]);
        }
	printf("\n");

	return 0;


}
