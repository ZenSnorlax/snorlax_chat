//
// Created by qing on 9/5/24.
//
#include "mysql.h"
#include <iostream>

Mysql::Mysql(const std::string &host, const std::string &user, int port,
             const std::string &password, const std::string &database)
    : session_(mysqlx::SessionSettings(host, port, user, password)) {
    try {
        session_.sql("USE " + database).execute();
        std::cout << "Connected to MySQL successfully!" << std::endl;
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error selecting database: " +
                                 std::string(e.what()));
    }
}

Mysql::Mysql(Mysql &&other) noexcept : session_(std::move(other.session_)) {}

Mysql::~Mysql() = default;
