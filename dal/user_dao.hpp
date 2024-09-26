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
};
