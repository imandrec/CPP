#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>

using namespace std;

void getArguments();
string input="";
vector<char*> arguments;

int main(int argc, char** argv) {

cout << "Welcome to my shell. Exit with �logout�.0" << endl;

while (input!= "logout") {
    getline(cin, input);
    //getArguments();
    size_t space = input.find(" ");
    string command= input.substr(0,space);
    int end = input.length() - space;
    string text = input.substr(space+1, ende);

    string path = "/usr/bin/" + command;

    pid_t pid = fork();
    if(pid == 0)
    {
        cout << "Process " << command << " wi: \n";
        execlp(path.c_str(), NULL);
    }
    if(text!="&")
        waitpid(pid, 0, 0);
}
return 0;
}
