// 8a. Write a C program that reads a matrix of integers from a file. It then creates as many threads as there are rows in the matrix, each thread calculates the sum of the numbers on a row. The main process waits for the threads to finish, then prints the sums. 

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int **a, *s, m;

void* thread(void* arg){
	int id = *(int*)arg;
	int j;
	s[id] = 0;

	for(j = 0; j<m; j++)
		s[id] += a[id][j];
	
	free(arg);
	return NULL;
}

int main(){
	FILE* f = fopen("matrix.txt", "r");
	int n, i, j;
	fscanf(f, "%d", &n);
	fscanf(f, "%d", &m);

	a = (int**)malloc(n*sizeof(int*));
	s = (int*)malloc(n*sizeof(int));

	for(i = 0; i<n; i++)
		a[i]=(int*)malloc(m*sizeof(int));
	
	for(i = 0; i<n; i++){
		for(j = 0; j<m; j++){
			fscanf(f, "%d", &a[i][j]);
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	fclose(f);
	pthread_t t[n];
	for(i = 0; i<n; i++){
		int *id = (int*)malloc(sizeof(int));
		*id = i;
		pthread_create(&t[i], NULL, thread, id);
	}

	for(i = 0; i<n; i++){
		pthread_join(t[i], NULL);
	}

	for(i = 0; i<n; i++){
		printf("The sum on row %d is %d.\n", i, s[i]);
	}	

	free(s);
	for(i = 0; i<n; i++){
		free(a[i]);
	}	
	free(a);

	return 0;
}
