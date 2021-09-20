#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
        int n,i, count =0;

        int a2b = open("a2b", O_RDONLY);
        if(a2b < 0){
                perror("Cannot open fifo");
                exit(1);
        }
        if(read(a2b, &n, sizeof(int))<0){
                perror("B cannot read");
                close(a2b);
                exit(2);
        }
	
	int* a = (int*)malloc(n*sizeof(int));

        if(read(a2b, a, n*sizeof(int))<0){
                perror("B cannot read");
                close(a2b);
                free(a);
                exit(2);
        }

        close(a2b);
    
	for(i=0; i<n; i++){
		if(a[i]%3 != 0){
			count++;
			printf("%d\n", a[i]);
			}
	}

	printf("Count %d\n", count);

	free(a);
        int b2a = open("b2a", O_WRONLY);
        if(a2b < 0){
                perror("Cannot open fifo");
                exit(1);
        }
        if(write(b2a, &count, sizeof(int))<0){
                perror("B cannot write");
                close(b2a);
                exit(2);
        }
	close(b2a);

        return 0;

}

