#ifndef INC_ESCAPERS_H
#define INC_ESCAPERS_H

#include "common_functions.h"
#include "assert.h"
#include "malloc.h"

typedef struct escaper_t *Escaper;
typedef enum {
    ESCAPER_OUT_OF_MEMORY,
    ESCAPER_NULL_PARAMETER,
    ESCAPER_INVALID_PARAMETER,
    ESCAPER_SUCCESS,
} EscaperResult;

/**
 * escaperCreate : Allocate & create a new company adt
 *
 * @param escaper - A pointer to the escaper to create to
 * @param email - The email of the escaper
 * @param faculty - The faculty of the escaper
 * @param skill - The skill of the escaper - number between 1-10
 * @return
 * ESCAPER_NULL_PARAMETER - if email is null
 * ESCAPER_INVALID_PARAMETER - if skill is not in legal range or email does not contain the char '@'
 * or faculty does not exist
 * ESCAPER_OUT_OF_MEMORY - if the allocation of escaper or email fails
 * ESCAPER_SUCCESS - if create succeed
 */
EscaperResult escaperCreate(Escaper *escaper, char *email, TechnionFaculty faculty, int skill);

/**
 * escaperDestroy : Deallocates escaper and his values
 *
 * @param escaper - Target to destroy
 * @return
 * ESCAPER_SUCCESS - always
 */
EscaperResult escaperDestroy(Escaper escaper);

/**
 * escaperCopy : Creates a copy of an existing escaper
 *
 * @param destination - A destination to copy the escaper to
 * @param source - The Target to copy from
 * @return
 * ESCAPER_OUT_OF_MEMORY - if memory allocation failed
 * ESCAPER_SUCCESS if copy succeed
 * the assumption is that the source values are legal.
 * if not the return value will be according to 'escaperCreate'
 */
EscaperResult escaperCopy(Escaper *destination, Escaper source);

/**
 * escaperGetEmail : Return a copy of a certain escaper email
 *
 * @param escaper - A pointer to a escaper to extract her email
 * @param email - a pointer to return a copy of the escaper email
 * @return
 * COMPANY_OUT_OF_MEMORY - if the allocation of email fails
 * COMPANY_SUCCESS - otherwise
 */
EscaperResult escaperGetEmail(Escaper escaper, char **email);

/**
 * escaperGetFaculty : Return the faculty of a certain escaper
 *
 * @param escaper - a pointer to the escaper target to extract the faculty
 * @param faculty - a pointer to return the faculty of the target
 * @return
 * ESCAPER_NULL_PARAMETER - if email is null
 * ESCAPER_SUCCESS - always
 */
EscaperResult escaperGetFaculty(Escaper escaper, TechnionFaculty *faculty);

/**
 * escaperGetSkill : Return the skill of a certain escaper
 *
 * @param escaper - a pointer to the escaper target to extract his skill
 * @param skill - a pointer to return the skill of the target
 * @return
 * ESCAPER_NULL_PARAMETER - if skill is null
 * ESCAPER_SUCCESS - otherwise
 */
EscaperResult escaperGetSkill(Escaper escaper, int *skill);

#endif //INC_ESCAPERS_H
