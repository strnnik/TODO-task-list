#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include "User.h"
#include "PasswordHasher.h"

class AuthService {
private:
    std::unordered_map<uint32_t, User>& users;

public:
    AuthService(std::unordered_map<uint32_t, User>& users);
    User* findUserByLogin(const std::string& login);
    bool loginExists(const std::string& login);
    bool registerUser(const std::string& name, const std::string& login, const std::string& password, uint8_t role, std::string& errorMessage);
    bool loginUser(const std::string& login, const std::string& password, std::string& errorMessage);
};