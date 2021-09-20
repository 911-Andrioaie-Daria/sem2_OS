// Write a C program that creates a child process. The parent reads strings (that do not contain spaces) from the keyboard and sends them to the child process via pipe. The child process prints a message for each string that contains only digits. The parent and the child terminate once the parent reads "stop" (lowercase letters only). The C program will perform all the necessary checks.

#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	int p2c[2];

	pipe(p2c);
	int f = fork();

	if(f == -1){
		perror("Error on fork");
		exit(1);
	}
	else if (f == 0){
		close(p2c[1]);

		while(1){
			int k, length, i, d=1;
	//		char d[] = "0123456789"
			char* s = (char*)malloc(100*sizeof(char));
			
			k = read(p2c[0], &length, sizeof(int));
			if(k < 0){
				perror("Child cannot read");
				free(s);
				exit(3);
			}
			else if(k == 0){
				free(s);
				break;
			}
			else{
				if(read(p2c[0], s, length)<0){
					perror("Child cannot read");
                                	free(s);
                               		 exit(3);
				}
				printf("Child read %s.\n", s);
				for(i=0; i<length-1; i++)
					if(!isdigit(s[i]))
						d = 0;
				if(d == 1)
					printf("%s contains only digits.\n", s);					
				free(s);
			}
		}


		close(p2c[0]);
		exit(0);
	}

	close(p2c[0]);
	char* s = (char*)malloc(100*sizeof(char));
	while(1){
		scanf("%s", s);
		if(strcmp(s, "stop")==0)
			break;
		int n = strlen(s)+1;
		if(write(p2c[1], &n, sizeof(int))<0){
			perror("Parent cannot write");
			exit(2);
		}		
		if(write(p2c[1], s, n)<0){
                        perror("Parent cannot write");
                        exit(2);
                }
		printf("Parent sent %s.\n", s);
	}
	free(s);
	close(p2c[1]);
	wait(0);
	return 0;
i}
