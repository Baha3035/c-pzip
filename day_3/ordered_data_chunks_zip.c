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

void merge_consecutive_runs(char* compressed) {
    // Input: "a3b2b3c2"  
    // Output: "a3b5c2"

    char result[1000] = "";
    int pos = 0;

    for(int i = 0; compressed[i] != '\0'; i += 2) {
        char current_char = compressed[i];
        int current_count = compressed[i+1] - '0'; // Convert char to int

        if(pos > 0 && result[pos-2] == current_char) {
            int prev_count = result[pos-1] - '0';
            result[pos-1] = (prev_count + current_count) + '0';
        } else {
            result[pos++] = current_char;
            result[pos++] = current_count + '0';
        }
    }

    result[pos] = '\0';
    strcpy(compressed, result);
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

// Now it is possible to:
// 1. Split file into chunks (any boundaries)
// 2. Compress each chunk in parallel
// 3. Merge results
// 4. Post-process to combine consecutive runs