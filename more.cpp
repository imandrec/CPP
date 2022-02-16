#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAXLINE 100
#define CAT "/bin/cat"   //cat program

int main(int argc, char *argv[]){
  int n;
  
  int  fds[2];

  pid_t  pid;

  if(pipe(fds) < 0){
      perror("Pipe error");
      exit(-1);
  }

  if((pid = fork()) < 0){
    perror("Fork error");
  }else if(pid > 0){
     //parent
    close(fds[0]); //close the read end of the pipe

    //re-direct STDOUT_FILENO to fds[1]
    if(fds[1] != STDOUT_FILENO){
       if(dup2(fds[1], STDOUT_FILENO) != STDOUT_FILENO) perror("dup2 error to stdout");
       close(fds[1]); //don't need this afer dup2
    }

    //parent process runs /usr/bin/ps -ef
   if(execl("/bin/ps", "e", (char*)0) < 0){ 
        perror("PS command failed");
   }

   if(waitpid(pid, NULL, 0) < 0) perror("Wait error");

   exit(0); //terminate parent process
  }else{
     //child process
     close(fds[1]); //close the write end of the pipe
     if(fds[0] != STDIN_FILENO){
         if( dup2(fds[0], STDIN_FILENO) != STDIN_FILENO)  perror("dup2 error to stdin");

         close(fds[0]); //don't need this after dup2.
     }

      char buff[100];

      //int n = read(STDIN_FILENO, buff, 100);
      
      write(STDOUT_FILENO, "child", 5);
     //execute command MORE
     //if(execl(CAT, argv[0], (char*) 0) < 0)  perror("execl error for cat.");
  }

  //printf("Parent terminate\n");

  exit(0);
}
