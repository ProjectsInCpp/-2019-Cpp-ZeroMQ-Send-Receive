cmake_minimum_required(VERSION 2.8)

project(2019_Cpp_ZeroMQ_Send_Receive)
find_package(cppzmq)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -lzmq -pthread")

add_executable("CLIENT" "client_main.cpp" ZeroMqUtils.hpp)
add_executable("SERVER" "server_main.cpp" ZeroMqUtils.hpp)

target_link_libraries(cppzmq ${cppzmq_LIBRARY})
