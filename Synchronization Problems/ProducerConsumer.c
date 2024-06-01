#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFFER_SIZE 10

sem_t empty, full, mutex;
int buffer[BUFFER_SIZE];
int count = 0;

void *producer(void *arg) {
    int item;
    while (1) {
        sem_wait(&empty);
        sem_wait(&mutex);
        item = rand() % 100;
        buffer[count] = item;
        printf("Producer produced %d at buffer[%d]\n", item, count);
        count = (count + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[count];
        buffer[count] = -1;
        printf("Consumer consumed %d from buffer[%d]\n", item, count);
        count = (count - 1 + BUFFER_SIZE) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
