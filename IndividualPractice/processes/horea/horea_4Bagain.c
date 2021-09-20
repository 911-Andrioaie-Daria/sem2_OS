#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){
        int i, a2b, b2a;
        int n;

        a2b = open("a2b", O_RDONLY);
        if(a2b < 0){
                perror("Cannot open fifo");
                exit(1);
        }

        b2a = open("b2a", O_WRONLY);
        if(b2a < 0){
                perror("Cannot open fifo");
                exit(1);
        }

	if(read(a2b, &n, sizeof(int))<0){
                        perror("B cannot read");
                        exit(2);
                }


        for(i = 1; i<=n; i++){
                int length;

                if(read(a2b, &length, sizeof(int))<0){
                        perror("B cannot read");
                        exit(2);
                }
		char* s = (char*)malloc(length*sizeof(char));

                if(read(a2b, s, length*sizeof(char))<0){
                        perror("B cannot read");
                        exit(2);
                }
		int j;
		printf("B received %s\n", s);
		for(j=0; j<length-1; j++){	
			if(s[j] >= 'a' && s[j] <= 'z')
				s[j] = s[j] + 'A' - 'a';	
		}
                if(write(b2a, s, length*sizeof(char))<0){
                        perror("B cannot write");
                        exit(3);

                }
		printf("B sent %s\n", s);
                free(s);
        }
        close(a2b);
        close(b2a);

        return 0;

}

