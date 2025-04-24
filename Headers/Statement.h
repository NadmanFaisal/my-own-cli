#ifndef STATEMENT_H
#define STATEMENT_H

#include <stdio.h>
#include <stdlib.h>

#include "InputBuffer.h"


typedef enum {
    LIST_STATEMENT,
    UNRECOGNISED_COMMAND
} StatementType;

StatementType execute_statement(InputBuffer *buffer);

#endif