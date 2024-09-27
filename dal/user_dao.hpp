#pragma once

#include <mysql-cppconn/mysqlx/xdevapi.h>

#include <memory>  // For std::unique_ptr
#include <string>

#include "../conn_pool/conn_pool.hpp"

// ConnectionGuard 类，用于管理数据库连接的生命周期
class ConnectionGuard {
   public:
    explicit ConnectionGuard(std::unique_ptr<mysqlx::Session> conn)
        : conn_(std::move(conn)) {}

    ~ConnectionGuard() {
        if (conn_) {
            SQLConnPool::getInstance().releaseConnection(std::move(conn_));
        }
    }

    mysqlx::Session* operator->() { return conn_.get(); }  // 方便访问连接
    mysqlx::Session& operator*() { return *conn_; }        // 方便访问连接

   private:
    std::unique_ptr<mysqlx::Session> conn_;
};

// UserDAO 类，用于处理用户注册和登录
class UserDAO {
   public:
    static std::string Register(const std::string& account,
                                const std::string& password) {
        ConnectionGuard connGuard(
            SQLConnPool::getInstance()
                .getConnection());  // 使用 ConnectionGuard
        try {
            connGuard->startTransaction();  // 开始事务

            // 获取用户表并检查账号是否存在
            mysqlx::Table usersTable =
                connGuard->getSchema("snorlax_chat").getTable("snorlax_user");

            mysqlx::RowResult result = usersTable.select("account")
                                           .where("account = :account")
                                           .bind("account", account)
                                           .execute();

            if (result.count() > 0) {
                connGuard->rollback();  // 如果用户已存在，则回滚事务
                LOG(Level::WARNING, "User already exists: ", account);
                return "User already exists";
            }

            // 插入新用户
            usersTable.insert("account", "password")
                .values(account, password)
                .execute();

            connGuard->commit();  // 提交事务
            LOG(Level::INFO, "User registered: ", account);
            return "Register successful";

        } catch (const std::exception& e) {
            connGuard->rollback();  // 如果发生错误，则回滚事务
            LOG(Level::ERROR, "Failed to register user: ", e.what());
            return "Registration failed";  // 返回失败消息
        }
    }

    static std::string Login(const std::string& account,
                             const std::string& password) {
        ConnectionGuard connGuard(
            SQLConnPool::getInstance()
                .getConnection());  // 使用 ConnectionGuard
        try {
            // 获取 snorlax_user 表并检查用户是否存在
            mysqlx::Table usersTable =
                connGuard->getSchema("snorlax_chat").getTable("snorlax_user");

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
            mysqlx::RowResult passwordCheckResult =
                usersTable.select("password")
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
