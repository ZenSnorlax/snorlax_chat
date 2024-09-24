cmake_minimum_required(VERSION 3.10)
project(snorlax_chat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


execute_process(
    COMMAND python3 ${CMAKE_SOURCE_DIR}/parse_config.py ${CMAKE_SOURCE_DIR}/config.json
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE config_output
)

string(REPLACE "\n" ";" config_list "${config_output}")
list(GET config_list 0 MYSQL_USERNAME)
list(GET config_list 1 MYSQL_PASSWORD)
list(GET config_list 2 MYSQL_DATABASE)

add_executable(snorlax_chat main.cpp)
target_compile_definitions(snorlax_chat PRIVATE
    MYSQL_USERNAME="${MYSQL_USERNAME}"
    MYSQL_PASSWORD="${MYSQL_PASSWORD}"
    MYSQL_DATABASE="${MYSQL_DATABASE}"
)
