// 3. Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte de la tastatură un caracter c şi un şir s şi le trimite prin pipe procesului copil, iar procesul copil verifică şi afişează numărul de apariţii ale caracterului c în şirul s.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(){

	int a2b = open("a2b", O_WRONLY);
	if(a2b < 0){
		perror("Cannot open fifo");
		exit(1);
	}
	char c;
	char* s = (char*)malloc(100*sizeof(char));

	printf("Enter a character: \n");
	scanf("%c", &c);

	printf("Enter a string: \n");
	scanf("%s", s);
	
	if(write(a2b, &c, sizeof(char))<=0){
		perror("A cannot write.");
		close(a2b);
		exit(2);
	}
	 int n = strlen(s)+1;

	if(write(a2b, &n, sizeof(int))<=0){
                perror("A cannot write.");
                close(a2b);
                exit(2);
        }
	
	if(write(a2b, s, n)<=0){
                perror("A cannot write.");
                close(a2b);
                exit(2);
        }
	
	close(a2b);

	return 0;
}
