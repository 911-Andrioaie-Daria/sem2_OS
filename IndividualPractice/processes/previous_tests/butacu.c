#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int isPrime(int n){
	int d;
	for(d = 2; d<=n/2; d++)
		if(n%d == 0)
			return 0;
	return 1;
}

int main(){
	int p2c[2],c2p[2];
	pipe(p2c); pipe(c2p);

	int f = fork();
	if(f == -1){
		perror("Error on fork");
		exit(1);
	}
	else if(f == 0){
		close(p2c[1]); close(c2p[0]);
		int n, i;
		
		if(read(p2c[0], &n, sizeof(int))<0){
			perror("Child cannot read");
			exit(2);
		}
		close(p2c[0]);
		for(i=2; i<n; i++){
			if(isPrime(i)){
				if(write(c2p[1], &i, sizeof(int))<0){
					perror("Child cannot write");
					exit(3);
				}
			}
		}

		close(c2p[1]);
		exit(0);
	}
	close(p2c[0]); close(c2p[1]);

	int n;
	printf("Enter a number:\n");
	scanf("%d", &n);
	if(write(p2c[1], &n, sizeof(int))<0){
		perror("Parent cannot write.");
		exit(2);
	}
	close(p2c[1]);
	while(1){
		int nr;
		int k = read(c2p[0], &nr, sizeof(int));
		if(k<0){
			perror("Parent cannot read");
			exit(3);
		}
		else if(k == 0){
			break;
		}
		printf("%d\n", nr);

	}
	wait(0);
	close(c2p[0]);
	return 0;	
}
