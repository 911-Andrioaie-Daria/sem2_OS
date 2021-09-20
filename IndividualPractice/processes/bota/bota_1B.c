#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
        int n;
        int a2b = open("a2b", O_RDONLY);
        if(a2b < 0){
                perror("Cannot open fifo");
                exit(1);
        }

        if(read(a2b, &n, sizeof(int))<=0){
                perror("Cannot read");
        	close(a2b);
	        exit(2);
        }
	
	if(n%2 == 0)
		printf("The number %d is even.\n", n);
	else
		printf("The number %d is odd.\n", n);

	close(a2b);
        return 0;
}

