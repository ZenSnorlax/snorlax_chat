#ifndef MESSAGES_MANAGER_H
#define MESSAGES_MANAGER_H

#include "db/db_init.h"
#include <string>

namespace manager {

class Messages {
  public:
    Messages(mysqlx::Session &session);

    void addMessage(const std::string &sender, const std::string &receiver, const std::string &content);
    bool queryMessage(int id);
    void deleteMessage(int id);
    void printMessage(int id);

  private:
    mysqlx::Session &session_;
};

} // namespace manager

#endif // MESSAGES_MANAGER_H
