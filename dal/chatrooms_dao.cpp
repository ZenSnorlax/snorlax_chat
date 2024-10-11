#include "conn_pool.hpp"
#include "dal.hpp"

std::string ChatRoomsDao::db_name_ = "snorlax_chat";
std::string ChatRoomsDao::table_name_ = "chat_rooms";

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
    auto table_schema = db_schema.getTable(table_name_);

    // 正确的字段名是 `id` 而不是 `room_id`
    auto result = table_schema.select("id")
                      .where("room_name = :room_name")
                      .bind("room_name", room_name)
                      .execute();

    // 检查是否有返回结果
    auto row = result.fetchOne();
    if (!row) {
        throw std::runtime_error("Room not found");
    }
    return row[0].get<int>();
}