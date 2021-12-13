#include "parser.h"
#include <stdlib.h>

#define CHUNK_SIZE 256
#define COMMAND_AMOUNT 10

static char *clearFirstSpaces(char *line);

static bool isContainHashtag(char *line);

static char *concat(const char *s1, const char *s2);

static void seperateNumbers(char *s, int *num1, int *num2);

static MtmErrorCode escapeTechnionToMtmError(EscapeTechnionResult result);

void fileToCommand(EscapeTechnion *system, FILE *input, FILE *output) {
    assert(system != NULL && input != NULL && output != NULL);
    MtmErrorCode error;
    char line[CHUNK_SIZE];
    while (fgets(line, CHUNK_SIZE, input) != NULL) {
        strtok(line, "\n");
        clearFirstSpaces(line);
        if (*line != '\0' && *line != '\n' && !isContainHashtag(line)) {
            error = compareCommand(system, output, line);
            if (error != MTM_SUCCESS) {
                mtmPrintErrorMessage(stderr, error);
                if (error == MTM_OUT_OF_MEMORY) {
                    return;
                }
            }
        }
        continue;
    }
    return;
}

static char *concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    if (!result) return NULL;
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

MtmErrorCode compareCommand(EscapeTechnion *system, FILE *output, char *line) {
    assert(system != NULL);
    MtmErrorCode error = MTM_SUCCESS;
    char adt[CHUNK_SIZE];
    char command[CHUNK_SIZE];
    char dict_command[COMMAND_AMOUNT][CHUNK_SIZE] = {{"companyadd"},
                                                     {"roomadd"},
                                                     {"escaperadd"},
                                                     {"escaperorder"},
                                                     {"reportday"},
                                                     {"escaperrecommend"},
                                                     {"reportbest"},
                                                     {"escaperremove"},
                                                     {"roomremove"},
                                                     {"companyremove"}};
    if (sscanf(line, "%s" "%s", adt, command) == 2) {
        char *unite;
        unite = concat(adt, command);
        for (int i = 0; i < COMMAND_AMOUNT; i++) {
            if (!strcmp(&dict_command[i][0], unite)) {
                error = lineToFunction(system, output, i, line);
                break;
            }
        }
        free(unite);
    }
    return error;
}

MtmErrorCode lineToFunction(EscapeTechnion *system, FILE *output, int i, char *line) {
    assert(system != NULL && output != NULL && i >= 0 && i <= 9);
    int faculty = 0, id = 0, price = 0, num_ppl = 0, skill_level = 0, difficulty = 0;
    char email[CHUNK_SIZE], working_hrs[CHUNK_SIZE], time[CHUNK_SIZE], adt[CHUNK_SIZE], command[CHUNK_SIZE];
    MtmErrorCode error = MTM_SUCCESS;
    switch (i) {
        case 0:
            sscanf(line, "%s" "%s" "%s" "%d", adt, command, email, &faculty);
            error = escapeTechnionToMtmError(escapeTechnionAddCompany(*system, email, (TechnionFaculty) faculty));
            break;
        case 1:
            sscanf(line, "%s" "%s" "%s" "%d" "%d" "%d" "%s" "%d", adt, command, email,
                   &id, &price, &num_ppl, working_hrs, &difficulty);
            int open_time, close_time;
            seperateNumbers(working_hrs, &open_time, &close_time);
            error = escapeTechnionToMtmError(escapeTechnionAddRoom(*system,
                                                                   email, id, price, num_ppl, difficulty, open_time,
                                                                   close_time));
            break;
        case 2:
            sscanf(line, "%s" "%s" "%s" "%d" "%d", adt, command, email, &faculty, &skill_level);
            error = escapeTechnionToMtmError(escapeTechnionAddEscaper(*system,
                                                                      email, (TechnionFaculty) faculty, skill_level));
            break;
        case 3:
            sscanf(line, "%s" "%s" "%s" "%d" "%d" "%s" "%d", adt, command, email, &faculty, &id, time, &num_ppl);
            int days, hour;
            seperateNumbers(time, &days, &hour);
            error = escapeTechnionToMtmError(escapeTechnionAddOrder(*system, email,
                                                                    (TechnionFaculty) faculty, id, days, hour,
                                                                    num_ppl));
            break;
        case 4:
            error = escapeTechnionToMtmError(escapeTechnionReportDay(*system, output));
            break;
        case 5:
            sscanf(line, "%s" "%s" "%s" "%d", adt, command, email, &num_ppl);
            error = escapeTechnionToMtmError(escapeTechnionRecommendRoom(*system, email, num_ppl));
            break;
        case 6:
            escapeTechnionReportBest(*system, output);
            break;
        case 7:
            sscanf(line, "%s" "%s" "%s", adt, command, email);
            error = escapeTechnionToMtmError(escapeTechnionRemoveEscaper(*system, email));
            break;
        case 8:
            sscanf(line, "%s" "%s" "%d" "%d", adt, command, &faculty, &id);
            error = escapeTechnionToMtmError(escapeTechnionRemoveRoom(*system, (TechnionFaculty) faculty, id));
            break;
        case 9:
            sscanf(line, "%s" "%s" "%s", adt, command, email);
            error = escapeTechnionToMtmError(escapeTechnionRemoveCompany(*system, email));
            break;
        default:;
    }
    return error;
}

static char *clearFirstSpaces(char *line) {
    assert(line != NULL);
    while (*line != ' ' && *line !='\0') {
        line++;
    }
    return line;
}

static bool isContainHashtag(char *line) {
    if (*line == '#') return 1;
    return 0;
}

static void seperateNumbers(char *s, int *num1, int *num2) {
    char s1[3];
    int i = 0;
    while (s[i] != '-') {
        s1[i] = s[i];
        i++;
    }
    s1[i] = '\0';
    *num1 = atol(s1);
    *num2 = atol((s + i + 1));
    return;
}

static MtmErrorCode escapeTechnionToMtmError(EscapeTechnionResult result) {
    switch (result) {
        case ESCAPETECHNION_CLIENT_IN_ROOM:
            return MTM_CLIENT_IN_ROOM;
        case ESCAPETECHNION_NO_ROOMS_AVAILABLE:
            return MTM_ROOM_NOT_AVAILABLE;
        case ESCAPETECHNION_ROOM_NOT_AVAILABLE:
            return MTM_ROOM_NOT_AVAILABLE;
        case ESCAPETECHNION_ID_DOES_NOT_EXIST:
            return MTM_ID_DOES_NOT_EXIST;
        case ESCAPETECHNION_OUT_OF_MEMORY:
            return MTM_OUT_OF_MEMORY;
        case ESCAPETECHNION_NULL_PARAMETER:
            return MTM_NULL_PARAMETER;
        case ESCAPETECHNION_INVALID_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case ESCAPETECHNION_SUCCESS:
            return MTM_SUCCESS;
        case ESCAPETECHNION_ID_ALREADY_EXIST:
            return MTM_ID_ALREADY_EXIST;
        case ESCAPETECHNION_EMAIL_ALREADY_EXISTS:
            return MTM_EMAIL_ALREADY_EXISTS;
        case ESCAPETECHNION_RESERVATION_EXISTS:
            return MTM_RESERVATION_EXISTS;
        case ESCAPETECHNION_CLIENT_EMAIL_DOES_NOT_EXIST:
            return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
        case ESCAPETECHNION_COMPANY_EMAIL_DOES_NOT_EXIST:
            return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    return MTM_SUCCESS;
}