#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]){

    if(argc < 2){
      perror("Usages: a.out  pid");
      exit(-1);
    }
  
    int pid;

    stringstream strValue;
    strValue << argv[1]; 

    strValue >> pid;

    if(kill(pid, 9) < 0){
      perror("Kill failed");
      exit(-1);
    }

    printf("Terminated");
    exit(0);
}
