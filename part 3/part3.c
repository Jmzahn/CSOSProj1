#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void print_hello();

void processCreator(int numP, int numC);

void consumer();

void producer();

int produce_item();

void insert_item(int item);

int remove_item();

void wakeup();

pthread_mutex_t task_queue_lock;
int task_available;

int main(int argc, char *argv[])
{
    task_available = 0;
    pthread_mutex_init(&task_queue_lock, NULL);

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

#define N 100
int count = 0;

void *consumer()
{
    int item;
    int removed;

    while(TRUE){
        removed = 0;
        while(removed == 0){
            pthread_mutex_lock(&task_queue_lock);
            if(task_available == 1){
                item = remove_item();
                task_available = 0;
                removed = 1;
            }
            pthread_mutex_unlock(&task_queue_lock);
        }
    }
}

void *producer()
{
    int item;
    int inserted;
    int total = 64;
    int x = 0;
    while(x<total){
        inserted = 0;
        item = produce_item();
        while(inserted == 0){
            pthread_mutex_lock(&task_queue_lock);
            if (task_available == 0){
                insert_item(item);
                task_available = 1;
                inserted = 1;
            }
            pthread_mutex_unlock(&task_queue_lock);
        }
    }
}

int produce_item()
{
    
}