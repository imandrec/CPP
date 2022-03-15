//use sigpromask to block all signlas except USER1
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  sigset_t set, oset;

  //set the singal mask to block everything
  if(sigfillset(&set) == -1){
    perror("Sigfillset failed");
    exit(-1);
  }

  if(sigdelset(&set, SIGUSR1) == -1){
    perror("sigdelset USR1 failed");
    exit(-1);
  }

 //Beginning of signal free region
 if(sigprocmask(SIG_BLOCK, &set, &oset) == -1){
   perror("sigprocmask failed");
   exit(-1);
  } 

  //sleep for 1 minute.  Critical region - blocks signal interruptions
  for(int i = 0; i < 6; i++){
    sleep(10); //sleep for 10 seconds.
    //write(1, "Sleep\n", 7);
    printf("Sleep\n");
  }//critical region (signal free)

  //unblock the signals
  if( sigprocmask(SIG_SETMASK, &oset, NULL) == -1){
     perror("reset old mask failed");
     exit(-1);
  }

  while(1){
    sleep(10);
    //printf("try to do someting forever!");
    write(1, "Sleep forever", 14);
  }


  exit(0);
}
