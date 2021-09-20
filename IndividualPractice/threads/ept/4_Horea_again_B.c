#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(){

        int a2b = open("a2b", O_RDONLY);
        int b2a = open("b2a", O_WRONLY);

	int m;
        if(read(a2b, &m, sizeof(int))<=0){
                perror("Error on reading from A");
                exit(1);
        }
	int i;

        for(i=0; i<m; i++){
                int n;
                if(read(a2b, &n, sizeof(int))<=0){
                        perror("Error on reading from A");
                        exit(1);
                }
		char* s =(char*)malloc(n*sizeof(char));
                if(read(a2b, s, n*sizeof(char))<=0){
                        perror("Error on reading from A");
                        exit(1);
                }

		int j;
		for(j=0; j<strlen(s); j++){
			if(s[j]>='a' && s[j]<='z')
				s[j] += 'A'-'a';			
		}

                if(write(b2a, s, n*sizeof(char))<=0){
                        perror("Error on writing to A");
                        exit(1);
                }
                free(s);
        }
	
        return 0;
}

