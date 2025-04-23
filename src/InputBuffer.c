#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "InputBuffer.h"

void clear_buffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) { }
}
int get_length(char *string) {
    int length = 0;
    while(string[length] != '\0') {
        length++;
    }

    return length;
}

InputBuffer *create_buffer() {
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));

    return input_buffer;
}
InputBuffer read_buffer(InputBuffer *buffer) {
    char input[MAX_CHARS];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    strcpy(buffer->buffer, input);
    buffer->buffer_length = get_length(buffer->buffer);
}

void free_buffer(InputBuffer *buffer) {
    free(buffer);
}