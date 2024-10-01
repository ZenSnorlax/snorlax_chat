cmake_minimum_required(VERSION 3.5.0)
project(snorlax_chat VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

enable_testing()  
find_package(GTest REQUIRED)  
include_directories(${GTEST_INCLUDE_DIRS})  

add_definitions(-DSTATIC_CONCPP)

include_directories(/usr/include/mysql-cppconn-8)

include_directories(include)  

add_executable(snorlax_chat ${SOURCE_FILES})

target_link_libraries(snorlax_chat
    /usr/lib64/libmysqlcppconnx-static.a  
    ssl  
    crypto  
    resolv  
)

set(TEST_FILES test/test_main.cpp) 

add_executable(snorlax_chat_tests ${TEST_FILES}) 

target_link_libraries(snorlax_chat_tests
    ${GTEST_LIBRARIES}  
    pthread  
)

add_test(NAME snorlax_chat_tests COMMAND snorlax_chat_tests)
