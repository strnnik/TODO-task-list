#include "User.h"

uint32_t User::counterID = 0;

User::User(std::string newName, std::string newLogin, uint8_t newRole) :
    name(newName), login(newLogin), role(newRole){
        ID = counterID++;
    }

void User::setTask(Task newTask) {
    taskList.push_back(newTask);
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

void User::getTasks() const {
    for (auto& task : taskList) {
        std::cout << "ID ������: " << task.getID() << "\n";
        std::cout << "��������: " << task.getName() << "\n";
        std::cout << "��������: " << task.getDescription() << "\n";
        std::cout << "�������: " << task.getDeadline() << "\n\n";
    }
}

void User::setName(std::string newName) {
    name = newName;
}

void User::setLogin(std::string newLogin) {
    login = newLogin;
}