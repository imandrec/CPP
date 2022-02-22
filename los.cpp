#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//Print the type of file for command-line argument
int main(int argc, char *argv[]){
    struct stat buf;

   if(chown("temp", 1000, 1000) < 0) perror("chown failed");

   system("ls -l temp");
   exit(0);

}
