cmake_minimum_required(VERSION 3.0)

project(raymarchengine)

add_executable(raymarchengine main.cpp)

install(TARGETS raymarchengine RUNTIME DESTINATION bin)
