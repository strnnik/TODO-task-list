#include <iostream>
#include <map>
#include <string>
#include <windows.h>
#include "../include/User.h"
#include "../include/Task.h"
#include "../include/Date.h"

using namespace std;

map<uint32_t, User> dataUser;
map<uint32_t, Task> dataTask;
map<string, uint32_t> userLoginID;

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
    string name, login;
    uint8_t role;
    cout << "\nИмя: ";
    cin >> name;
    cout << "Логин: ";
    cin >> login;
    cout << "Роль: ";
    cin >> role;
    User newUser = User(name, login, role);
    dataUser[newUser.getID()] = newUser;
    cout << "ID: " << newUser.getID() << endl;
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
    dataUser[userID].setTask(newTask);
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
            dataUser[currUserID].getTasks();
            break;
        }
        case 4: {
            cout << "Введите номер задачи: ";
            int num;
            cin >> num;

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

int main(){
    setlocale(LC_ALL, "Russian");
    //tConsoleOutputCP(CP_UTF8);
    //tConsoleCP(CP_UTF8);

    while (true) {
        cout << "\n0. Войти\n";
        cout << "1. Создать пользователя\n";
        cout << "2. Вывести список всех пользователей\n";
        cout << "3. Выход\n";
        cout << "Выберите действие: ";
        int k;
        cin >> k;

        switch (k) {
        case 0: {
            cout << "\nВведите ID пользователя: ";
            uint32_t idUser;
            cin >> idUser;
            if (dataUser.find(idUser) != dataUser.end())
                session(idUser);
            else {
                cout << "Такого пользователя не существует\n";
            }
            break;
        }
        case 1: {
            inputUserData();
            break;
        }
        case 2: {

            break;
        }
        case 3: {

            break;
        }
        default:
            break;
        }
    }

    return 0;
}