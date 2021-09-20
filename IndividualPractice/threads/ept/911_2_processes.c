#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int p2c[2], c2p[2];
	if(pipe(p2c)<0){
		perror("Error on pipe");
		exit(1);
	}
	if(pipe(c2p)<0){
		perror("Error on pipe");
		exit(1);
	}

	if(fork()==0){  /// child
		close(p2c[1]); close(c2p[0]);
		int N;
		char* array;

		if(read(p2c[0], &N, sizeof(int))<0){
			perror("Error on reading from parent");
			exit(1);
		}
		
		array = (char*)malloc(N*sizeof(int));
		
		if(read(p2c[0], array, N*sizeof(int))<0){
			perror("Error on reading from parent");
			exit(1);
		}

		int i;
		for(i=0; i<N; i++){
			int c = rand()%25;
			array[i] += c;
		}

		if(write(c2p[1], array, N*sizeof(int))<0){
			perror("Error on write to parent");
			exit(1);
		}
    
                free(array);
		close(p2c[0]); close(c2p[1]);
		exit(0);
	}

	/// parent
	close(p2c[0]); close(c2p[1]);
	int N = rand()%21 + 10;
	char* array = (char*)malloc(N*sizeof(char));
	int i;
	for(i=0; i<N; i++){
		array[i] = 'a';
	}

	if(write(p2c[1], &N, sizeof(int))<0){
		perror("Error on write to child");
		exit(1);
	}
	if(write(p2c[1], array, N*sizeof(int))<0){
		perror("Error on write to child");
		exit(1);
	}
	close(p2c[1]);
	wait(0);

	if(read(c2p[0], array, N*sizeof(int))<0){
		perror("Error on read from child");
		exit(1);
	}

	printf("N is %d and the array is %s.\n", N, array);


	free(array);
	close(c2p[0]);
	return 0;
}
