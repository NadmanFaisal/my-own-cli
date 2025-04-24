#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

#include "Constants.h"

/**
 * Structure to represent an input buffer.
 *  - buffer: a character array to store the input string.
 *  - buffer_length: the length of the stored string (excluding null terminator).
*/
typedef struct {
    char buffer[MAX_CHARS];     // buffer to hold the input string
    int buffer_length;          // Length of the input buffer
} InputBuffer;

/**
 * Clears any remaining characters in the input buffer (stdin).
 * Useful for removing unwanted characters after reading input.
*/
void clear_buffer();

/**
 * Allocates memory for a new InputBuffer structure.
 * Initializes buffer_length to 0.
 *
 * @return A pointer to the newly allocated InputBuffer.
 */
InputBuffer *create_buffer();

/**
 * Reads input from standard input (stdin) into the provided InputBuffer.
 * Removes any trailing newline character and updates buffer_length accordingly.
 *
 * @param buffer Pointer to the InputBuffer where input will be stored.
 */
void read_buffer(InputBuffer *buffer);

/**
 * Prints the contents of the provided InputBuffer to standard output (stdout).
 * Prints each character one by one, followed by a newline.
 *
 * @param buffer Pointer to the InputBuffer to be printed.
 */
void print_buffer(InputBuffer *buffer);

/**
 * Frees the memory allocated for the provided InputBuffer.
 *
 * @param buffer Pointer to the InputBuffer to be freed.
 */
void free_buffer(InputBuffer *buffer);

#endif