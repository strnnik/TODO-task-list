#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>
#include "../include/User.h"
#include "../include/Task.h"
#include "../include/AuthService.h"
#include "../include/UserSession.h"
#include "../include/UserDashBoard.h"
#include "../include/AdminDashBoard.h"
#include "../include/BaseDashBoard.h"

using namespace std;

unordered_map<uint32_t, User> dataUser;
unordered_map<uint32_t, Task> dataTask;

void registration() {
    AuthService auth = AuthService(dataUser);
    string name, login, password, errorMessage = "";
    int role;
    cout << "\nРегистрация пользователя\n";
    cout << "Имя: ";
    cin >> name;
    cout << "Логин: ";
    cin >> login;
    cout << "Пароль: ";
    cin >> password;

    while (!auth.registerUser(name, login, password, 0, errorMessage)) {
        cout << errorMessage << ". Повторить ввод? (1/0) ";
        int key;
        cin >> key;
        if (!key)
            return;
        cout << "\nИмя: ";
        cin >> name;
        cout << "Логин: ";
        cin >> login;
        cout << "Пароль: ";
        cin >> password;
        errorMessage = "";
    }

    cout << "Регистрация прошла успешно\n";
}

void authorization() {
    AuthService auth = AuthService(dataUser);
    string login, password, errorMessage = "";
    cout << "\nВведите логин: ";
    cin >> login;
    cout << "Введите пароль: ";
    cin >> password;

    while (!auth.loginUser(login, password, errorMessage)) {
        cout << errorMessage << ". Повторить ввод? (1/0) ";
        int key;
        cin >> key;
        if (!key)
            return;
        cout << "Введите пароль: ";
        cin >> password;
    }

    UserSession session = UserSession(&dataUser[auth.findUserByLogin(login)->getID()], dataTask, dataUser);

    if (dataUser[auth.findUserByLogin(login)->getID()].getRole()) {
        AdminDashboard adminDashboard = AdminDashboard(&session);
        adminDashboard.run();
    } else {
        UserDashboard userDashboard = UserDashboard(&session);
        userDashboard.run();
    }
}

void showAuthMenu() {
    cout << "=== ГЛАВНОЕ МЕНЮ ===\n";
    cout << "1. Регистрация\n";
    cout << "2. Авторизация\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main(){
    setlocale(LC_ALL, "Russian");   
    AuthService adminAuth = AuthService(dataUser);
    string s = "";
    adminAuth.registerUser("adminka", "admin", "admin123", 1, s);
    adminAuth.registerUser("nikita", "nik123", "nik123", 0, s);

    while (true) {
        showAuthMenu();
        int k;
        cin >> k;

        switch (k) {
            case 1: registration(); break;
            case 2: authorization(); break;
            case 0: return 0; break;
            default: std::cout << "Неверный выбор! Попробуйте снова.\n";
        }

        cout << endl;
    }

    return 0;
}