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

void BaseDashboard::viewProfile() {
    if (currentSession->getCurrentUser()) {
        User* user = currentSession->getCurrentUser();
        std::cout << "\n=== ВАШ ПРОФИЛЬ ==="
            << "\nID: " << user->getID()
            << "\nИмя пользователя: " << user->getName()
            << "\nРоль: " << (user->getRole() ? "администратор" : "пользователь")
            << "\nЛогин: " << user->getLogin()
            << "\nКоличество задач: " << currentSession->getUserTasks(user->getID()).size() << std::endl;
    }
}

void BaseDashboard::showEditProfileMenu() {
    std::cout << "\n=== РЕДАКТИРОВАНИЕ ПРОФИЛЯ ===\n";
    std::cout << "1. Изменить имя\n";
    std::cout << "2. Изменить логин\n";
    std::cout << "3. Изменить пароль\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

void BaseDashboard::editProfile() {
    showEditProfileMenu();
    int choice;
    std::cin >> choice;
    switch (choice) {
    case 1: changeName(); break;
    case 2: changeLogin(); break;
    case 3: changePassword(); break;
    default: std::cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

void BaseDashboard::changeName() {
    std::string newName, errorMessage = "";
    std::cout << "\nВведите новое имя: ";
    std::cin >> newName;
    if (currentSession->changeName(newName, errorMessage)) {
        std::cout << "Имя изменено\n";
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void BaseDashboard::changeLogin() {
    std::string newLogin, errorMessage = "";
    std::cout << "\nВведите новый логин: ";
    std::cin >> newLogin;
    if (currentSession->changeLogin(newLogin, errorMessage)) {
        std::cout << "Логин изменен\n";
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void BaseDashboard::changePassword() {
    std::string newPassword, oldPassword, errorMessage;
    std::cout << "\nВведите старый пароль: ";
    std::cin >> oldPassword;
    std::cout << "Введите новый пароль: ";
    std::cin >> newPassword;
    if (currentSession->changePassword(oldPassword, newPassword, errorMessage)) {
        std::cout << "Пароль изменен" << std::endl;
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void BaseDashboard::logout() {
    if (currentSession) {
        currentSession->invalidate();
        std::cout << "Вы вышли из системы.\n";
    }
}