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
