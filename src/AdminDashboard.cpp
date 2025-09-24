#include "../include/AdminDashBoard.h"
#include <iostream>

AdminDashboard::AdminDashboard(UserSession *session) 
	: BaseDashboard(session){
	setlocale(LC_ALL, "Russian");
}

AdminDashboard::~AdminDashboard() {}

void AdminDashboard::showMenu() {
    std::cout << "\n=== ЛИЧНЫЙ КАБИНЕТ АДМИНИСТРАТОРА ===\n";
    std::cout << "1. Вывести список всех пользователей\n";
    std::cout << "2. Вывести список задач пользователя\n";
    std::cout << "3. Назначить администратора\n";
    std::cout << "4. Разжаловать администратора\n";
    std::cout << "5. Удалить задачу пользователя\n";
    std::cout << "6. Удалить пользователя\n";
    std::cout << "7. Посмотреть профиль\n";
    std::cout << "8. Редактировать профиль\n";
    std::cout << "0. Выйти\n";
    std::cout << "Выберите действие: ";
}

void AdminDashboard::processChoice(int choice) {
    switch (choice) {
        case 1: viewAllUsers(); break;
        case 2: viewAllTasksUser(); break;
        case 3: appointAdministrator(); break;
        case 4: demoteAdministrator(); break;
        case 5: deleteTask(); break;
        case 6: deleteUser(); break;
        case 7: viewProfile(); break;
        case 8: editProfile(); break;
        default: std::cout << "Неверный выбор! Попробуйте снова.\n";
    }
}

void AdminDashboard::viewAllUsers() {
    std::string errorMessage = "";
    std::vector<User*> users = currentSession->getUsers(errorMessage);
    
    if (!errorMessage.empty()) {
        std::cout << errorMessage << std::endl;
        return;
    }

    if (users.empty()) {
        std::cout << "Список пользователей пуст\n";
        return;
    }

    std::cout << "=== СПИСОК ВСЕХ ПОЛЬЗОВАТЕЛЕЙ ===\n";

    for (const auto& user : users) {
        std::cout
            << "\nID: " << user->getID()
            << "\nИмя:" << user->getName()
            << "\nЛогин: " << user->getLogin()
            << "\nРоль: " << (user->getRole() ? "администратор\n" : "пользователь\n")
            << "\nКоличество задач: " << currentSession->getUserTasks(user->getID()).size() << std::endl;
    }
}

void AdminDashboard::viewAllTasksUser() {
    int userID;
    std::string errorMessage = "";
    std::cout << "Введите ID пользователя: ";
    std::cin >> userID;

    if (!currentSession->findUserID(userID, errorMessage)) {
        std::cout << errorMessage << std::endl;
        return;
    }

    std::vector<Task*> tasks = currentSession->getTasks(errorMessage);

    if (!errorMessage.empty()) {
        std::cout << errorMessage << std::endl;
        return;
    }

    if (tasks.empty()) {
        std::cout << "У пользователя нет задач.\n";
        return;
    }

    std::cout << "\n=== ЗАДАЧИ ПОЛЬЗОВАТЕЛЯ " << userID << " ===";
    for (const auto& task : tasks) {
        std::cout 
            << "\nНомер: " << task->getID()
            << "\nДата создания: " << task->getDateCreate()
            << "\nНазвание: " << task->getName()
            << "\nОписание: " << task->getDescription()
            << "\nДедлайн: " << task->getDeadline()
            << "\nПриоритет задачи: " << +task->getPriority()
            << "\nСтатус задачи: " << +task->getStatus() << std::endl;
    }
}

void AdminDashboard::appointAdministrator() {
    int userID;
    std::string errorMessage = "";
    std::cout << "\nВведите ID пользователя для выдачи роли администратора: ";
    std::cin >> userID;
    if (currentSession->appointAdministrator(userID, errorMessage)) {
        std::cout << "Роль выдана\n";
    } else {
        std::cout << errorMessage << std::endl;
    }
}

void AdminDashboard::demoteAdministrator() {
    int userID;
    std::string errorMessage = "";
    std::cout << "\nВведите ID пользователя для снятия роли администратора: ";
    std::cin >> userID;
    if (currentSession->demoteAdministrator(userID, errorMessage)) {
        std::cout << "Роль снята\n";
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void AdminDashboard::deleteTask() {
    int taskID;
    std::string errorMessage = "";
    std::cout << "\nВведите ID задачи для удаления: ";
    std::cin >> taskID;
    if (currentSession->deleteTask(taskID, errorMessage)) {
        std::cout << "Задача удалена.\n";
    } else {
        std::cout << errorMessage << std::endl;
    }
}

void AdminDashboard::deleteUser() {
    int userID;
    std::string errorMessage = "";
    std::cout << "\nВведите ID задачи для удаления: ";
    std::cin >> userID;

    if (currentSession->deleteTask(userID, errorMessage)) {
        std::cout << "Пользователь и все его задачи удалены.\n";
    } else {
        std::cout << errorMessage << std::endl;
    }
}