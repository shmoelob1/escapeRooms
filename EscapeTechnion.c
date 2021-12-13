#include "EscapeTechnion.h"

#define SQUARE(x) ((x)*(x))
struct escape_technion_t {
    Set escaper_set;
    Set room_set;
    int revenue[(int) UNKNOWN];
    Set company_set;
    List orders_list;
    int day;
};

/**
 * daysLeftFilter : Filter for List of Orders by days left.
 *
 * @param order order to compare
 * @param days - Number of days to keep
 * @return
 * true - if order has @param days left
 * false - otherwise
 */
static bool daysLeftFilter(ListElement order, ListFilterKey days);

/**
 * daysOrMotrFilter : Filter for List of Orders by days left.
 *
 * @param order - Order to compare
 * @param days - Number of days to keep
 * @return
 * true - if Order has @param days left or MORE
 * false - otherwise
 */
static bool daysOrMoreFilter(ListElement order, ListFilterKey days);

/**
 * roomHasOrders : Checks if a specific Room has Orders
 *
 * @param system - Escape Room System
 * @param faculty - Faculty the room belongs to
 * @param id - Room ID
 * @return
 * true - Room has impending orders
 * false - otherwise
 */
static bool roomHasOrders(EscapeTechnion system, TechnionFaculty faculty, int id);

/**
 * removeCompanyRooms : Remove all of certain Company Rooms
 *
 * @param system - Escape Room system
 * @param email - Company Email
 * @return
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPETECHNION_SUCCESS - Remove succeed
 */
static EscapeTechnionResult removeCompanyRooms(EscapeTechnion system, char *email);

/**
 * isEscaperAvilable : Checks if certain Escaper has an Order for a specific time
 *
 * @param system - Escape Room system
 * @param email - Escaper email
 * @param days - Days left to Order
 * @param time - Order time of day
 * @param result - ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 *                 ESCAPETECHNION_SUCCESS - Everything went OK
 * @return
 * true - Escaper is availble - has no Orders for that time and day
 * false - Escaper is unavailble
 */
static bool isEscaperAvailable(EscapeTechnion system, char *email, int days, int time, EscapeTechnionResult *result);

/**
 * orderToTechnoinResult : Converts OrderResult to  EscapeTechnionResult
 *
 * @param result -  Result to convert
 * @return
 * EscapeTechnionResult Converted result
 */
static EscapeTechnionResult orderToTechnionResult(OrderResult result);

/**
 * nextDay : Sets the system to next day :
 *
 *             Remove's old Orders
 *             Increases system day counter
 *             Decreases all Orders day counter
 * @param system - Escape Room system
 * @return
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPETECHNION_SUCCESS - Everything went OK
 */
static EscapeTechnionResult nextDay(EscapeTechnion system);

/**
 * isRoomAvailable : Check if certain room is available at certain time and day
 *
 * @param system - Escape Room system
 * @param room - Room to check
 * @param faculty - Room Faculty
 * @param id - Room ID
 * @param days - Days left to check
 * @param time - Time in day to check
 * @param result ESCAPETECHNION_OUT_OF_MEMORY - MEMORY Allocation failed
 *               ESCAPETECHNION_SUCCESS - Everything went OK
 * @return
 * true - Room is available
 * false - Room Unavailable or memory problem
 */
static bool isRoomAvailable(EscapeTechnion system, Room room, TechnionFaculty faculty, int id, int days, int time,
                            EscapeTechnionResult *result);

/**
 * getOrderPrice : Check what is the Price for a certain order:
 *                 The price will be calculated :(Price of Room) * (Number of People)
 *                 If the Escaper is from the same Faculty as the room then
 *                 he recives 25% discount
 *
 * @param system - Escape Room system
 * @param order - Order to extract the information
 * @param result - ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 *                 ESCAPETECHNION_SUCCESS - Everything went fine
 * @return
 * Price for Order
 */
static int getOrderPrice(EscapeTechnion system, Order order, EscapeTechnionResult *result);//
/**
 * orderToRoom : Check's what is the Room for a certain Order
 *
 * @param system - Escape Room system
 * @param order - Order to certract the information
 * @return
 * Room ADT of a certain Order
 */
static Room orderToRoom(EscapeTechnion system, Order order);

/**
 * emailFilter : Filter Function For a List of Orders by Email
 *
 * @param order - Order to filter
 * @param email - Email to filter
 * @return
 * true - Order's email is the same as the given email
 * false - otherwise
 */
static bool emailFilter(ListElement order, ListFilterKey email);

/**
 * getRoom : Converts Faculty and Room ID to Room ADT
 *
 * @param system - Escape Room system
 * @param faculty - Room Faculty
 * @param id - Room ID
 * @return
 * Room ADT
 */
static Room getRoom(EscapeTechnion system, TechnionFaculty faculty, int id);

/**
 * emailToEscaper : Converts a certain email to Escaper ADT
 *
 * @param system - Escape Room system
 * @param email - Escaper's email
 * @param escaper - Pointer to Escaper.
 * @return
 * Updates escaper to wanted Escaper. will be NULL if Escaper email doesn't exist
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocattion failed
 * ESCAPETECHNION_SUCCESS - Everything wen fine
 */
static EscapeTechnionResult emailToEscaper(EscapeTechnion system, char *email, Escaper *escaper);

/**
 * emailToCompamy : Converts a certain email to Company ADT
 *
 * @param system - Escape Room system
 * @param email - Company's email
 * @param escaper - Pointer to Company.
 * @return
 * Updates company to wanted Escaper. will be NULL if Company email doesn't exist
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocattion failed
 * ESCAPETECHNION_SUCCESS - Everything wen fine
 */
