#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>
#include <algorithm>
#include <cstring>
#include <signal.h>
#include <array>
#include <getopt.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

using std::string;
using std::vector;
using std::array;

pid_t pid, ppid;//current and parentkind of
int laststatus = 0;


//vectors

vector<vector<int> > pidsofbacks;//holcs pids of background process. first int is the process leader 
vector<string> environexp = {};

int parse(string input);//cuts up the input and puts them in to a vector
int eval(vector<string> clean);//takes the cleaned vector and evaluates the args
string getcurrentdir();//gets the current working directory, also if home replace with tilde
int runprog(vector<string> io, vector< vector<string> > pargs);//runs the program;
char* convert(const std::string& s);//converts string into char*
void close_pipe(int pipefd[2]);//closes pipes


int strtosig(string csig); //converts a string signal to an int signal
void checkio(vector<string>& io, bool& out, bool& err, bool& stin, bool& stout, bool& sterr);//checks io vector for trunc and append and sets appropriate booleans



//BUILT-INS
int isbuiltin(string prog);//returns bool if program is a builtin
int runbuilt(int ind, vector<string> prog);//tries to run the builtin

int exit(vector<string> args);//probably want to wait until all children are dead
int cd(vector<string> args);//takes args for chdir



int kill(vector<string> args);
//
void my_handler(int signo) {
} // my_handler


int main(int argc, char* argv[], const char* envp[]) {
    //populate vector exports


    //  pid = getpid();

    signal(SIGINT, my_handler);//ignore C-c
    signal(SIGQUIT, my_handler);//ignore C-backslash
    signal(SIGTSTP, my_handler);//ignore C-z
    signal(SIGTTIN, my_handler);//ignore
    signal(SIGTTOU, my_handler);//ignore
    signal(SIGCHLD, my_handler);//ignore


    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);

    //open messafe

    printf("\nType exit to quit\n\n");

    bool exit = 0;//maybe when logout, not really for this program

    while (!exit) {// will have condition while array is not logout
        string input;
        const int BUFF_SIZE = 1024; // size of data buffer
        char buffer[BUFF_SIZE];    // data buffer
        int n = 0;                  // number of bytes read


        printf("1730sh:%s/$ ", getcurrentdir().c_str());
        //preoblem may lay in buffer
        if ((n = read(STDIN_FILENO, buffer, BUFF_SIZE)) > 0) {
            //      input = (string)buffer;//the real problem lies here
            input.assign(buffer, n - 1);//n - 1 bc \n key
        }

        if (parse(input) == -1) {
            fprintf(stderr, "%s\n", "-1730sh: Oops, an error has occurred.");
        }
    } // while



    return EXIT_SUCCESS;
}


int parse(string input) {

    input += " ";
    vector<string> clean;
    //looks for words surrounded by spaces and pushes them into clean vector
    for (unsigned int i = 0; i < input.length(); i++) {
        if (input.at(i) != ' ') {
            unsigned int j = i + 1;
            unsigned int length = 1;
            if (input.at(i) == '"') {//looking at double quotes
                while (j < input.length()) {
                    if (input.at(j) == '"' && input.at(j - 1) != '\\') {
                        --length;
                        break;
                    }
                    else if (input.at(j) == '"' && input.at(j - 1) == '\\') {
                        input.erase(j - 1, 1);
                    }
                    else {
                        ++j;
                        ++length;
                    }
                }//while
                ++i;
            }//if
            else {
                while (input.at(j) != ' ' && j < input.length()) {
                    ++j;
                    ++length;
                }
            }//else
            clean.push_back(input.substr(i, length));
            i = j;
        }//if

    }//for

    return eval(clean);
}//parse


int eval(vector<string> clean) {
    /*
    for(string arg : copy)
      printf("%s\n", arg.c_str());
    */

    if (clean.size() == 0) {
        return 0;
    }

    string stdin = "STDIN_FILENO";
    string stdout = "STDOUT_FILENO";
    string stderr = "STDERR_FILENO";

    for (unsigned int i = 0; i < clean.size() - 1; i++) {
        //printf("%s\n", clean.at(i).c_str());
        if (clean.at(i).compare("<") == 0) {
            stdin = clean.at(i + 1);
        }
        if (clean.at(i).compare(">") == 0) {
            stdout = clean.at(i + 1) + " (truncate)";
        }
        if (clean.at(i).compare(">>") == 0) {
            stdout = clean.at(i + 1) + " (append)";
        }
        if (clean.at(i).compare("e>") == 0) {
            stderr = clean.at(i + 1) + " (truncate)";
        }
        if (clean.at(i).compare("e>>") == 0) {
            stderr = clean.at(i + 1) + " (append)";
        }
    }//for jobs

    vector<string> io = { stdin, stdout, stderr };

    vector< vector<string> > pargs;
    unsigned int pindex = 0;//index of processes
    unsigned int k = 0;
    while (k < clean.size()) {
        int eindex = 0;//index of elements
        vector<string> args;

        while (k < clean.size() && clean.at(k) != "|") {
            if (clean.at(k).compare("<") == 0 || clean.at(k).compare(">") == 0 || clean.at(k).compare(">>") == 0 || clean.at(k).compare("e>") == 0 || clean.at(k).compare("e>>") == 0) {
                k += 2;
            }
            else {
                args.push_back(clean.at(k));
                ++eindex;
                ++k;
            }//else
        }//inside while
        ++k;
        ++pindex;
        pargs.push_back(args);
    }//loop through to get pipes and args now to print



    return runprog(io, pargs);
}


