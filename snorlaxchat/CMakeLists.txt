cmake_minimum_required(VERSION 3.10)
project(Client)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#设置编译选项
add_compile_definitions(USE_MYSQL)
# 查找redis++的路径
#include_directories(/usr/include/sw/redis++)
#include_directories(/usr/include/hiredis)
# 查找mysql-cppconn-8的路径
include_directories(/usr/include/mysql-cppconn-8)
link_directories(/usr/lib64/mysql-cppconn-8)
#查找boost的路径
#include_directories(/usr/include/boost)
#link_directories(/usr/lib64/boost)
add_executable(Client mysql_redis.cpp)

# 链接库
target_link_libraries(Client
#    redis++  # redis++ 库
#    hiredis   # hiredis 库
    mysqlcppconn8
#    boost_system
#    boost_thread
)
