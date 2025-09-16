#pragma once

#include "User.h"
#include "Task.h"
#include "PasswordHasher.h"
#include <string>
#include <unordered_map>
#include <algorithm>
#include <ctime>

class UserSession {
	User* currentUser;
	std::unordered_map<uint32_t, Task>& tasks;
	std::unordered_map<uint32_t, User>& users;
	time_t createdSession;
	bool isValid;
public:
	UserSession(User* user, std::unordered_map<uint32_t, Task>& tasks, std::unordered_map<uint32_t, User>& users);
	bool addTask(const std::string& nameTask, const std::string& description, const uint8_t priotity, 
		const uint8_t status, const std::string& deadline, std::string& errorMessage);
	bool isValidSession() const;
	void invalidate();
	User* getCurrentUser() const;
	bool changeName(const std::string& newName, std::string& errorMessage);
	bool changeLogin(const std::string& newLogin, std::string& errorMessage);
	bool changePassword(const std::string& oldPassword, const std::string& newPassword, std::string& errorMessage);
	bool deleteTask(const uint32_t taskID, std::string& errorMessage);
};
