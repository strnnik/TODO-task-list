#include "../include/AdminDashBoard.h"
#include <iostream>

AdminDashboard::AdminDashboard(UserSession *session) 
	: BaseDashboard(session){
	setlocale(LC_ALL, "Russian");
}

AdminDashboard::~AdminDashboard() {}

void AdminDashboard::showMenu() {
    std::cout << "\n=== ������ ������� �������������� ===\n";
    std::cout << "1. ������� ������ ���� �������������\n";
    std::cout << "2. ������� ������ ����� ������������\n";
    std::cout << "3. ��������� ��������������\n";
    std::cout << "4. ����������� ��������������\n";
    std::cout << "5. ������� ������ ������������\n";
    std::cout << "6. ������� ������������\n";
    std::cout << "7. ���������� �������\n";
    std::cout << "8. ������������� �������\n";
    std::cout << "0. �����\n";
    std::cout << "�������� ��������: ";
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
        default: std::cout << "�������� �����! ���������� �����.\n";
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
        std::cout << "������ ������������� ����\n";
        return;
    }

    std::cout << "=== ������ ���� ������������� ===\n";

    for (const auto& user : users) {
        std::cout
            << "\nID: " << user->getID()
            << "\n���:" << user->getName()
            << "\n�����: " << user->getLogin()
            << "\n����: " << (user->getRole() ? "�������������\n" : "������������\n")
            << "\n���������� �����: " << currentSession->getUserTasks(user->getID()).size() << std::endl;
    }
}

void AdminDashboard::viewAllTasksUser() {
    int userID;
    std::string errorMessage = "";
    std::cout << "������� ID ������������: ";
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
        std::cout << "� ������������ ��� �����.\n";
        return;
    }

    std::cout << "\n=== ������ ������������ " << userID << " ===";
    for (const auto& task : tasks) {
        std::cout 
            << "\n�����: " << task->getID()
            << "\n���� ��������: " << task->getDateCreate()
            << "\n��������: " << task->getName()
            << "\n��������: " << task->getDescription()
            << "\n�������: " << task->getDeadline()
            << "\n��������� ������: " << +task->getPriority()
            << "\n������ ������: " << +task->getStatus() << std::endl;
    }
}

void AdminDashboard::appointAdministrator() {
    int userID;
    std::string errorMessage = "";
    std::cout << "\n������� ID ������������ ��� ������ ���� ��������������: ";
    std::cin >> userID;
    if (currentSession->appointAdministrator(userID, errorMessage)) {
        std::cout << "���� ������\n";
    } else {
        std::cout << errorMessage << std::endl;
    }
}

void AdminDashboard::demoteAdministrator() {
    int userID;
    std::string errorMessage = "";
    std::cout << "\n������� ID ������������ ��� ������ ���� ��������������: ";
    std::cin >> userID;
    if (currentSession->demoteAdministrator(userID, errorMessage)) {
        std::cout << "���� �����\n";
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void AdminDashboard::deleteTask() {
    int taskID;
    std::string errorMessage = "";
    std::cout << "\n������� ID ������ ��� ��������: ";
    std::cin >> taskID;
    if (currentSession->deleteTask(taskID, errorMessage)) {
        std::cout << "������ �������.\n";
    } else {
        std::cout << errorMessage << std::endl;
    }
}

void AdminDashboard::deleteUser() {
    int userID;
    std::string errorMessage = "";
    std::cout << "\n������� ID ������ ��� ��������: ";
    std::cin >> userID;

    if (currentSession->deleteTask(userID, errorMessage)) {
        std::cout << "������������ � ��� ��� ������ �������.\n";
    } else {
        std::cout << errorMessage << std::endl;
    }
}