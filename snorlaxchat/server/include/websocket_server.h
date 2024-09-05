#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include "mysql.h"
#include "redis.h"
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>

class websocketServer {
public:
    static websocketServer &instance(Mysql &&mysql, Redis &&redis);
    [[noreturn]] void start();

    websocketServer(const websocketServer &) = delete;
    websocketServer &operator=(const websocketServer &) = delete;

private:
    Mysql mysql_;
    Redis redis_;

    websocketServer(Mysql &&mysql, Redis &&redis);
};

#endif // WEBSOCKET_SERVER_H
