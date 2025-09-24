#pragma once
#include "../include/BaseDashboard.h"

class UserDashboard : public BaseDashboard {
private:
    void showMenu() override;
    void processChoice(int choice) override;

    void addTask();
    void viewTasks();
    void editTask();
    void deleteTask();
    void viewProfile();

    void changeDescription(const uint8_t taskID);
    void changeDeadline(const uint8_t taskID);
    void changeStatus(const uint8_t taskID);

public:
    UserDashboard(UserSession* session);
    ~UserDashboard() override;
};