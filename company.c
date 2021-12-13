#include "company.h"
#include <assert.h>

struct company_t {
    char *email;
    int rooms_num;
    TechnionFaculty faculty;
};

CompanyResult companyCreate(Company *company, char *email, TechnionFaculty faculty) {
    assert(company != NULL);
    if (!email) {
        return COMPANY_NULL_PARAMETER;
    }
    if (!isLegalEmail(email)) {
        return COMPANY_MAIL_ILLEGAL;
    }
    if (!isLegalFaculty(faculty)) {
        return COMPANY_INVALID_PARAMETER;
    }
    struct company_t *tmp = malloc(sizeof(*tmp));
    if (!tmp) {
        return COMPANY_OUT_OF_MEMORY;
    }
    if (!copyString(&tmp->email, email)) {
        return COMPANY_OUT_OF_MEMORY;
    }
    tmp->rooms_num = 0;
    tmp->faculty = faculty;
    *company = tmp;
    return COMPANY_SUCCESS;
}

CompanyResult companyDestroy(Company company) {
    if (company != NULL) {
        free(company->email);
        free(company);
    }
    return COMPANY_SUCCESS;
}

CompanyResult companyCopy(Company *destination, Company source) {
    assert(source != NULL && destination != NULL);
    Company tmp;
    CompanyResult result = companyCreate(&tmp, source->email, source->faculty);
    if (result != COMPANY_SUCCESS) {
        return result;
    }
    tmp->rooms_num = source->rooms_num;
    *destination = tmp;
    return COMPANY_SUCCESS;
}

CompanyResult companyAddRoom(Company company) {
    assert(company != NULL);
    company->rooms_num++;
    return COMPANY_SUCCESS;
}

CompanyResult companyRemoveRoom(Company company) {
    assert(company != NULL);
    if (company->rooms_num==0){
        return COMPANY_INVALID_PARAMETER;
    }
    company->rooms_num--;
    return COMPANY_SUCCESS;
}

TechnionFaculty companyGetFaculty(Company company) {
    assert(company != NULL);
    return company->faculty;
}

CompanyResult companyGetEmail(Company company, char **email) {
    assert(company != NULL);
    if (email == NULL){
        return COMPANY_NULL_PARAMETER;
    }
    assert(isLegalEmail(company->email));
    if (!copyString(email, company->email)) {
        return COMPANY_OUT_OF_MEMORY;
    }
    return COMPANY_SUCCESS;

}

