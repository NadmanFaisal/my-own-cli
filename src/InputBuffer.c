#include <stdlib.h>
#include <stdio.h>

#include "InputBuffer.h"

InputBuffer *create_buffer() {
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));

    return input_buffer;
}
InputBuffer read_buffer(InputBuffer *buffer, char *input);
void print_buffer(InputBuffer *buffer);
void free_buffer(InputBuffer *buffer);