#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include "Task.h"

class User {
    static uint32_t counterID;
    uint32_t ID;
    std::string name;
    std::string login;
    std::string hash;
    std::string salt;
    uint8_t nameLength;
    uint8_t loginLength;
    uint8_t hashLength;
    uint8_t saltLength;
    uint8_t role;
public:
    User() = default;
    User(std::string name, std::string login, uint8_t role, std::string hash, std::string salt);
    uint32_t getID() const;
    std::string getName() const;
    std::string getLogin() const;
    std::string getHash() const;
    std::string getSalt() const;
    uint8_t getNameLength() const;
    uint8_t getLoginLength() const;
    uint8_t getHashLength() const;
    uint8_t getRole() const;
    void setName(std::string newName);
    void setLogin(std::string newLogin);
    void setHash(std::string newHash);
    void setSalt(std::string newSalt);
};