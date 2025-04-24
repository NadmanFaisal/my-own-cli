#include "Statement.h"
#include <string.h>

StatementType execute_statement(InputBuffer *buffer) {
    char string[MAX_CHARS];
    strcpy(string, buffer->buffer);
    const char delimiter[] = " ";
    
    char *command = strtok(string, delimiter);
    if (command == NULL) {
        return UNRECOGNISED_COMMAND;
    }

    char *extra_arg = strtok(NULL, delimiter);

    if (strcmp(command, "ls") == 0) {
        return LIST_STATEMENT;
    } else if (strcmp(command, "cd") == 0) {
        return CHANGE_DIR_STATEMENT;
    } else if (strcmp(command, "exit") == 0) {
        return EXIT_STATEMENT;
    } else {
        return UNRECOGNISED_COMMAND;
    }
}

