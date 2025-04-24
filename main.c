#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Headers/InputBuffer.h"
#include "Headers/Statement.h"
#include "Headers/BashCommands.h"

int main(int argc, char **argv) {
    InputBuffer *buffer = create_buffer();
    
    while(true) {
        printf("Write an input: \n");
        read_buffer(buffer);
        
        switch (execute_statement(buffer)) {
        case LIST_STATEMENT:
            list_dir();
            break;
        case UNRECOGNISED_COMMAND:
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    free_buffer(buffer);
    return 0;
}