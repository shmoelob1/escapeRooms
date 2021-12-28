#include "ScaryRoom.h"

namespace mtm {
    namespace escaperoom {
        ScaryRoom::ScaryRoom(char *name, const int &escapeTime, const int &level, const int &maxParticipants,
                             const int &ageLimit, const int &numOfScaryEnigmas) :
                EscapeRoomWrapper(name, escapeTime, level, maxParticipants), ageLimit(ageLimit),
                numOfScaryEnigmas(numOfScaryEnigmas) {
        }

        void ScaryRoom::setNewAgeLimit(const int &limit) {
            if (limit < 0) {
                throw ScaryRoomIllegalAgeLimit();
            }
            this->ageLimit = limit;
        }

        void ScaryRoom::incNumberOfScaryEnigmas() {
            this->numOfScaryEnigmas++;
        }

        int ScaryRoom::getAgeLimit() {
            return this->ageLimit;
        }

        ScaryRoom *ScaryRoom::clone() const {
            return new ScaryRoom(*this);
        }

        std::ostream &ScaryRoom::print(std::ostream &output) const {
            return output << "Scary Room: " << getName() << " (" << getMaxTime() << "/" << level() << "/" <<
                          getMaxParticipants() << "/" << ageLimit << ")";
        }

        std::ostream &operator<<(std::ostream &output, const ScaryRoom &scaryRoom) {
            return scaryRoom.print(output);
        }
    }
}