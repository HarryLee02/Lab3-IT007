#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

// Define the bounded buffer and semaphores
int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

// Define functions for producer and consumer
void *producer(void *arg) {
    int sum = 0;
    while (1) {
        int item = rand() % 11 + 10; // Generate a random number between 10 and 20
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        // Add item to buffer
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == 0) {
                buffer[i] = item;
                printf("Producer produced: %d\n", item);
                break;
            }
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sum += item;

        // Check if the total sum is greater than 100
        if (sum > 100) {
            break;
        }
    }
    printf("Total sum: %d\n", sum);
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int sum = 0;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        // Remove item from buffer
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] != 0) {
                printf("Consumer consumed: %d\n", buffer[i]);
                sum += buffer[i];
                buffer[i] = 0;
                break;
            }
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // Check if the total sum is greater than 100
        if (sum > 100) {
            break;
        }
    }
    pthread_exit(NULL);
}

int main() {
    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads for producer and consumer
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
