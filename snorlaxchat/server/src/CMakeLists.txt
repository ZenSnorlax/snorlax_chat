

# 查找第三方库
include_directories(/usr/include/sw/redis++)
include_directories(/usr/include/hiredis)
include_directories(/usr/include/mysql-cppconn-8)
include_directories(/usr/include/boost)
link_directories(/usr/lib64/mysql-cppconn-8)
link_directories(/usr/lib64/boost)


# 源文件列表
set(CORE_SOURCE_FILES 
    db/conn_pool.cpp
    mgr/user.cpp
    mgr/session_guard.cpp
    db/config.cpp
)

# 创建静态库
add_library(core STATIC ${CORE_SOURCE_FILES})

# 链接依赖库到静态库
target_link_libraries(core
    redis++
    hiredis
    mysqlcppconn8
    boost_system
    boost_thread
)

# 添加可执行文件
add_executable(ws_server main.cpp)

# 链接静态库和其他库到可执行文件
target_link_libraries(ws_server
    core  # 链接静态库
    redis++
    hiredis
    mysqlcppconn8
    boost_system
    boost_thread
)

# 设置静态库的输出目录
set_target_properties(core PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
