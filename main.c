#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Headers/InputBuffer.h"
#include "Headers/Statement.h"
#include "Headers/BashCommands.h"

int main(int argc, char **argv) {
    InputBuffer *buffer = create_buffer();
    bool is_running = true;
    printf("Write an input: \n");

    while(is_running) {
        read_buffer(buffer);
        
        switch (execute_statement(buffer)) {
        case LIST_STATEMENT:
            list_dir(buffer);
            break;
        case CHANGE_DIR_STATEMENT:
            change_dir(buffer);
            break;
        case MAKE_DIR_STATEMENT:
            make_dir(buffer);
            break;
        case TOUCH_FILE_STATEMENT:
            touch_file(buffer);
            break;
        case DELETE_STATEMENT:
            remove_file_dir(buffer);
            break;
        case UNRECOGNISED_COMMAND:
            printf("Unrecognised command.\n");
            break;
        case EXIT_STATEMENT:
            is_running = false;
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }

    free_buffer(buffer);
    return 0;
}