cmake_minimum_required(VERSION 2.9)
#add_executable(server src/client.cpp)
add_executable(server src/server.cpp)
add_executable(client src/client.cpp)
add_executable(server_multithread src/server_multithread.cpp)
target_link_libraries(server_multithread pthread)
