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
