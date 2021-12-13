
#ifndef INC_ESCAPETECHNION_H
#define INC_ESCAPETECHNION_H

#include "list.h"
#include "set.h"
#include "mtm_ex3.h"
#include "company.h"
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "escaper.h"
#include "room.h"
#include "order.h"

typedef struct escape_technion_t *EscapeTechnion;

typedef enum {
    ESCAPETECHNION_OUT_OF_MEMORY, // You should exit program after this error
    ESCAPETECHNION_NULL_PARAMETER,
    ESCAPETECHNION_INVALID_PARAMETER,
    ESCAPETECHNION_EMAIL_ALREADY_EXISTS,
    ESCAPETECHNION_COMPANY_EMAIL_DOES_NOT_EXIST,
    ESCAPETECHNION_CLIENT_EMAIL_DOES_NOT_EXIST,
    ESCAPETECHNION_ID_ALREADY_EXIST,
    ESCAPETECHNION_ID_DOES_NOT_EXIST,
    ESCAPETECHNION_CLIENT_IN_ROOM,
    ESCAPETECHNION_ROOM_NOT_AVAILABLE,
    ESCAPETECHNION_RESERVATION_EXISTS,
    ESCAPETECHNION_NO_ROOMS_AVAILABLE,
    ESCAPETECHNION_SUCCESS,
} EscapeTechnionResult;

/**
 * systemCreate : Allocates a new Escape Room System
 *
 * @param system - A pointer of EscapeTechnion ADT to create the system
 * @return
 * ESCAPETECHNION_OUT_OF_MEMORY - Allocation failed
 * ESCAPETECHNION_SUCCESS - Create succeed
 *
 */
EscapeTechnionResult systemCreate(EscapeTechnion *system);

/**
 * systemDestroy : Deallocates a system and it's components
 *
 * @param system - escape Room system to deallocate
 * @return
 * ESCAPETECHNION_SUCCESS - Always
 */
EscapeTechnionResult systemDestroy(EscapeTechnion system);

/**
 * escapeTechnionPrintOrder : Prints an Order
 *
 * @param system EscapeTechnion system of the Order
 * @param output - Output channel
 * @param order - Order to print
 * @param escaper_email - Email of the Escaper fro, the Order
 * @return
 * ESCAPETECHNION_INVALID_PARAMETER - Order does not exist
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPETECHNION_SUCCESS - Print successful
 */
EscapeTechnionResult escapeTechnionPrintOrder(EscapeTechnion system, FILE *output, Order order, char *escaper_email);

/**
 * escapeTechnionReportDay : Prints a summary of Today's activity
 *
 * @param system - Escape Room system to print from
 * @param output - Output Channel
 * @return
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPETECHNION_SUCCESS - Print succeed
 */
EscapeTechnionResult escapeTechnionReportDay(EscapeTechnion system, FILE *output);

/**
 * escapeTechnionReportBest : Prints the total of all Faculties &
 *                            summary of the Top 3 Faculties base & on revenues.
 *
 * @param system - Escape Room system
 * @param output - Output Channel
 */
void escapeTechnionReportBest(EscapeTechnion system, FILE *output);

/**
 * escapeTechnioAddCompany : Allocates escape Room Company and add's it to the system
 *
 * @param system - Escape Room system to add the Company
 * @param email - Email of the Company
 * @param faculty - Faculty the Company belongs to
 * @return
 * ESCAPE_TECHNION_NULL_PARAMETER - Email is null
 * ESCAPETECHNION_INVALID_PARAMETER - Email or Faculty are illegal
 * ESCAPE_TECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPE_TECHNION_SUCCESS - Add successful
 */
EscapeTechnionResult escapeTechnionAddCompany(EscapeTechnion system, char *email, TechnionFaculty faculty);

