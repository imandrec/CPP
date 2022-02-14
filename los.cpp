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
