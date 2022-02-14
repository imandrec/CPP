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
