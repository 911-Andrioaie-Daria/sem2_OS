// 5. Write two independent programs A and B that communicate using fifos. Program A reads words from keyboard and send them to process B, receiving back the word in uppercase letters and a number representing the number of letters of the word. Program B received from A a word, computes the corresponsing word with uppercase letters and number of letters and sends these to to program A. This continues in a loop, untill program A sends word "000" and receives back the same word and number 0 and terminates. So doesa program B, when received "000", sends to A "000" and number 0 and terminates.

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int a2b = open("a2b", O_WRONLY);
	int b2a = open("b2a", O_RDONLY);

	int n;
	char* array = (char*)malloc(100*sizeof(char));

	do{
		printf("Enter word:\n");
		scanf("%s", array);
		n = strlen(array);
	
		if(write(a2b, &n, sizeof(int))<0){
                        perror("Error on writing to B");
                        exit(1);
                }
	

		if(write(a2b, array, n*sizeof(char))<0){
			perror("Error on writing to B");
			exit(1);
		}

		if(read(b2a, array, n*sizeof(char))<0){
                        perror("Error on reading from B");
                        exit(1);
                }
		printf("A received %s.\n", array);

	}while(strcmp(array, "000")!=0);
	free(array);
	close(a2b);
	close(b2a);
	return 0;
}
