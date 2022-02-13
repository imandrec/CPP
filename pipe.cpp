#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXLINE 100

int main(){
  int n;

  int  fds[2]; //

  pid_t  pid;

  char  line[MAXLINE];

  if(pipe(fds) < 0){
      printf("Pipe error");
      exit(-1);
  }

  if((pid = fork()) < 0){
    printf("Fork error");
    exit(-1);
  }else if(pid > 0){
     //parent
    printf("This is parent %d\n", getpid());
    close(fds[0]); //close the read/input file descriptor of the pipe
    write(fds[1], "Hello From Parent.", 19);
  }else{
     close(fds[1]); //close the write/output file decriptor of the pipe
     printf("This is child %d\n", getpid());
     n = read(fds[0], line, MAXLINE);
     write(STDOUT_FILENO, line, n);
     printf("Child terminates\n");
     exit(0);
  }

  printf("Parent terminates\n");

  exit(0);
}
