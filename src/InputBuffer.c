#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "InputBuffer.h"

void clear_buffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) { }
}

InputBuffer *create_buffer() {
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->buffer_length = 0;

    return input_buffer;
}

void read_buffer(InputBuffer *buffer) {
    char input[MAX_CHARS];
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    strcpy(buffer->buffer, input);
    buffer->buffer_length = strlen(buffer->buffer);
}

void print_buffer(InputBuffer *buffer) {
    for(int i = 0; i < buffer->buffer_length; i++) {
        printf("%c", buffer->buffer[i]);
    }
    printf("\n");
}

void free_buffer(InputBuffer *buffer) {
    if(buffer != NULL) {
        free(buffer);
    }
}