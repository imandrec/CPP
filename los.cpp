#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//Print the type of file for command-line argument
int main(int argc, char *argv[]){
    struct stat buf;

    //create a file temp
    int fd;

    if((fd=creat("temp", 0444)) < 0) perror("creat() error");
    else{
       system("ls -l temp"); //print temp file's permission

       //get current permission of temp file
       if(stat("temp", &buf) < 0){
          perror("Stat error for temp");
       }
        //turn on set-group-ID and turn off group-execute
       if(chmod("temp", buf.st_mode & ~S_IXGRP | S_ISGID) <0 ){
           perror("chmod failed for temp");
       }

       system("ls -l temp");

       //set absolute mode to "rw-r--r--"
       if(chmod("temp", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0){
          perror("chmod error for temp");
       }

       close(fd);
     }

   system("ls -l temp");
   exit(0);

}
