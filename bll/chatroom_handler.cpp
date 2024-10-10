#include <bcrypt.h>

#include <regex>

#include "bll.hpp"

ErrorCode ChatroomHandler::joinChatroom(const std::string& username,
                                        const std::string& password,
                                        const std::string& room_name) {
    if (!UsersDao::usernameExists(username)) {
        return ErrorCode::UsernameNotExists;
    }

    std::string password_hash;
    try {
        password_hash = UsersDao::getPasswordHash(username);

    } catch (...) {
        return ErrorCode::UnknownError;
    }

    if (!bcrypt::validatePassword(password, password_hash))
        return ErrorCode::PasswordError;

    if (!ChatRoomsDao::roomExists(room_name)) {
        return ErrorCode::RoomNotExists;
    }

    try {
        UserRoomRelationsDao::insert(UsersDao::getUserId(username),
                                     ChatRoomsDao::getRoomId(room_name),
                                     UserRole::member);
    } catch (...) {
        return ErrorCode::UnknownError;
    }

    return ErrorCode::Success;
}

ErrorCode ChatroomHandler::createChatroom(const std::string& username,
                                          const std::string& password,
                                          const std::string& room_name) {
    if (!UsersDao::usernameExists(username)) {
        return ErrorCode::UsernameNotExists;
    }

    std::string password_hash;
    try {
        password_hash = UsersDao::getPasswordHash(username);
    } catch (...) {
        return ErrorCode::UnknownError;
    }

    if (!std::regex_match(room_name, std::regex("[a-zA-Z0-9]{4,16}"))) {
        return ErrorCode::RoomnameFormatError;
    }

    if (!bcrypt::validatePassword(password, password_hash))
        return ErrorCode::PasswordError;

    if (ChatRoomsDao::roomExists(room_name)) {
        return ErrorCode::RoomExists;
    }

    try {
        ChatRoomsDao::insert(room_name, UsersDao::getUserId(username));
    } catch (...) {
        return ErrorCode::UnknownError;
    }
    return ErrorCode::Success;
}

