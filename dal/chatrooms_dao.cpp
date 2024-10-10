#include "conn_pool.hpp"
#include "dal.hpp"

std::string UsersDao::db_name_ = "snorlax_chat";
std::string UsersDao::table_name_ = "chat_rooms";

void ChatRoomsDao::insert(const std::string& room_name, int created_by) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable("chat_rooms");

    auto result = table_schema.insert("room_name", "created_by")
                      .values(room_name, created_by)
                      .execute();
}

bool ChatRoomsDao::roomExists(const std::string& room_name) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable("chat_rooms");

    auto result = table_schema.select("room_name")
                      .where("room_name = :room_name")
                      .bind("room_name", room_name)
                      .execute();

    return result.count() > 0;
}

int ChatRoomsDao::getRoomId(const std::string& room_name) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable("chat_rooms");

    auto result = table_schema.select("room_id")
                      .where("room_name = :room_name")
                      .bind("room_name", room_name)
                      .execute();

    auto row = result.fetchOne();
    return row[0].get<int>();
}