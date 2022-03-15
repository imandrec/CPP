#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_handler(int signo);

static int num = 0;

static double x = 0;

int main(){
   struct sigaction act;

   act.sa_handler = sig_handler; //assign a funtion to act.sa_handler

   sigemptyset(&act.sa_mask); //empty the currect mask 
  
   act.sa_flags = 0;

   if(sigaction(SIGUSR1, &act, NULL) == -1){
     perror("signal SIGUSR1 error");
     exit(-1);
   }

   if(sigaction(SIGALRM, &act, NULL) == -1){
     perror("signal SIGALRM error");
     exit(-1);
   }

  // alarm(10); //set alarm in 10 seconds

   for(; ;){
     x++;
     if(num){
       num = 0; 
       printf("x = %f\n", x);
       fflush(stdout);
     }
   }
   
  exit(0);
}


void sig_handler(int signo){
   printf("I am awake: %d.   ", signo);
 
   if(signo == SIGALRM) alarm(10); //set alarm to go off in 10 seconds
   num = 1;
}
