#include<iostream>
#include <fstream>
#include<unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <stdio.h>
#include <cstring>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
using namespace std;

#define LINE_LEN 80
#define MAX_ARGS 64
#define MAX_ARG_LEN 16
#define MAX_PATHS 64
#define MAX_PATH_LEN 96
#define WHITESPACE " .,\t\n"

#ifndef NULL
#define NULL
#endif

struct command_t
{
	char * name;
	int argc;
	char* argv[MAX_ARGS];
};
void printPrompt()
{
    char tmp[256];
    getcwd(tmp, 256);
    cout<<"HeckerMan@@<<"<<tmp;

}
void platform_setCurrentWorkingDir(const char *path)
{
    chdir(path);
}
void readCommand(char *buffer)
{
	//gets(buffer); //cannot use because of no check of buffer overrun in gets
	cin.getline(buffer,60,'\n');
}
void parsePath(char *dirs[])
{
	char* pathEnvVar;	
	for(int i=0; i<MAX_PATHS; i++)
	{
		dirs[i] = NULL;
	}
	//search for environment variable PATH
	pathEnvVar = strdup(getenv("PATH")); //getenv gets the PATH absolute directories name
	//cout << "pathEnvVar " << pathEnvVar << endl; //to check
	char* token;
	token = strtok(pathEnvVar,":");
	int i = 0;
	if(token != NULL)
	{	cout << endl;
		
		dirs[i] = token;
		i++;
		while(token != NULL)
		{
			token = strtok(NULL,":");
			dirs[i] = token;
			i++;
		}
	}
}



void parseCommand(char * str , command_t * com , bool& isCommandCD)
{
	char*token;
	token=strtok(str," ");
	if(token[0] == 'c' && token[1] == 'd')
	{
		isCommandCD = true;
		if(chdir(str+3) < 0)
		{
			cout << "cannot change directory" << endl;
		}
		else
		{
			return;
		}
	}
	com->argc=0;
	int i=0;
	if(token!=NULL)
	{
		com->argv[i]=token;
		
		i++;
		while(token!=NULL)
		{
			//cout << token << endl; //to check
			token=strtok(NULL," ");
			com->argv[i]= token;
			i++;
			com->argc++;
		}
	}
	i++;
	com->argv[i]=NULL;
}

char * lookUpPath(char ** argv , char ** dir)
{	
	char * result = new char [50];
	char pName[MAX_PATH_LEN];
	if(argv[0][0] == '.' && argv[0][1] == '/')
	{
		//F_OK existence test mode
		int allow = access(argv[0] , F_OK); //access return 0 if accces allowed else -1
	
		if(allow == 0)
			return argv[0];
		return NULL;
	}
	int i = 0;
	for(i; dir[i] != NULL; i++)
	{	
		strcpy(result , dir[i]);
		strcat(result , "/");
		strcat(result , argv[0]);
		int allow = access(result, F_OK);
//cout << result << endl;
		if(allow == 0)
		{
			return result;
		}
	} 
	
	cout<<"File Name Not found in any path variable "<<endl;
	return NULL;
}
void parsePipedCommand(char * str)
{
	char** pipes = new char*[10];
	char** pipes_second = new char*[10]; //second copy of pipes just for parsing because strtok destroy originals
	
	for(int i=0; i<10; i++)
	{
		pipes[i] = NULL;
		pipes_second[i] = NULL;
	}
	char*token = (strtok(str,"|\n"));
	int i=0;
	while(token != NULL)
	{
		pipes[i] = new char[strlen(token)+1];
		pipes_second[i] = new char[strlen(token)+1];
		strcpy(pipes[i],token);
		strcpy(pipes_second[i],token);
		//cout << pipes[i] << endl;
		token = strtok(NULL,"|\n");
		i++;
	}
	pipes[i] = NULL;
	pipes_second[i] = NULL;
//Till here pipes command are parsed

	char** commands = new char*[64];
	for(int i=0; i<64; i++)
	{
		commands[i] = NULL;
	}
	int ** pp = new int*[20];
	for(int i=0; i<20; i++)
	{
		pp[i] = new int[2];
	}
	
	int saveINPPUTSTATE = dup(0);
	int saveOUTPUTSTATE = dup(1);


	for(int i=0;pipes[i] != NULL;i++)
	{
		int j=0;
		char*token1 = (strtok(pipes_second[i]," "));
		while(token1!= NULL)
		{
			commands[j] = new char[strlen(token1)+1];
			strcpy(commands[j],token1);
			//cout << commands[j] << endl;
			token1 = strtok(NULL," ");
			j++;
		}
		commands[j] = NULL;
		if(pipe(pp[i]) == -1)
		{
			cout << "PIPE FAILED TO CREATE " << endl;
		}
		pid_t id = fork();
		if(id == 0) //child
		{
	
			if(pipes[i+1] == NULL) //if last command is NULL then redrect to screen again
			{
								
				dup2(saveOUTPUTSTATE,1);
			}
			else
			{
				dup2(pp[i][1], 1);
			}
			execvp(commands[0],commands);

		}
		else
		{
			wait(NULL);

				dup2(pp[i][0],0);

				close(pp[i][1]);

			if(pipes[i+1] == NULL)
			{

				dup2(saveINPPUTSTATE,0);
			}
	
		}
	}
}	

