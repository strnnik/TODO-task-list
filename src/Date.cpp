#include "../include/Date.h"
#include <ctime>

void Date::createNowDate() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    
    year = static_cast<uint16_t>(now->tm_year + 1900);
    month = static_cast<uint8_t>(now->tm_mon + 1);
    day = static_cast<uint8_t>(now->tm_mday);
}