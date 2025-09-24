#pragma once
#include "../include/BaseDashboard.h"
#include <vector>

class AdminDashboard : public BaseDashboard {
private:
    void showMenu() override;
    void processChoice(int choice) override;

    void viewAllUsers();
    void viewAllTasksUser();
    void appointAdministrator();
    void demoteAdministrator();
    void deleteTask();
    void deleteUser();

public:
    AdminDashboard(UserSession* session);
    ~AdminDashboard() override;
};