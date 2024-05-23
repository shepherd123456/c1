cmake_minimum_required(VERSION 3.20.0)
project(c1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED_ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(PROJECT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_PROJECT_NAME})

include_directories(.)

find_package(jwt-cpp REQUIRED)
find_package(SqliteOrm REQUIRED)
find_package(Crow REQUIRED)

link_libraries(jwt-cpp::jwt-cpp)
link_libraries(sqlite_orm::sqlite_orm)
link_libraries(Crow::Crow)
link_libraries(${PROJECT_DIRECTORY}/bcrypt/libbcrypt.a)

add_subdirectory(c1/main)
#add_subdirectory(c1/bcrypt)