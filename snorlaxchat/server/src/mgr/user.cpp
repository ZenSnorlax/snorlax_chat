#include "mgr/user.h"
#include "mgr/session_guard.h"
#include <iostream>
#include <vector>

namespace mgr {

UserManager::UserManager(db::MysqlConnectionPool *db_pool)
    : db_pool_(db_pool) {}

bool UserManager::executeCountQuery(const std::string &query,
                                    const std::vector<std::string> &params,
                                    int &result_count) {
    try {
        SessionGuard session_guard(db_pool_);
        auto session = session_guard.session();
        auto statement = session->sql(query);
        for (const auto &param : params) {
            statement.bind(param);
        }
        auto result = statement.execute();
        result_count = result.fetchOne()[0]; // 假设返回结果是整型

        return true;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Database query failed. Query: " << query
                  << " Params: "
                  << params[0]; // 打印出第一个参数，若有多个可以迭代打印
        std::cerr << " Exception: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::isUserExists(const std::string &user_name) {
    int count = 0;
    std::string query = "SELECT COUNT(*) FROM users WHERE user_name = ?";
    if (executeCountQuery(query, {user_name}, count)) {
        std::cout << "[INFO] User existence check for: " << user_name
                  << " Result: " << (count > 0 ? "Exists" : "Does not exist")
                  << std::endl;
        return count > 0;
    }
    return false;
}

bool UserManager::verifyUserCredentials(const std::string &user_name,
                                        const std::string &password) {
    int count = 0;
    std::string query =
        "SELECT COUNT(*) FROM users WHERE user_name = ? AND password = ?";
    if (executeCountQuery(query, {user_name, password}, count)) {
        std::cout << "[INFO] Verifying credentials for user: " << user_name
                  << " Password match: " << (count == 1 ? "Yes" : "No")
                  << std::endl;
        return count == 1;
    }
    return false;
}

bool UserManager::addUser(const std::string &user_name,
                          const std::string &password) {
    if (isUserExists(user_name)) {
        std::cerr << "[ERROR] Failed to add user: " << user_name
                  << ". Reason: Username already exists." << std::endl;
        return false;
    }

    try {
        SessionGuard session_guard(db_pool_);
        auto session = session_guard.session();
        session->startTransaction();

        std::string query =
            "INSERT INTO users (user_name, password) VALUES (?, ?)";
        session->sql(query).bind(user_name, password).execute();

        session->commit();
        std::cout << "[INFO] User created successfully: " << user_name
                  << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to create user: " << user_name
                  << ". Exception: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::deleteUser(const std::string &user_name,
                             const std::string &password) {
    if (!verifyUserCredentials(user_name, password)) {
        std::cerr << "[ERROR] Failed to delete user: " << user_name
                  << ". Reason: User does not exist or password is incorrect."
                  << std::endl;
        return false;
    }

    try {
        SessionGuard session_guard(db_pool_);
        auto session = session_guard.session();
        session->startTransaction();

        std::string query = "DELETE FROM users WHERE user_name = ?";
        session->sql(query).bind(user_name).execute();
        session->commit();
        std::cout << "[INFO] User deleted successfully: " << user_name
                  << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to delete user: " << user_name
                  << ". Exception: " << e.what() << std::endl;
        return false;
    }
}

bool UserManager::updatePassword(const std::string &user_name,
                                 const std::string &oldpassword,
                                 const std::string &newpassword) {
    if (!verifyUserCredentials(user_name, oldpassword)) {
        std::cerr << "[ERROR] Failed to update password for user: " << user_name
                  << ". Reason: Old password is incorrect." << std::endl;
        return false;
    }

    try {
        SessionGuard session_guard(db_pool_);
        auto session = session_guard.session();
        session->startTransaction();

        std::string query = "UPDATE users SET password = ? WHERE user_name = ?";
        session->sql(query).bind(newpassword, user_name).execute();
        session->commit();
        std::cout << "[INFO] Password updated successfully for user: "
                  << user_name << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to update password for user: " << user_name
                  << ". Exception: " << e.what() << std::endl;
        return false;
    }
}

std::optional<std::pair<std::string, std::string>>
UserManager::getUserInfo(const std::string &user_name) {
    try {
        SessionGuard session_guard(db_pool_);
        auto session = session_guard.session();

        std::string query =
            "SELECT user_name, password FROM users WHERE user_name = ?";
        auto result = session->sql(query).bind(user_name).execute();

        auto row = result.fetchOne();
        if (!row.isNull()) {
            std::string fetched_user_name = row[0].get<std::string>();
            std::string fetched_password = row[1].get<std::string>();

            std::cout << "[INFO] Retrieved info for user: " << user_name
                      << std::endl;
            return std::make_pair(fetched_user_name, fetched_password);
        } else {
            std::cout << "[INFO] User not found: " << user_name << std::endl;
        }
        return std::nullopt;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] Failed to retrieve user info for: " << user_name
                  << ". Exception: " << e.what() << std::endl;
        return std::nullopt;
    }
}

} // namespace mgr
