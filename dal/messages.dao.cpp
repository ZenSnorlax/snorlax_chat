#include "conn_pool.hpp"
#include "dao.hpp"

std::string MessagesDao::db_name_ = "snorlax_chat";
std::string MessagesDao::table_name_ = "messages";

void MessagesDao::insert(int user_id, int room_id, const std::string &content) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    table_schema.insert("user_id", "room_id", "content")
        .values(user_id, room_id, content)
        .execute();
}