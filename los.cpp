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
