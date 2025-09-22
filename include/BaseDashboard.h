#pragma once

#include <iostream>
#include "UserSession.h"

class BaseDashboard {
protected:
    UserSession* currentSession;

    virtual void showMenu() = 0;
    virtual void processChoice(int choice) = 0;

public:
    BaseDashboard(UserSession* session);
    virtual ~BaseDashboard();

    virtual void run();
    void logout();
    bool isSessionValid() const;
};