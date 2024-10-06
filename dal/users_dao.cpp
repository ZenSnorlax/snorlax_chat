#include "conn_pool.hpp"
#include "dal.hpp"

std::string UsersDao::db_name_ = "snorlax_chat";
std::string UsersDao::table_name_ = "users";

// 检查邮箱是否存在
bool UsersDao::emailExists(const std::string &email) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    auto result = table_schema.select("email")
                      .where("email = :email")
                      .bind("email", email)
                      .execute();

    return result.count() > 0;
}

// 插入新用户
void UsersDao::insert(const std::string &username,
                      const std::string &password_hash,
                      const std::string &email) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    std::string statusStr =
        statusToString(UserStatus::Inactive);  // 转换状态为字符串

    table_schema.insert("username", "password_hash", "email", "status")
        .values(username, password_hash, email, statusStr)
        .execute();
}

// 检查用户名是否存在
bool UsersDao::usernameExists(const std::string &username) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    auto result = table_schema.select("username")
                      .where("username = :username")
                      .bind("username", username)
                      .execute();

    return result.count() > 0;
}

// 验证用户名和密码是否匹配
bool UsersDao::match(const std::string &username,
                     const std::string &password_hash) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    auto result =
        table_schema.select("username", "password_hash")
            .where("username = :username AND password_hash = :password")
            .bind("username", username)
            .bind("password", password_hash)
            .execute();

    return result.count() > 0;
}

// 删除用户
void UsersDao::deleteuser(const std::string &username,
                          const std::string &password_hash) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    table_schema.remove()
        .where("username = :username AND password_hash = :password")
        .bind("username", username)
        .bind("password", password_hash)
        .execute();
}

// 设置用户状态
void UsersDao::updataStatus(const std::string &username, UserStatus status) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    std::string statusStr =
        statusToString(status);  // 将 UserStatus 转换为字符串

    table_schema.update()
        .set("status", statusStr)
        .where("username = :username")
        .bind("username", username)
        .execute();
}

// 获取用户状态
UserStatus UsersDao::getStatus(const std::string &username) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    auto result = table_schema.select("status")
                      .where("username = :username")
                      .bind("username", username)
                      .execute();

    auto row = result.fetchOne();
    if (row) {
        std::string status = row[0].get<std::string>();
        return (status == "active") ? UserStatus::Active : UserStatus::Inactive;
    }
    return UserStatus::Inactive;  // 默认值
}

// 将 UserStatus 转换为字符串
std::string UsersDao::statusToString(UserStatus status) {
    switch (status) {
        case UserStatus::Active:
            return "active";
        case UserStatus::Inactive:
            return "inactive";
        default:
            return "unknown";  // 处理未定义状态
    }
}