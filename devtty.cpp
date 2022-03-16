#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){

   printf("Hello world\n");
   fflush(stdout); 

   //close standard output
   close(1);

   int file = open("temp", O_CREAT | O_RDWR, 0777);

   if(file < 0){
     perror("Error in open temp file");
     exit(-1);
   }

   dup(file);//redirect IO

   printf("After closing Standard IO\n");

   //call open /dev/tty to take the controlling terminal 
   int i = open("/dev/tty", O_RDWR);

   if(i < 0) {
     perror("Error in open /dev/ty");
     exit(-1);
   }

   printf("After open /dev/tty\n");

   write(i, "This", 5);

    exit(0);

}
