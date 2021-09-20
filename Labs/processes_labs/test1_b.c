#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv){
    int a2b;
    a2b = open("myfifo", O_RDONLY);
    if(a2b<0){
	perror("FIFO not opened");
	exit(1);
	}   

    //char** arguments;
    int count=0;
    read(a2b, &count, sizeof(int));
    for(int i=1; i<=count;i++){
        int len = 0;
        if(read(a2b, &len, sizeof(int))<0){
		perror("Error on send");
		exit(2);
	}
	if(len>0){
	 char arg[len]=0;
        read(a2b, arg, len);

	}
    }
    close(a2b);
    return 0;
}

