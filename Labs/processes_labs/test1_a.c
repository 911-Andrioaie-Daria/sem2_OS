#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char** argv){
    int a2b;
    a2b = open("myfifo", O_WRONLY);
    write(a2b, &argc, sizeof(int);
    for(int i=1; i<argc; i++){
        int n = strlen(argv[i])+1;
        write(a2b, &n, sizeof(int));
        write(a2b, argv+i, n);
    }

}

