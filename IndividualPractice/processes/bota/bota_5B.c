#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
        int n, m, sum;

        int a2b = open("a2b", O_RDONLY);
	int b2a = open("b2a", O_WRONLY);

        if(a2b < 0){
                perror("Cannot open fifo");
                exit(1);
        }

	if(b2a < 0){
                perror("Cannot open fifo");
                exit(1);
        }        

	if(read(a2b, &n, sizeof(int))<0){
                perror("Cannot read from fifo");
                exit(2);
        }

        if(read(a2b, &m, sizeof(int))<0){
                perror("Cannot read from fifo");
                exit(2);
        }
	
	sum = n+m;
        if(write(b2a, &sum, sizeof(int))<0){
                perror("Cannot write to fifo");
                exit(3);
        }

	 close(a2b);


        return 0;
}
                             
