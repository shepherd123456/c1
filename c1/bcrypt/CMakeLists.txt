# https://github.com/hilch/Bcrypt.cpp
add_executable(bcrypt main.cpp)
target_link_libraries(bcrypt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libbcrypt.a)