cmake_minimum_required(VERSION 3.7)

project(GLTutorial01)

link_directories("../lib")
find_package(SDL2 REQUIRED COMPONENTS SDL2)

add_executable(tutorial01 main.c)
target_include_directories(tutorial01 PRIVATE ../include)
target_link_libraries(tutorial01 PRIVATE SDL2::SDL2)
target_link_libraries(tutorial01 PRIVATE EGL)
target_link_libraries(tutorial01 PRIVATE GLESv2)
