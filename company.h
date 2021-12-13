#ifndef INC_3_2_COMPANY_H
#define INC_3_2_COMPANY_H

#include "common_functions.h"

/** Type for defining the list */
typedef struct company_t *Company;

/** Type used for returning error codes from list functions */
typedef enum CompanyResult_t {
    COMPANY_INVALID_PARAMETER,
    COMPANY_NULL_PARAMETER,
    COMPANY_EMAIL_ALREADY_EXISTS,
    COMPANY_EMAIL_DOES_NOT_EXIST,
    COMPANY_RESERVATION_EXISTS,
    COMPANY_OUT_OF_MEMORY,
    COMPANY_MAIL_ILLEGAL,
    COMPANY_SUCCESS,
} CompanyResult;

/**
 * companyCreate : Allocate & create a new company adt
 *
 * @param company
 * A pointer to the company which to create
 * @param email - string of the company email
 * @param faculty - The enum of the company faculty
 * @return
 * COMPANY_NULL_PARAMETER - if email is null
 * COMPANY_MAIL_ILLEAGEL - if the email does not contain the char '@'
 * COMPANY_INVALID_PARAMETER - if the faculty is not in the list of faculties
 * COMPANY_OUT_OF_MEMORY - if the memory allocation of company_t struct or the email copy fails
 * COMPANY_SUCCESS - if the create succeed
 */
CompanyResult companyCreate(Company *company, char *email, TechnionFaculty faculty);

/**
 * CompanyDestroy : Free's all company elements inculding the company itself
 *
 * @param company - the company which we want to destroy
 *               if company is NULL then nothing happens
 * @return
 * COMPANY_SUCCESS - always.
 */
CompanyResult companyDestroy(Company company);

/**
 * companyCopy : Creates a copy of an exisiting company
 *
 * @param destination - A pointer to the copy
 * @param source - The source which is the copy from.
 * @return
 * COMPANY_OUT_OF_MEMORY - if the memory allocation of the copy fails
 * COMPANY_SUCCESS - if the copy succeed
 * the assumption is that the source values are legal.
 * if not the return value will be according to 'companyCreate'
 */
CompanyResult companyCopy(Company *destination, Company source);

/**
 * companyAddRoom : Increases the counter of room number in a certain company by 1
 *
 * @param company - A pointer to the company to increase the room counter in
 * @return
 * COMPANY_SUCCESS - always
 */
CompanyResult companyAddRoom(Company company);

/**
 * companyRemoveRoom : Decreases the room counter in a certain company by 1
 *
 * @param company - a pointer to the company to decrease the room counter
 * @return
 * COMPANY_INVALID_PARAMETER - if there are no rooms in the room
 * COMPANY_SUCCESS - remove succeed
 */
CompanyResult companyRemoveRoom(Company company);

/**
 * companyGetFaculty : Return the faculty of a certain company
 *
 * @param company - A pointer to the company to extract the faculty
 * @return - A enum of TechnionFaculty of the faculty which the company belongs to
 */
TechnionFaculty companyGetFaculty(Company company);

/**
 * companyGetEmail : Return a copy of a certain company email
 *
 * @param company - A pointer to a company to extract her email
 * @param email - A pointer to return a copy of the company email
 * @return
 * COMPANY_OUT_OF_MEMORY - if the allocation of email fails
 * COMPANY_SUCCESS - otherwise
 */
CompanyResult companyGetEmail(Company company, char **email);

#endif //INC_3_2_COMPANY_H