/**
 * escapeTechnionRemoveCompany : Remove Company from the system
 *
 * @param system - Escape Room system the Company belongs to
 * @param email - Email of the Company
 * @return
 * ESCAPETECHNION_NULL_PARAMETER - Email is null
 * ESCAPETECHNION_INVALID_PARAMETER - Email illegal
 * ESCAPE_TECHNION_SUCCESS - Remove successful
 * ESCAPETECHNION_COMPANY_EMAIL_DOES_NOT_EXIST - Company email doesnt exist
 * ESCAPETECHNION_RESERVATION_EXISTS - Company has an Order
 */
EscapeTechnionResult escapeTechnionRemoveCompany(EscapeTechnion system, char *email);

/**
 * companyFree : Free Function of Company element
 *
 * @param company - Company Element to free
 */
void companyFree(SetElement company);

/**
 * companyCompare : Compare 2 Companys by email
 *
 * @param company1 - First company to compare
 * @param company2 - Second company to compare
 * @return
 * 0 if emails are equal & legal
 * 1 otherwise
 */
int companyCompare(SetElement company1, SetElement company2);

/**
 * companySetCopy : Copy Function of Company Element
 *
 * @param source Company to copy
 * @return
 * Copy of Company Element
 */
SetElement companySetCopy(SetElement source);

/**
 * escapeTechnionAddEscaper : Add Escaper to Escapetechnion system
 *
 * @param system - System to add the Escaper
 * @param email - Email of the Escaper
 * @param faculty - Faculty of the Escaper
 * @param skill - Skill of the Escaper
 * @return
 * ESCAPETECHNION_NULL_PARAMETER - Email is null
 * ESCAPETECHNION_INVALID_PARAMETER - Faculty or skill illegal
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPETECHNION_SUCCESS Add successful
 */
EscapeTechnionResult escapeTechnionAddEscaper(EscapeTechnion system, char *email, TechnionFaculty faculty, int skill);

/**
 * escapeTechnionTremoveEscaper : Remove a certain Escaper from EscapeTechnion system
 *
 * @param system - Escape Room system to remove from
 * @param email Escaper email
 * @return
 * ESCAPETECHNION_NULL_PARAMETER - Email is null
 * ESCAPETECHNION_INVALID_PARAMETER - Email illegal
 * ESCAPETECHNION_CLIENT_EMAIL_DOES_NOT_EXIST - Escaper doesnt exist
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPETECHNION_SUCCESS - Remove successful
 */
EscapeTechnionResult escapeTechnionRemoveEscaper(EscapeTechnion system, char *email);

/**
 * escaperCompare : Compare Function of Escaper Elements. Compare by emails
 *
 * @param escaper1 - First Escaper to compare
 * @param escaper2 - Second Escaper to compare
 * @return
 * 0 - Emails are the same and legal
 * 1 - Otherwise
 */
int escaperCompare(SetElement escaper1, SetElement escaper2);

/**
 * escaperSetCopy : Copy Function for SetElemnt Escaper
 *
 * @param source Escaper to copy
 * @return
 * Copy of the Escaper Element
 */
SetElement escaperSetCopy(SetElement source);

/**
 * escaperFree : Deallocate a certain SetElement Escaper
 *
 * @param escaper Escaper to free
 */
void escaperFree(SetElement escaper);

/**
 * escapeTechnionAddRoom : Add a certain escape Room to EscapeTechnoiin system
 *
 * @param system - Escape Room system to add the Room to
 * @param email - Email of the Company which the Room belong to
 * @param room_id - ID of the Room
 * @param price - Price for the Room per person
 * @param num_ppl - Recomended number of people to use the Room
 * @param difficulty - Difficulty level of the Room
 * @param open_time - Opening time of the Room
 * @param close_time - Closing time of the Room
 * @return
 * ESCAPETECHNION_NULL_PARAMETER - Email is null
 * ESCAPTETECHNION_INVALID_PARAMETER - if ID <=0 || email illegal || price<=0 || price%4!=0
 *                                      || num_ppl<=0 || diificulty illegal || opening &closing time illegal
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPETECHNION_SUCCESS - Add successful
 */
