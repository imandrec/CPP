#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdint.h>
#include <string>

using namespace std;

string SearchFile(string file, string dir);

int main(int argc, char * argv[]){
    char currentDir[100] ;

    getcwd(currentDir, 100); //get the current working directory name
 
    cout << "Current Dir: " << currentDir << endl;

    string file = SearchFile(argv[1], currentDir);

    cout << "Found " << argv[1] << " at: " << file << endl;

    exit(0);
}

string SearchFile(string filename, string dir){
    struct dirent * fileDir;

    DIR * dirp;

    struct stat fileStat;

    dirp = opendir(dir.c_str()); //open the current directory

    if(dirp == NULL){
      perror("Error opening directory ");
      exit(-1);
    }

    while ((fileDir = readdir(dirp)) != NULL){
         if(string(fileDir->d_name).compare(".") == 0 || string(fileDir->d_name).compare("..") == 0) continue;

         int result = lstat((dir + "/" + string(fileDir->d_name)).c_str(), &fileStat);

         if(filename.compare(string(fileDir->d_name)) == 0 && (fileStat.st_mode & S_IFMT) == S_IFREG){
            closedir(dirp);
            return dir + "/" + filename;
         }else if((fileStat.st_mode & S_IFMT) == S_IFDIR) {
           string subFile = SearchFile(filename, (dir + "/" + string(fileDir->d_name)).c_str() );

           if(subFile.length() > 0 && subFile.compare("File Not Found") != 0){
             closedir(dirp);
             return subFile;
           }
         }
    }

   closedir(dirp);
   return "File Not Found";
}
