#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include "Constants.h"

typedef struct {
    char buffer[MAX_CHARS];
} InputBuffer;

InputBuffer *create_buffer();
InputBuffer read_buffer(InputBuffer *buffer, char *input);
void print_buffer(InputBuffer *buffer);
void free_buffer(InputBuffer *buffer);

#endif