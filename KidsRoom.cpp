#include "KidsRoom.h"

namespace mtm {
    namespace escaperoom {

        KidsRoom::KidsRoom(char *name, const int &escapeTime, const int &level, const int &maxParticipants,
                           const int &ageLimit) :
                EscapeRoomWrapper(name, escapeTime, level, maxParticipants) {
            setNewAgeLimit(ageLimit);
        }

        void KidsRoom::setNewAgeLimit(const int &limit) {
            if (limit < 0) {
                throw KidsRoomIllegalAgeLimit();
            }
            this->ageLimit = limit;
        }

        int KidsRoom::getAgeLimit() const {
            return this->ageLimit;
        }

        std::ostream &KidsRoom::print(std::ostream &output) const {
            return output << "Kids Room: " << getName() << " " << "(" << getMaxTime() << "/" << level() << "/" <<
                          getMaxParticipants() << "/" << getAgeLimit() << ")";
        }

        std::ostream &operator<<(std::ostream &output, const KidsRoom &kidsRoom) {
            return kidsRoom.print(output);
        }

        KidsRoom *KidsRoom::clone() const {
            return new KidsRoom(*this);
        }

    }
}