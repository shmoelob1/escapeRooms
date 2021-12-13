#include <malloc.h>
#include <assert.h>
#include "order.h"
#include "common_functions.h"

struct order_t {
    char *email;
    TechnionFaculty faculty;
    int id;
    int time;
    int days;
    int num_ppl;
};

OrderResult orderCreate(Order *order, char *email, TechnionFaculty faculty, int id, int day, int time, int num_ppl) {
    assert(order != NULL);
    if (email==NULL){
        return ORDER_NULL_PARAMETER;
    }
    if (!isLegalEmail(email)) {
        return ORDER_MAIL_ILLEGAL;
    }
    if (!isLegalFaculty(faculty) || id<=0 || day<0 || time<0 || time >23 || num_ppl<=0) {
        return ORDER_INVALID_PARAMETER;
    }
    Order tmp = malloc(sizeof(struct order_t));
    if (!tmp) {
        return ORDER_OUT_OF_MEMORY;
    }
    if (!copyString(&tmp->email, email)) {
        free(tmp);
        return ORDER_OUT_OF_MEMORY;
    }
    tmp->faculty = faculty;
    tmp->id = id;
    tmp->days = day;
    tmp->time = time;
    tmp->num_ppl = num_ppl;
    *order = tmp;
    return ORDER_SUCCESS;
}

OrderResult orderDestroy(Order order) {
    if (order != NULL) {
        free(order->email);
        free(order);
    }
    return ORDER_SUCCESS;
}

OrderResult orderCopy(Order *destination, Order source) {
    assert(source != NULL && destination != NULL);
    return orderCreate(destination, source->email, source->faculty, source->id, source->days, source->time,
                       source->num_ppl);
}

OrderResult orderGetEmail(Order order, char **email) {
    assert(order != NULL);
    if (email == NULL) {
        return ORDER_NULL_PARAMETER;
    }
    assert(isLegalEmail(order->email));
    if (!copyString(email, order->email)) {
        return ORDER_OUT_OF_MEMORY;
    }
    return ORDER_SUCCESS;
}

TechnionFaculty orderGetFaculty(Order order) {
    assert(order != NULL);
    return order->faculty;
}

OrderResult orderNextDay(Order order) {
    assert(order != NULL);
    if (order->days <= 0) {
        return ORDER_INVALID_PARAMETER;
    }
    order->days--;
    return ORDER_SUCCESS;
}

int orderCompareTime(Order order1, Order order2) {
    assert(order1 != NULL && order2 != NULL);
    if (order1->days < order2->days) {
        return -1;
    } else if (order1->days > order2->days) {
        return 1;
    }
    if (order1->time < order2->time) {
        return -1;
    } else if (order1->time > order2->time) {
        return 1;
    }
    return 0;
}

int orderGetDay(Order order) {
    assert (order != NULL);
    return order->days;
}

int orderGetTimeOfDay(Order order) {
    assert (order != NULL);
    return order->time;
}

int orderGetNumEscapers(Order order) {
    assert (order != NULL);
    return order->num_ppl;
}

int orderGetId(Order order) {
    assert(order != NULL);
    return order->id;
}