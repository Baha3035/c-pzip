#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Build a thread coordinator
typedef struct {
    int thread_id;
    char* file_data;
    int start;
    int end;
    char* result;
    int result_length;
} ThreadData;

void* compression_work(void* arg) {
    ThreadData* data = (ThreadData*)arg;

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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    // TODO: Read entire file into memory
    
    char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file!");
        return -1;
    }

    // Seek to end of file
    fseek(fp, 0, SEEK_END);

    // Get current position (which is the file size)
    long file_size = ftell(fp);

    // Add this after getting file size to go back to beginning
    fseek(fp, 0, SEEK_SET);

    char* file = malloc(file_size);
    ssize_t bytes_read = fread(file, 1, file_size, fp);
    if (bytes_read > 0) {
        file[bytes_read] = '\0';
    }

    // TODO: Calculate chunk sizes
    int num_threads = 4;
    int chunk_size = file_size / num_threads;
    // TODO: Create worker threads
    ThreadData thread_data[4];
    pthread_t threads[4];

    for(int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == num_threads - 1) ? file_size : (i + 1) * chunk_size;
        thread_data[i].file_data = file;
        thread_data[i].result = malloc(2 * file_size);

        pthread_create(&threads[i], NULL, compression_work, &thread_data[i]);
    }

    // TODO: Wait for all workers
    for(int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Debug and test with printf
    for(int i = 0; i < num_threads; i++) {
        printf("Thread %d result: ", i);
        for(int j = 0; j < thread_data[i].result_length; j+=5) {
            char character = thread_data[i].result[j];
            int count = *((int*)&thread_data[i].result[j + 1]);
            printf("%c%d", character, count);
        }
        printf("\n");
    }

    // TODO: Merge results
    char* final_result = malloc(2 * file_size);
    int final_pos = 0;
    char current_char = '\0';
    int current_count = 0;

    for(int i = 0; i < num_threads; i++) {
        for(int j = 0; j < thread_data[i].result_length; j+=5) {
            char character = thread_data[i].result[j];
            int count = *((int*)&thread_data[i].result[j + 1]);

            if (current_char == character) {
                current_count += count;
            } else {
                if (current_char != '\0') {
                    final_result[final_pos++] = current_char;
                    *((int*)&final_result[final_pos]) = current_count;
                    final_pos += sizeof(int);
                }
                current_char = character;
                current_count = count;
            }
        }
    }

    if (current_char != '\0') {
        final_result[final_pos++] = current_char;
        *((int*)&final_result[final_pos]) = current_count;
        final_pos += sizeof(int);
    }

    // NOW print it properly (not as string!)
    printf("Final result: ");
    for(int i = 0; i < final_pos; i += 5) {
        char character = final_result[i];
        int count = *((int*)&final_result[i + 1]);
        printf("%c%d", character, count);
    }
    printf("\n");
    
    fclose(fp);
    free(file);
    return 0;
}