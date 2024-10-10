#include "bll.hpp"

ErrorCode MessageHanlder::addMessage(const std::string& username,
                                     const std::string& room_name,
                                     const std::string& content) {
    if (!UsersDao::usernameExists(username)) {
        return ErrorCode::UsernameNotExists;
    }

    if (!ChatRoomsDao::roomExists(room_name)) {
        return ErrorCode::RoomNotExists;
    }

    try {
        MessagesDao::insert(UsersDao::getUserId(username),
                            ChatRoomsDao::getRoomId(room_name),
                            content);
    } catch (...) {
        return ErrorCode::UnknownError;
    }

    return ErrorCode::Success;
}
