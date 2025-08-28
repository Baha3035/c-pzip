#include <pthread.h>
#include <stdio.h>
#include <string.h>

void* compress_chunk(void* chunk_data) {
    char* data = (char*)chunk_data;
    printf("Thread processing: %s\n", data);

    char current_char = data[0];
    int count = 1;
    int len = strlen(data);

    for (int i = 1; i < len; i++) {
        if (data[i] == current_char) {
            count++;
        }
        else {
            printf("%c%d", current_char, count);
            current_char = data[i];
            count = 1;
        }
    }

    printf("%c%d", current_char, count);

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