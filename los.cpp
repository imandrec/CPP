#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//Print the type of file for command-line argument
int main(int argc, char *argv[]){
    struct stat statbuf;
    struct timespec times[3]; //structure timespec has two member variables: tv_sec and tv_nsec

    int i, fd;

    for(i = 1; i < argc; i++){
      if(stat(argv[i], &statbuf) < 0 ){  //fetch current times
         perror("stat error");
         continue;
      }

     if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0) { //truncate the file
       perror("Open file Error");
       continue;
     }

     times[0] = statbuf.st_atim;  //get last access time
     times[1] = statbuf.st_mtim;  //get last access time
     times[2] = statbuf.st_ctim;  //get last status change time

     printf("Last Access time is: %ld seconds, %ld nano-seconds\n", times[0].tv_sec, times[0].tv_nsec);
     printf("Last Modified time is: %ld seconds, %ld nano-seconds\n", times[1].tv_sec, times[1].tv_nsec);
     printf("Last Status Change time is: %ld seconds, %ld nano-seconds\n", times[2].tv_sec, times[2].tv_nsec);


     if(futimens(fd, times) < 0){ //reset times
        perror("futimens error");
     }

     close(fd);
    }
    

   exit(0);

}
