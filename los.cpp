#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//Print the type of file for command-line argument
int main(int argc, char *argv[]){
    int fd;

    mode_t oldmask;

    oldmask = umask(S_IRWXG); //set the Group's RWX bit on

    printf("Old umask is %i\n", oldmask);

    if((fd=creat("temp.txt", S_IRWXU | S_IRWXG)) < 0) perror("creat() error");
    else{
       system("ls -l temp.txt");
       close(fd);
     }
    
   umask(oldmask);

   exit(0);

}
