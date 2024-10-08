#include <chrono>
#include <ctime>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <random>
#include <string>

#include "bll.hpp"

ErrorCode RegisterHandler::sendEmailCode(const std::string& email) {
    // 检查邮箱是否存在
    if (UsersDao::emailExists(email)) {
        return ErrorCode::EmailExists;
    }

    // 生成验证码
    this->code = std::to_string(generateVerificationCode());

    // 创建邮件内容
    mailio::message msg;
    msg.from(mailio::mail_address(
        "snorlax", "1510017673@qq.com"));  // 可以替换为配置文件中的值
    msg.add_recipient(mailio::mail_address("", email));
    msg.subject("Your verification code");
    msg.content("Your verification code is: " + code);

    // 连接并发送邮件
    mailio::smtps conn("smtp.qq.com", 587);

    // 进行身份认证

    try {
        conn.authenticate("1510017673@qq.com",
                          "zpkbzczuzdttjgci",
                          mailio::smtps::auth_method_t::START_TLS);
    } catch (...) {
        return ErrorCode::SmtpError;
    }

    // 提交邮件
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
    if (code != this->code) {
        return ErrorCode::CodeError;
    }

    if (UsersDao::usernameExists(username)) {
        return ErrorCode::UsernameExists;
    }

    try {
        UsersDao::insert(username, password, email);
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
