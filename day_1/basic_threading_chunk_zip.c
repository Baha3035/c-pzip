#include <pthread.h>
#include <stdio.h>

void* compress_chunk(void* chunk_data) {
    char* data = (char*)chunk_data;
    printf("Thread processing: %s\n", data);

    // Compressing logic
    
    return NULL;
}

int main() {
    pthread_t threads[2];
    char* chunks[] = {"aaabbb", "cccddd"};

    for(int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, compress_chunk, chunks[i]);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}