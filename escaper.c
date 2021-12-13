#include "escaper.h"

struct escaper_t {
    char *email;
    TechnionFaculty faculty;
    int skill;
};

EscaperResult escaperCreate(Escaper *escaper, char *email, TechnionFaculty faculty, int skill) {
    assert(escaper != NULL);
    if (email == NULL) {
        return ESCAPER_NULL_PARAMETER;
    }
    struct escaper_t *tmp = malloc(sizeof(*tmp));
    if (!tmp) {
        return ESCAPER_OUT_OF_MEMORY;
    }
    if (isLegalSkill(skill) == false || isLegalFaculty(faculty) == false || isLegalEmail(email) == false) {
        return ESCAPER_INVALID_PARAMETER;
    }
    if (copyString(&tmp->email, email) == false) {
        return ESCAPER_OUT_OF_MEMORY;
    }
    tmp->faculty = faculty;
    tmp->skill = skill;
    *escaper = tmp;
    return ESCAPER_SUCCESS;
}

EscaperResult escaperDestroy(Escaper escaper) {
    if (escaper != NULL) {
        free(escaper->email);
        free(escaper);
    }
    return ESCAPER_SUCCESS;
}

EscaperResult escaperCopy(Escaper *destination, Escaper source) {
    assert(source != NULL && destination != NULL);
    return escaperCreate(destination, source->email, source->faculty, source->skill);
}

EscaperResult escaperGetEmail(Escaper escaper, char **email) {
    assert(escaper != NULL && email != NULL);
    char *tmp = malloc(strlen(escaper->email) + 1);
    if (!tmp) {
        return ESCAPER_OUT_OF_MEMORY;
    }
    strcpy(tmp, escaper->email);
    *email = tmp;
    return ESCAPER_SUCCESS;
}

EscaperResult escaperGetFaculty(Escaper escaper, TechnionFaculty *faculty) {
    assert(escaper != NULL);
    if (faculty == NULL) {
        return ESCAPER_NULL_PARAMETER;
    }
    *faculty = escaper->faculty;
    return ESCAPER_SUCCESS;
}

EscaperResult escaperGetSkill(Escaper escaper, int *skill) {
    assert(escaper != NULL);
    if (skill == NULL){
        return ESCAPER_NULL_PARAMETER;
    }
    *skill = escaper->skill;
    return ESCAPER_SUCCESS;
}
