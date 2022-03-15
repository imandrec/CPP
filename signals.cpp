#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    sigset_t set, oset;

    //set the signal mask to block nothing
    if(sigemptyset(&set) < 0){
        perror("Sigemptyset fail");
        exit(-1);
    }

    //add SIGINT
    if(sigaddset(&set, SIGINT) < 0){
      perror("Add SIGINT failed");
      exit(-1);
    }

    //check if SIGINT exists in the set
    if(sigismember(&set, SIGINT) == 1){
      printf("SIGINT is set");
    }else{
        printf("SIGINT is not set");
    }


   fflush(stdout); //flush the standard output immediately

    //set the signalpromask to block SIGINT so Ctrl + C cannot stop the process
    if(sigprocmask(SIG_BLOCK, &set, &oset) == -1){
      perror("Sigpromask() failed");
      exit(-1);
    }


    //let the program sleep for 30 seconds and then terminate
    sleep(30); 

    printf("Terminated");
    exit(-1);

}
