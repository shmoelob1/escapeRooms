#include "common_functions.h"

bool isLegalEmail(char *email) {
    if (email == NULL) return false;
    int length = (int) strlen(email);
    int count = 0;
    for (int i = 0; i <= length; i++) {
        if (email[i] == '@') {
            if (++count >= 2) {
                return false;
            }
        }
    }
    if (count == 0) {
        return false;
    }
    return true;
}

bool isLegalFaculty(TechnionFaculty faculty) {
    if ((int) faculty >= 0 && (int) faculty < (int) UNKNOWN)
        return true;
    return false;
}

bool isLegalSkill(int skill) {
    if (skill >= 1 && skill <= 10) {
        return true;
    }
    return false;
}

bool copyString(char **destination, char *source) {
    assert(destination != NULL && source != NULL);
    char *tmp = malloc(strlen(source) + 1);
    if (!tmp) {
        return false;
    }
    strcpy(tmp, source);
    *destination = tmp;
    return true;
}

bool isLegalTime(int open, int close) {
    if (open < 0 || open > 24 || close < 0 || close > 24 || open >= close) {
        return false;
    }
    return true;
}