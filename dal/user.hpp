#pragma once

#include <mysql-cppconn/mysqlx/xdevapi.h>

#include <string>

#include "../conn_pool/conn_pool.hpp"

class UserDAO {
   public:
    static void Register(const std::string& user, const std::string& password) {
        auto conn = SQLConnPool::getInstance().getConnection();
        try {
            conn->startTransaction();
            mysqlx::Table usersTable =
                conn->getSchema("snorlax_chat").getTable("snorlax_user");
            usersTable.insert("account", "password")
                .values(user, password)
                .execute();

            conn->commit();
            LOG(Level::INFO, "User registered: ", user);
        } catch (const std::exception& e) {
            conn->rollback();
            LOG(Level::ERROR, "Failed to register user: ", e.what());
            throw;
        }
    }
};
