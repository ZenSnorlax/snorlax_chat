#include "conn_pool.hpp"
#include "dao.hpp"

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

void UsersDao::insert(const std::string &username, const std::string &password,
                      const std::string &email) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    auto result = table_schema.insert("username", "password", "email")
                      .values(username, password, email)
                      .execute();
}

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

bool UsersDao::match(const std::string &username, const std::string &password) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    auto result = table_schema.select("username", "password")
                      .where("username = :username AND password = :password")
                      .bind("username", username)
                      .bind("password", password)
                      .execute();

    return result.count() > 0;
}