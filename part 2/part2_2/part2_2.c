#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_hello();

void processCreator(int numP);

int main(int argc, char *argv[])
{
    if(argc != 2){
        return(-1);
    }
    else{
        char *p;
        long conv = strtol(argv[1], &p, 10);
        int numP;
        numP = conv;
        processCreator(numP);
    }
}

void print_hello()
{
    int processID;
    processID = getpid();
    printf("Hello from process: %d\n",processID);
}

void processCreator(int numP)
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
    for(int i = numP-1; i>=0; i--)
    {
        if(status[i] == 0)
        {
            print_hello();
            exit(0);
        }
    }
    
}