#ifndef INC_ORDERS_H
#define INC_ORDERS_H

#include "mtm_ex3.h"

typedef struct order_t *Order;

typedef enum OrderResult_t {
    ORDER_INVALID_PARAMETER,
    ORDER_NULL_PARAMETER,
    ORDER_EMAIL_ALREADY_EXISTS,
    ORDER_EMAIL_DOES_NOT_EXIST,
    ORDER_RESERVATION_EXISTS,
    ORDER_OUT_OF_MEMORY,
    ORDER_MAIL_ILLEGAL,
    ORDER_SUCCESS,
} OrderResult;

/**
 * orderCreate : Allocates and create an order of a certain escape room
 *
 * @param order - A pointer to create the order to
 * @param email - The email of the escaper that made the order
 * @param faculty - The faculty which the room
 * @param id - The Room id
 * @param day - How many are left to visit the escape room
 * @param time - What is the time of the reservation
 * @param num_ppl - The number of people that will arrive
 * @return
 * ORDER_MAIL_ILLEAGEL - if escaper email is illeagel - does not contain '@'
 * ORDER_INVALID_PARAMETER - if one of the following parameters are invalid:
 *                           faculty does not exist
 *                           room id is negative
 *                           day is negative
 *                           time<0 || time>23
 *                           num_ppl<=0
 * ORDER_OUT_OF_MEMORY - if memory allocation failed
 * ORDER_NULL_PARAMETER - if email is null
 * ORDER_SUCCESS - Create succeed
 */
OrderResult orderCreate(Order *order, char *email, TechnionFaculty faculty, int id, int day, int time, int num_ppl);

/**
 * orderDestroy : Deallocates an order.
 *              if order is null, nothing happens
 *
 * @param order - The order to destroy
 * @return
 * ORDER_SUCCESS - always
 */
OrderResult orderDestroy(Order order);

/**
 * orderCopy : Creates a copy of an existing order
 *
 * @param destination - A destination to copy the order to
 * @param source - The Target to copy from
 * @return
 * ORDER_OUT_OF_MEMORY - if memory allocation failed
 * ORDER_SUCCESS if copy succeed
 * the assumption is that the source values are legal.
 * if not the return value will be according to 'orderCreate'
 */
OrderResult orderCopy(Order *destination, Order source);

/**
 * orderGetEmail : Return a copy of a certain order email
 *
 * @param order - A pointer to a order to extract her email
 * @param email - A pointer to return a copy of the escaper email
 * @return
 * ORDER_NULL_PARAMETER - if email is null
 * ORDER_OUT_OF_MEMORY - if the allocation of email fails
 * ORDER_SUCCESS - otherwise
 */
OrderResult orderGetEmail(Order order, char **email);

/**
 * orderGetFaculty : Return the faculty of the room from the order
 *
 * @param order - A pointer to the order target to extract the faculty
 * @param faculty - A pointer to return the faculty of the target
 * @return
 * ESCAPER_NULL_PARAMETER - if email is null
 * ESCAPER_SUCCESS - otherwise
 */
TechnionFaculty orderGetFaculty(Order order);

/**
 * orderNextDay : Updates the field of how many days are left for the reservation
 *
 * @param order - A pointer to the order Target
 * @return
 * ORDER_INVALID_PARAMETER - if the order is for today
 */
OrderResult orderNextDay(Order order);

/**
 * orderCompareTime : Compares 2 orders and returns which one comes first
 *
 * @param order1 - First order to compare
 * @param order2 - Second order to compare
 * @return
 * -1 - if order1 is first
 * 1 - if order2 is first
 * 0 - if order1 & order2 are for the same time
 *
 */
int orderCompareTime(Order order1, Order order2);

/**
 * orderGetDay : How many days are left for the order
 *
 * @param order - The order to extract the information
 * @return
 * The number of days are left for the order
 */
int orderGetDay(Order order);

/**
 * orderGetTimeOfDay : What time in the day is the reservation
 *
 * @param order - The order to extract the information
 * @return
 * The time of the order
 */
int orderGetTimeOfDay(Order order);

/**
 * orderGetNumEscapers : How many visitors are coming in the order
 *
 * @param order - The order to extract the information
 * @return
 * The number of visitors.
 */
int orderGetNumEscapers(Order order);

/**
 * orderGetId : What is the escape room ID
 *
 * @param order - The order to extract the information
 * @return
 * The escape room ID
 */
int orderGetId(Order order);


#endif //INC_ORDERS_H
