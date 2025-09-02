#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int thread_id;
    char* file_data;      // Pointer to the entire file in memory
    int start;            // Where this thread starts processing
    int end;              // Where this thread stops
    char* result;         // Where to store compressed output
    int result_length;    // How many bytes were compressed
} ThreadData;

void* compression_work(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    // Process data->file_data from data->start to data->end
    // Store result in data->result

    int char_count = 0;
    char current_character = data->file_data[data->start];
    int pos = 0;

    for(int i = data->start; i < data->end; i++) {
        
        if (current_character == data->file_data[i]) {
            char_count++;
        } else {
            data->result[pos++] = current_character;
            *((int*)&data->result[pos]) = char_count;
            pos += sizeof(int);

            current_character = data->file_data[i];
            char_count = 1;
        }
    }

    data->result[pos++] = current_character;
    *((int*)&data->result[pos]) = char_count;
    pos += sizeof(int);

    data->result[pos] = '\0';

    data->result_length = pos;
    return NULL;
}

int main () {
    char test_input[] = "aaabbcccc";

    ThreadData data;
    data.thread_id = 1;
    data.file_data = test_input;
    data.start = 0;
    data.end = strlen(test_input);

    data.result = malloc(2 * strlen(test_input));

    compression_work(&data);

    printf("Test input: %s\n", test_input);
    printf("Output: ");

    for(int i = 0; i < data.result_length; i += 5) {
        char character = data.result[i];
        int count = *((int*)&data.result[i + 1]);
        printf("%c%d", character, count);
    }
    printf("\n");

    free(data.result);
    return 0;
}