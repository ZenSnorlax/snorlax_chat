cmake_minimum_required(VERSION 3.5.0)
project(snorlax_chat VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

# python
set(PYTHON_SCRIPT "${CMAKE_SOURCE_DIR}/script/init.py")

execute_process(
    COMMAND python3 ${PYTHON_SCRIPT}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/script
    RESULT_VARIABLE result
)

if(result EQUAL 0)
    message(STATUS "Python script executed successfully.")
else()
    message(FATAL_ERROR "Python script failed with error code ${result}.")
endif()

# mysql
add_definitions(-DSTATIC_CONCPP)

include_directories(/usr/include/mysql-cppconn-8)
include_directories(include)

# boost
find_package(Boost REQUIRED COMPONENTS system date_time regex)

# mailio
find_package(mailio REQUIRED)

# bcrypt
include_directories(/usr/local/include)  # 头文件路径
link_directories(/usr/local/lib)          # 库文件路径


add_executable(snorlax_chat ${SOURCE_FILES})

set(SNORLAX_MYSQL "/usr/lib64/libmysqlcppconnx-static.a" "ssl" "crypto" "resolv")
target_link_libraries(snorlax_chat
    ${SNORLAX_MYSQL}
    mailio
    Boost::system
    Boost::date_time
    Boost::regex
    bcrypt
)

# test
enable_testing()  
find_package(GTest REQUIRED)  
include_directories(${GTEST_INCLUDE_DIRS})  


add_executable(test_dao test/dao.cpp dal/users_dao.cpp  dal/messages_dao.cpp
dal/chatroom_relations_dao.cpp
dal/chatrooms_dao.cpp)
target_link_libraries(test_dao ${SNORLAX_MYSQL} 
    ${GTEST_LIBRARIES}  
    pthread 
)

add_executable(test_bll test/bll.cpp bll/register_handler.cpp dal/users_dao.cpp bll/login_handler.cpp dal/messages_dao.cpp)
target_link_libraries(test_bll ${SNORLAX_MYSQL} 
    ${GTEST_LIBRARIES}  
    pthread 
    mailio 
    Boost::system
    Boost::date_time
    Boost::regex
    bcrypt
)

add_test(NAME test_dao COMMAND test_dao)  # 这里修改为 test_dao

add_test(NAME test_bll COMMAND test_bll)  # 这里修改为 test_bll
