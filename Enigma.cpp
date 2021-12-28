#include "Enigma.h"
#include <string.h>

mtm::escaperoom::Enigma::Enigma(const std::string &name, const Difficulty &difficulty, const int &numOfElements) {
    const char *c=name.c_str();
    this->name = new char[strlen(c)+1];
    this->name = name;
    this->difficulty = difficulty;
    this->numOfElements = numOfElements;
}

mtm::escaperoom::Enigma::Enigma(const Enigma &enigma){
    const char *c = enigma.name.c_str();
    this->name = new char[strlen(c)+1];
    this->name = enigma.name;
    this->difficulty = enigma.difficulty;
    this->numOfElements = enigma.numOfElements;
}

mtm::escaperoom::Enigma& mtm::escaperoom::Enigma::operator=(const Enigma &enigma){
    if(this == &enigma){
        return *this;
    }
    delete[] &this->name;
    this->name = new char[strlen(enigma.name.c_str())+1];
    this->name = enigma.name;
    this->difficulty = enigma.difficulty;
    this->numOfElements = enigma.numOfElements;
}

bool mtm::escaperoom::Enigma::operator==(const Enigma &enigma) const {
    const char *c = this->name.c_str();
    const char *d = enigma.name.c_str();
    return this->difficulty == enigma.difficulty && strcmp(c,d) == 0;
}

bool mtm::escaperoom::Enigma::operator!=(const Enigma &enigma) const {
    const char *c = this->name.c_str();
    const char *d = enigma.name.c_str();
    return !(this->difficulty == enigma.difficulty && strcmp(c,d) == 0);
}

bool mtm::escaperoom::Enigma::operator<(const Enigma &enigma) const {
    return (int)this->difficulty < (int)enigma.difficulty;
}

bool mtm::escaperoom::Enigma::operator>(const Enigma &enigma) const {
    return (int)this->difficulty > (int)enigma.difficulty;
}

bool mtm::escaperoom::Enigma::areEqualyComplex(const Enigma &enigma) const {
    return this->difficulty == enigma.difficulty && this->numOfElements == enigma.numOfElements;
}

mtm::escaperoom::Difficulty mtm::escaperoom::Enigma::getDifficulty() const{
    return this->difficulty;
}

string mtm::escaperoom::Enigma::getName() const {
    return this->name;
}

std::ostream& mtm::escaperoom::operator<<(std::ostream &output, const Enigma &enigma){
    return output << enigma.name << " " << "(" << enigma.difficulty << ")" << " " << enigma.numOfElements;
}