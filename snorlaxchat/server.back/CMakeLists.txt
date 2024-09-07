cmake_minimum_required(VERSION 3.10)
project(snorlaxchat)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 redis++ 和 hiredis 的路径
include_directories(/usr/include/sw/redis++)
include_directories(/usr/include/hiredis)

# 查找 mysql-cppconn-8 的路径
include_directories(/usr/include/mysql-cppconn-8)
link_directories(/usr/lib64/mysql-cppconn-8)

# 查找 Boost 的路径
include_directories(/usr/include/boost)
link_directories(/usr/lib64/boost)

# 包含项目的头文件
include_directories(${CMAKE_SOURCE_DIR}/include)

# 源文件列表
set(SOURCE_FILES
    src/db/conn_pool.cpp
    src/db/db_init.cpp
    src/mgr/msg_mgr.cpp
    src/mgr/user_mgr.cpp
    src/ws/ws_server.cpp
    main.cpp
)

# 添加可执行文件
add_executable(snorlaxchat ${SOURCE_FILES})

# 链接库
target_link_libraries(snorlaxchat
    redis++  # redis++ 库
    hiredis  # hiredis 库
    mysqlcppconn8  # MySQL C++ 连接器库
    boost_system  # Boost 系统库
    boost_thread  # Boost 线程库
)
