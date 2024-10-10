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
        this->username_ = username;
        return ErrorCode::Success;
    } else {
        return ErrorCode::PasswordError;
    }
}

std::vector<std::string> LoginHandler::getMissingMessage() {
    std::vector<std::string> messages;

    std::string login_time = UsersDao::getLoginTime(username_);

    if (login_time.empty()) return {};

    return MessagesDao::getMessages(username_, login_time);
}