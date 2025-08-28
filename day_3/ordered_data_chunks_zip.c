#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    char* data;
    int chunk_number;
    char** results;
} chunk_info_t;

void* compress_chunk(void* arg) {
    chunk_info_t* info = (chunk_info_t*)arg;

    printf("Process %d starting\n", info->chunk_number);

    sleep(info->chunk_number == 0 ? 1 : 2);

    char* result = malloc(20);
    sprintf(result, "a3b3");

    info->results[info->chunk_number] = result;

    printf("Chunk %d compressed!\n", info->chunk_number);
    return NULL;
}

int main() {
    char* results[2] = {NULL, NULL};

    pthread_t threads[2];
    chunk_info_t chunks[] = {
        {"aaabbb", 0, results},
        {"cccddd", 1, results}
    };

    for(int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, compress_chunk, &chunks[i]);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    for(int i = 0; i < 2; i++) {
        printf("%s\n", results[i]);
        free(results[i]);
    }

    // It is to know which result belongs to which chunk
    return 0;
}