#pragma once

#include <string>
#include <cstdint>
#include <ctime>

class Task {
    static uint32_t counterID;
    uint32_t ID;
    uint32_t userID;
    std::string name;
    std::string description;
    std::string deadline;
    std::string dateCreate;
    uint8_t status;
    uint8_t priority;
    uint16_t nameLength;
    uint32_t descriptionLength;
    
public:
    Task() = default;
    Task(uint32_t userID, std::string name, std::string description, 
        uint8_t priorityTask, uint8_t statusTask, std::string deadline);
    uint32_t getUserID() const;
    uint32_t getID() const;
    uint8_t getStatus() const;
    uint8_t getPriority() const;
    std::string createNowDate() const;
    std::string getDateCreate() const;
    std::string getDeadline() const;
    uint16_t getNameLength() const;
    uint32_t getDescriptionLength() const;
    std::string getName() const;
    std::string getDescription() const;
};