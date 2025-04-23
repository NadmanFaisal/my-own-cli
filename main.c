#include <stdio.h>
#include <stdlib.h>

#include "Headers/InputBuffer.h"

int main(int argc, char **argv) {
    InputBuffer *buffer = create_buffer();
    printf("Write an input: \n");
    read_buffer(buffer);

    free_buffer(buffer);
    return 0;
}