#pragma once

#include <string>
#include <cstdint>
#include "Date.h"

class Task {
    static uint32_t counterID;
    uint32_t userID;
    uint32_t ID;
    uint8_t status;
    uint8_t priority;
    Date dateCreate;
    std::string deadline;
    uint16_t nameLength;
    uint32_t descriptionLength;
    std::string name;
    std::string description;
public:
    Task(uint32_t userID, std::string name, std::string description, std::string deadline);
    uint32_t getUserID() const;
    uint32_t getID() const;
    uint8_t getStatus() const;
    uint8_t getPriority() const;
    Date getDateCreate() const;
    std::string getDeadline() const;
    uint16_t getNameLength() const;
    uint32_t getDescriptionLength() const;
    std::string getName() const;
    std::string getDescription() const;
};