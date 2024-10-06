#include "conn_pool.hpp"
#include "dal.hpp"

void UserRoomRelationsDao::insert(int chat_room_id, int user_id,
                                  UserRole role) {
    auto session_guard =
        ConnectionGuard(ConnectionPool::getInstance().getConnection());
    auto db_schema = session_guard->getSchema(db_name_);
    auto table_schema = db_schema.getTable(table_name_);

    table_schema.insert("chat_room_id", "user_id", "role")
        .values(chat_room_id, user_id, roleToString(role))
        .execute();
}

std::string UserRoomRelationsDao::roleToString(UserRole role) {
    switch (role) {
        case UserRole::admin:
            return "admin";
        case UserRole::member:
            return "member";
        default:
            return "unknown";
    }
}