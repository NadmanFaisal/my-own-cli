#ifndef BASHCOMMANDS_H
#define BASHCOMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

/**
 * Creates a new file or updates the timestamp of an existing file.
 * 
 * This function parses the provided InputBuffer to extract the file name
 * and uses the `open()` system call to create the file if it doesn't exist.
 * If the file exists, it simply opens and closes it (updating the access/modification time).
 * 
 * - If no file name is provided, the function performs no action.
 * - If the file cannot be created (e.g., due to permission issues), an error message is printed.
 * 
 * @param buffer Pointer to the InputBuffer containing the user input (e.g., "touch <file>").
 */
void touch_file(InputBuffer *buffer);

/**
 * Recursively removes a file or directory at the specified path.
 * 
 * - If the path points to a regular file, the file is deleted.
 * - If the path points to a directory, it recursively removes all files and subdirectories,
 *   and then deletes the directory itself.
 * - Prints error messages if any file or directory cannot be removed.
 * 
 * @param path A string representing the absolute or relative path to the file or directory.
 * @return 0 on success, -1 on failure.
 */
int remove_file_dir_path(const char *path);

/**
 * Parses the user input buffer to extract the path for removal and triggers the deletion process.
 * 
 * - Extracts the target path from the InputBuffer (expects a command like "rm <path>").
 * - Calls `remove_file_dir_path()` to recursively delete the specified file or directory.
 * - Prints an error if no path is provided.
 * 
 * @param buffer Pointer to the InputBuffer containing the user input.
 * @return 0 on success, -1 on failure.
 */
int remove_file_dir(InputBuffer *buffer);

/**
 * Renames a file or directory based on user input.
 * 
 * - Parses the original and new names from the provided InputBuffer.
 * - Checks if the original file or directory exists.
 * - Ensures the new name does not already exist to prevent overwriting.
 * - Uses the `rename()` system call to rename the file or directory.
 * - Prints appropriate error messages if any operation fails.
 * 
 * @param buffer Pointer to the InputBuffer containing the rename command and arguments.
 *               Expects the format: "rename <original_name> <new_name>".
 * 
 * @return 0 on success, -1 on failure (e.g., missing arguments, file not found, or rename error).
 */
int rename_file_or_dir(InputBuffer *buffer);

/**
 * Copies a file from the source (original name) to the destination (new file name) 
 * within the current working directory.
 * 
 * - Parses the source and destination file names from the InputBuffer.
 * - Opens the source file for reading and creates the destination file for writing.
 * - Checks if the destination file already exists to prevent overwriting.
 * - Copies the content of the source file to the destination file, character by character.
 * - Closes both files after the operation is complete.
 * 
 * @param buffer Pointer to the InputBuffer containing the copy command and arguments.
 *               Expects the format: "cp <source_file> <destination_file>".
 * 
 * @return 0 on success, -1 on failure (e.g., missing arguments, file not found, file already exists, or copy error).
 */
int copy_to_curr_dir(InputBuffer *buffer);

void print_help();
#endif