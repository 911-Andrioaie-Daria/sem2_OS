// 5. Write two C programs that communicate via fifo. Program A is responsible for creating/deleting the fifo. Program A reads commands from the standard input, executes them and sends the output to program B. Program B keeps reading from the fifo and displays whatever it receives at the standard output. This continues until program A receives the "stop" command. (solution has 2 C source files, A and B, and a common C header that defines the fifo name so we don't hardcode it).

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(){
	int a2b;
	FILE* fp;
	char* buffer = (char*)malloc(200*sizeof(char));

	a2b = open("a2b5", O_WRONLY);
	if(a2b < 0){
		fprintf(stderr, "Cannot open fifo");
		exit(1);
	}

	char* command = (char*)malloc(200*sizeof(char));
	do{
		int k = read(0, command, 200);
		if(k<=0){
			perror("Cannot read command");
			exit(2);
		}
		command[k] = 0;	
		
		if(strcmp(command, "stop") == 0)
			break;

		fp = popen(command, "r");
		if(fp==NULL){
			perror("Error on executing popen");
			exit(2);
		}
		else{
			while(fread(buffer, 1, 199, fp)>0){
				int n = strlen(buffer);	
				if(write(a2b, &n, sizeof(int))<=0){
					perror("A cannot send length");
					exit(4);
				}
				
				if(write(a2b, buffer, n*sizeof(char))<=0){
					perror("A cannot send output");
                                        exit(4);
				}				
				memset(buffer, 0, 200*sizeof(char));
			}	
		}
		pclose(fp);
		memset(command, 0, 200*sizeof(char));		

	}while(1);
	
	free(command);
	free(buffer);
	close(a2b);
	return 0;

}

