#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

int read_count=0;
pthread_t t[5];
sem_t mutex, rw_mutex;

void *reader(void *arg)
{
    sem_wait(&mutex);
    read_count++;
    if(read_count==1)
        sem_wait(&rw_mutex);
    sem_post(&mutex);
    printf("A thread is reading\n");
    sleep(1);
    printf("Reading over\n");
    sem_wait(&mutex);
    read_count--;
    if(read_count==0)
        sem_post(&rw_mutex);
    sem_post(&mutex);
    //return (void*)0;
}

void* writer(void* arg)
{
    sem_wait(&rw_mutex);
    printf("A thread is writing\n");
    sleep(1);
    printf("Writing over\n");
    sem_post(&rw_mutex);
    //return (void*)0;
}

void main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);
    pthread_create(&t[0], NULL, reader, NULL);
    pthread_create(&t[1], NULL, reader, NULL);
    pthread_create(&t[2], NULL, writer, NULL);
    sleep(10);
    pthread_create(&t[3], NULL, reader, NULL);
    pthread_create(&t[4], NULL, writer, NULL);
    for(int i=0;i<=4;i++)
        pthread_join(t[i], NULL);
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    return;
}
