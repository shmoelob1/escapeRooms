#ifndef HW4_MATAM_KIDSROOM_H
#define HW4_MATAM_KIDSROOM_H

#include "EscapeRoomWrapper.h"

namespace mtm {
    namespace escaperoom {
        class KidsRoom : public EscapeRoomWrapper {
            int ageLimit;

            /**
             * print : print to output stream a description of KidsRoom in this pattern:
             * Kids Room: <name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)
             * @param output
             * @return output stream
             */
            std::ostream &print(std::ostream &output) const;

        public:
            /**
             * KidsRoom : KidsRoom constructor
             * @param name - Name of Room
             * @param escapeTime - Maximum time to Escape
             * @param level - Level of the escape room  - integer between 1 and 10.
             * @param maxParticipants - Maximum number of participants in room - integer bigger than 1.
             * @param ageLimit - Age limit in room - integer >=0
             */
            KidsRoom(char *name, const int &escapeTime, const int &level, const int &maxParticipants,
                     const int &ageLimit);

            /**
             * setNewAgeLimit : Set's new age limit for room
             * @param limit - Age limitation
             * @Exceptions :
             *  KidsRoomIllegalAgeLimit - Illegal age limit (age<0)
             */
            void setNewAgeLimit(const int &limit);

            /**
             * getAgeLimit : Return age limit of room
             * @return - Room age limit
             */
            int getAgeLimit() const;

            /**
            * clone : Creates a KidsRoom clone to avoid slicing
            * @return clone of KidsRoom
            */
            KidsRoom *clone() const;

            /**
             * makes << operator friend so it will have access to print function
             * which is private
             */
            friend std::ostream &operator<<(std::ostream &output, const KidsRoom &kidsRoom);


        };

        std::ostream &operator<<(std::ostream &output, const KidsRoom &kidsRoom);

    }
}
#endif //HW4_MATAM_KIDSROOM_H
