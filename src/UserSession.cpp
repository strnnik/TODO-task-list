#include "UserSession.h"

UserSession::UserSession(User* user,
    std::unordered_map<uint32_t, Task>& tasks,
    std::unordered_map<uint32_t, User>& users)
    : currentUser(user), tasks(tasks), users(users) {
    createdSession = time(nullptr);
    isValid = true;
}

User* UserSession::getCurrentUser() const {
    return currentUser;
}

bool UserSession::isValidSession() const {
    const time_t sessionDuration = 24 * 60 * 60;
    return isValid && (time(nullptr) - createdSession < sessionDuration);
}

void UserSession::invalidate() {
    isValid = false;
}

bool UserSession::addTask(const std::string& nameTask, const std::string& description, const uint8_t priorityTask, 
    const uint8_t statusTask, const std::string& deadline, std::string& errorMessage) {
    
    if (!isValidSession()) {
        errorMessage = "Сессия неактуальна";
        return false;
    }

    if (nameTask.empty() || description.empty()) {
        errorMessage = "Название и описание задачи не могут быть пустыми";
        return false;
    }

    if (priorityTask > 3 || statusTask > 3) {
        errorMessage = "Неверно указан приоритет или статус задачи";
        return false;
    }

    Task newTask(currentUser->getID(), nameTask, description, priorityTask, statusTask, deadline);
    tasks[newTask.getID()] = newTask;

    return true;
}

bool UserSession::changePassword(const std::string& oldPassword, const std::string& newPassword, std::string& errorMessage) {
    if (!isValidSession()) {
        errorMessage = "Сессия неактуальна";
        return false;
    }

    if (!PasswordHasher::verifyPassword(oldPassword, currentUser->getHash(), currentUser->getSalt())) {
        errorMessage = "Неверный пароль";
        return false;
    }

    std::string newSalt = PasswordHasher::generateSalt();
    std::string newHash = PasswordHasher::generateHash(newPassword, newSalt);

    currentUser->setHash(newHash);
    currentUser->setSalt(newSalt);

    return true;
}

bool UserSession::changeName(const std::string& newName, std::string& errorMessage) {
    if (!isValidSession()) {
        errorMessage = "Сессия неактуальна";
        return false;
    }

    if (newName.empty()) {
        errorMessage = "Новое имя не может быть пустым";
    }

    currentUser->setName(newName);

    return true;
}

bool UserSession::changeLogin(const std::string& newLogin, std::string& errorMessage) {
    if (!isValidSession()) {
        errorMessage = "Сессия неактуальна";
        return false;
    }

    if (newLogin.empty()) {
        errorMessage = "Новый логин не может быть пустым";
    }

    for (auto& pair : users)
        if (pair.second.getLogin() == newLogin) {
            errorMessage = "Пользователь с таким логином уже существует";
            return false;
        }

    currentUser->setLogin(newLogin);

    return true;
}

bool UserSession::deleteTask(uint32_t delTaskID, std::string& errorMessage) {
    if (!isValidSession()) {
        errorMessage = "Сессия неактуальна";
        return false;
    }

    for (auto& [taskID, task] : tasks) {
        if (taskID == delTaskID) 
            if (task.getUserID() == currentUser->getID() || currentUser->getRole()) {
                tasks.erase(delTaskID);
                return true;
            }
    }

    errorMessage = "Задачи с таким ID не существует или недостаточно прав, чтобы удалить чужую задачу!";

    return false;
}