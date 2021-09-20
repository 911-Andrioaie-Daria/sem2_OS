// 4. Write 2 C programs, A and B. A receives however many command line arguments and sends them to process B. Process B converts all lowercase letters from the received arguments to uppercase arguments and sends the results back to A. A reads the results, concatenates them and prints.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char** argv){
	if(argc == 1){
		perror("Please provide some arguments");
		exit(1);
	}

	int a2b = open("a2b", O_WRONLY);
	int b2a = open("b2a", O_RDONLY);
	
	int i,total_l = 0;
	for(i=1; i<argc; i++){
		total_l += strlen(argv[i]);
	}

	char *result = (char*)malloc(total_l*sizeof(char));
	
	int m = argc-1;
	if(write(a2b, &m, sizeof(int))<=0){
                perror("Error on writing to B");
                exit(1);
        }

	
	for(i=1; i<argc; i++){
		int n = strlen(argv[i]);
		if(write(a2b, &n, sizeof(int))<=0){
			perror("Error on writing to B");
        	        exit(1);
		}
		if(write(a2b, argv[i], n*sizeof(char))<=0){
                        perror("Error on writing to B");
                        exit(1);
                }
		char* s =(char*)malloc(n*sizeof(char));
	
		if(read(b2a, s, n*sizeof(char))<=0){
                        perror("Error on writing to B");
                        exit(1);
                }
		strcat(result, s);
		free(s);
	}

	printf("The result is %s.\n", result);
	free(result);

	return 0;
}
