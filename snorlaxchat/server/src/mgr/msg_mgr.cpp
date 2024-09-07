#include "mgr/msg_mgr.h"
#include <iostream>

namespace manager {
Messages::Messages(mysqlx::Session &session) : session_(session) {}

void Messages::addMessage(const std::string &sender,
                          const std::string &receiver,
                          const std::string &content) {
    try {
        session_
            .sql("INSERT INTO messages (sender, receiver, content) VALUES (?, "
                 "?, ?)")
            .bind(sender, receiver, content)
            .execute();
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error adding message: " +
                                 std::string(e.what()));
    }
}

bool Messages::queryMessage(int id) {
    try {
        mysqlx::RowResult result =
            session_.sql("SELECT id FROM messages WHERE id = ?")
                .bind(id)
                .execute();
        return result.count() > 0;
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error querying message: " +
                                 std::string(e.what()));
    }
}

void Messages::deleteMessage(int id) {
    try {
        if (queryMessage(id)) {
            session_.sql("DELETE FROM messages WHERE id = ?")
                .bind(id)
                .execute();
        } else {
            std::cout << "Message not found!" << std::endl;
        }
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error deleting message: " +
                                 std::string(e.what()));
    }
}

void Messages::printMessage(int id) {
    try {
        mysqlx::RowResult result = session_
                                       .sql("SELECT sender, receiver, content "
                                            "FROM messages WHERE id = ?")
                                       .bind(id)
                                       .execute();

        mysqlx::Row row = result.fetchOne();
        if (!row.isNull()) {
            std::cout << "Sender: " << row[0].get<std::string>() << std::endl;
            std::cout << "Receiver: " << row[1].get<std::string>() << std::endl;
            std::cout << "Content: " << row[2].get<std::string>() << std::endl;
        } else {
            std::cout << "Message not found!" << std::endl;
        }
    } catch (const mysqlx::Error &e) {
        throw std::runtime_error("Error fetching message: " +
                                 std::string(e.what()));
    }
}

} // namespace manager
