#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv){
	int i, a2b, b2a;
	int n = argc - 1;

	a2b = open("a2b", O_WRONLY);
	if(a2b < 0){
		perror("Cannot open fifo");
		exit(1);
	}

	b2a = open("b2a", O_RDONLY);
        if(b2a < 0){
                perror("Cannot open fifo");
                exit(1);
        }

	int total =0;
	for(i= 1; i<=n; i++){
		total+= strlen(argv[i]);
		total+=1;
	}

	char* res = (char*)malloc(total*sizeof(char));


	if(write(a2b, &n, sizeof(int))<0){
                        perror("A cannot write");
                        exit(2);
                }

	for(i = 1; i<=n; i++){
		int length = strlen(argv[i]) + 1;

		if(write(a2b, &length, sizeof(int))<0){
			perror("A cannot write");
			exit(2);
		}
		if(write(a2b, argv[i], length*sizeof(char))<0){
                        perror("A cannot write");
                        exit(2);
                }

		char* s = (char*)malloc(length*sizeof(char));

		if(read(b2a, s, length*sizeof(char))<0){
			perror("A cannot read");
			exit(3);

		}

		strcat(res, s);
		strcat(res, " ");

		free(s);
	}
	close(a2b);
	close(b2a);

	printf("The resulted string is %s\n", res);

	free(res);

	return 0;

}
