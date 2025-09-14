#include <iostream>
#include <string>

class PasswordHasher {
public:
    static std::string generateSalt();
    static std::string generateHash(const std::string& password, const std::string& salt);
    static bool verifyPassword(const std::string& password, const std::string& storedHash, const std::string& salt);
};
