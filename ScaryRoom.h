#ifndef HW4_MATAM_SCARYROOM_H
#define HW4_MATAM_SCARYROOM_H

#include "EscapeRoomWrapper.h"

namespace mtm {
    namespace escaperoom {
        class ScaryRoom : public EscapeRoomWrapper {
            int ageLimit;
            int numOfScaryEnigmas;

            /**
             * print : print to output stream a description of ScaryRoom in this pattern:
             * Scary Room: <name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)
             * @param output
             * @return output stream
             */
            std::ostream &print(std::ostream &output) const;

        public:
            /**
             * ScaryRoom : ScaryRoom constructor
             * @param name - Name of Room
             * @param escapeTime - Maximum time to Escape
             * @param level - Level of the escape room  - integer between 1 and 10.
             * @param maxParticipants - Maximum number of participants in room - integer bigger than 1.
             * @param ageLimit - Age limit in room - integer >=0
             * @param numOfScaryEnigmas - Number of scary Enigma's in room - integer >=0
             */
            ScaryRoom(char *name, const int &escapeTime, const int &level, const int &maxParticipants,
                      const int &ageLimit, const int &numOfScaryEnigmas);

            /**
             * setNewAgeLimit : Set's a new age limit for ScaryRoom
             * @param limit - age limit
             * @Exceptions :
             *  ScaryRoomIllegalAgeLimit - Illegal age limit(limit<0)
             */
            void setNewAgeLimit(const int &limit);

            /**
             * incNumberOfScaryEnigmas : Increases number of scary Enigm'a by 1
             */
            void incNumberOfScaryEnigmas();

            /**
             * getAgeLimit : Return's room age limit
             * @return  age limit of room
             */
            int getAgeLimit();

            /**
             * operator<< :
             * Scary Room: <name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)
             * @param output output stream
             * @param scaryRoom ScaryRoom to print
             * @return output stream
             */
            /**
             * clone : Creates a ScaryRoom clone to avoid slicing
             * @return clone of ScaryRoom
             */
            ScaryRoom *clone() const;

            /**
             * makes << operator friend so it will have access to print function
             * which is private
             */
            friend std::ostream &operator<<(std::ostream &output, const ScaryRoom &scaryRoom);
        };

        std::ostream &operator<<(std::ostream &output, const ScaryRoom &scaryRoom);

    }
}
#endif //HW4_MATAM_SCARYROOM_H
