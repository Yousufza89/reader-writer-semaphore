#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex;   // Protects read_count
sem_t wsem;    // Writers semaphore for exclusive access

int read_count = 0;

void* reader(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wsem);
        }
        sem_post(&mutex);

        printf("Reader %d is reading...\n", id);
        sleep(1);

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wsem);
        }
        sem_post(&mutex);

        sleep(1);
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *((int*)arg);
    while (1) {
        sem_wait(&wsem);
        printf("Writer %d is writing...\n", id);
        sleep(2);
        sem_post(&wsem);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    
    sem_init(&mutex, 0, 1);
    sem_init(&wsem, 0, 1);
    
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    sem_destroy(&mutex);
    sem_destroy(&wsem);
    
    return 0;
}

