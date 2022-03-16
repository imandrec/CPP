#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){

   pid_t pid;

   if((pid = fork()) < 0){
     perror("Failed Fork");
     exit(-1);
   }else if(pid == 0){
     //child

     pid_t id = getpi d(); //get the child process id
     //the child will have the same id as the group id of the parent because
     //is duplocate (we called fork)
     printf("Child Process ID: %d, group id: %d\n", id, getpgrp());
 

     //i can also say: if (setpgid(id, id) < 0) {
     if(setpgid(0, 0) < 0){
       perror("Failed setpgid()");
       exit(-1);
     }else{
       printf("Child Process ID after setpgid: %d, group id: %d\n", id, getpgrp());
     }

     exit(0);
   }

   int status;
   int child_pid = wait(&status);

   printf("Parent PID is %d, group id is: %d\n", getpid(), getpgrp());

   exit(0);

}
