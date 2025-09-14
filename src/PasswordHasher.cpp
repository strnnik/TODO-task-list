#include "PasswordHasher.h"

bool PasswordHasher::verifyPassword(const std::string& password, const std::string& storedHash, const std::string& salt) {
    if (generateHash(password, salt) == storedHash)
        return true;
    else
        return false;
}

std::string PasswordHasher::generateHash(const std::string& password, const std::string& salt) {
    std::string symbol = "abcdefghijklmnopqrstuvwxyz1234567890";
    std::string hash = salt;

    for (int i = 0; i < password.length(); i++) {
        hash[i] = symbol[(salt[i] + password[i] - 2 * 'a') % symbol.length()];
    }

    std::cout << "HASH: " << hash << std::endl;
    return hash;
}

std::string PasswordHasher::generateSalt() {
    std::string symbol = "abcdefghijklmnopqrstuvwxyz1234567890";
    std::string salt = "0000111122223333";

    for (size_t i = 0; i < salt.length(); i++) {
        salt[i] = symbol[rand() % 36];
    }

    std::cout << "SALT: " << salt << std::endl;
    return salt;
}