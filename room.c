#include <stdbool.h>
#include "room.h"
#include <assert.h>

struct room_t {
    char *email;
    TechnionFaculty faculty;
    int id;
    int price;
    int num_ppl;
    int open_time;
    int close_time;
    int difficulty;
};

RoomResult roomCreate(Room *room, char *email, TechnionFaculty faculty, int id, int price, int num_ppl,
                      int difficulty, int open_time, int close_time) {
    assert(room != NULL);
    if (!email) {
        return ROOM_NULL_PARAMETER;
    }
    if (id <= 0 || !isLegalTime(open_time,close_time)|| isLegalSkill(difficulty) == false ||
        num_ppl <= 0 || isLegalPrice(price) == false || isLegalEmail(email) == false ||
        isLegalFaculty(faculty) == false) {
        return ROOM_INVALID_PARAMETER;
    }
    struct room_t *tmp = malloc(sizeof(*tmp));
    if (copyString(&tmp->email, email) == false) {
        return ROOM_OUT_OF_MEMORY;
    }
    tmp->id = id;
    tmp->faculty = faculty;
    tmp->price = price;
    tmp->num_ppl = num_ppl;
    tmp->open_time = open_time;
    tmp->close_time = close_time;
    tmp->difficulty = difficulty;
    *room = tmp;
    return ROOM_SUCCESS;
}

RoomResult roomDestroy(Room room) {
    if (room != NULL) {
        free(room->email);
        free(room);
    }
    return ROOM_SUCCESS;
}

RoomResult roomCopy(Room *destination, Room source) {
    assert(destination != NULL && source != NULL);
    return roomCreate(destination, source->email, source->faculty, source->id, source->price, source->num_ppl,
                      source->difficulty,
                      source->open_time, source->close_time);
}

TechnionFaculty roomGetFaculty(Room room) {
    assert(room != NULL);
    return room->faculty;
}

RoomResult roomGetEmail(Room room, char **email) {
    assert(room != NULL);
    if (email == NULL) {
        return ROOM_NULL_PARAMETER;
    }
    assert(isLegalEmail(room->email));
    if (!copyString(email, room->email)) {
        return ROOM_OUT_OF_MEMORY;
    }
    return ROOM_SUCCESS;
}

bool isLegalPrice(int price) {
    if (price <= 0 || price % 4 != 0) {
        return false;
    }
    return true;
}

int roomGetPrice(Room room) {
    assert(room != NULL);
    return room->price;
}

int roomGetId(Room room) {
    assert(room != NULL);
    return room->id;
}


int roomGetDifficulty(Room room) {
    assert(room != NULL);
    return room->difficulty;
}

int roomGetOpening(Room room) {
    assert(room != NULL);
    return room->open_time;
}

int roomGetClosing(Room room) {
    assert(room != NULL);
    return room->close_time;
}

int roomGetRecommendation(Room room) {
    assert(room != NULL);
    return room->num_ppl;
}
