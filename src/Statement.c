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
    // if (extra_arg != NULL) {
    //     return UNRECOGNISED_COMMAND;
    // }

    if (strcmp(command, "ls") == 0) {
        printf("List command\n");
        return LIST_STATEMENT;
    } else {
        return UNRECOGNISED_COMMAND;
    }
}

