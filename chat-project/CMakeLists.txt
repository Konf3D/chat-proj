cmake_minimum_required(VERSION 3.8)

project("ChatCLI")

set(CMAKE_CXX_STANDARD 20)

set(SRCFILES user.cpp message.cpp db.cpp gui.cpp main.cpp)

add_executable(ChatCLI ${SRCFILES})
