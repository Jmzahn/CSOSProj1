#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_hello();

void processCreator(int numP, int numC);

int main(int argc, char *argv[])
{
    if(argc != 3){
        return(-1);
    }
    else{
        char *tempChar;
        long conv = strtol(argv[1], &tempChar, 10);
        int numP;
        int numC;
        numP = conv;
        conv = strtol(argv[2], &tempChar, 10);
        numC = conv;
        processCreator(numP, numC);
    }
}

void print_hello()
{
    int processID;
    int parentProcessID;
    processID = getpid();
    parentProcessID = getppid();
    printf("Hello from process: %d, my parent is: %d\n",processID,parentProcessID);
}

void processCreator(int numP, int numC)
{
    pid_t waits[numP];
    pid_t status[numP];
    for(int i = 0; i<numP; i++)
    {
        status[i] = fork();
        if(status[i] != 0)
        {
            waits[i] = wait(NULL);
            break;
        }
    }
    print_hello();
    exit(0);

    /*for(int i = numP-1; i>=0; i--)
    {
        if(status[i] == 0)
        {
            print_hello();
            exit(0);
        }
    }*/
    
}