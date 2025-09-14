// AuthService.h
#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include "User.h"
#include "PasswordHasher.h"

class AuthService {
private:
    std::unordered_map<int, User>& users;

public:
    AuthService(std::unordered_map<int, User>& users);

    User* findUserByLogin(const std::string& login);
    bool loginExists(const std::string& login);
    bool registerUser(const std::string& name, const std::string& login, uint8_t role, const std::string password, std::string& errorMessage);
    bool login(const std::string& login, const std::string& password, std::string& errorMessage);
    void session(User* user);
};