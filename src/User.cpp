#include "User.h"

uint32_t User::counterID = 0;

User::User(std::string newName, std::string newLogin, std::string newPassword, uint8_t newRole) :
    name(newName), login(newLogin), role(newRole){
        ID = counterID++;
        nameLength = name.length();
        loginLength = login.length();
        salt = generateSalt();
        hash = generateHash(newPassword);
    }

bool User::verifyPassword(std::string password) {
    if (generateHash(password) == hash)
        return true;
    else 
        return false;
}

std::string User::generateHash(std::string password) {
    std::string symbol = "abcdefghijklmnopqrstuvwxyz1234567890";
    std::string hash = salt;

    for (int i = 0; i < password.length(); i++) {
        hash[i] = symbol[(salt[i] + password[i] - 2 * 'a') % symbol.length()];
    }

    std::cout << "HASH: " << hash << std::endl;
    return hash;
}

std::string User::generateSalt() {
    std::string symbol = "abcdefghijklmnopqrstuvwxyz1234567890";
    salt = "0000111122223333";

    for (size_t i = 0; i < salt.length(); i++) {
        salt[i] = symbol[rand() % 36];
    }

    std::cout << "SALT: " << salt << std::endl;
    return salt;
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