#include "User.h"

uint32_t User::counterID = 0;

User::User(std::string newName, std::string newLogin, uint8_t newRole, std::string newHash, std::string newSalt) :
    name(newName), login(newLogin), role(newRole), hash(newHash), salt(newSalt) {
        ID = counterID++;
        nameLength = static_cast<uint8_t>(name.length());
        loginLength = static_cast<uint8_t>(login.length());
        hashLength = static_cast<uint8_t>(hash.length());
        saltLength = static_cast<uint8_t>(salt.length());
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

void User::setHash(std::string newHash) {
    hash = newHash;
}

void User::setSalt(std::string newSalt) {
    salt = newSalt;
}

void User::setRole(uint8_t newRole) {
    role = newRole;
}