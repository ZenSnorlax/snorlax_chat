#include <string>
#include <vector>

#include "conn_pool.hpp"
#include "dal.hpp"

std::string MessagesDao::db_name_ = "snorlax_chat";
std::string MessagesDao::table_name_ = "messages";

void MessagesDao::insert(int user_id, int room_id, const std::string& content) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    table_schema.insert("user_id", "room_id", "content")
        .values(user_id, room_id, content)
        .execute();
}

std::vector<std::string> MessagesDao::getMessages(
    std::string username, const std::string& login_time) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    auto query =
        table_schema.select("content").where("username = ? and created_at > ?");

    query.bind(username);
    query.bind(login_time);

    auto result = query.execute();

    std::vector<std::string> messages;

    mysqlx::Row row;
    while ((row = result.fetchOne())) {
        messages.push_back(row[0].get<std::string>());
    }
    return messages;
}
