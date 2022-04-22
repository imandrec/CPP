#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(){

   pid_t pid;

   pid_t temp;

   pid = getpid(); //
   printf("Parent's process id is %d\n", pid);

   pid_t terminal_gpid;

   terminal_gpid = tcgetpgrp(0);

   printf("Terminal group pid: %d\n", terminal_gpid);

   //set parent process's group id to its own pid.
   // if(setpgid(0, 0) < 0){
   //   perror("setpgid() failed in parent");
   //   exit(-1);
  // }

   printf("parent group id is %d\n", getpgrp());

   if((pid = fork()) < 0){
     perror("Failed Fork");
     exit(-1);
   }else if(pid == 0){//ch
     //child
    // sleep(10);
     pid_t id = getpid(); 

     printf("Child Process ID: %d, group id: %d\n", id, getpgrp());
 
     if(setpgid(0, 0) < 0){
       perror("Failed setpgid()");
       exit(-1);
     }else{
       printf("Child Process ID after setpgid: %d, group id: %d\n", id, getpgrp());
     }

     printf("Enter a number: ");
     int number;
     scanf("%d", &number);
     printf("Number is %d\n", number);

     exit(0);
   }

   int status;
   wait(&status);

   printf("Parent group id: %d\n", getpgrp());
   
   exit(0);
}
