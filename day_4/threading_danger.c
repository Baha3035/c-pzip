#include <pthread.h>
#include <stdio.h>

int shared_counter = 0;
pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;

void* worker_function( void* arg) {
    for(int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&counter_lock);
        shared_counter++;
        pthread_mutex_unlock(&counter_lock);
    }
    return NULL;
}

int main() {
    pthread_t thread_1, thread_2;

    pthread_create(&thread_1, NULL, worker_function, NULL);
    pthread_create(&thread_2, NULL, worker_function, NULL);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    printf("Counter is %d", shared_counter);
    return 0;
}