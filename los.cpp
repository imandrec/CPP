#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_SIZE 126

//Print the type of file for command-line argument
int main(int argc, char *argv[]){
   char buff[100];

   //get the current working directory of this process
   if(getcwd(buff, MAX_SIZE) < 0){
       perror("Failed in getting current working directory");
   }
   else{
      printf("%s\n", buff);
   }
   
   //change the current working directory to /home/gtian
   if(chdir("/home/cis356") < 0){
       perror("Failed in changing current working directory");
   }
   else{
        //get the current working directory of this process
       if(getcwd(buff, MAX_SIZE) < 0){
           perror("Failed in getting current working directory");
       }
       else{
          printf("%s\n", buff);
       }
   }

   exit(0);

}
