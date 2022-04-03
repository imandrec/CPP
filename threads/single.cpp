#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
using namespace std;

int arr[5000];
int arrSize;

struct parameters{
    int sSubIndex; // starting index of sub array
    int eSubIndex; // ending index of sub array
    int MaxNumber; // Max number that the result of sub array
    int arraystart;
    int arrayEnd;
}parameters;

int readData(char *fileName) { // this program can read max 5000 integers from the file
    FILE* file;
    file = fopen(fileName, "r");

    if (file == NULL) {
        cout<<"File Not open\n ";
        arrSize = 0;
        return -1;
    }
    int bufferSize = 1000;
    char buffer[1000];
    int index = 0;

	while (fgets(buffer, bufferSize, file) != NULL && index<5000) {
        if( buffer[strlen(buffer) - 1] == '\0')
            buffer[strlen(buffer) - 1] = '\0';

        char* str = strtok(buffer, " ");
        for (; str != NULL; index++) {
            arr[index] = atoi(str);
            str = strtok(NULL, " ");
        }
	}
    
    arrSize = index;

    return 1;
}

void* maximum_sum(void* para) {
    struct parameters* ptr = (struct parameters*)para;
    
    int max_sum = INT_MIN;    
    int sum = 0;
    for (int i = ptr->arraystart; i < ptr->arrayEnd; i++) {
        sum = 0;
        for (int j = i; j < arrSize; j++) {
            sum += arr[j];
            if (sum > max_sum) {
                ptr->sSubIndex  = i;
                ptr->eSubIndex = j;
                max_sum = sum;
            }
        }
    }
    ptr->MaxNumber = max_sum;
    return NULL;
}

int main(int argc, char * argv[]) {
    if(argc != 2){
        cout<<"\nCommand line argument not valid :-(";
        cout<<"\n<EXE_FILE> <DATA_FILE>\n";
        return -1;
    }
    if(readData(argv[1]) == -1){ //read data from the file
        return 0;
    } 
    struct parameters par;
    //prepare system for the parameters
    par.arraystart = 0;
    par.arrayEnd = arrSize;

    pthread_t pid1;

    pthread_create(&pid1, NULL, maximum_sum, &par);


    pthread_join(pid1,NULL);

    cout<<"\nMax sum of the sub array : "<<par.MaxNumber;
    cout<<"\nMax subarray : ";

    for(int i = par.sSubIndex; i <= par.eSubIndex; i++ ){
        cout<<arr[i]<<", ";
    }
    
    
    printf("\n");
    
    return 0;
}
