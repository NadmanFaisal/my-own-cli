#ifndef BASHCOMMANDS_H
#define BASHCOMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

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
DIR *verify_path(char *path, PathConfirmation *status);

/**
 * Lists the contents of a directory based on the input buffer.
 * - If the buffer contains only "ls", lists the current directory.
 * - If the buffer contains "ls <path>", lists the contents of the specified directory.
 * 
 * @param buffer Pointer to the InputBuffer containing the command and optional path.
 */
void list_dir(InputBuffer *buffer);

/**
 * Changes the current working directory of the process.
 * 
 * This function parses the provided InputBuffer to extract the target directory path
 * and attempts to change the current working directory to that path.
 * - If no path is provided, it outputs an error message.
 * - If the directory does not exist or cannot be accessed, it outputs an error message.
 * - On success, it prints the new current working directory.
 * 
 * @param buffer Pointer to the InputBuffer containing the user input (e.g., "cd <path>").
 */
void change_dir(InputBuffer *buffer);

/**
 * Creates a new directory at the specified path.
 * 
 * This function parses the provided InputBuffer to extract the target directory name/path
 * and attempts to create a directory at that location with standard permissions.
 * - If no folder name is provided, it outputs an error message.
 * 
 * @param buffer Pointer to the InputBuffer containing the user input (e.g., "mkdir <folder>").
 */
void make_dir(InputBuffer *buffer);

#endif