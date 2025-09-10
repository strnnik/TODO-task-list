#include <iostream>
#include <unordered_map>
#include <string>
#include <windows.h>
#include "../include/User.h"
#include "../include/Task.h"
#include "../include/Date.h"

using namespace std;

unordered_map<uint32_t, User> dataUser;
unordered_map<uint32_t, Task> dataTask;
unordered_map<string, uint32_t> userLoginID;

void editUser(uint32_t userID) {
    cout << "1. Изменить имя\n";
    cout << "2. Изменить логин\n";
    cout << "Выберите действие: ";
    int k;
    cin >> k;
    while (true) {
        switch (k) {
        case 1: {
            cout << "Введите новое имя: ";
            string newName;
            cin >> newName;

            break;
        }
        }
    }
}

void inputUserData() {
    string name, login, password;
    uint8_t role;
    cout << "\nИмя: ";
    cin >> name;
    cout << "Логин: ";
    cin >> login;
    cout << "Пароль: ";
    cin >> password;
    cout << "Роль: ";
    cin >> role;
    User newUser = User(name, login, password, role);
    dataUser[newUser.getID()] = newUser;
    userLoginID[login] = newUser.getID();
}

void addTask(uint32_t userID) {
    string name, description, deadline;
    cout << "\nНазвание: ";
    cin >> name;
    cout << "Описание: ";
    cin >> description;
    cout << "Дедлайн: ";
    cin >> deadline;
    Task newTask = Task(userID, name, description, deadline);
    dataTask[userID] = newTask;
}

void outputTaskList(uint32_t userID) {
    bool findTask = false;

    for (auto [id, task] : dataTask) {
        if (id == userID) {
            findTask = true;
            cout << "Номер задачи: " << task.getID() << endl;
            cout << "Название: " << task.getName() << endl;
            cout << "Описание: " << task.getDescription() << endl;
            cout << "Дедлайн: " << task.getDeadline() << endl;
            cout << "Приоритет задачи: " << task.getPriority() << endl;
            cout << "Статус задачи: " << task.getStatus() << endl << endl;
        }
    }

    if (!findTask)
        cout << "Список задач пользователя пуст.\n";
}

void deleteTask(uint32_t userID) {
    cout << "Введите ID задачи: ";
    int taskID;
    cin >> taskID;

    for (auto [id, task] : dataTask) {
        if (taskID == task.getID() && (userID == task.getID() || dataUser[userID].getRole())) {
            dataTask.erase(id);
            cout << "Задача удалена.\n";
            return;
        }
    }

    cout << "Задачи с таким ID не существует или недостаточно прав, чтобы удалить чужую задачу!\n";
}

void session(uint32_t currUserID) {
    cout << "\nВы вошли в аккаунт пользователя: " << dataUser[currUserID].getName() << endl;
    bool login = true;
    while (login) {
        cout << "\n1. Добавить задачу\n";
        cout << "2. Редактировать информацию о пользователе\n";
        cout << "3. Вывести список задач\n";
        cout << "4. Удалить задачу\n";
        cout << "0. Выход из сессии\n";
        cout << "Выберите действие: ";
        int k;
        cin >> k;
        switch (k)
        {
        case 1: {
            addTask(currUserID);
            break;
        }
        case 2: {
            editUser(currUserID);
            break;
        }
        case 3: {
            outputTaskList(currUserID);
            break;
        }
        case 4: {
            deleteTask(currUserID);
            break;
        }
        case 0: {
            login = false;
            break;
        }
        default:
            break;
        }
    }
}

void authorization() {
    cout << "\nВведите логин: ";
    string login, password;
    cin >> login;
    if (userLoginID.find(login) == userLoginID.end()){
        cout << "Такого пользователя не существует\n";
        return;
    }
    
    cout << "Введите пароль: ";
    cin >> password;

    while (!dataUser[userLoginID[login]].verifyPassword(password)) {
        cout << "Пароль неправильный. Повторить ввод? (1/0) ";
        int key;
        cin >> key;
        if (key) {
            cout << "Введите пароль: ";
            cin >> password;
        }
        else {
            return;
        }
    }

    session(userLoginID[login]);
}

void outputAllUsers() {
    cout << endl;
    for (auto [id, user] : dataUser) {
        cout << "ID: " << id << endl;
        cout << "Имя: " << user.getName() << endl;
        cout << "Роль: " << user.getRole() << endl;
    }
}

int main(){
    setlocale(LC_ALL, "Russian");
    //tConsoleOutputCP(CP_UTF8);
    //tConsoleCP(CP_UTF8);

    while (true) {
        cout << "0. Войти\n";
        cout << "1. Создать пользователя\n";
        cout << "2. Вывести список всех пользователей\n";
        cout << "3. Выход\n";
        cout << "Выберите действие: ";
        int k;
        cin >> k;

        switch (k) {
        case 0: {
            authorization();
            break;
        }
        case 1: {
            inputUserData();
            break;
        }
        case 2: {
            outputAllUsers();
            break;
        }
        case 3: {
            return 0;
            break;
        }
        default:
            break;
        }

        cout << endl;
    }

    return 0;
}