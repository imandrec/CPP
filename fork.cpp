#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]){
   int pid = fork();

   if(pid == -1){
     fprintf(stderr, "Fork failed\n");
     exit(-1);
   }

   if(pid == 0){
      printf("This is the child procee\n");

      //execute one command
      execl("helloWorld", argv[0], NULL);

      printf("This is after exec()\n");
      
      exit(0);
   }

   if(pid > 0){
     printf("This is parent process\n");
     exit(0);
   }
}
