#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *consumer(void *ptr);

void *producer(void *ptr);

#define N 100
pthread_mutex_t task_queue_lock;
pthread_cond_t condc, condp;
int buffer = 0;

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
        pthread_t pro[numP];
        pthread_t con[numC];
        pthread_mutex_init(&task_queue_lock, 0);
        pthread_cond_init(&condc, 0);
        pthread_cond_init(&condp, 0);
        for(int i = 0; i<numC; i++){
            pthread_create(&con[i],NULL,consumer,NULL);
            pthread_join(con[i],0);
        }
        for(int i = 0; i<numP; i++){
            pthread_create(&pro[i],NULL,producer,NULL);
            pthread_join(pro[i],0);
        }
        pthread_cond_destroy(&condc);
        pthread_cond_destroy(&condp);
        pthread_mutex_destroy(&task_queue_lock);
    }
}

void *consumer(void *ptr)
{
    int i;

    for(i=1;i<=N;i++){
        pthread_mutex_lock(&task_queue_lock);
        while(buffer==0) pthread_cond_wait(&condc, &task_queue_lock);
        buffer = 0;
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&task_queue_lock);
    }
    pthread_exit(0);
}

void *producer(void *ptr)
{
    int i;

    for(i=1;i<=N;i++){
        pthread_mutex_lock(&task_queue_lock);
        while(buffer!=0) pthread_cond_wait(&condp, &task_queue_lock);
        buffer = i;
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&task_queue_lock);
    }
    pthread_exit(0);
}