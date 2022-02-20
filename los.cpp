#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>

using namespace std;

//Print the type of file for command-line argument
int main(int argc, char *argv[]){
    int i;
    struct stat buf;

    string permission;

    for(i = 1; i < argc; i++){
      printf("%s: ", argv[i]);

      if(lstat(argv[i], &buf) < 0){
        perror("lstat error");
        continue;
      }


      if(S_IRUSR & buf.st_mode) permission += "r";
      else permission += "-";

      if(S_IWUSR & buf.st_mode) permission += "w";
      else permission += "-";

      if(S_IXUSR & buf.st_mode) permission += "x";
      else permission += "-";

      printf("%s\n", permission.c_str());
    }


   exit(0);
