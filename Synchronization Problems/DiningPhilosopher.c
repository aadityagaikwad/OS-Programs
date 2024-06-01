#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

#define NUM_PHILO 5

sem_t forks[NUM_PHILO];

typedef struct{
    int id;
}Philosopher;

void *philosopher_routine(void *arg)
{
    Philosopher *philosopher = (Philosopher *arg);
    int id = philosopher->id;
    while(1)
    {
        printf("\nPhilosopher %d is thinking",id);
        usleep(rand()%100 * 1000);
        sem_wait(&forks[id]);
        sem_wait(&forks[(id+1)%NUM_PHILO]);
        printf("\nPhilosopher %d is grabbing forks and eating",id);
        usleep(rand()%100*1000);

        sem_post(&forks[(id+1)%NUM_PHILO]);
        sem_post(&forks[id]);

        printf("\nPhilosopher %d is putting forks down",id);
    }
}

int main()
{
    pthread_t threads[NUM_PHILO];
    Philosopher philosophers[NUM_PHILO];

    for(int i=0;i<NUM_PHILO;i++)
    {
        sem_init(%forks[i],0,1);
    }
    for(int i=0;i<NUM_PHILO;i++)
    {
        philosophers[i].id = i;
        pthread_create(&forks[i],NULL,philosopher_routine,&philosophers[i]);
    }
    for(int i =0;i<NUM_PHILO;i++)
    {
        pthread_join(threads[i],NULL);
    }
    for(int i=0;i<NUM_PHILO;i++)
    {
        sem_destroy(&forks[i]);
    }

    return 0;
}
