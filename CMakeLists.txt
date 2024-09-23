cmake_minimum_required(VERSION 3.10)
project(snorlax_chat)

add_custom_target(run_sql ALL
    COMMAND mysql -u abs -p1510017673 -e "CREATE DATABASE IF NOT EXISTS snorlax_chat;"
    COMMAND mysql -u abs -p1510017673 snorlax_chat < ${CMAKE_CURRENT_SOURCE_DIR}/sql/user.sql
    COMMAND mysql -u abs -p1510017673 snorlax_chat < ${CMAKE_CURRENT_SOURCE_DIR}/sql/message.sql
    COMMENT "Creating database and running SQL scripts..."
)