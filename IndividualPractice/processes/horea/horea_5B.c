#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
        int a2b;
	char* buffer = (char*)malloc(200*sizeof(char));
	int length, i, k;

        a2b = open("a2b5", O_RDONLY);
        if(a2b <0 ){
                fprintf(stderr, "Cannot open fifo");
                exit(1);
        }
	while(1){
		if(read(a2b, &length, sizeof(int))<=0){
			 perror("B cannot read length");
                         exit(4);
		}	
		if(length > 0){
			i=0;
			while(i < length){
				k = read(a2b, buffer, 200);			
				if(k<0){
					perror("B cannot read output");
                       			exit(4);
				}
				else{
					i+=k;
					printf("%s\n", buffer);
					memset(buffer, 0, 200*sizeof(char));
				}
			}
		}
	}	

	close(a2b);
	free(buffer);
	return 0;
}

