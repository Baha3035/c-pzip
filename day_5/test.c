#include <string.h>
#include <stdio.h>

int main() {
    int size = 50;
    char compressed_output[2 * size];
    char temp[10];

    compressed_output[0] = '\0';

    for(int i = 0; i < size; i++) {
        sprintf(temp, "%c%d", 'a', 2);
        strcat(compressed_output, temp);
    }

    printf("%s\n", compressed_output);

    return 0;
}