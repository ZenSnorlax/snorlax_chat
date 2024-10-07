#include <openssl/sha.h>

#include <iomanip>
#include <iostream>
#include <sstream>

#include "dal.hpp"

class RegisterHandler {
   public:
    bool registerUser(const std::string& username, const std::string& password,
                      const std::string& email);
    std::string hashPassword(const std::string& password);
    bool verifyEmail(const std::string& email, const std::string& code);
};

bool RegisterHandler::registerUser(const std::string& username,
                                   const std::string& password,
                                   const std::string& email) {
    UsersDao::insert(username, hashPassword(password), email);
    return true;
}

std::string RegisterHandler::hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];  // SHA256_HASH_SIZE = 32
    SHA256(reinterpret_cast<const unsigned char*>(password.c_str()),
           password.size(),
           hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(hash[i]);
    }
    return ss.str();
}


