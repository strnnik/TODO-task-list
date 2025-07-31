#include "../include/Task.h"
#include <chrono>
using namespace std::chrono;
uint32_t Task::counterID = 0;

Task::Task(uint32_t _userID, std::string _name, std::string _description, uint64_t _deadline) :
    userID(_userID), name(_name), description(_description), deadline(_deadline){
        ID = counterID++;
        dateCreate.createNowDate();
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

Date Task::getDateCreate() const {
    return dateCreate;
}

uint64_t Task::getDeadline() const {
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