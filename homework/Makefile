CC = g++
CXX_FLAGS := -w -Wall -Wextra -std=c++17 -ggdb #Flag use to detect memory leack
GDB = -g # flag for the debuging
REMOVE = -rf # Flag for removing the files
LIB = -pthread # use to include the pthread library
SC_FILE	= singleThread.cpp
ES_FILE	= singleThread

MC_FILE	= multiThread.cpp
EM_FILE	= multiThread

IN_FILE = input.txt

all: # execute the file 
	$(CC) $(GDB) $(CXX_FLAGS) $(LIB) $(SC_FILE) -o $(ES_FILE)
	$(CC) $(GDB) $(CXX_FLAGS) $(LIB) $(MC_FILE) -o $(EM_FILE)
	
SingleThread_exe:
	clear
	./$(ES_FILE) $(IN_FILE)

MultiThread_exe:
	clear
	./$(EM_FILE) $(IN_FILE)


clean_exe:
	rm $(REMOVE) $(ES_FILE) $(EM_FILE)

