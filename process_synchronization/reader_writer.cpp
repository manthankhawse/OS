#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int *buffer;
int count = 0;
int buffer_size;
sem_t empty;          
sem_t full;           
pthread_mutex_t mutex;


void *producer(void *arg) {
    int num_produce;
    printf("Enter number of items to produce: ");
    scanf("%d", &num_produce);
    
    for (int i = 0; i < num_produce; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex); 
        
        int item = rand() % 100;  
        buffer[count++] = item;      
        printf("Produced: %d | Buffer: ", item);
        
        for (int j = 0; j < count; j++) {
            printf("%d ", buffer[j]);
        }
        printf("\n");
        
        pthread_mutex_unlock(&mutex); 
        sem_post(&full);              
        sleep(1);                     
    }
    
    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        char choice;
        printf("Do you want to consume an item? (y/n): ");
        scanf(" %c", &choice);
        
        if (choice == 'y') {
            sem_wait(&full);          
            pthread_mutex_lock(&mutex); 
            
            int item = buffer[--count];
            printf("Consumed: %d | Buffer: ", item);
            
            for (int j = 0; j < count; j++) {
                printf("%d ", buffer[j]);
            }
            printf("\n");
            
            pthread_mutex_unlock(&mutex); 
            sem_post(&empty);             
        } else {
            break; 
        }
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    
    printf("Enter buffer size: ");
    scanf("%d", &buffer_size);
    
    buffer = (int *)malloc(buffer_size * sizeof(int));
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        return 1;
    }

    sem_init(&empty, 0, buffer_size); 
    sem_init(&full, 0, 0);            
    pthread_mutex_init(&mutex, NULL); 

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL); 
    pthread_join(cons, NULL); 

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex); 

    free(buffer); 
    return 0;
}
