#include <bcrypt.h>

#include <chrono>
#include <ctime>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <random>
#include <regex>
#include <string>

#include "bll.hpp"

ErrorCode RegisterHandler::sendEmailCode(const std::string& email) {
    if (UsersDao::emailExists(email)) {
        return ErrorCode::EmailExists;
    }

    this->code = std::to_string(generateVerificationCode());

    mailio::message msg;
    msg.from(mailio::mail_address("snorlax", "1510017673@qq.com"));
    msg.add_recipient(mailio::mail_address("", email));
    msg.subject("Your verification code");
    msg.content("Your verification code is: " + code);

    mailio::smtps conn("smtp.qq.com", 587);

    try {
        conn.authenticate("1510017673@qq.com",
                          "zpkbzczuzdttjgci",
                          mailio::smtps::auth_method_t::START_TLS);
    } catch (...) {
        return ErrorCode::SmtpError;
    }

    try {
        conn.submit(msg);
    } catch (...) {
        return ErrorCode::SmtpError;
    }

    return ErrorCode::Success;
}

ErrorCode RegisterHandler::registerUser(const std::string& username,
                                        const std::string& password,
                                        const std::string& email,
                                        const std::string& code) {
    if (!std::regex_match(username, std::regex("[a-zA-Z0-9]{4,16}"))) {
        return ErrorCode::UsernameFormatError;
    }
    if (!std::regex_match(password, std::regex("[a-zA-Z0-9]{6,16}"))) {
        return ErrorCode::PasswordFormatError;
    }

    if (code != this->code) {
        return ErrorCode::CodeError;
    }

    if (UsersDao::usernameExists(username)) {
        return ErrorCode::UsernameExists;
    }

    std::string psw_hash = bcrypt::generateHash(password);

    try {
        UsersDao::insert(username, psw_hash, email);
    } catch (...) {
        return ErrorCode::UnknownError;
    }

    return ErrorCode::Success;
}

int RegisterHandler::generateVerificationCode() {
    std::mt19937 generator(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> distribution(100000, 999999);
    return distribution(generator);
}
