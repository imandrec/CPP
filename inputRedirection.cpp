#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char * argv[]){

    close(0);  //close standard input file descriptor

    printf("%s", argv[1]);

    int fd;
    if( (fd = open(argv[1], O_RDONLY)) < 0){
        printf("Failed in openning file %s\n", argv[2]);
        exit(-1);
    }

   char readBuffer[100];

   int i = 0;
   if( (i = read(STDIN_FILENO, readBuffer, 100)) < 0){
       printf("Read failed");
   }else if(i > 0){
       printf("%s", readBuffer);
   }
   else{
       printf("The End");
   }

  close(fd);

  return 0;
}
