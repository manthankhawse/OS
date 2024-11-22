#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

pthread_mutex_t mutex;
pthread_mutex_t rw_mutex;
int reader_count = 0;
int reader_num = 1; 
int writer_num = 1; 

// Function to check for keypress
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt); // Save terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new terminal settings
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar(); // Check for input
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore terminal settings
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin); // Put character back if read
        return 1;
    }

    return 0;
}

void* reader(void* arg) {
    while (1) {
        if (kbhit()) break; // Exit on keypress

        pthread_mutex_lock(&mutex);
        int r_num = reader_num++;
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1) {
            pthread_mutex_lock(&rw_mutex); 
        }
        pthread_mutex_unlock(&mutex);

        printf("Reader %d entered the critical section.\n", r_num);
        sleep(1); 
        printf("Reader %d left the critical section.\n", r_num);

        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0) {
            pthread_mutex_unlock(&rw_mutex); 
        }
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate time for next operation
    }
    return NULL;
}

void* writer(void* arg) {
    while (1) {
        if (kbhit()) break; // Exit on keypress

        pthread_mutex_lock(&mutex);
        int w_num = writer_num++;
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&rw_mutex);

        printf("Writer %d entered the critical section.\n", w_num);
        sleep(1); 
        printf("Writer %d left the critical section.\n", w_num);

        pthread_mutex_unlock(&rw_mutex);

        sleep(1); // Simulate time for next operation
    }
    return NULL;
}

int main() {
    int readers, writers;
    printf("Enter number of readers: ");
    scanf("%d", &readers);
    printf("Enter number of writers: ");
    scanf("%d", &writers);

    pthread_t r_threads[readers], w_threads[writers];

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&rw_mutex, NULL);

    for (int i = 0; i < readers; i++) {
        pthread_create(&r_threads[i], NULL, reader, NULL);
    }

    for (int i = 0; i < writers; i++) {
        pthread_create(&w_threads[i], NULL, writer, NULL);
    }

    printf("Press any key to terminate...\n");

    for (int i = 0; i < readers; i++) {
        pthread_join(r_threads[i], NULL);
    }

    for (int i = 0; i < writers; i++) {
        pthread_join(w_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&rw_mutex);

    return 0;
}
