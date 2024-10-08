#include <chrono>
#include <ctime>
#include <mailio/message.hpp>
#include <mailio/smtp.hpp>
#include <random>
#include <string>

#include "bll.hpp"

bool RegisterHandler::sendEmailCode(const std::string& email) {
    if (UsersDao::emailExists(email)) {
        return false;
    }

    this->code = std::to_string(generateVerificationCode());

    mailio::message msg;
    msg.from(mailio::mail_address("snorlax", "1510017673@qq.com"));
    msg.add_recipient(mailio::mail_address("", email));
    msg.subject("Your verification code");
    msg.content("Your verification code is: " + code);

    mailio::smtps conn("smtp.qq.com", 587);
    conn.authenticate("1510017673@qq.com",
                      "zpkbzczuzdttjgci",
                      mailio::smtps::auth_method_t::START_TLS);
    conn.submit(msg);

    return true;
}

int RegisterHandler::generateVerificationCode() {
    std::mt19937 generator(static_cast<unsigned int>(
        std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> distribution(100000, 999999);
    return distribution(generator);
}
