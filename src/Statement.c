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
    } else if(strcmp(command, "mkdir") == 0) {
        return MAKE_DIR_STATEMENT;
    } else if(strcmp(command, "touch") == 0) {
        return TOUCH_FILE_STATEMENT;
    } else if(strcmp(command, "rm") == 0) {
        return DELETE_STATEMENT;
    } else if(strcmp(command, "cp") == 0) {
        return COPY_STATEMENT;
    } else if(strcmp(command, "mv") == 0) {
        return RENAME_FILE_STATEMENT;
    } else if(strcmp(command, "help") == 0) {
        return HELP_STATEMENT;
    } else {
        return UNRECOGNISED_COMMAND;
    }
}