string getcurrentdir() {
    char cwd[1024];
    string cfixed;
    string home;

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cfixed = (string)cwd;
    }
    else {
        perror("getcwd() error");
        return "?";
    }

    struct passwd* pw = getpwuid(getuid());
    home = (string)pw->pw_dir;

    if (home.compare(cfixed.substr(0, home.length())) == 0) {
        cfixed.replace(0, home.length(), "~");
    }

    return cfixed;
}







void checkio(vector<string>& io, bool& outapp, bool& errapp, bool& stin, bool& stout, bool& sterr) {
    int alength = 9;
    int tlength = 11;//" (truncate)"
    if (io.at(0).compare("STDIN_FILENO") == 0) {
        stin = 1;
    }
    if (io.at(1).compare("STDOUT_FILENO") == 0) {
        stout = 1;
    }
    else if (io.at(1).substr(io.at(1).length() - alength, alength).compare(" (append)") == 0) {//out
        outapp = 1;
        io.at(1) = io.at(1).substr(0, io.at(1).length() - alength);
    }
    else {
        outapp = 0;
        io.at(1) = io.at(1).substr(0, io.at(1).length() - tlength);
    }

    if (io.at(2).compare("STDERR_FILENO") == 0) {
        sterr = 1;
    }
    else if (io.at(2).substr(io.at(2).length() - alength, alength).compare(" (append)") == 0) {//err
        errapp = 1;
        io.at(2) = io.at(2).substr(0, io.at(2).length() - alength);
    }
    else {
        errapp = 0;
        io.at(2) = io.at(2).substr(0, io.at(2).length() - tlength);
    }
}//check io

/*
  jobHandler
  @param vector<string> currentjob
  @return void
  --> Handles our jobs.
 */




void close_pipe(int pipefd[2]) {
    if (close(pipefd[0]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    } // if
    if (close(pipefd[1]) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    } // if
} // close_pipe

char* convert(const std::string& s) {
    char* pc = new char[s.size() + 1];
    std::strcpy(pc, s.c_str());
    return pc;
}//http://stackoverflow.com/questions/7048888/stdvectorstdstring-to-char-array



int isbuiltin(string prog) {
    string listbuilts[3] = { "exit", "cd"};

    for (int i = 0; i < 3; i++) {
        if (prog.compare(listbuilts[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int runbuilt(int ind, vector<string> prog) {

    switch (ind) {
    case 0://exit
        return exit(prog);
    case 1://cd
        return cd(prog);

        //case 7:
        //return kill(prog);
    default:
        return -1;
    }

}//runbuilt

int exit(vector<string> args) {


    //should be also if no argument, then supply with last process value
    if (args.size() > 1)
        exit(stoi(args.at(1)));
    else if (args.size() == 1) {
        exit(laststatus);
    }
    else
        exit(0);

    return -1;
}
int cd(vector<string> args) {

    string path;
    struct passwd* pw = getpwuid(getuid());//to get home

    if (args.size() == 1 || args.at(1).compare("~") == 0) {
        path = (string)pw->pw_dir;
    }
    else
        path = args.at(1);

    if (chdir(path.c_str()) == -1) {
        perror("cd");
        return -1;
    }

    return 0;
}








int strtosig(string csignal) {
    int idx;
    int flag;
    string signalbuilt[19] = { "SIGHUP", "SIGINT", "SIGQUIT" , "SIGILL",
                  "SIGABRT", "SIGFPE", "SIGKILL", "SIGSEGV",
                  "SIGPIPE" , "SIGALRM", "SIGTERM", "SIGUSR1",
                  "SIGUSR2", "SIGCHLD", "SIGCONT", "SIGSTOP",
                  "SIGTSTP" , "SIGTTIN", "SIGTTOU" };
    for (unsigned int i = 0; i < 19; i++) {
        if (csignal.compare(signalbuilt[i]) == 0) {
            idx = i;
            flag = 1;
            break;
        }
    }
    if (!flag) {
        return -1;
    }
    switch (idx) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 6;
    case 6:
        return 8;
    case 7:
        return 9;
    case 8:
        return 11;
    case 9:
        return 13;
    case 10:
        return 14;
    case 11:
        return 15;
    case 12:
        return 10;
    case 13:
        return 12;
    case 14:
        return 17;
    case 15:
        return 18;
    case 16:
        return 19;
    case 17:
        return 20;
    case 18:
        return 21;
    case 19:
        return 22;
    }
    return -1;
}
