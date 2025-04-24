#ifndef BASHCOMMANDS_H
#define BASHCOMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "InputBuffer.h"

/**
 * Enum to represent the status of a directory path confirmation.
 * - PATH_RECOGNISED: The directory path exists and can be opened.
 * - PATH_UNRECOGNISED: The directory path does not exist or cannot be opened.
 */
typedef enum {
    PATH_RECOGNISED,
    PATH_UNRECOGNISED
} PathConfirmation;


/**
 * Attempts to open a directory at the given path.
 *
 * @param path   The path to the directory (if NULL, opens the current directory).
 * @param status Output parameter that will be set to PATH_RECOGNISED if the directory
 *               was successfully opened, or PATH_UNRECOGNISED if it could not be opened.
 * @return       A pointer to the opened DIR structure, or NULL if opening failed.
 */
DIR *open_path(char *path, PathConfirmation *status);

/**
 * Lists the contents of a directory based on the input buffer.
 * - If the buffer contains only "ls", lists the current directory.
 * - If the buffer contains "ls <path>", lists the contents of the specified directory.
 * 
 * @param buffer Pointer to the InputBuffer containing the command and optional path.
 */
void list_dir(InputBuffer *buffer);

#endif