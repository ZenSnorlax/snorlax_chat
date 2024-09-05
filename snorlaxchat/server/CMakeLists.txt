cmake_minimum_required(VERSION 3.10)
project(snorlaxchat)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找redis++的路径
include_directories(/usr/include/sw/redis++)
include_directories(/usr/include/hiredis)

# 查找mysql-cppconn-8的路径
include_directories(/usr/include/mysql-cppconn-8)
link_directories(/usr/lib64/mysql-cppconn-8)

include_directories(${CMAKE_SOURCE_DIR}/include)
#查找boost的路径
include_directories(/usr/include/boost)
link_directories(/usr/lib64/boost)
add_executable(snorlaxchat
        include/redis.h
        include/mysql.h
        include/websocket_server.h
        src/redis.cpp
        src/mysql.cpp
        src/websocket_server.cpp
        src/main.cpp
)

# 链接库
target_link_libraries(snorlaxchat
        redis++  # redis++ 库
        hiredis   # hiredis 库
        mysqlcppconn8
        boost_system
        boost_thread
)