#include "../include/Task.h"

uint32_t Task::counterID = 0;

Task::Task(uint32_t _userID, std::string _name, std::string _description, 
    uint8_t _priority, uint8_t _status, std::string _deadline) :
    userID(_userID), name(_name), 
    description(_description), priority(_priority), 
    status(_status), deadline(_deadline), 
    dateCreate(createNowDate()), ID(counterID++) {

}

std::string Task::createNowDate() const {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::string date = "";

    if (std::to_string(now->tm_mday).length() == 1)
        date += '0';

    date += '.' + std::to_string(now->tm_mday);

    if (std::to_string(now->tm_mon).length() == 1)
        date += '0';

    date += '.' + std::to_string(now->tm_mon + 1);
    date += '.' + std::to_string(now->tm_year + 1900);

    return date;
}

uint32_t Task::getUserID() const {
    return userID;
}

uint32_t Task::getID() const {
    return ID;
}

uint8_t Task::getStatus() const {
    return status;
}

uint8_t Task::getPriority() const {
    return priority;
}

std::string Task::getDateCreate() const {
    return dateCreate;
}

std::string Task::getDeadline() const {
    return deadline;
}

uint16_t Task::getNameLength() const {
    return nameLength;
}

uint32_t Task::getDescriptionLength() const {
    return descriptionLength;
}

std::string Task::getName() const {
    return name;
}

std::string Task::getDescription() const {
    return description;
}