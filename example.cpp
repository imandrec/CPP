#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

using namespace std;

int main(){

  int fd = open("test.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);

  printf("File descriptor %d\n", fd);

  string buff = "This is a test for O_APPEND\n";
  write(fd, buff.c_str(), buff.size());

  close(fd);
  return 0;
}
