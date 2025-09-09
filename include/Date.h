#pragma once

#include <cstdint>
#include <ctime>

struct Date {
    uint16_t year;
    uint8_t month;
    uint8_t day;

    void createNowDate();
};