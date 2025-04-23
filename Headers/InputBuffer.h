#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include "Constants.h"

typedef struct {
    char buffer[MAX_CHARS];
    int buffer_length;
} InputBuffer;

void clear_buffer();
int get_length(char *string);
InputBuffer *create_buffer();
InputBuffer read_buffer(InputBuffer *buffer);
void print_buffer(InputBuffer *buffer);
void free_buffer(InputBuffer *buffer);

#endif