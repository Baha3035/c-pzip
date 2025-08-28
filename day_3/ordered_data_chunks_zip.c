#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


typedef struct {
    char* data;
    int chunk_number;
} chunk_info_t;

void* compress_chunk(void* arg) {
    chunk_info_t* info = (chunk_info_t*)arg;

    printf("Process %d starting\n", info->chunk_number);

    sleep(info->chunk_number == 0 ? 1 : 2);

    printf("Chunk %d compressed!\n", info->chunk_number);
    return NULL;
}

int main() {
    pthread_t threads[2];
    chunk_info_t chunks[] = {
        {"aaabbb", 0},
        {"cccddd", 1}
    };

    for(int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, compress_chunk, &chunks[i]);
    }

    for(int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    // It is to know which result belongs to which chunk
    return 0;
}