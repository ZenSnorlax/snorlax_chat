#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H
#include "mgr/user_mgr.h"
#include <boost/asio.hpp>
#include <boost/beast/websocket.hpp>

class websocketServer {
  public:
    static websocketServer &instance(manager::Users &users);
    [[noreturn]] void start();

    websocketServer(const websocketServer &) = delete;
    websocketServer &operator=(const websocketServer &) = delete;

  private:
    manager::Users users_;
    websocketServer(manager::Users &users);
    
};

#endif // WEBSOCKET_SERVER_H
