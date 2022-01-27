#include <stdio.h>
#include <iostream>

using namespace std;

int main(){

   char * buffer;

   int number = 10;

   sprintf(buffer, "the number is %d", number);

   std::cout << buffer << std::endl;

   char * name = const_cast<char*>("Tian Guanyu 32");

   char first_name[100];
   char last_name[100];
   int i;

   sscanf(name, "%s %s %d", first_name, last_name, &i);

   printf("My first name is %s\nMy last name is %s\nMy age is %d\n", first_name, last_name, i);

   return 0;
}
