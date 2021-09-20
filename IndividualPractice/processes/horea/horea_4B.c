
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/// B
int main(int argc, char ** argv){

        int fd_a2b = open("a2b", O_RDONLY);
        int fd_b2a = open("b2a", O_WRONLY);
	

	while(1){
		int n = 0, i;
		if(read(fd_a2b, &n, sizeof(int))<=0){
                        perror("B cannot read length.");
                        break;
                }
		char* arg = (char*)malloc((n+1)*sizeof(char));

                if(read(fd_a2b, arg, n*sizeof(char))<=0){
                        perror("B cannot read argument");
                        break;
                }
		arg[n] = 0;
		printf("B received %d %s from A.\n", n, arg);
		/// modify
		for(i=0; i<n; i++){
			if(arg[i] >= 'a' && arg[i] <= 'z')
				arg[i] = arg[i] + 'A' - 'a';
		}
		//arg[n] = 0;
                if(write(fd_b2a, arg, n)<=0){
                        perror("B cannot send arg to A");
                        break;
                }
		free(arg);

	}

        close(fd_a2b); close(fd_b2a);

        return 0;
}

