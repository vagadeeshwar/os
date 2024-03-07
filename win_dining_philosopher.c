#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define EATINGTIME 1

void *philosopher1();
void *philosopher2();
void *philosopher3();
void *philosopher4();
void *philosopher5();
sem_t sem_1, sem_2, sem_3, sem_4, sem_5;
int end = 0;
int main()
{
    pthread_t t1, t2, t3, t4, t5;
    pthread_attr_t at1;
    pthread_attr_init(&at1);
    pthread_attr_setdetachstate(&at1, PTHREAD_CREATE_DETACHED);
    sem_init(&sem_1, 0, 1);
    sem_init(&sem_2, 0, 1);
    sem_init(&sem_3, 0, 1);
    sem_init(&sem_4, 0, 1);
    sem_init(&sem_5, 0, 1);
    printf("\n threads are called......");
    printf("\n\n\n\n\n\n");
    printf("\n\n\t\tNO. OF PHILOSOPHERS :5");
    printf("\n\n\t\tNO. OF FORKS(SPOONS):5\n\n");
    pthread_create(&t1, &at1, philosopher1, NULL);
    pthread_create(&t2, &at1, philosopher2, NULL);
    pthread_create(&t3, &at1, philosopher3, NULL);
    pthread_create(&t4, &at1, philosopher4, NULL);
    pthread_create(&t5, &at1, philosopher5, NULL);
    while (end != 5)
    {
    }
}

void *philosopher1()
{
    int i = 0;
    printf("\n\t\tPHILOSOPHER-1 THINKING.\n");
    while (i < EATINGTIME)
    {
        sleep(1);
        sem_wait(&sem_1);
        sem_wait(&sem_2);
        printf("\n\t\t\t* PHILOSOPHER-1 EATING.*\n");
        sleep(1);
        sem_post(&sem_1);
        sem_post(&sem_2);
        printf("\n\t\tPHILOSOPHER-1 THINKING.\n");
        i++;
    }
    end++;
}

void *philosopher2()
{
    int i = 0;
    printf("\n\t\tPHILOSOPHER-2 THINKING.\n");
    while (i < EATINGTIME)
    {
        sleep(1);
        sem_wait(&sem_2);
        sem_wait(&sem_3);
        printf("\n\t\t\t* PHILOSOPHER-2 EATING.*\n");
        sleep(1);
        sem_post(&sem_2);
        sem_post(&sem_3);
        printf("\n\t\tPHILOSOPHER-2 THINKING.\n");
        i++;
    }
    end++;
}

void *philosopher3()
{
    int i = 0;
    printf("\n\t\tPHILOSOPHER-3 THINKING.\n");
    while (i < EATINGTIME)
    {
        sleep(1);
        sem_wait(&sem_3);
        sem_wait(&sem_4);
        printf("\n\t\t\t* PHILOSOPHER-3 EATING.*\n");
        sleep(1);
        sem_post(&sem_3);
        sem_post(&sem_4);
        printf("\n\t\tPHILOSOPHER-3 THINKING.\n");
        i++;
    }
    end++;
}

void *philosopher4()
{
    int i = 0;
    printf("\n\t\tPHILOSOPHER-4 THINKING.\n");
    while (i < EATINGTIME)
    {
        sleep(1);
        sem_wait(&sem_4);
        sem_wait(&sem_5);
        printf("\n\t\t\t* PHILOSOPHER-4 EATING.*\n");
        sleep(1);
        sem_post(&sem_4);
        sem_post(&sem_5);
        printf("\n\t\tPHILOSOPHER-4 THINKING.\n");
        i++;
    }
    end++;
}

void *philosopher5()
{
    int i = 0;
    printf("\n\t\tPHILOSOPHER-5 THINKING.\n");
    while (i < EATINGTIME)
    {
        sleep(1);
        sem_wait(&sem_5);
        sem_wait(&sem_1);
        sem_wait(&sem_4);
        printf("\n\t\t\t* PHILOSOPHER-5 EATING.*\n");
        sleep(1);
        sem_post(&sem_5);
        sem_post(&sem_1);
        sem_post(&sem_4);
        printf("\n\t\tPHILOSOPHER-5 THINKING.\n");
        i++;
    }
    end++;
}