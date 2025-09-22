#include "../include/BaseDashboard.h"

BaseDashboard::BaseDashboard(UserSession* session)
    : currentSession(session) {

}

BaseDashboard::~BaseDashboard() {

}

bool BaseDashboard::isSessionValid() const {
    return currentSession && currentSession->isValidSession();
}

void BaseDashboard::run() {
    if (!isSessionValid()) {
        std::cout << "������: ������ ��������������� ��� �������!\n";
        return;
    }

    std::cout << "\n����� ����������, " << currentSession->getCurrentUser()->getName() << "!\n";

    int choice = -1;

    do {
        showMenu();

        std::cin >> choice;

        if (!isSessionValid()) {
            std::cout << "������ �������. ����������, ������� �����.\n";
            break;
        }

        if (choice != 0) {
            processChoice(choice);
        }

    } while (choice != 0);

    std::cout << "����� �� ������� ��������...\n";
}

void BaseDashboard::logout() {
    if (currentSession) {
        currentSession->invalidate();
        std::cout << "�� ����� �� �������.\n";
    }
}