#include "AuthService.h"

AuthService::AuthService(std::unordered_map<uint32_t, User>& users) : users(users) {
    setlocale(LC_ALL, "Russian");
};

User* AuthService::findUserByLogin(const std::string& login) {
    for (auto& pair : users) {
        if (pair.second.getLogin() == login) {
            return &pair.second;
        }
    }
    return nullptr;
}

bool AuthService::loginExists(const std::string& name) {
    return findUserByLogin(name) != nullptr;
}

bool AuthService::registerUser(const std::string& name, const std::string& login, const std::string& password, uint8_t role, std::string& errorMessage) {
    if (name.empty() || login.empty() || password.empty()) {
        errorMessage = "Имя пользователя, логин и пароль не могут быть пустыми";
        return false;
    }

    if (loginExists(name)) {
        errorMessage = "Пользователь с таким логином уже существует";
        return false;
    }

    if (password.length() < 6) {
        errorMessage = "Пароль должен содержать не менее 6 символов";
        return false;
    }

    if (role > 2) {
        errorMessage = "Такой роли не предусмотрено";
        return false;
    }

    std::string salt = PasswordHasher::generateSalt();
    std::string hash = PasswordHasher::generateHash(password, salt);

    User newUser(name, login, role, hash, salt);
    users[newUser.getID()] = newUser;

    return true;
}

bool AuthService::loginUser(const std::string& login, const std::string& password, std::string& errorMessage) {
    if (login.empty() || password.empty()) {
        errorMessage = "Имя пользователя и пароль не могут быть пустыми";
        return false;
    }

    if (!loginExists(login)) {
        errorMessage = "Пользователя с таким логином не существует";
        return false;
    }

    User* user = findUserByLogin(login);

    if (!PasswordHasher::verifyPassword(password, user->getHash(), user->getSalt())) {
        errorMessage = "Неверный пароль";
        return false;
    }

    return true;
}