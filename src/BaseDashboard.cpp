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
        std::cout << "������ �����������\n";
        return;
    }

    std::cout << "\n����� ����������, " << currentSession->getCurrentUser()->getName() << "!\n";

    int choice;

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
    logout();
}

void BaseDashboard::viewProfile() {
    if (currentSession->getCurrentUser()) {
        User* user = currentSession->getCurrentUser();
        std::cout << "\n=== ��� ������� ==="
            << "\nID: " << user->getID()
            << "\n��� ������������: " << user->getName()
            << "\n����: " << (user->getRole() ? "�������������" : "������������")
            << "\n�����: " << user->getLogin()
            << "\n���������� �����: " << currentSession->getUserTasks(user->getID()).size() << std::endl;
    }
}

void BaseDashboard::showEditProfileMenu() {
    std::cout << "\n=== �������������� ������� ===\n";
    std::cout << "1. �������� ���\n";
    std::cout << "2. �������� �����\n";
    std::cout << "3. �������� ������\n";
    std::cout << "0. �����\n";
    std::cout << "�������� ��������: ";
}

void BaseDashboard::editProfile() {
    showEditProfileMenu();
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1: changeName(); break;
    case 2: changeLogin(); break;
    case 3: changePassword(); break;
    default: std::cout << "�������� �����! ���������� �����.\n";
    }
}

void BaseDashboard::changeName() {
    std::string newName, errorMessage = "";
    std::cout << "\n������� ����� ���: ";
    std::cin >> newName;
    if (currentSession->changeName(newName, errorMessage)) {
        std::cout << "��� ��������\n";
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void BaseDashboard::changeLogin() {
    std::string newLogin, errorMessage = "";
    std::cout << "\n������� ����� �����: ";
    std::cin >> newLogin;
    if (currentSession->changeLogin(newLogin, errorMessage)) {
        std::cout << "����� �������\n";
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void BaseDashboard::changePassword() {
    std::string newPassword, oldPassword, errorMessage;
    std::cout << "\n������� ������ ������: ";
    std::cin >> oldPassword;
    std::cout << "������� ����� ������: ";
    std::cin >> newPassword;
    if (currentSession->changePassword(oldPassword, newPassword, errorMessage)) {
        std::cout << "������ �������" << std::endl;
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void BaseDashboard::logout() {
    if (currentSession) {
        currentSession->invalidate();
        std::cout << "�� ����� �� �������.\n";
    }
}