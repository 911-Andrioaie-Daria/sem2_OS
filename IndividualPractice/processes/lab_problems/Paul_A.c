#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

//Program A
int main(int argc, char** argv) {
    int a2b;
    a2b=open("a2b", O_WRONLY);
    if(a2b<0){
        perror("FIFO not opened");
        exit(1);
    }
    int i;
    for(i=1;i<argc;i++) {
        int length = strlen(argv[i]);
        if( write(a2b, &length, sizeof(int)) < 0) {
            perror("Error on send");
            exit(2);
        }
        if( write(a2b, argv[i], length*sizeof(char))<0) {
            perror("Error on sending arg");
            exit(3);
        }
    }
     close(a2b);
     return 0;
}
