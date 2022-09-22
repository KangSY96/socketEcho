cmake_minimum_required(VERSION 3.0.0)

project(tcpServer)

add_executable(${PROJECT_NAME}
    ./tcp_server.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)