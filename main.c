#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "Headers/InputBuffer.h"
#include "Headers/Statement.h"
#include "Headers/BashCommands.h"

int main(int argc, char **argv) {
    InputBuffer *buffer = create_buffer();
    bool is_running = true;
    printf("Write an input: \n");

    while(is_running) {
        char *current_working_dir = get_current_dir_name();
        printf("%s > ", current_working_dir);
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
        case RENAME_FILE_STATEMENT:
            rename_file_or_dir(buffer);
            break;
        case COPY_STATEMENT:
            copy_to_curr_dir(buffer);
            break;
        case HELP_STATEMENT:
            print_help(buffer);
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
        free(current_working_dir);                // Free mem allocated for get_current_dir_name method
    }

    free_buffer(buffer);
    return 0;
}