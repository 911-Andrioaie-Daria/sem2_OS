 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>


 //Program B
 int main(int argc, char** argv) {
     int a2b;
     a2b=open("a2b", O_RDONLY);
     if(a2b<0){
         perror("FIFO not opened");
         exit(1);
     }
//     int i;
     while(1)
     {
         int length=0;
         if( read(a2b, &length, sizeof(int)) < 0) {
             perror("Error on send");
             exit(2);
         }
         printf("Length %d\n", length);
         if(length>0) {
             char* buffer = (char*)malloc(sizeof(char)*(length+1));
              if( read(a2b, buffer, length*sizeof(char))<0) {
                 perror("Error on receive arg");
                 exit(3);
              }
             buffer[length]=0;
             printf("Received %s\n", buffer);
             free(buffer);
         }
         else
             break;
     }
     close(a2b);
     return 0;
 }
