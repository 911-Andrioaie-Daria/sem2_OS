#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
	int p2c[2], c2p[2];

	pipe(p2c); pipe(c2p);

	int f = fork();
	if(f == -1){
		perror("Error on fork");
		exit(1);
	}
	else if(f == 0){
		int length;
		char* s = (char*)malloc(100*sizeof(char));
		close(p2c[1]); close(c2p[0]);
		while(1){
			if(read(p2c[0], &length, sizeof(int))<0){
				perror("Child cannot read");
				free(s);
				close(p2c[0]); close(c2p[1]);
				exit(2);
			}
			if(read(p2c[0], s, length*sizeof(char))<0){
				perror("Parent cannot write");
				free(s);
				close(p2c[0]); close(c2p[1]);

				exit(2);
			}
			printf("Child received %d %s\n", length, s);
			s[length-5] = 0;
			length = strlen(s)+1;


			if(write(c2p[1], &length, sizeof(int))<0){
				perror("Parent cannot read");
				free(s);
				close(p2c[0]); close(c2p[1]);
				exit(2);
			}

			if(write(c2p[1], s, length*sizeof(char))<0){
				perror("Parent cannot read");
				free(s);
				close(p2c[0]); close(c2p[1]);

				exit(2);
			}

			if(length <= 8)
				break;			

		}
		free(s);
		close(p2c[0]); close(c2p[1]);
		exit(0);

	}

	close(p2c[0]); close(c2p[1]);

	char*s = (char*)malloc(100*sizeof(char));
	printf("Enter string:\n");
	scanf("%s", s);

	int length = strlen(s)+1;

	while(length - 1 > 7){
		if(write(p2c[1], &length, sizeof(int))<0){
			perror("Parent cannot write");
			free(s);
			close(p2c[1]); close(c2p[0]);
			wait(0);
			exit(2);
		}
		if(write(p2c[1], s, length*sizeof(char))<0){
			perror("Parent cannot write");
			free(s);
			close(p2c[1]); close(c2p[0]);
			wait(0);
			exit(2);
		}
		if(read(c2p[0], &length, sizeof(int))<0){
			perror("Parent cannot read");
			free(s);
			close(p2c[1]); close(c2p[0]);
			wait(0);
			exit(2);
		}	

		if(read(c2p[0], s, length*sizeof(char))<0){
			perror("Parent cannot read");
			free(s);
			close(p2c[1]); close(c2p[0]);
			wait(0);
			exit(2);
		}
		printf("Parent received %d %s\n", length, s);

		char one[] = "1";
		strcat(one, s);
		strcpy(s, one);
		length = strlen(s)+1;

	}

	free(s);
	close(p2c[1]); close(c2p[0]);
	wait(0);

	return 0;
}
