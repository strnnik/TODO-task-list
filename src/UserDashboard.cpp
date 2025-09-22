// UserDashboard.cpp
#include "../include/UserDashboard.h"
#include <iostream>

UserDashboard::UserDashboard(UserSession* session)
    : BaseDashboard(session) {}

UserDashboard::~UserDashboard() {}

void UserDashboard::showMenu() {
    std::cout << "\n=== ������ ������� ������������ ===\n";
    std::cout << "1. �������� ������\n";
    std::cout << "2. ����������� ��� ������\n";
    std::cout << "3. ������������� ������\n";
    std::cout << "4. ������� ������\n";
    std::cout << "5. ���������� �������\n";
    std::cout << "6. ������������� �������\n";
    std::cout << "0. �����\n";
    std::cout << "�������� ��������: ";
}

void UserDashboard::processChoice(int choice) {
    switch (choice) {
    case 1: addTask(); break;
    case 2: viewTasks(); break;
    case 3: editTask(); break;
    case 4: deleteTask(); break;
    case 5: viewProfile(); break;
    case 6: editProfile(); break;
    default: std::cout << "�������� �����! ���������� �����.\n";
    }
}

void UserDashboard::addTask() {
    std::string nameTask, descriptionTask, deadlineTask, errorMessage = "";
    int priorityTask, statusTask;
    std::cout << "\n���� ���������� � ������\n";
    std::cout << "��������: ";
    std::cin >> nameTask;
    std::cout << "��������: ";
    std::cin >> descriptionTask;
    std::cout << "�������: ";
    std::cin >> deadlineTask;
    std::cout << "��������� ������ (0, 1, 2 - �� �������� � �������� ����������): ";
    std::cin >> priorityTask;
    std::cout << "������ ������ (0 - �� �����������, 1 - � �������� ����������, 2 - ���������): ";
    std::cin >> statusTask;
    if (currentSession->addTask(nameTask, descriptionTask, static_cast<uint8_t>(priorityTask),
        static_cast<uint8_t>(statusTask), deadlineTask, errorMessage))
        std::cout << "������ ���������\n";
    else
        std::cout << errorMessage << std::endl;
}

void UserDashboard::viewTasks() {
    std::vector<Task*> tasks = currentSession->getUserTasks();

    if (tasks.empty()) {
        std::cout << "� ��� ��� �����.\n";
        return;
    }

    std::cout << "\n=== ���� ������ ===";
    for (const auto& task : tasks) {
        std::cout << "\n�����: " << task->getID()
            << "\n���� ��������: " << task->getDateCreate()
            << "\n��������: " << task->getName()
            << "\n��������: " << task->getDescription()
            << "\n�������: " << task->getDeadline()
            << "\n��������� ������: " << +task->getPriority()
            << "\n������ ������: " << +task->getStatus() << std::endl;
    }
}

void UserDashboard::editTask() {
    int taskID, choice;
    std::string errorMessage = "";
    std::cout << "\n������� ID ������ ��� ��������������: ";
    std::cin >> taskID;

    if (!currentSession->findUserTaskID(taskID, errorMessage)) {
        std::cout << errorMessage;
        return;
    }

    std::cout << "\n=== �������������� ������ " << taskID << " === \n";
    std::cout << "1. ��������\n";
    std::cout << "2. �������\n";
    std::cout << "3. ������ ����������\n";
    std::cout << "�������� ��������: ";
    std::cin >> choice;

    switch (choice) {
        case 1: changeDeadline(taskID); break;
        case 2: changeDeadline(taskID); break;
        case 3: changeStatus(taskID); break;
        default: std::cout << "�������� �����! ���������� �����.\n";
    }
}

void UserDashboard::changeDescription(const uint8_t taskID) {
    std::string newDescr = "", errorMessage = "";
    std::cout << "\n������� ����� ��������: ";
    std::getline(std::cin, newDescr);
    if (currentSession->changeDescription(taskID, newDescr, errorMessage)) {
        std::cout << "�������� ������ ��������" << std::endl;
    } else {
        std::cout << errorMessage << std::endl;
    }
}

void UserDashboard::changeDeadline(const uint8_t taskID) {
    std::string newDeadline = "", errorMessage = "";
    std::cout << "\n������� ����� �������: ";
    std::cin >> newDeadline;
    if (currentSession->changeDeadline(taskID, newDeadline, errorMessage)) {
        std::cout << "������� ������ �������" << std::endl;
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void UserDashboard::changeStatus(const uint8_t taskID) {
    std::string errorMessage = "";
    int newStatus;
    std::cout << "\n������� ����� ������: ";
    std::cin >> newStatus;
    if (currentSession->changeStatus(taskID, static_cast<uint8_t>(newStatus), errorMessage)) {
        std::cout << "������ ������ �������" << std::endl;
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void UserDashboard::deleteTask() {
    int taskID;
    std::string errorMessage = "";
    std::cout << "\n������� ID ������ ��� ��������: ";
    std::cin >> taskID;
    if (currentSession->deleteTask(taskID, errorMessage)) {
        std::cout << "������ �������.\n";
    }
    else {
        std::cout << errorMessage << std::endl;
    }
}

void UserDashboard::viewProfile() {
    if (currentSession->getCurrentUser()) {
        User* user = currentSession->getCurrentUser();
        std::cout << "\n=== ��� ������� ==="
            << "\nID: " << user->getID()
            << "\n��� ������������: " << user->getName()
            << "\n�����: " << user->getLogin()
            << "\n���������� �����: " << currentSession->getUserTasks().size() << std::endl;
    }
}

void showEditProfileMenu() {
    std::cout << "\n=== �������������� ������� ===\n";
    std::cout << "1. �������� ���\n";
    std::cout << "2. �������� �����\n";
    std::cout << "3. �������� ������\n";
    std::cout << "0. �����\n";
    std::cout << "�������� ��������: ";
}

void UserDashboard::editProfile(){
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

void UserDashboard::changeName(){
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

void UserDashboard::changeLogin(){
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

void UserDashboard::changePassword() {
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