#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){

        int a2b = open("a2b", O_RDONLY);
        if(a2b < 0){
                perror("Cannot open fifo");
                exit(1);
        }
        char c;
        if(read(a2b, &c, sizeof(char))<=0){
                perror("B cannot read.");
                close(a2b);
                exit(2);
        }
        int n;

        if(read(a2b, &n, sizeof(int))<=0){
                perror("B cannot read.");
                close(a2b);
                exit(2);
        }

	char* s = (char*) malloc(n*sizeof(char));

        if(read(a2b, s, n)<=0){
                perror("B cannot read.");
                close(a2b);
                exit(2);
        }
	
	int i, count = 0;
	for(i=0; i < n-1; i++)
		if(s[i] == c)
			count++;

	printf("The character %c appears %d times in %s.\n", c, count, s);
	
	close(a2b);

        return 0;
}

