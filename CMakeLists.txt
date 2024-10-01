cmake_minimum_required(VERSION 3.5.0)
project(snorlax_chat VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)  

set(SOURCE_FILES main.cpp)  

add_definitions(-DSTATIC_CONCPP)  

include_directories(/usr/include/mysql-cppconn-8)  

add_executable(snorlax_chat ${SOURCE_FILES})

target_link_libraries(snorlax_chat
    /usr/lib64/libmysqlcppconnx-static.a  
    ssl  
    crypto  
    resolv  
)