static EscapeTechnionResult emailToCompany(EscapeTechnion system, char *email, Company *company);

/**
 * escaperEmailExist : Check if certain Escaper exist
 *
 * @param system - Escape Room System
 * @param email - Escaper's email
 * @param result - ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 *                 ESCAPTECHNION_SUCCESS - Everything went OK
 * @return
 * true - Escaper exist
 * false - Escaper doesn't exist
 */
static bool escaperEmailExist(EscapeTechnion system, char *email, EscapeTechnionResult *result);

/**
 * compamyEmailExist : Check if certain Company exist
 *
 * @param system - Escape Room System
 * @param email - Company's email
 * @param result - ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 *                 ESCAPTECHNION_SUCCESS - Everything went OK
 * @return
 * true - Company exist
 * false - Company doesn't exist
 */
static bool companyEmailExist(EscapeTechnion system, char *email, EscapeTechnionResult *result);

/**
 * EscaperEmailExist : Check if certain email exist in system
 *
 * @param system - Escaper Room System
 * @param email - Email target
 * @param result - ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 *                 ESCAPTECHNION_SUCCESS - Everything went OK
 * @return
 * true - Email exist
 * false - Email doesn't exist
 */
static bool emailExist(EscapeTechnion system, char *email, EscapeTechnionResult *result);

/**
 * listToTechnionResult : Converts ListResult to EscapeTechnionResult
 *
 * @param result - Result to convert
 * @return
 * EscapeTechnionResult type result
 */
static EscapeTechnionResult listToTechnionResult(ListResult result);

/**
 * companyToTechnionResult : Converts CompanyResult to EscapeTechnionResult
 *
 * @param result - Result to convert
 * @return
 * EscapeTechnionResult type result
 */
static EscapeTechnionResult companyToTechnionResult(CompanyResult result);

/**
 * escaperToTechnionResult : Converts EscaperResult to EscapeTechnionResult
 *
 * @param result - Result to convert
 * @return
 * EscapeTechnionResult type result
 */
static EscapeTechnionResult escaperToTechnionResult(EscaperResult result);

/**
 * roomToTechnionResult : Converts RoomResult to EscapeTechnionResult
 *
 * @param result - Result to convert
 * @return
 * EscapeTechnionResult type result
 */
static EscapeTechnionResult roomToTechnionResult(RoomResult result);

/**
 * setToTechnionResult : Converts SetResult to EscapeTechnionResult
 *
 * @param result - Result to convert
 * @return
 * EscapeTechnionResult type result
 */
static EscapeTechnionResult setToTechnionResult(SetResult result);

/**
 * emailRemoveFilter : Filter Function For a List of Orders by Email
 *
 * @param order - Order to filter
 * @param email - Email to filter
 * @return
 * true - Order's email is different from given email
 * false - otherwise
 */
static bool emailRemoveFilter(ListElement order, ListFilterKey email);

/**
 * getRecommended : Find the Recommended Room for a certain Escaper
 *
 * @param system - Escape Room system
 * @param faculty - Escaper's Faculty
 * @param num_ppl - Number of people arriving
 * @param skill - Escaper's Skill
 * @return
 * Recommended Room
 */
static Room getRecommended(EscapeTechnion system, TechnionFaculty faculty, int num_ppl, int skill);

/**
 * companyHasReservation : Check's if certain Company has impending Orders
 *
 * @param system - Escape Room System
 * @param email - Company's Email
 * @param result - ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 *                 ESCAPTECHNION_SUCCESS - Everything went fine
 * @return
 * true : Company has Orders
 * false : Company doesn't have Orders or Memory problem
 */
static bool companyHasReservation(EscapeTechnion system, char *email, EscapeTechnionResult *result);

/**
 * removeEscaperOrders : Remove all Orders for certain Escaper
 *
 * @param system - Escape Room System
 * @param email - Escaper's Email
 * @return
 * ESCAPETECHNION_OUT_OF_MEMORY - Memory allocation failed
 * ESCAPETECHNION_SUCCESS - Everything went fine
 */
static EscapeTechnionResult removeEscaperOrders(EscapeTechnion system, char *email);


EscapeTechnionResult systemDestroy(EscapeTechnion system) {
    assert(system != NULL);
    setDestroy(system->room_set);
    setDestroy(system->escaper_set);
    setDestroy(system->company_set);
    listDestroy(system->orders_list);
    free(system);
    return ESCAPETECHNION_SUCCESS;
}

EscapeTechnionResult systemCreate(EscapeTechnion *system) {
    assert(system != NULL);
    EscapeTechnion tmp = malloc(sizeof(struct escape_technion_t));
    if (!tmp) {
        return ESCAPETECHNION_OUT_OF_MEMORY;
    }
    tmp->escaper_set = setCreate(escaperSetCopy, escaperFree, escaperCompare);
    tmp->room_set = setCreate(roomSetCopy, roomFree, roomCompare);
    tmp->company_set = setCreate(companySetCopy, companyFree, companyCompare);
    tmp->orders_list = listCreate(orderListCopy, orderFree);
    if (!tmp->escaper_set || !tmp->room_set || !tmp->company_set || !tmp->orders_list) {
        setDestroy(tmp->company_set);
        setDestroy(tmp->escaper_set);
        setDestroy(tmp->room_set);
        listDestroy(tmp->orders_list);
        return ESCAPETECHNION_OUT_OF_MEMORY;
    }
    tmp->day = 0;
    for (int i = 0; i < (int) UNKNOWN; i++) {
        tmp->revenue[i] = 0;
    }
    *system = tmp;
    return ESCAPETECHNION_SUCCESS;
}

