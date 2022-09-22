cmake_minimum_required(VERSION 3.0.0)

project(tcpClient)

add_executable(${PROJECT_NAME}
    ./tcp_client.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)