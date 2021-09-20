// 4. Write a program that creates a child process. The two communicate through a pipe. The parent reads a string with >25 characters and sends it to the child, which removes 1 vowel and sends it to the parent, which removes the first and the last character and sends it to the child back which removes again a vowel and sends it back .... and so on untill the string contains 3 or less characters.
//
// Print the intermediary results and consider the initial string does not contain spaces or tabs, but only alphanumeric characters. You can use strstr() function.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int p2c[2], c2p[2];

	pipe(p2c); pipe(c2p);
	 char* s = (char*)malloc(100);

	int f = fork();
	if(f == -1){
		perror("Error on fork");
		exit(1);
	}
	else if (f == 0){
		close(p2c[1]); close(c2p[0]);

		while(1){
			int length, k;

			k = read(p2c[0], &length, sizeof(int));
			if(k < 0){
				perror("Child cannot read");
				exit(2);
			}
			else if(k == 0){
				printf("Game over.\n");
				break;
			}
//			char* s = (char*)malloc(100);
			if(read(p2c[0], s, length)<0){
				perror("Child cannot read");
                                exit(2);
			}
			printf("Child received %d %s\n", length, s);			

			if(length <= 4){
				break;			
			}
			else{
				/// compute
				int i, j;
				char v[] = "aeiouAEIOU";
				int p = -1;

				for(i=0; i< length-1 && p == -1; i++)
					for(j=0; j<10; j++)
						if(s[i] == v[j])
							p = i;								strcpy(s+p, s+p+1);
				printf("Removed %d\n", p);
				length = strlen(s) + 1;
				
				if(write(c2p[1], &length, sizeof(int))<0){
					perror("Child cannot write");
					exit(3);
				}
				if(write(c2p[1], s, length)<0){
                                	perror("Child cannot write");
                               		 exit(3);
                        	}
				printf("Child sends %d %s\n", length, s);
			}

//			free(s);
		}
	
		close(p2c[0]); close(c2p[1]);
		exit(0);
	}

	close(p2c[0]); close(c2p[1]);
	
//	char* s = (char*)malloc(100);

	scanf("%s", s);

	int length = strlen(s)+1;

	if(write(p2c[1], &length, sizeof(int) )<0){
                perror("Parent cannot write.");
                exit(3);
        }


	if(write(p2c[1], s, length*sizeof(char))<0){
		perror("Parent cannot write.");
		exit(3);
	}

	printf("Parent sends %d %s\n", length, s);	
//	free(s);
	while(1){
		 int k;

                        k = read(c2p[0], &length, sizeof(int));
                        if(k < 0){
                                perror("Parent cannot read");
                                exit(2);
                        }
                        else if(k == 0){
                                printf("Game over.\n");
                                break;
                        }
//			char* s = (char*)malloc(100);
                        if(read(c2p[0], s, length)<0){
                                perror("Child cannot read");
                                exit(2);
                        }
			 printf("Parent received %d %s\n", length, s);
	
                        if(length <= 4){
                                break;
                        }
                        else{
                                strcpy(s, s+1);
				s[length - 3] = 0;	
			
                                length = strlen(s) + 1;

                                if(write(p2c[1], &length, sizeof(int))<0){
                                        perror("Parent cannot write");
                                        exit(3);
                                }
                                if(write(p2c[1], s, length)<0){
                                        perror("Parent cannot write");
                                         exit(3);
                                }
				 printf("Parent sends %d %s\n", length, s);
 
                       }
//			free(s);
	}
	
	close(p2c[1]); close(c2p[0]);
	wait(0);
	free(s);
	return 0;
}

