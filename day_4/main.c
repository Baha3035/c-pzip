#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* file = fopen("test.txt", "r");

    if (file == NULL) {
        printf("File not found");
        return -1;
    }

    char* file_contents = malloc(100);
    ssize_t bytes_read = fread(file_contents, 1, 100, file);
    printf("Bytes read: %zd\n", bytes_read);
    if (bytes_read > 0) {
        file_contents[bytes_read] = '\0';
    }
    printf("%s", file_contents);
    free(file_contents);
}