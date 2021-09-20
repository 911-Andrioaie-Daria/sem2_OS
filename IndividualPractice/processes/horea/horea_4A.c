// 4. Write 2 C programs, A and B. A receives however many command line arguments and sends them to process B. Process B converts all lowercase letters from the received arguments to uppercase arguments and sends the results back to A. A reads the results, concatenates them and prints.
//


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


/// A
int main(int argc, char ** argv){
	//char* a2b = "./a2b";
	//char* b2a = "./b2a";

	int fd_a2b, fd_b2a, i;
	char* arg;
	char* s;
	
//	if(mkfifo(a2b, 0600) < 0){
//		perror("Error on create fifo");
//		exit(1);
//	}
//	if(mkfifo(b2a, 0600) < 0){
//		perror("Error on create fifo");
//		exit(1);
//	}
	fd_a2b = open("a2b", O_WRONLY);
	fd_b2a = open("b2a", O_RDONLY);
	
	if (0 > fd_a2b) {
    	         perror("Error opening a2b");
     	  	 exit(1);
    	}
   	 if (0 > fd_b2a) {
       		 perror("Error opening b2a");
       		 exit(1);
    	}
	
	int length = 0;
	for(i=1; i<argc; i++){
		length += strlen(argv[i]);
		length++;
	}
	printf("Length: %d\n", length);
	s = (char*)malloc(length*sizeof(char));
	
	for(i=1; i<argc; i++){
		int n = strlen(argv[i]);
		if(write(fd_a2b, &n, sizeof(int))<0){
			perror("A cannot send length.");
			break;
		}
	
		if(write(fd_a2b, argv[i], n*sizeof(char))<=0){
			perror("A cannot send argument to B");
			break;
		}
		printf("A sent %d %s to B.\n", n, argv[i]);
		///free(buffer);
		arg = (char*)malloc(n+1);
		if(read(fd_b2a, arg, n)<=0){
			perror("A cannot read from B");
			break;
		}
	
		arg[n] = 0;
		printf("A received %s from B.\n", arg);
		strcat(s, arg);
		strcat(s, " ");
		free(arg);
	}
	s[length-1] = 0;
	printf("%s\n", s);
	free(s);
	close(fd_a2b); close(fd_b2a);
	//unlink(a2b); unlink(b2a);
	
	return 0;
}	
