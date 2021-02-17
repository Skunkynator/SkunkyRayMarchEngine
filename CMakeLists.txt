cmake_minimum_required(VERSION 3.0)

include_directories(./include/)
link_libraries(GL)
link_libraries(glfw)
link_libraries(dl)

project(raymarchengine)

file(GLOB SOURCES "Source/*.cpp" "Source/*.c" "Source/*.hpp" "Source/*.h")
#file(REMOVE_RECURSE build/Shaders/)
#file(COPY Shaders/ DESTINATION Shaders/)

add_executable(raymarchengine ${SOURCES})

install(TARGETS raymarchengine RUNTIME DESTINATION bin)
