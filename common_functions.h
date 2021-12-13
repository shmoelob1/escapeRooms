
#include <stdbool.h>
#include <string.h>
#include "mtm_ex3.h"
#include "assert.h"
#include "malloc.h"

#ifndef INC_COMMON_FUNCTIONS_H
#define INC_COMMON_FUNCTIONS_H
/**
 * isLegalEmail : Checks if email is legal
 * @param email - Email to check
 * @return
 * true if email is legal - contains '@'
 * false email illegal
 */
bool isLegalEmail(char *email);
/**
 * isLegalFaculty : Checks if faculty exist
 * @param faculty - Faculty to check
 * @return
 * true if exist
 * false if doesnt exist
 */
bool isLegalFaculty(TechnionFaculty faculty);
/**
 * copyString: Allocates and copy string
 * @param destination - The destination to copy the string to
 * @param source - The string to copy
 * @return
 * true - if copy succeed
 * false if memory allocation failed
 */
bool copyString(char **destination, char *source);
/**
 * isLegalSkill : Checks is skill is legal
 * @param skill - Skill to check
 * @return
 * true - if skill is in legal range (1-10)
 * false - if not
 */
bool isLegalSkill(int skill);
/**
 * isLegalTime : Checks if opening time and closing time of room is legal
 * @param open - opening time
 * @param close - closing time
 * @return
 * true - if legal : 24>open>=0 && 24>=close>0 && open<close
 * false - othewise
 */
bool isLegalTime(int open, int close);

#endif //INC_COMMON_FUNCTIONS_H
