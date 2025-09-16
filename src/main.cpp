#include <iostream>
#include <unordered_map>
#include <string>
#include <ctime>
#include "../include/User.h"
#include "../include/Task.h"
#include "../include/AuthService.h"
#include "../include/UserSession.h"

using namespace std;

unordered_map<uint32_t, User> dataUser;
unordered_map<uint32_t, Task> dataTask;

void outputTaskList(uint32_t userID) {
    bool findTask = false;

    for (auto& [id, task] : dataTask) {
        if (task.getUserID() == userID) {
            findTask = true;
            cout << "\nНомер: " << task.getID() << endl;
            cout << "Дата создания: " << task.getDateCreate() << endl;
            cout << "Название: " << task.getName() << endl;
            cout << "Описание: " << task.getDescription() << endl;
            cout << "Дедлайн: " << task.getDeadline() << endl;
            cout << "Приоритет задачи: " << +task.getPriority() << endl;
            cout << "Статус задачи: " << +task.getStatus() << endl;
        }
    }

    if (!findTask)
        cout << "\nСписок задач пользователя пуст.\n";
}

void adminDashboard(UserSession* session) {
    cout << "\nВы вошли в аккаунт администратора: " << session->getCurrentUser()->getName() << endl;
    std::string errorMessage = "";
    while (session->isValidSession()) {
        cout << "\n1. Добавить задачу\n";
        cout << "2. Редактировать профиль\n";
        cout << "3. Вывести список задач\n";
        cout << "4. Удалить задачу\n";
        cout << "0. Выход из сессии\n";
        cout << "Выберите действие: ";
        int key1;
        cin >> key1;
        switch (key1)
        {
        case 1: {
            string nameTask, descriptionTask, deadlineTask;
            int priorityTask, statusTask;
            cout << "\nВвод информации о задаче\n";
            cout << "Название: ";
            cin >> nameTask;
            cout << "Описание: ";
            cin >> descriptionTask;
            cout << "Дедлайн: ";
            cin >> deadlineTask;
            cout << "Приоритет задачи (0, 1, 2 - от меньшего к большему приоритету): ";
            cin >> priorityTask;
            cout << "Статус задачи (0 - не выполняется, 1 - в процессе выполнения, 2 - выполнена): ";
            cin >> statusTask;
            if (session->addTask(nameTask, descriptionTask, static_cast<uint8_t>(priorityTask),
                static_cast<uint8_t>(statusTask), deadlineTask, errorMessage))
                cout << "Задача добавлена\n";
            else
                cout << errorMessage << endl;
            break;
        }
        case 2: {
            cout << "\nРедактирование профиля:\n";
            cout << "1. Изменить имя\n";
            cout << "2. Изменить логин\n";
            cout << "3. Изменить пароль\n";
            cout << "0. Выход\n";
            cout << "Выберите действие: ";
            int key2;
            cin >> key2;
            switch (key2) {
            case 1: {
                string newName;
                cout << "\nВведите новое имя: ";
                cin >> newName;
                if (session->changeName(newName, errorMessage)) {
                    cout << "Имя изменено\n";
                }
                else {
                    cout << errorMessage << endl;
                }
                break;
            }
            case 2: {
                string newLogin;
                cout << "\nВведите новый логин: ";
                cin >> newLogin;
                if (session->changeLogin(newLogin, errorMessage)) {
                    cout << "Логин изменен\n";
                }
                else {
                    cout << errorMessage << endl;
                }
                break;
            }
            case 3: {
                string newPassword, oldPassword;
                cout << "\nВведите старый пароль: ";
                cin >> oldPassword;
                cout << "Введите новый пароль: ";
                cin >> newPassword;
                if (session->changePassword(oldPassword, newPassword, errorMessage)) {
                    cout << "Пароль изменен" << endl;
                }
                else {
                    cout << errorMessage << endl;
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case 3: {
            outputTaskList(session->getCurrentUser()->getID());
            break;
        }
        case 4: {
            cout << "\nВведите ID задачи: ";
            int taskID;
            cin >> taskID;
            if (session->deleteTask(taskID, errorMessage)) {
                cout << "Задача удалена.\n";
            }
            else {
                cout << errorMessage << endl;
            }
            break;
        }
        case 0: {
            cout << "\nСессия пользователя " << session->getCurrentUser()->getName() << " завершена\n";
            session->invalidate();
            break;
        }
        default:
            break;
        }
    }
}

void userDashboard(UserSession* session) {
    cout << "\nВы вошли в аккаунт пользователя: " << session->getCurrentUser()->getName() << endl;
    std::string errorMessage = "";
    while (session->isValidSession()) {
        cout << "\n1. Добавить задачу\n";
        cout << "2. Редактировать профиль\n";
        cout << "3. Вывести список задач\n";
        cout << "4. Удалить задачу\n";
        cout << "0. Выход из сессии\n";
        cout << "Выберите действие: ";
        int key1;
        cin >> key1;
        switch (key1)
        {
        case 1: {
            string nameTask, descriptionTask, deadlineTask;
            int priorityTask, statusTask;
            cout << "\nВвод информации о задаче\n";
            cout << "Название: ";
            cin >> nameTask;
            cout << "Описание: ";
            cin >> descriptionTask;
            cout << "Дедлайн: ";
            cin >> deadlineTask;
            cout << "Приоритет задачи (0, 1, 2 - от меньшего к большему приоритету): ";
            cin >> priorityTask;
            cout << "Статус задачи (0 - не выполняется, 1 - в процессе выполнения, 2 - выполнена): ";
            cin >> statusTask;
            if (session->addTask(nameTask, descriptionTask, static_cast<uint8_t>(priorityTask),
                static_cast<uint8_t>(statusTask), deadlineTask, errorMessage))
                cout << "Задача добавлена\n";
            else
                cout << errorMessage << endl;
            break;
        }
        case 2: {
            cout << "\nРедактирование профиля:\n";
            cout << "1. Изменить имя\n";
            cout << "2. Изменить логин\n";
            cout << "3. Изменить пароль\n";
            cout << "0. Выход\n";
            cout << "Выберите действие: ";
            int key2;
            cin >> key2;
            switch (key2) {
            case 1: {
                string newName;
                cout << "\nВведите новое имя: ";
                cin >> newName;
                if (session->changeName(newName, errorMessage)) {
                    cout << "Имя изменено\n";
                }
                else {
                    cout << errorMessage << endl;
                }
                break;
            }
            case 2: {
                string newLogin;
                cout << "\nВведите новый логин: ";
                cin >> newLogin;
                if (session->changeLogin(newLogin, errorMessage)) {
                    cout << "Логин изменен\n";
                }
                else {
                    cout << errorMessage << endl;
                }
                break;
            }
            case 3: {
                string newPassword, oldPassword;
                cout << "\nВведите старый пароль: ";
                cin >> oldPassword;
                cout << "Введите новый пароль: ";
                cin >> newPassword;
                if (session->changePassword(oldPassword, newPassword, errorMessage)) {
                    cout << "Пароль изменен" << endl;
                }
                else {
                    cout << errorMessage << endl;
                }
                break;
            }
            default:
                break;
            }
            break;
        }
        case 3: {
            outputTaskList(session->getCurrentUser()->getID());
            break;
        }
        case 4: {
            cout << "\nВведите ID задачи: ";
            int taskID;
            cin >> taskID;
            if (session->deleteTask(taskID, errorMessage)) {
                cout << "Задача удалена.\n";
            }
            else {
                cout << errorMessage << endl;
            }
            break;
        }
        case 0: {
            cout << "\nСессия пользователя " << session->getCurrentUser()->getName() << " завершена\n";
            session->invalidate();
            break;
        }
        default:
            break;
        }
    }
}

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
    userDashboard(&session);
}

int main(){
    setlocale(LC_ALL, "Russian");   
    AuthService adminAuth = AuthService(dataUser);
    string s = "";
    adminAuth.registerUser("adminka", "admin", "admin123", 0, s);

    while (true) {
        cout << "1. Регистрация\n";
        cout << "2. Авторизация\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        int k;
        cin >> k;

        switch (k) {
        case 1: {
            registration();
            break;
        }
        case 2: {
            authorization();
            break;
        }
        case 0: {
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