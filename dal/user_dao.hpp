#pragma once

#include <mysql-cppconn/mysqlx/xdevapi.h>

#include <string>

#include "../conn_pool/conn_pool.hpp"

class UserDAO {
   public:
    static std::string Register(const std::string& account,
                                const std::string& password) {
        auto conn = SQLConnPool::getInstance().getConnection();
        try {
            conn->startTransaction();  // Start transaction

            // Get users table and check if the account exists
            mysqlx::Table usersTable =
                conn->getSchema("snorlax_chat").getTable("snorlax_user");

            mysqlx::RowResult result = usersTable.select("account")
                                           .where("account = :account")
                                           .bind("account", account)
                                           .execute();

            if (result.count() > 0) {
                conn->rollback();  // Rollback if user exists
                LOG(Level::WARNING, "User already exists: ", account);
                return "User already exists";
            }

            // Insert new user
            usersTable.insert("account", "password")
                .values(account, password)
                .execute();

            conn->commit();  // Commit transaction
            LOG(Level::INFO, "User registered: ", account);
            return "Register successful";

        } catch (const std::exception& e) {
            conn->rollback();  // Rollback on error
            LOG(Level::ERROR, "Failed to register user: ", e.what());
            return "Registration failed";  // Return a failure message
        }
    }
static std::string Login(const std::string& account,
                         const std::string& password) {
    auto conn = SQLConnPool::getInstance().getConnection();
    try {
        // 获取 snorlax_user 表并检查用户是否存在
        mysqlx::Table usersTable =
            conn->getSchema("snorlax_chat").getTable("snorlax_user");

        // 检查用户是否存在
        mysqlx::RowResult userCheckResult = usersTable.select("account")
                                                       .where("account = :account")
                                                       .bind("account", account)
                                                       .execute();

        if (userCheckResult.count() == 0) {
            LOG(Level::WARNING, "User does not exist: ", account);
            return "User does not exist";  // 返回用户不存在的消息
        }

        // 用户存在，接下来检查密码是否正确
        mysqlx::RowResult passwordCheckResult = usersTable.select("password")
                                                           .where("account = :account AND password = :password")
                                                           .bind("account", account)
                                                           .bind("password", password)
                                                           .execute();

        if (passwordCheckResult.count() > 0) {
            LOG(Level::INFO, "Login successful for user: ", account);
            return "Login successful";
        } else {
            LOG(Level::WARNING, "Invalid credentials for user: ", account);
            return "Invalid credentials";  // 密码错误
        }

    } catch (const std::exception& e) {
        LOG(Level::ERROR, "Login failed for user: ", e.what());
        return "Login failed";
    }
}

};