static bool emailExist(EscapeTechnion system, char *email, EscapeTechnionResult *result) {
    if (companyEmailExist(system, email, result)) {
        return true;
    }
    if (*result == ESCAPETECHNION_OUT_OF_MEMORY) {
        return false;
    }
    if (escaperEmailExist(system, email, result)) {
        return true;
    }
    if (*result == ESCAPETECHNION_OUT_OF_MEMORY) {
        return false;
    }
    return false;
}

//Company
static bool companyEmailExist(EscapeTechnion system, char *email, EscapeTechnionResult *result) {
    assert (system != NULL && email != NULL && result != NULL);
    char *tmp = NULL;
    if (setGetSize(system->company_set) == 0) {
        return false;
    }
    SET_FOREACH(Company, i, system->company_set) {
        *result = companyToTechnionResult(companyGetEmail(i, &tmp));
        if (*result != ESCAPETECHNION_SUCCESS) {
            return false;
        }
        if (strcmp(tmp, email) == 0) {
            free(tmp);
            return true;
        }
        free(tmp);
    }
    return false;
}

EscapeTechnionResult escapeTechnionAddCompany(EscapeTechnion system, char *email,
                                              TechnionFaculty faculty) {
    assert(system != NULL);
    if (!email) {
        return ESCAPETECHNION_NULL_PARAMETER;
    }
    EscapeTechnionResult result = ESCAPETECHNION_SUCCESS;
    if (!isLegalEmail(email) || !isLegalFaculty(faculty)) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    if (emailExist(system, email, &result)) {
        if (result != ESCAPETECHNION_SUCCESS) {
            return ESCAPETECHNION_OUT_OF_MEMORY;
        }
        return ESCAPETECHNION_EMAIL_ALREADY_EXISTS;
    }
    Company company;
    result = companyToTechnionResult(companyCreate(&company, email, faculty));
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    setAdd(system->company_set, company);
    companyDestroy(company);
    return ESCAPETECHNION_SUCCESS;
}

static bool companyHasReservation(EscapeTechnion system, char *email, EscapeTechnionResult *result) {
    LIST_FOREACH(Order, i, system->orders_list) {
        Room room = getRoom(system, orderGetFaculty(i), orderGetId(i));
        char *room_email;
        *result = roomToTechnionResult(roomGetEmail(room, &room_email));
        if (*result == ESCAPETECHNION_OUT_OF_MEMORY) {
            return false;
        }
        if (strcmp(email, room_email) == 0) {
            free(room_email);
            return true;
        }
        free(room_email);
    }
    return false;
}

static EscapeTechnionResult removeCompanyRooms(EscapeTechnion system, char *email) {
    assert(email != NULL);
    assert(isLegalEmail(email));
    SET_FOREACH(Room, i, system->room_set) {
        char *tmp = NULL;
        EscapeTechnionResult result = roomToTechnionResult(roomGetEmail(i, &tmp));
        if (result != ESCAPETECHNION_SUCCESS) {
            return result;
        }
        if (strcmp(tmp, email) == 0) {
            setToTechnionResult(setRemove(system->room_set, i));
            setGetFirst(system->room_set);
        }
        free(tmp);
    }
    return ESCAPETECHNION_SUCCESS;
}

