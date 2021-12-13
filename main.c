#include "EscapeTechnion.h"
#include "parser.h"

static bool InitFiles(int argc, char **argv, FILE **input, FILE **output);

int main(int argc, char **argv) {
    if (argc != 5 && argc != 3 && argc != 1) {
        return 0;
    }
    FILE *input = NULL;
    FILE *output = NULL;
    //Initialize input&output streams
    if (!InitFiles(argc, argv, &input, &output)) {
        return 0;
    }
    EscapeTechnion system = NULL;
    if (!systemCreate(&system)) {
        return 0;
    }
    fileToCommand(&system, input, output);
    //Close program
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }
    systemDestroy(system);
    return 0;
}


static bool InitFiles(int argc, char **argv, FILE **input, FILE **output) {
    char *in = "-i";
    char *out = "-o";
    if (argc == 1) {
        *input = stdin;
        *output = stdout;
    } else if (argc == 3) {
        if (strcmp(argv[1], in) == 0) { //input - file from user. output - stdout
            *input = fopen(argv[2], "r");
            *output = stdout;
        } else if (strcmp(argv[1], out) == 0) { //input - stdin. output - file from user
            *output = fopen(argv[2], "w");
            *input = stdin;
        } else {
            mtmPrintErrorMessage(stderr, MTM_INVALID_COMMAND_LINE_PARAMETERS);
            return false;
        }
        if (!*input || !*output) {
            mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
            return false;
        }
    } else if (argc == 5) {
        if (strcmp(argv[1], in) == 0 && strcmp(argv[3], out) == 0) { // input&output files from user
            *input = fopen(argv[2], "r");
            *output = fopen(argv[4], "w");
        } else if (strcmp(argv[3], in) == 0 && strcmp(argv[1], out) == 0) { // input&output files from user
            *input = fopen(argv[4], "r");
            *output = fopen(argv[2], "w");
        } else {
            mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
            return false;
        }
        if (!*input && !*output) { //file open failed for input&output
            mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
            return false;
        } else if (!*input) {
            fclose(*output);
            mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE); // file open failed for input
            return false;
        } else if (!*output) {
            fclose(*input);
            mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE); // file open failed for output
            return false;
        }
    }
    return true;
}
