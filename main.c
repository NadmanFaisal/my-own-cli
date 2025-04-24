#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Headers/InputBuffer.h"
#include "Headers/Statement.h"
#include "Headers/BashCommands.h"

int main(int argc, char **argv) {
    InputBuffer *buffer = create_buffer();
    bool is_running = true;
    while(is_running) {
        printf("Write an input: \n");
        read_buffer(buffer);
        
        switch (execute_statement(buffer)) {
        case LIST_STATEMENT:
            list_dir(buffer);
            is_running = false;
            exit(EXIT_SUCCESS);
            break;
        case UNRECOGNISED_COMMAND:
            printf("Unrecognised command.\n");
            is_running = false;
            exit(EXIT_FAILURE);
        default:
            break;
        }

    }

    free_buffer(buffer);
    return 0;
}