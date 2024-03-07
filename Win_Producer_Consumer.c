#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUF_SIZE 5

sem_t full, empty;
pthread_mutex_t mutex;
pthread_t tid[11];

void *producer(void *arg)
{
    printf("Entered Producer\n");
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    printf("Adding Produced item\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    printf("Added\n");
}

void *consumer(void *arg)
{
    printf("Entered Consumer\n");
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    printf("Consuming item\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    printf("Consumed\n");
}
// sleep is very useful to fully show that the program is working as needed or

void main() // else the scheduler can mess up the output
{
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUF_SIZE);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid[0], NULL, consumer, NULL);
    pthread_create(&tid[1], NULL, consumer, NULL);
    pthread_create(&tid[2], NULL, producer, NULL);
    sleep(10);                                     // sleep gives time for above producer so that we can see adding produced item
    pthread_create(&tid[3], NULL, producer, NULL); // and then Consumed item back to back, or else Consumed item can happen anywhere ofc atomically only
    sleep(10);
    pthread_create(&tid[4], NULL, producer, NULL);
    pthread_create(&tid[5], NULL, producer, NULL);
    pthread_create(&tid[6], NULL, producer, NULL);
    pthread_create(&tid[7], NULL, producer, NULL);
    pthread_create(&tid[8], NULL, producer, NULL);
    sleep(10); // gives time for above five produces to add the item
    pthread_create(&tid[9], NULL, producer, NULL);
    sleep(10); // Useful in seeing that the abv producer won't add as queue is full
    pthread_create(&tid[10], NULL, consumer, NULL);

    for (int i = 0; i <= 10; ++i)
        pthread_join(tid[i], NULL);
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
    return;
}