EscapeTechnionResult escapeTechnionRemoveCompany(EscapeTechnion system, char *email) {
    assert(system != NULL);
    if (email == NULL) {
        return ESCAPETECHNION_NULL_PARAMETER;
    }
    EscapeTechnionResult result = ESCAPETECHNION_SUCCESS;
    if (!isLegalEmail(email)) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    if (!companyEmailExist(system, email, &result)) {
        if (result == ESCAPETECHNION_OUT_OF_MEMORY) {
            return result;
        }
        return ESCAPETECHNION_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    if (companyHasReservation(system, email, &result)) {
        return ESCAPETECHNION_RESERVATION_EXISTS;
    }
    if (result == ESCAPETECHNION_OUT_OF_MEMORY) {
        return result;
    }
    removeCompanyRooms(system, email);
    Company tmp;
    if (emailToCompany(system, email, &tmp) == ESCAPETECHNION_OUT_OF_MEMORY) {
        return ESCAPETECHNION_OUT_OF_MEMORY;
    }
    assert(tmp != NULL);
    setRemove(system->company_set, tmp);
    return ESCAPETECHNION_SUCCESS;
}

void companyFree(SetElement company) {
    companyDestroy(company);
}

int companyCompare(SetElement company1, SetElement company2) {
    assert(company1 != NULL && company2 != NULL);
    char *email1 = NULL;
    char *email2 = NULL;
    if (companyGetEmail(company1, &email1) != COMPANY_SUCCESS ||
        companyGetEmail(company2, &email2) != COMPANY_SUCCESS) {
        free(email1);
        free(email2);
        return 0;
    }
    int i = strcmp(email1, email2);
    free(email1);
    free(email2);
    return i;
}

ListElement orderListCopy(ListElement source) {
    assert(source != NULL);
    Order copy = NULL;
    if (orderCopy(&copy, source) != ORDER_SUCCESS) {
        return NULL;
    }
    return copy;
}

SetElement companySetCopy(SetElement source) {
    assert(source != NULL);
    Company copy = NULL;
    if (companyCopy(&copy, source) != COMPANY_SUCCESS) {
        return NULL;
    }
    return copy;
}

SetElement escaperSetCopy(SetElement source) {
    assert(source != NULL);
    Escaper destination;
    if (escaperCopy(&destination, source) != ESCAPER_SUCCESS) {
        return NULL;
    }
    return destination;
}

SetElement roomSetCopy(SetElement source) {
    Room copy;
    if (roomCopy(&copy, source) != ROOM_SUCCESS) {
        return NULL;
    }
    return copy;
}

static EscapeTechnionResult emailToCompany(EscapeTechnion system, char *email, Company *company) {
    assert(system != NULL && email != NULL && company != NULL);
    assert(isLegalEmail(email));
    char *tmp;
    SET_FOREACH(Company, i, system->company_set) {
        if (companyGetEmail(i, &tmp) == COMPANY_OUT_OF_MEMORY) {
            return ESCAPETECHNION_OUT_OF_MEMORY;
        }
        if (strcmp(email, tmp) == 0) {
            free(tmp);
            *company = i;
            return ESCAPETECHNION_SUCCESS;
        }
        free(tmp);
    }
    *company = NULL;
    return ESCAPETECHNION_SUCCESS;
}

void orderFree(ListElement order) {
    if (order != NULL) {
        orderDestroy(order);
    }
    return;
}

void escaperFree(SetElement escaper) {
    escaperDestroy(escaper);
    return;
}

int escaperCompare(SetElement escaper1, SetElement escaper2) {
    assert(escaper1 != NULL && escaper2 != NULL);
    char *email1 = NULL;
    char *email2 = NULL;
    EscaperResult result1, result2;
    result1 = escaperGetEmail(escaper1, &email1);
    result2 = escaperGetEmail(escaper2, &email2);
    if (result1 != ESCAPER_SUCCESS || result2 != ESCAPER_SUCCESS) {
        free(email1);
        free(email2);
        return 0;
    }
    int i = strcmp(email1, email2);
    free(email1);
    free(email2);
    return i;
}

static EscapeTechnionResult emailToEscaper(EscapeTechnion system, char *email, Escaper *escaper) {
    assert(system != NULL && email != NULL);
    assert(isLegalEmail(email));
    EscapeTechnionResult result;
    char *tmp;
    SET_FOREACH(Escaper, i, system->escaper_set) {
        result = escaperToTechnionResult(escaperGetEmail(i, &tmp));
        if (result != ESCAPETECHNION_SUCCESS) {
            return result;
        }
        if (strcmp(email, tmp) == 0) {
            free(tmp);
            *escaper = i;
            return ESCAPETECHNION_SUCCESS;
        }
        free(tmp);
    }
    *escaper = NULL;
    return ESCAPETECHNION_SUCCESS;
}

static bool escaperEmailExist(EscapeTechnion system, char *email, EscapeTechnionResult *result) {
    assert(system != NULL && email != NULL && result != NULL);
    char *tmp = NULL;
    if (setGetSize(system->escaper_set) == 0) {
        return false;
    }
    SET_FOREACH(Escaper, i, system->escaper_set) {
        *result = escaperToTechnionResult(escaperGetEmail(i, &tmp));
        if (*result == ESCAPETECHNION_OUT_OF_MEMORY) {
            return false;
        }
        if (strcmp(tmp, email) == 0) {
            free(tmp);
            return true;
        }
        free(tmp);
    }
    return false;
}
//End of Escaper

EscapeTechnionResult escapeTechnionAddEscaper(EscapeTechnion system, char *email,
                                              TechnionFaculty faculty, int skill) {
    assert(system != NULL);
    EscapeTechnionResult result = ESCAPETECHNION_SUCCESS;
    if (email == NULL) {
        return ESCAPETECHNION_NULL_PARAMETER;
    }
    if (!isLegalEmail(email) || !isLegalFaculty(faculty) || !isLegalSkill(skill)) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    if (emailExist(system, email, &result)) {
        return ESCAPETECHNION_EMAIL_ALREADY_EXISTS;
    }
    if (result == ESCAPETECHNION_OUT_OF_MEMORY) {
        return result;
    }
    Escaper escaper;
    result = escaperToTechnionResult(escaperCreate(&escaper, email, faculty, skill));
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    setAdd(system->escaper_set, escaper);
    escaperDestroy(escaper);
    return ESCAPETECHNION_SUCCESS;
}

//Room
EscapeTechnionResult escapeTechnionAddRoom(EscapeTechnion system, char *email, int room_id,
                                           int price, int num_ppl, int difficulty, int open_time, int close_time) {
    assert(system != NULL);
    EscapeTechnionResult result = ESCAPETECHNION_SUCCESS;
    if (!email) {
        return ESCAPETECHNION_NULL_PARAMETER;
    }
    if (!isLegalEmail(email) || !isLegalTime(open_time, close_time) || room_id <= 0 ||
        !isLegalPrice(price) || !isLegalSkill(difficulty) || num_ppl <= 0) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    if (escaperEmailExist(system, email, &result)) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    if (result == ESCAPETECHNION_OUT_OF_MEMORY) {
        return result;
    }
    if (!companyEmailExist(system, email, &result)) {
        if (result == ESCAPETECHNION_OUT_OF_MEMORY) {
            return result;
        }
        return ESCAPETECHNION_COMPANY_EMAIL_DOES_NOT_EXIST;
    }
    Company company;
    if (emailToCompany(system, email, &company) == ESCAPETECHNION_OUT_OF_MEMORY) {
        return ESCAPETECHNION_OUT_OF_MEMORY;
    }
    Room room;
    TechnionFaculty faculty = companyGetFaculty(company);
    assert(isLegalFaculty(faculty));
    result = roomToTechnionResult(roomCreate(&room, email, faculty,
                                             room_id, price, num_ppl, difficulty, open_time, close_time));
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    if (setIsIn(system->room_set, room)) {
        roomDestroy(room);
        return ESCAPETECHNION_ID_ALREADY_EXIST;
    }
    SetResult set_result = setAdd(system->room_set, room);
    if (set_result != SET_SUCCESS) {
        return setToTechnionResult(set_result);
    }
    companyAddRoom(company);
    roomDestroy(room);
    return ESCAPETECHNION_SUCCESS;
}

static EscapeTechnionResult removeEscaperOrders(EscapeTechnion system, char *email) {
    assert(system != NULL && email != NULL);
    assert(isLegalEmail(email));
    List filtered_list = listFilter(system->orders_list, emailRemoveFilter, email);
    if (!filtered_list) {
        return ESCAPETECHNION_OUT_OF_MEMORY;
    }
    listDestroy(system->orders_list);
    system->orders_list = filtered_list;
    return ESCAPETECHNION_SUCCESS;
}

EscapeTechnionResult escapeTechnionRemoveEscaper(EscapeTechnion system, char *email) {
    assert(system != NULL);
    EscapeTechnionResult result = ESCAPETECHNION_SUCCESS;
    if (email == NULL) {
        return ESCAPETECHNION_NULL_PARAMETER;
    }
    if (!isLegalEmail(email)) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    if (!escaperEmailExist(system, email, &result)) {
        if (result == ESCAPETECHNION_OUT_OF_MEMORY) {
            return result;
        }
        return ESCAPETECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    Escaper tmp;
    result = emailToEscaper(system, email, &tmp);
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    if (removeEscaperOrders(system, email) == ESCAPETECHNION_OUT_OF_MEMORY) {
        return ESCAPETECHNION_OUT_OF_MEMORY;
    }
    assert(tmp != NULL);
    setRemove(system->escaper_set, tmp);
    return ESCAPETECHNION_SUCCESS;
}

static Room getRoom(EscapeTechnion system, TechnionFaculty faculty, int id) {
    assert(system != NULL && isLegalFaculty(faculty));
    SET_FOREACH(Room, room, system->room_set) {
        if (roomGetId(room) == id && roomGetFaculty(room) == faculty) {
            return room;
        }
    }
    return NULL;
}

static bool roomHasOrders(EscapeTechnion system, TechnionFaculty faculty, int id) {
    LIST_FOREACH(Order, i, system->orders_list) {
        if (orderGetFaculty(i) == faculty && orderGetId(i) == id) {
            return true;
        }
    }
    return false;
}

EscapeTechnionResult escapeTechnionRemoveRoom(EscapeTechnion system, TechnionFaculty faculty, int id) {
    assert(system != NULL);
    if (!isLegalFaculty(faculty) || id <= 0) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    Room room = getRoom(system, faculty, id);
    if (room == NULL) {
        return ESCAPETECHNION_ID_DOES_NOT_EXIST;
    }
    if (roomHasOrders(system, faculty, id)) {
        return ESCAPETECHNION_RESERVATION_EXISTS;
    }
    char *email;
    roomGetEmail(room, &email);
    Company company;
    if (emailToCompany(system, email, &company) == ESCAPETECHNION_OUT_OF_MEMORY) {
        return ESCAPETECHNION_OUT_OF_MEMORY;
    }
    SetResult result = setRemove(system->room_set, room);
    if (result != SET_SUCCESS) {
        return setToTechnionResult(result);
    }
    companyRemoveRoom(company);
    free(email);
    return ESCAPETECHNION_SUCCESS;
}


void roomFree(SetElement room) {
    roomDestroy(room);
    return;
}

int roomCompare(SetElement room1, SetElement room2) {
    if (roomGetId(room1) == roomGetId(room2) &&
        roomGetFaculty(room1) == roomGetFaculty(room2)) {
        return 0;
    }
    return -1;
}

//End Of Room
//Order
static bool daysLeftFilter(ListElement order, ListFilterKey days) {
    if (order == NULL) {
        return false;
    }
    if (orderGetDay(order) == *(int *) days) {
        return true;
    }
    return false;
}

static bool daysOrMoreFilter(ListElement order, ListFilterKey days) {
    if (order == NULL) {
        return false;
    }
    if (orderGetDay(order) >= *(int *) days) {
        return true;
    }
    return false;
}

static bool emailFilter(ListElement order, ListFilterKey email) {
    assert(order != NULL && email != NULL);
    char *tmp = NULL;
    orderGetEmail(order, &tmp);
    if (strcmp(tmp, email) == 0) {
        free(tmp);
        return true;
    }
    free(tmp);
    return false;
}

static bool emailRemoveFilter(ListElement order, ListFilterKey email) {
    assert(order != NULL && email != NULL);
    char *tmp = NULL;
    orderGetEmail(order, &tmp);
    if (strcmp(tmp, email) != 0) {
        free(tmp);
        return true;
    }
    free(tmp);
    return false;
}


static bool isEscaperAvailable(EscapeTechnion system, char *email, int days, int time, EscapeTechnionResult *result) {
    *result = ESCAPETECHNION_SUCCESS;
    assert(system != NULL && email != NULL && days >= 0 && time >= 0 &&
           time <= 23);
    List filtered_list = listFilter(system->orders_list, emailFilter, email);
    if (!filtered_list) {
        *result = ESCAPETECHNION_OUT_OF_MEMORY;
        return false;
    }
    LIST_FOREACH(Order, order, filtered_list) {
        if (orderGetDay(order) == days && orderGetTimeOfDay(order) == time) {
            listDestroy(filtered_list);
            return false;
        }
    }
    listDestroy(filtered_list);
    return true;
}

static bool isRoomAvailable(EscapeTechnion system, Room room, TechnionFaculty faculty, int id, int days, int time,
                            EscapeTechnionResult *result) {
    assert(system != NULL && isLegalFaculty(faculty) && days >= 0 && time >= 0 && time <= 23);
    if (time < roomGetOpening(room) || time >= roomGetClosing(room)) {
        return false;
    }
    List filtered_list = listFilter(system->orders_list, daysLeftFilter, (ListFilterKey) &days);
    if (!filtered_list) {
        *result = ESCAPETECHNION_OUT_OF_MEMORY;
        return false;
    }
    LIST_FOREACH(Order, order, filtered_list) {
        if (orderGetFaculty(order) == faculty && orderGetId(order) == id && orderGetTimeOfDay(order) == time) {
            listDestroy(filtered_list);
            return false;
        }
    }
    listDestroy(filtered_list);
    return true;
}

EscapeTechnionResult escapeTechnionAddOrder(EscapeTechnion system, char *email,
                                            TechnionFaculty faculty, int id, int days, int time, int num_ppl) {
    assert(system != NULL);
    if (email == NULL) {
        return ESCAPETECHNION_NULL_PARAMETER;
    }
    EscapeTechnionResult result = ESCAPETECHNION_SUCCESS;
    if (!isLegalEmail(email) || !isLegalFaculty(faculty) || time < 0 ||
        time > 23 || days < 0 || num_ppl <= 0) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    if (!escaperEmailExist(system, email, &result)) {
        if (result == ESCAPETECHNION_OUT_OF_MEMORY) {
            return result;
        }
        return ESCAPETECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    Room room = getRoom(system, faculty, id);
    if (!room) {
        return ESCAPETECHNION_ID_DOES_NOT_EXIST;
    }
    if (!isEscaperAvailable(system, email, days, time, &result)) {
        if (result != ESCAPETECHNION_SUCCESS) {
            return result;
        }
        return ESCAPETECHNION_CLIENT_IN_ROOM;
    }
    if (!isRoomAvailable(system, room, faculty, id, days, time, &result)) {
        if (result != ESCAPETECHNION_SUCCESS) {
            return result;
        }
        return ESCAPETECHNION_ROOM_NOT_AVAILABLE;
    }
    Order order;
    result = orderToTechnionResult(orderCreate(&order, email, faculty, id, days, time, num_ppl));
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    EscapeTechnionResult list_result = listToTechnionResult(listInsertFirst(system->orders_list, order));
    if (list_result != ESCAPETECHNION_SUCCESS) {
        orderDestroy(order);
        return list_result;
    }
    orderDestroy(order);
    return ESCAPETECHNION_SUCCESS;
}

EscapeTechnionResult escapeTechnionRecommendRoom(EscapeTechnion system, char *email, int num_ppl) {
    EscapeTechnionResult result, result2 = ESCAPETECHNION_SUCCESS;
    assert(system != NULL);
    if (email == NULL) {
        return ESCAPETECHNION_NULL_PARAMETER;
    }
    if (!isLegalEmail(email) || num_ppl <= 0) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    Escaper escaper;
    result = emailToEscaper(system, email, &escaper);
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    if (!escaper) {
        return ESCAPETECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    int skill;
    escaperGetSkill(escaper, &skill);
    TechnionFaculty faculty;
    escaperGetFaculty(escaper, &faculty);
    Room room = NULL;
    room = getRecommended(system, faculty, num_ppl, skill);
    if (room != NULL) {
        int open = roomGetOpening(room);
        int close = roomGetClosing(room);
        int id = roomGetId(room);
        TechnionFaculty room_faculty = roomGetFaculty(room);
        int day = 0;
        for (int j = open; j < close; j++) {
            if (isRoomAvailable(system, room, room_faculty, id, day, j, &result)) {
                if (isEscaperAvailable(system, email, day, j, &result2)) {
                    return escapeTechnionAddOrder(system, email, room_faculty, id, day, j, num_ppl);
                } else if (result2 != ESCAPETECHNION_SUCCESS) {
                    return ESCAPETECHNION_OUT_OF_MEMORY;
                }
            } else if (result != ESCAPETECHNION_SUCCESS) {
                return ESCAPETECHNION_OUT_OF_MEMORY;
            }
            if (j == close - 1) {
                day++;
                j = open - 1;
            }
        }
    }
    return ESCAPETECHNION_NO_ROOMS_AVAILABLE;

}

static Room getRecommended(EscapeTechnion system, TechnionFaculty faculty, int num_ppl, int skill) {
    Room room = NULL;
    int score = -1;
    SET_FOREACH(Room, i, system->room_set) {
        TechnionFaculty i_faculty = roomGetFaculty(i);
        int i_id = roomGetId(i);
        int tmp = SQUARE(roomGetRecommendation(i) - num_ppl) + SQUARE(roomGetDifficulty(i) - skill);
        if (tmp < score || score == -1) {   //better score
            score = tmp;
            room = i;
        } else if (score == tmp) { // same score
            TechnionFaculty room_faculty = roomGetFaculty(room);
            if (SQUARE(faculty - i_faculty) < SQUARE(faculty - room_faculty)) { //distance from faculty is closer
                room = i;
            } else if (SQUARE(faculty - i_faculty) == SQUARE(faculty - room_faculty)) { //same distance from faculty
                if (i_faculty < room_faculty) { //lower faculty id
                    room = i;
                } else if (i_faculty == room_faculty &&
                           i_id < roomGetId(room)) {   //same faculty id && room id is lower
                    room = i;
                }
            }
        }
    }
    return room;
}

int orderCompare(ListElement order1, ListElement order2) {
    assert(order1 != NULL && order2 != NULL);
    int result = orderCompareTime(order1, order2);
    if (result != 0) {
        return result;
    }
    result = orderGetFaculty(order1) - orderGetFaculty(order2);
    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    }
    result = orderGetId(order1) - orderGetId(order2);
    if (result < 0) {
        return -1;
    }
    return 1;

}

//End of Order

//Report
static EscapeTechnionResult nextDay(EscapeTechnion system) {
    assert(system != NULL);
    int filter = 1;
    List list = listFilter(system->orders_list, daysOrMoreFilter, &filter);
    if (!list) {
        return ESCAPETECHNION_OUT_OF_MEMORY;
    }
    system->day++;
    LIST_FOREACH(Order, i, list) {
        orderNextDay(i);
    }
    listDestroy(system->orders_list);
    system->orders_list = list;
    return ESCAPETECHNION_SUCCESS;
}

static Room orderToRoom(EscapeTechnion system, Order order) {
    assert(system != NULL && order != NULL);
    TechnionFaculty faculty = orderGetFaculty(order);
    int id = orderGetId(order);
    return getRoom(system, faculty, id);
}

static int getOrderPrice(EscapeTechnion system, Order order, EscapeTechnionResult *result) {
    assert(system != NULL && order != NULL && result != NULL);
    *result = ESCAPETECHNION_SUCCESS;
    Room room = orderToRoom(system, order);
    int price = roomGetPrice(room);
    char *email = NULL;
    *result = orderToTechnionResult(orderGetEmail(order, &email));
    if (*result != ESCAPETECHNION_SUCCESS) {
        return 0;
    }
    TechnionFaculty faculty;
    Escaper escaper;
    *result = emailToEscaper(system, email, &escaper);
    if (*result != ESCAPETECHNION_SUCCESS) {
        return 0;
    }
    escaperGetFaculty(escaper, &faculty);
    if (orderGetFaculty(order) == faculty) {
        free(email);
        return (orderGetNumEscapers(order) * price * 3 / 4);
    }
    free(email);
    return orderGetNumEscapers(order) * price;
}

EscapeTechnionResult escapeTechnionReportDay(EscapeTechnion system, FILE *output) {
    listSort(system->orders_list, orderCompare);
    int today = 0;
    List today_orders = listFilter(system->orders_list, daysLeftFilter, &today);
    mtmPrintDayHeader(output, system->day, listGetSize(today_orders));
    LIST_FOREACH(Order, order, today_orders) {
        char *escaper_email = NULL;
        if (orderGetEmail(order, &escaper_email) != ORDER_SUCCESS) {
            listDestroy(today_orders);
            return ESCAPETECHNION_OUT_OF_MEMORY;
        }
        EscapeTechnionResult result = escapeTechnionPrintOrder(system, output, order, escaper_email);
        if (result != ESCAPETECHNION_SUCCESS) {
            free(escaper_email);
            listDestroy(today_orders);
            return result;
        }
        free(escaper_email);
    }
    mtmPrintDayFooter(output, system->day);
    listDestroy(today_orders);
    nextDay(system);
    return ESCAPETECHNION_SUCCESS;
}

EscapeTechnionResult
escapeTechnionPrintOrder(EscapeTechnion system, FILE *output, Order order, char *escaper_email) {
    Escaper escaper;
    EscapeTechnionResult result = emailToEscaper(system, escaper_email, &escaper);
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    assert(escaper != NULL);
    Room room = orderToRoom(system, order);
    if (!room) {
        return ESCAPETECHNION_INVALID_PARAMETER;
    }
    int skill;
    escaperGetSkill(escaper, &skill);
    TechnionFaculty escaper_faculty;
    TechnionFaculty company_faculty = roomGetFaculty(room);
    char *company_email = NULL;
    result = roomToTechnionResult(roomGetEmail(room, &company_email));
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    int room_id = roomGetId(room);
    int hour = orderGetTimeOfDay(order);
    int difficulty = roomGetDifficulty(room);
    escaperGetFaculty(escaper, &escaper_faculty);
    int price = getOrderPrice(system, order, &result);
    if (result != ESCAPETECHNION_SUCCESS) {
        return result;
    }
    int num_ppl = orderGetNumEscapers(order);
    system->revenue[company_faculty] += price;
    mtmPrintOrder(output, escaper_email, skill, escaper_faculty, company_email, company_faculty, room_id, hour,
                  difficulty, num_ppl, price);
    free(company_email);
    return ESCAPETECHNION_SUCCESS;
}

void escapeTechnionReportBest(EscapeTechnion system, FILE *output) {
    int first = -1, second = -1, third = -1, total_revenue = 0;
    TechnionFaculty first_faculty = UNKNOWN, second_faculty = UNKNOWN, third_faculty = UNKNOWN;
    for (int i = 0; i < (int) UNKNOWN; i++) {
        int revenue = system->revenue[i];
        total_revenue += revenue;
        if (revenue > first) {
            third = second;
            third_faculty = second_faculty;
            second = first;
            second_faculty = first_faculty;
            first = revenue;
            first_faculty = (TechnionFaculty) i;
        } else if (revenue > second) {
            third = second;
            third_faculty = second_faculty;
            second = revenue;
            second_faculty = (TechnionFaculty) i;
        } else if (revenue > third) {
            third = revenue;
            third_faculty = (TechnionFaculty) i;
        }
    }
    mtmPrintFacultiesHeader(output, (int) UNKNOWN, system->day, total_revenue);
    mtmPrintFaculty(output, first_faculty, first);
    mtmPrintFaculty(output, second_faculty, second);
    mtmPrintFaculty(output, third_faculty, third);
    mtmPrintFacultiesFooter(output);
}

//Error Converter
static EscapeTechnionResult companyToTechnionResult(CompanyResult result) {
    switch (result) {
        case COMPANY_INVALID_PARAMETER :
            return ESCAPETECHNION_INVALID_PARAMETER;
        case COMPANY_NULL_PARAMETER :
            return ESCAPETECHNION_NULL_PARAMETER;
        case COMPANY_EMAIL_ALREADY_EXISTS :
            return ESCAPETECHNION_EMAIL_ALREADY_EXISTS;
        case COMPANY_EMAIL_DOES_NOT_EXIST :
            return ESCAPETECHNION_INVALID_PARAMETER;
        case COMPANY_RESERVATION_EXISTS :
            return ESCAPETECHNION_RESERVATION_EXISTS;
        case COMPANY_OUT_OF_MEMORY :
            return ESCAPETECHNION_OUT_OF_MEMORY;
        case COMPANY_MAIL_ILLEGAL :
            return ESCAPETECHNION_INVALID_PARAMETER;
        case COMPANY_SUCCESS :
            return ESCAPETECHNION_SUCCESS;
    }
    return ESCAPETECHNION_SUCCESS;
}

static EscapeTechnionResult setToTechnionResult(SetResult result) {
    switch (result) {
        case SET_OUT_OF_MEMORY :
            return ESCAPETECHNION_OUT_OF_MEMORY;
        case SET_NULL_ARGUMENT :
            return ESCAPETECHNION_NULL_PARAMETER;
        case SET_SUCCESS :
            return ESCAPETECHNION_SUCCESS;
        case SET_ITEM_ALREADY_EXISTS :
            return ESCAPETECHNION_INVALID_PARAMETER;
        case SET_ITEM_DOES_NOT_EXIST :
            return ESCAPETECHNION_INVALID_PARAMETER;
    }
    return ESCAPETECHNION_SUCCESS;
}

static EscapeTechnionResult roomToTechnionResult(RoomResult result) {
    switch (result) {
        case ROOM_OUT_OF_MEMORY :
            return ESCAPETECHNION_OUT_OF_MEMORY;
        case ROOM_NULL_PARAMETER :
            return ESCAPETECHNION_NULL_PARAMETER;
        case ROOM_INVALID_PARAMETER :
            return ESCAPETECHNION_INVALID_PARAMETER;
        case ROOM_SUCCESS :
            return ESCAPETECHNION_SUCCESS;
    }
    return ESCAPETECHNION_SUCCESS;
}

static EscapeTechnionResult escaperToTechnionResult(EscaperResult result) {
    switch (result) {
        case ESCAPER_OUT_OF_MEMORY :
            return ESCAPETECHNION_OUT_OF_MEMORY;
        case ESCAPER_NULL_PARAMETER :
            return ESCAPETECHNION_NULL_PARAMETER;
        case ESCAPER_INVALID_PARAMETER :
            return ESCAPETECHNION_INVALID_PARAMETER;
        case ESCAPER_SUCCESS :
            return ESCAPETECHNION_SUCCESS;
    }
    return ESCAPETECHNION_SUCCESS;
}

static EscapeTechnionResult orderToTechnionResult(OrderResult result) {
    switch (result) {
        case ORDER_OUT_OF_MEMORY :
            return ESCAPETECHNION_OUT_OF_MEMORY;
        case ORDER_NULL_PARAMETER :
            return ESCAPETECHNION_NULL_PARAMETER;
        case ORDER_INVALID_PARAMETER :
            return ESCAPETECHNION_INVALID_PARAMETER;
        case ORDER_SUCCESS :
            return ESCAPETECHNION_SUCCESS;
        case ORDER_EMAIL_ALREADY_EXISTS :
            return ESCAPETECHNION_EMAIL_ALREADY_EXISTS;
        case ORDER_RESERVATION_EXISTS :
            return ESCAPETECHNION_RESERVATION_EXISTS;
        case ORDER_MAIL_ILLEGAL :
            return ESCAPETECHNION_INVALID_PARAMETER;
        case ORDER_EMAIL_DOES_NOT_EXIST :
            return ESCAPETECHNION_CLIENT_EMAIL_DOES_NOT_EXIST;
    }
    return ESCAPETECHNION_SUCCESS;
}

static EscapeTechnionResult listToTechnionResult(ListResult result) {
    switch (result) {
        case LIST_OUT_OF_MEMORY :
            return ESCAPETECHNION_OUT_OF_MEMORY;
        case LIST_NULL_ARGUMENT :
            return ESCAPETECHNION_NULL_PARAMETER;
        case LIST_SUCCESS :
            return ESCAPETECHNION_SUCCESS;
        case LIST_INVALID_CURRENT :
            return ESCAPETECHNION_INVALID_PARAMETER;
    }
    return ESCAPETECHNION_SUCCESS;
}