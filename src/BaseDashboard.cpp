#include "../include/BaseDashboard.h"

BaseDashboard::BaseDashboard(UserSession* session)
    : currentSession(session) {
    setlocale(LC_ALL, "Russian");
}

BaseDashboard::~BaseDashboard() {}

bool BaseDashboard::isSessionValid() const {
    return currentSession && currentSession->isValidSession();
}

void BaseDashboard::run() {
    if (!isSessionValid()) {
        std::cout << "Сессия неактуальна\n";
        return;
    }

    std::cout << "\nДобро пожаловать, " << currentSession->getCurrentUser()->getName() << "!\n";

    int choice;

    do {
        showMenu();

        std::cin >> choice;

        if (!isSessionValid()) {
            std::cout << "Сессия истекла. Пожалуйста, войдите снова.\n";
            break;
        }

        if (choice != 0) {
            processChoice(choice);
        }

    } while (choice != 0);

    std::cout << "Выход из личного кабинета...\n";
    logout();
}

void BaseDashboard::logout() {
    if (currentSession) {
        currentSession->invalidate();
        std::cout << "Вы вышли из системы.\n";
    }
}