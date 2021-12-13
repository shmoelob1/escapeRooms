#ifndef INC_3_2_PARSER_H
#define INC_3_2_PARSER_H

#include <stdbool.h>
#include "stdio.h"
#include "EscapeTechnion.h"

#define CHUNK_SIZE 256
#define COMMAND_AMOUNT 10


void fileToCommand(EscapeTechnion *system, FILE *input, FILE *output);

MtmErrorCode compareCommand(EscapeTechnion *system, FILE *output, char *line);

MtmErrorCode lineToFunction(EscapeTechnion *system, FILE *output, int i, char *line);

#endif //INC_3_2_PARSER_H
