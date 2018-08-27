cmake_minimum_required(VERSION 3.9)
find_package(Boost ${BOOST_VER} REQUIRED COMPONENTS system date_time random) 
add_executable(echo_server echo_server.cpp)
target_link_libraries(echo_server boost_system boost_thread pthread)

