#include <bcrypt.h>

#include "bll.hpp"

ErrorCode LoginHandler::login(const std::string& username,
                              const std::string& password) {
    if (!UsersDao::usernameExists(username)) {
        return ErrorCode::UsernameNotExists;
    }
    std::string password_hash;
    try {
        password_hash = UsersDao::getPasswordHash(username);
    } catch (...) {
        return ErrorCode::UnknownError;
    }

    if (bcrypt::validatePassword(password, password_hash)) {
        return ErrorCode::Success;
    } else {
        return ErrorCode::PasswordError;
    }
}