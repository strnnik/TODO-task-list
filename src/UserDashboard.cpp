// UserDashboard.cpp
#include "../include/UserDashboard.h"
#include <iostream>

UserDashboard::UserDashboard(UserSession* session)
    : BaseDashboard(session) {}

UserDashboard::~UserDashboard() {}

void UserDashboard::showMenu() {
    std::cout << "\n=== ЛИЧНЫЙ КАБИНЕТ ПОЛЬЗОВАТЕЛЯ ===\n";
    std::cout << "1. Добавить задачу\n";
    std::cout << "2. Просмотреть мои задачи\n";
    std::cout << "3. Редактировать задачу\n";
    std::cout << "4. Удалить задачу\n";
    std::cout << "5. Посмотреть профиль\n";
    std::cout << "6. Редактировать профиль\n";
    std::cout << "0. Выйти\n";
    std::cout << "Выберите действие: ";
}

void UserDashboard::processChoice(int choice) {
    switch (choice) {
    case 1: addTask(); break;
    case 2: viewTasks(); break;
    case 3: editTask(); break;
    case 4: deleteTask(); break;
    case 5: viewProfile(); break;
    case 6: editProfile(); break;
    default: std::cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

void UserDashboard::addTask() {
    std::string nameTask, descriptionTask, deadlineTask, errorMessage = "";
    int priorityTask, statusTask;
    std::cout << "\nВвод информации о задаче\n";
    std::cout << "Название: ";
    std::cin >> nameTask;
    std::cout << "Описание: ";
    std::cin >> descriptionTask;
    std::cout << "Дедлайн: ";
    std::cin >> deadlineTask;
    std::cout << "Приоритет задачи (0, 1, 2 - от меньшего к большему приоритету): ";
    std::cin >> priorityTask;
    std::cout << "Статус задачи (0 - не выполняется, 1 - в процессе выполнения, 2 - выполнена): ";
    std::cin >> statusTask;
    if (currentSession->addTask(nameTask, descriptionTask, static_cast<uint8_t>(priorityTask),
        static_cast<uint8_t>(statusTask), deadlineTask, errorMessage))
        std::cout << "Задача добавлена\n";
    else
        std::cout << errorMessage << std::endl;
}

void UserDashboard::viewTasks() {
    std::vector<Task*> tasks = currentSession->getUserTasks();

    if (tasks.empty()) {
        std::cout << "У вас нет задач.\n";
        return;
    }

    std::cout << "\n=== ВАШИ ЗАДАЧИ ===";
    for (const auto& task : tasks) {
        std::cout << "\nНомер: " << task->getID()
            << "\nДата создания: " << task->getDateCreate()
            << "\nНазвание: " << task->getName()
            << "\nОписание: " << task->getDescription()
            << "\nДедлайн: " << task->getDeadline()
            << "\nПриоритет задачи: " << +task->getPriority()
            << "\nСтатус задачи: " << +task->getStatus() << std::endl;
    }
}

void UserDashboard::editTask() {
    int taskID, choice;
    std::string errorMessage = "";
    std::cout << "\nВведите ID задачи для редактирования: ";
    std::cin >> taskID;

    if (!currentSession->findUserTaskID(taskID, errorMessage)) {
        std::cout << errorMessage;
        return;
    }

    std::cout << "\n=== РЕДАКТИРОВАНИЕ ЗАДАЧИ " << taskID << " === \n";
    std::cout << "1. Описание\n";
    std::cout << "2. Дедлайн\n";
    std::cout << "3. Статус выполнения\n";
    std::cout << "Выберите действие: ";
    std::cin >> choice;

    switch (choice) {
        case 1: changeDeadline(taskID); break;
        case 2: changeDeadline(taskID); break;
        case 3: changeStatus(taskID); break;
        default: std::cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

void UserDashboard::changeDescription(const uint8_t taskID) {
    std::string newDescr = "", errorMessage = "";
    std::cout << "\nВведите новое описание: ";
    std::getline(std::cin, newDescr);
    if (currentSession->changeDescription(taskID, newDescr, errorMessage)) {
        std::cout << "Описание задачи изменено" << std::endl;
    } else {
        std::cout << errorMessage << std::endl;
    }
}

void UserDashboard::changeDeadline(const uint8_t taskID) {
    std::string newDeadline = "", errorMessage = "";
    std::cout << "\nВведите новый дедлайн: ";
    std::cin >> newDeadline;
    if (currentSession->changeDeadline(taskID, newDeadline, errorMessage)) {
        std::cout << "Дедлайн задачи изменен" << std::endl;
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void UserDashboard::changeStatus(const uint8_t taskID) {
    std::string errorMessage = "";
    int newStatus;
    std::cout << "\nВведите новый статус: ";
    std::cin >> newStatus;
    if (currentSession->changeStatus(taskID, static_cast<uint8_t>(newStatus), errorMessage)) {
        std::cout << "Статус задачи изменен" << std::endl;
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void UserDashboard::deleteTask() {
    int taskID;
    std::string errorMessage = "";
    std::cout << "\nВведите ID задачи для удаления: ";
    std::cin >> taskID;
    if (currentSession->deleteTask(taskID, errorMessage)) {
        std::cout << "Задача удалена.\n";
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void UserDashboard::viewProfile() {
    if (currentSession->getCurrentUser()) {
        User* user = currentSession->getCurrentUser();
        std::cout << "\n=== ВАШ ПРОФИЛЬ ==="
            << "\nID: " << user->getID()
            << "\nИмя пользователя: " << user->getName()
            << "\nЛогин: " << user->getLogin()
            << "\nКоличество задач: " << currentSession->getUserTasks().size() << std::endl;
    }
}

void showEditProfileMenu() {
    std::cout << "\n=== РЕДАКТИРОВАНИЕ ПРОФИЛЯ ===\n";
    std::cout << "1. Изменить имя\n";
    std::cout << "2. Изменить логин\n";
    std::cout << "3. Изменить пароль\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

void UserDashboard::editProfile(){
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

void UserDashboard::changeName(){
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

void UserDashboard::changeLogin(){
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

void UserDashboard::changePassword() {
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