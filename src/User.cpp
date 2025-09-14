#include "User.h"

uint32_t User::counterID = 0;

User::User(std::string newName, std::string newLogin, uint8_t newRole, std::string newHash, std::string newSalt) :
    name(newName), login(newLogin), role(newRole){
        ID = counterID++;
    }

uint32_t User::getID() const {
    return ID;
}

std::string User::getName() const {
    return name;
}

std::string User::getLogin() const {
    return login;
}

std::string User::getHash() const {
    return hash;
}

std::string User::getSalt() const {
    return salt;
}

uint8_t User::getNameLength() const {
    return nameLength;
}

uint8_t User::getLoginLength() const {
    return loginLength;
}

uint8_t User::getHashLength() const {
    return hashLength;
}

uint8_t User::getRole() const {
    return role;
}

void User::setName(std::string newName) {
    name = newName;
}

void User::setLogin(std::string newLogin) {
    login = newLogin;
}