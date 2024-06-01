#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t wrt = PTHREAD_COND_INITIALIZER;
int readersCount = 0;

void *reader(void *arg) {
    pthread_mutex_lock(&mutex);
    readersCount++;
    if (readersCount == 1) {
        pthread_cond_wait(&wrt, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    
    // Reading operation
    printf("Reader is reading...\n");
    sleep(1);
    
    pthread_mutex_lock(&mutex);
    readersCount--;
    if (readersCount == 0) {
        pthread_cond_signal(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *writer(void *arg) {
    pthread_cond_wait(&wrt, &mutex);
    printf("Writer is writing...\n");
    sleep(2);
    pthread_cond_signal(&wrt);
    return NULL;
}

int main() {
    pthread_t readers[5];
    pthread_t writers[2];

    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&writers[i], NULL, writer, NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&wrt);
    return 0;
}
