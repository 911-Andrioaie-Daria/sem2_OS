//3. Să se scrie un program C care creează un proces copil cu care comunică prin pipe. Procesul părinte citeşte de la tastatură un caracter c şi un şir s şi le trimite prin pipe procesului copil, iar procesul copil verifică şi afişează numărul de apariţii ale caracterului c în şirul s.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int p2c[2];
	pipe(p2c);

	int f = fork();
	if(f == -1){
		perror("Error on fork");
		exit(1);
	}
	else if(f == 0){
		close(p2c[1]);
		char c;
		if(read(p2c[0], &c, sizeof(char))<=0){
        	        perror("Child cannot read");
              		close(p2c[0]);
               		exit(3);
	        }
      		int n = 0;
       		 if(read(p2c[0], &n, sizeof(int))<=0){
               		 perror("Child cannot read");
               		 close(p2c[0]);
               		 exit(3);
        	}
		char* s = (char*)malloc(100*sizeof(char));
    	   	 if(read(p2c[0], s, n)<=0){
               		 perror("Child cannot read");
               		 close(p2c[0]);
              		 exit(3);
        	}

		int count=0, i;
		for(i=0; i<n-1;i++){
			if(s[i] == c)
				count++;
		}		
		printf("The character %c appears %d times in %s.\n", c, count, s);

		close(p2c[0]);
		exit(0);
	}

	close(p2c[0]);
	char c;
	char* s = (char*)malloc(100*sizeof(char));
	
	printf("Enter character: \n");
	scanf("%c", &c);

	printf("Enter string: \n");
        scanf("%s",s);

	if(write(p2c[1], &c, sizeof(char))<=0){
		perror("Parent cannot write");
        	close(p2c[1]); 
	        exit(2);
	}
	int n = strlen(s) + 1;
	if(write(p2c[1], &n, sizeof(int))<=0){
                perror("Parent cannot write");
        	close(p2c[1]);
	        exit(2);
        }

	if(write(p2c[1], s, n)<=0){
                perror("Parent cannot write");
        	close(p2c[1]); 
	        exit(2);
        }

	close(p2c[1]);
	wait(0);
	return 0;
}

