//bounded buffer using monitor


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 89767

pthread_cond_t empty, full;
int count = 0;
pthread_mutex_t mutex;
int buffer[N];
int bufPtr = -1;

pthread_t tid;       
pthread_attr_t attr; 

void monitor_enter() {

    pthread_mutex_lock(&mutex);

    while (count == N)
        pthread_cond_wait(&full, &mutex);

    bufPtr++;
    int item = rand();
    printf("Producer produced %d\n", item);
    buffer[bufPtr] = item;

    count++;
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mutex);
}

void monitor_remove() {

    pthread_mutex_lock(&mutex);

    while (count == 0)
        pthread_cond_wait(&empty, &mutex);

    printf("Consumer consumed: %d\n", buffer[bufPtr]);
    buffer[bufPtr] = 0;
    bufPtr--;

    count--;
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mutex);
}

void *producer(void* param) {

    while (1) {
        usleep(rand()/678);
        monitor_enter();
    }
}

void *consumer(void* param) {

    while (1) {
        usleep(rand()/678);
        monitor_remove();
    }
}

int main() {

    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, producer, NULL);
    pthread_create(&tid, &attr, consumer, NULL);

    sleep(10);
    exit(0);
}