void parseIOCommand(char * str , bool greaterSign , bool lesserSign)
{
	//cout << "we areIN" << endl;
	char** redirect = new char*[2];
	for(int i=0; i<2; i++)
	{
		redirect[i] = NULL;
	}
	int saveINPPUTSTATE = dup(0);
	int saveOUTPUTSTATE = dup(1);
	if(greaterSign == true && lesserSign == false)
	{
//cout << "we areIN2" << endl;
		char*token = (strtok(str,">\n"));
		int i=0;
		while(token != NULL)
		{
			redirect[i] = new char[strlen(token)+1];
			strcpy(redirect[i],token);
//cout << redirect[i] << endl;
			token = strtok(NULL,">\n");
			i++;
		}
		redirect[i] = NULL;
		bool isPipedCommand = false;
		for(int i = 0; i < strlen(redirect[0]); i++)
		{
			if(redirect[0][i] == '|')
				isPipedCommand = true;
		}
		int f1 = open(redirect[1],O_CREAT | O_WRONLY, S_IRWXU);
		dup2(f1,1);
		if(isPipedCommand == true)
		{
			parsePipedCommand(redirect[0]);		
		}
		else
		{
			char** commands = new char*[64];
			for(int i=0; i<64; i++)
			{
				commands[i] = NULL;
			}
			int j=0;
			char*token1 = (strtok(redirect[0]," "));
			while(token1!= NULL)
			{
				commands[j] = new char[strlen(token1)+1];
				strcpy(commands[j],token1);
				//cout << commands[j] << endl;
				token1 = strtok(NULL," ");
				j++;
			}
			commands[j] = NULL;
			execvp(commands[0],commands);
		}

		dup2(saveOUTPUTSTATE,1);
	}
	else
	{
		char*token = (strtok(str,"<\n"));
		int i=0;
		while(token != NULL)
		{
			redirect[i] = new char[strlen(token)+1];
			strcpy(redirect[i],token);

			token = strtok(NULL,"<\n");
			i++;
		}
		redirect[i] = NULL;
		bool isPipedCommand = false;
		for(int i = 0; i < strlen(redirect[0]); i++)
		{
			if(redirect[0][i] == '|')
				isPipedCommand = true;
		}
		//int f1 = open(redirect[1],O_CREAT | O_WRONLY, S_IRWXU);
		int fd = open(redirect[1],O_RDONLY);
		dup2(fd,0);
		if(isPipedCommand == true)
		{
			parsePipedCommand(redirect[0]);		
		}
		else
		{
			char** commands = new char*[64];
			for(int i=0; i<64; i++)
			{
				commands[i] = NULL;
			}
			int j=0;
			char*token1 = (strtok(redirect[0]," "));
			while(token1!= NULL)
			{
				commands[j] = new char[strlen(token1)+1];
				strcpy(commands[j],token1);
				//cout << commands[j] << endl;
				token1 = strtok(NULL," ");
				j++;
			}
			commands[j] = NULL;
			execvp(commands[0],commands);
		}

		dup2(saveINPPUTSTATE,0);
	}

}


int main(int argc , char * argv[])
{
	char * pathv[MAX_PATHS];
	parsePath(pathv);
	char  commandLine[60];
	command_t com;
	com.name = NULL;
	com.argc = 0;
	bool isCommandCD = false;
	bool isPipedCommand = false;
	bool isIOCommand = false;
	bool greaterSign = false;
	bool lesserSign = false;
	platform_setCurrentWorkingDir("/c");
	while(true)
	{
		isCommandCD = false;
		isPipedCommand = false;
		isIOCommand = false;
		greaterSign = false;
		lesserSign = false;
		printPrompt();
		readCommand(commandLine);
		if(commandLine[0] == 'e' && commandLine[1] == 'x' && commandLine[2] == 'i' && commandLine[3]=='t' )
		{
			return 0;
		}
		int len = strlen(commandLine);
		for(int i = 0; i<len && isIOCommand == false; i++)
		{
			if(commandLine[i] == '>'){
				isIOCommand = true;
				greaterSign = true;
			}
			if(commandLine[i] == '<'){
				isIOCommand = true;
				lesserSign = true;
			}
		}
		for(int i=0; i<len && isPipedCommand == false && isIOCommand == false; i++)
		{
			if(commandLine[i] == '|'){
				isPipedCommand = true;
			}
		}
		if(isIOCommand == true && isPipedCommand == false)
		{
			parseIOCommand(commandLine,greaterSign,lesserSign);
		}
		if(isPipedCommand == true && isIOCommand == false)
		{
			parsePipedCommand(commandLine);
		}
		else
		{
			parseCommand(commandLine , &com , isCommandCD);
		}
		if(isCommandCD == false && isPipedCommand == false && isIOCommand == false)
		{
			com.name = lookUpPath(com.argv , pathv);
			if(com.name == NULL)
			{
				cout<<"ERROR!"<<endl;
			}
			else 
			{
				pid_t pid = fork();
				if(pid == 0)
				{

					execv(com.name , com.argv);
					cout<<"Command is not Found"<<endl;
				}
				if(pid > 0)
				{
					wait(NULL);
				}
				
			}	
		}
		else
		{
			isCommandCD = false;
		}
		
	}
	return 0;	
}
