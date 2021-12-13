#ifndef INC_ROOM_H
#define INC_ROOM_H

#include "set.h"
#include "mtm_ex3.h"
#include "common_functions.h"
#include <string.h>
#include <malloc.h>

typedef struct room_t *Room;

typedef enum {
    ROOM_OUT_OF_MEMORY, // You should exit program after this error
    ROOM_NULL_PARAMETER,
    ROOM_INVALID_PARAMETER,
    ROOM_SUCCESS,
} RoomResult;
/**
 *  * orderCreate : Allocates and create a certain escape room
 *
 * @param room - A pointer to allocate the room
 * @param email - The email of the company which the room belongs to
 * @param faculty - The faculty the rooms belongs to
 * @param id - The room id
 * @param price - The price for the room (per person)
 * @param num_ppl - The recommended number of people the use the room
 * @param difficulty - The difficulty level of the room
 * @param open_time - The time the room open's
 * @param close_time - The time the room close
 * @return
 * ROOM_NULL_PARAMETER - email is null
 * ROOM_INVALID_PARAMETER - if one of the following parameters are invalid:
 *                          ID is not positive
 *                          open time<0 || open time >23
 *                          close time<1 || close time >24
 *                          open time >= close time
 *                          difficulty is not in legal range(1-10)
 *                          price is illeagel : price%4!=0 or price<=0
 *                          faculty does not exist
 * ROOM_OUT_OF_MEMORY - if memory allocation failed
 */
RoomResult roomCreate(Room *room, char *email, TechnionFaculty faculty, int id, int price, int num_ppl,
                      int difficulty, int open_time, int close_time);
/**
 * roomDestroy : Deallocates a room.
 *              if room is null, nothing happens
 *
 * @param room - The room to destroy
 * @return
 * ROOM_SUCCESS - always
 */
RoomResult roomDestroy(Room room);
/**
 * roomCopy : Creates a copy of an existing room
 *
 * @param destination - A destination to copy the room to
 * @param source - The Target to copy from
 * @return
 * ROOM_OUT_OF_MEMORY - if memory allocation failed
 * ROOM_SUCCESS if copy succeed
 * the assumption is that the source values are legal.
 * if not the return value will be according to 'roomCreate'
 */
RoomResult roomCopy(Room *destination, Room source);

TechnionFaculty roomGetFaculty(Room room);
/**
 * roomGetEmail : Return a copy of an email of the company which a certain room belongs to
 *
 * @param room - A pointer to a room to extract company email
 * @param email - A pointer to return a copy of the company email
 * @return
 * ROOM_NULL_PARAMETER - if email is null
 * ROOM_OUT_OF_MEMORY - if the allocation of email fails
 * ROOM_SUCCESS - otherwise
 */
RoomResult roomGetEmail(Room room, char **email);

/**
 * isLegalPrice : Checks if price is legal
 *
 * @param price - Price to check
 * @return
 * true if price%4=0 && price>0
 * false otherwise
 */
bool isLegalPrice(int price);
/**
 * roomGetPrice : What is the price for a certain room per person
 *
 * @param room - The room to extract the information from
 * @return
 * The price for the room
 */
int roomGetPrice(Room room);
/**
 * roomGetId : What is the ID of a certain room
 *
 * @param room - The room to extract the ID from
 * @return
 * The room ID
 */
int roomGetId(Room room);
/**
 * roomGetDifficulty : What is the difficulty level for a certain room
 *
 * @param room - The room to extract the difficulty from
 * @return
 * The room difficulty
 */
int roomGetDifficulty(Room room);
/**
 * roomGetOpening : What is the opening time for a certain room
 *
 * @param room - The room to extract the opening time from
 * @return
 * The room opening time
 */
int roomGetOpening(Room room);
/**
 * roomGetClosing : What is the losing time for a certain room
 *
 * @param room - The room to extract the closing time from
 * @return
 * The room closing time
 */
int roomGetClosing(Room room);
/**
 * roomGetRecommendation : What is the recommended number of people for a certain room
 *
 * @param room - The room to extract the recommendation from
 * @return
 * The recommended number of people for the room
 */
int roomGetRecommendation(Room room);

#endif //INC_ROOM_H


