#include "mgr/user_mgr.h"
#include <mutex>

namespace manager {

Users::Users(mysqlx::Session &session) : session_(session) {}

void Users::addUser(const std::string &username, const std::string &password) {
    std::lock_guard<std::mutex> lock(*mutex_);
    try {
        session_.sql("INSERT INTO users (username, password) VALUES (?, ?)")
            .bind(username, password)
            .execute();
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error adding user: " + std::string(e.what()));
    }
}

bool Users::queryUser(const std::string &username) {
    std::lock_guard<std::mutex> lock(*mutex_);
    try {
        mysqlx::RowResult result =
            session_.sql("SELECT username FROM users WHERE username = ?")
                .bind(username)
                .execute();
        return result.count() > 0;
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error querying user: " +
                                 std::string(e.what()));
    }
}

void Users::deleteUser(const std::string &username) {
    std::lock_guard<std::mutex> lock(*mutex_);
    try {
        session_.sql("DELETE FROM users WHERE username = ?")
            .bind(username)
            .execute();
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error deleting user: " +
                                 std::string(e.what()));
    }
}

void Users::changePassword(const std::string &username,
                           const std::string &password) {
    std::lock_guard<std::mutex> lock(*mutex_);
    try {
        session_.sql("UPDATE users SET password = ? WHERE username = ?")
            .bind(password, username)
            .execute();
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error changing password: " +
                                 std::string(e.what()));
    }
}

} // namespace manager
