#include "AuthService.h"

AuthService::AuthService(std::unordered_map<int, User>& users) : users(users) {};

User* AuthService::findUserByLogin(const std::string& name) {
    for (auto& pair : users) {
        if (pair.second.getLogin() == name) {
            return &pair.second;
        }
    }
    return nullptr;
}

bool AuthService::loginExists(const std::string& name) {
    return findUserByLogin(name) != nullptr;
}

bool AuthService::registerUser(const std::string& name, const std::string& login, uint8_t role, const std::string password, std::string& errorMessage) {
    if (name.empty() || login.empty() || password.empty()) {
        errorMessage = "��� ������������ � ������ �� ����� ���� �������";
        return false;
    }

    if (loginExists(name)) {
        errorMessage = "������������ � ����� ������� ��� ����������";
        return false;
    }

    if (password.length() < 6) {
        errorMessage = "������ ������ ��������� �� ����� 6 ��������";
        return false;
    }

    std::string salt = PasswordHasher::generateSalt();
    std::string hash = PasswordHasher::generateHash(password, salt);

    User newUser(name, login, role, hash, salt);
    users[newUser.getID()] = newUser;

    return true;
}

bool AuthService::login(const std::string& login, const std::string& password, std::string& errorMessage) {
    if (login.empty() || password.empty()) {
        errorMessage = "��� ������������ � ������ �� ����� ���� �������";
        return false;
    }

    if (!loginExists(login)) {
        errorMessage = "������������ � ����� ������� �� ����������";
        return false;
    }

    User* user = findUserByLogin(login);

    if (PasswordHasher::verifyPassword(password, user->getHash(), user->getSalt())) {
        errorMessage = "�������� ������";
        return false;
    }

    return true;
}