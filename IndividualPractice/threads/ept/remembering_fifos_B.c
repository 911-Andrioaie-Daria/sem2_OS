#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int a2b = open("a2b", O_RDONLY);
	int b2a = open("b2a", O_WRONLY);

	int n;
	char* array = (char*)malloc(100*sizeof(char));

	do{

		if(read(a2b, &n, sizeof(int))<0){
			perror("Error on reading from A");
			exit(1);
		}


		if(read(a2b, array, n*sizeof(char))<0){
			perror("Error on reading from A");
			exit(1);
		}

		printf("B received %s.\n", array);		

		if(strcmp(array, "000")!=0){
			int i;
			for(i=0; i<n; i++){
				if(array[i] >= 'a' && array[i] <= 'z')
					array[i] += 'A' - 'a';
			}	
		}
		if(write(b2a, array, n*sizeof(char))<0){
			perror("Error on writing to A");
			exit(1);
		}

	}while(strcmp(array, "000")!=0);
	free(array);
	close(a2b);
	close(b2a);

	return 0;
}

