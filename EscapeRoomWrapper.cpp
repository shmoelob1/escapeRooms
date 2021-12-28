#include "EscapeRoomWrapper.h"
#include <string.h>

mtm::escaperoom::EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& escapeTime, const int& level, const int& maxParticipants){
    this->room = escapeRoomCreate(name,escapeTime,maxParticipants,level);
}

mtm::escaperoom::EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& level){
    const int  max_time = 60;
    const int max_participants = 6;
    this->room = escapeRoomCreate(name,max_time,max_participants,level);
}

mtm::escaperoom::EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper& room){
    this->room = escapeRoomCopy(room.room);
}

mtm::escaperoom::EscapeRoomWrapper& mtm::escaperoom::EscapeRoomWrapper::operator=(const EscapeRoomWrapper &room) {
        if(this == &room){
            return *this;
        }
        escapeRoomDestroy(this->room);
        this->room = escapeRoomCreate(roomGetName(room.room),roomGetMaxTime(room.room),
                                      roomGetMaxParticipants(room.room),getLevel(room.room));
        return *this;
}

bool mtm::escaperoom::EscapeRoomWrapper::operator==(const EscapeRoomWrapper &room) const {
    return areEqualRooms(this->room,room.room);
}

bool mtm::escaperoom::EscapeRoomWrapper::operator!=(const EscapeRoomWrapper &room) const {
    return !areEqualRooms(this->room, room.room);
}

bool mtm::escaperoom::EscapeRoomWrapper::operator<(const EscapeRoomWrapper &room) const {
    return isBiggerRoom(room.room,this->room);
}

bool mtm::escaperoom::EscapeRoomWrapper::operator>(const EscapeRoomWrapper &room) const {
    return isBiggerRoom(this->room,room.room);
}

mtm::escaperoom::EscapeRoomWrapper::~EscapeRoomWrapper() {
    escapeRoomDestroy(this->room);
}

std::ostream& mtm::escaperoom::operator<<(std::ostream &output, const EscapeRoomWrapper &room){
    output << roomGetName(room.room) << " (" << roomGetMaxTime(room.room) << "/" << getLevel(room.room) << "/" <<
           roomGetMaxParticipants(room.room) << ")";
}

int mtm::escaperoom::EscapeRoomWrapper::level() const {
    return getLevel(this->room);
}

void mtm::escaperoom::EscapeRoomWrapper::rate(const int &newRate) const {
    updateRate(this->room,newRate);
}

std::string mtm::escaperoom::EscapeRoomWrapper::getName() const {
    return roomGetName(this->room);
}

int mtm::escaperoom::EscapeRoomWrapper::getMaxTime() const {
    return roomGetMaxTime(this->room);
}

int mtm::escaperoom::EscapeRoomWrapper::getMaxParticipants() const {
    return roomGetMaxParticipants(this->room);
}

double mtm::escaperoom::EscapeRoomWrapper::getRate() const {
    return roomGetRate(this->room);
}