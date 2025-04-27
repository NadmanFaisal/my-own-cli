#ifndef STATEMENT_H
#define STATEMENT_H

#include <stdio.h>
#include <stdlib.h>

#include "InputBuffer.h"

/**
 * Enum to represent different types of supported statements/commands.
 * - LIST_STATEMENT: Represents the 'ls' command, used to list directory contents.
 * - UNRECOGNISED_COMMAND: Represents any command that is not recognized by the parser.
 * - CHANGE_DIR_STATEMENT: Represents the 'cd' command, used to change directory. 
 * - MAKE_DIR_STATEMENT: Represends the 'mkdir' command used to make a directory. 
 * - RENAME_FILE_STATEMENT: Represents the 'mv' command used to rename a file
 * - TOUCH_FILE_STATEMENT: Represents the 'touch' command used to create a file
 * - COPY_STATEMENT: Represents the 'cp' command to copy files to the current directory.
 * - EXIT_STATEMENT: Represends the 'exit' command used to exit the bash
 */
typedef enum {
    LIST_STATEMENT,
    UNRECOGNISED_COMMAND,
    CHANGE_DIR_STATEMENT,
    MAKE_DIR_STATEMENT,
    TOUCH_FILE_STATEMENT,
    RENAME_FILE_STATEMENT,
    COPY_STATEMENT,
    DELETE_STATEMENT,
    EXIT_STATEMENT
} StatementType;

/**
 * Parses the input from the InputBuffer and determines the type of statement.
 * - Recognizes specific commands (e.g., 'ls') and returns the corresponding StatementType.
 * - Returns UNRECOGNISED_COMMAND if the input does not match any known command.
 *
 * @param buffer Pointer to the InputBuffer containing the user input.
 * @return The determined StatementType based on the input.
 */
StatementType execute_statement(InputBuffer *buffer);

#endif