EscapeTechnionResult escapeTechnionAddRoom(EscapeTechnion system, char *email, int room_id,
                                           int price, int num_ppl, int difficulty, int open_time, int close_time);

/**
 * escapeTechnionRemoveRoom : Remove a certain escape Room from EscapeTechnion system
 *
 * @param system - EscapeTechnion system of Rooms to remove the Room from
 * @param faculty - Faculty the Room belongs to
 * @param id - Room ID
 * @return
 * ESCAPETECHNION_NULL_PARAMETER - Email is null
 * ESCAPETECHNION_INVALID_PARAMTER - if Faculty or id illegal
 * ESCAPETECHNION_ID_DOES_NOT_EXIST - Room id does not exist
 * ESCAPETECHNION_RESERVATION_EXISTS - Room has resservation
 */
EscapeTechnionResult escapeTechnionRemoveRoom(EscapeTechnion system, TechnionFaculty faculty, int id);

/**
 * roomFree : Deallocates SetElement Room
 *
 * @param room Room to free
 */
void roomFree(SetElement room);

/**
 * roomCompare : Compares 2 SetElement Rooms by their ID and Faculties
 *
 * @param room1 - First Room to compare
 * @param room2 - Second Room to compare
 * @return
 * 0 - Rooms are alike
 * 1 - Rooms are different
 */
int roomCompare(SetElement room1, SetElement room2);

/**
 * roomSetCopy : Copy Function of SetElement Room for Set
 *
 * @param source - Room to compare
 * @return
 * Copy of the Room
 */
SetElement roomSetCopy(SetElement source);

/**
 * orderListCopy : Copy Function of ListElement Order for List
 *
 * @param source - Order to copy
 * @return
 * Copy of the Order
 */
ListElement orderListCopy(ListElement source);
/**
 * orderFree : Free Function for ListElemnt of Order
 * @param order - Order to free
 */
void orderFree(ListElement order);

/**
 * escapeTechnionAddOrder : Allocates and Create an Order for Escape Room system
 *
 * @param system - EscapeTechnion system to add the Order to
 * @param email - email of the Company the Order belongs to
 * @param faculty - Faculty of the Company for the Order
 * @param id - ID of the Room of the Order
 * @param day - How many days until the Order arrives
 * @param time - Time of Order
 * @param num_ppl - Number of people arriving
 * @return
 */
EscapeTechnionResult escapeTechnionAddOrder(EscapeTechnion system, char *email,
                                            TechnionFaculty faculty, int id, int day, int time, int num_ppl);

/**
 * orderCompare : Compare Function of ListElement Order for List.
 *                Comparison is by what Order comes first by days left and time.
 *                If the date and time are the same than The Order with the lower
 *                Faculty ID will count as first. If they belong to the same Faculty
 *                then the Order with the lowest Room ID will be counted as "lower"
 *
 * @param order1 - First Order to compare
 * @param order2 - Second Order to compare
 * @return
 * -1 if the first Order is "lower"
 * 1 if second Order is "lower"
 */
int orderCompare(ListElement order1, ListElement order2);


/**
 * escapeTechnionRecommendRoom : Make an Order to a certain Escaper to a recomended Room
 *
 * @param system - Escape Room system of the Escaper
 * @param email - Email of the Escaper
 * @param num_ppl - Number of people arriving
 * @return
 * ESCAPETECHNION_NULL_PARAMETER - Email is null
 * ESCAPETECHNION_INVALID_PARAMETER - Email illegal or num_ppl<=0
 * ESCAPETECHNION_CLIENT_EMAIL_DOES_NOT_EXIST - Escaper doesn't exist
 * ESCAPETECHNION_NO_ROOMS_AVAILABLE - No Rooms in the system
 * ESCAPETECHNION_SUCCESS - Escaper get a reservation for the recommended room
 */
EscapeTechnionResult escapeTechnionRecommendRoom(EscapeTechnion system, char *email, int num_ppl);


#endif //INC_ESCAPETECHNION_H
