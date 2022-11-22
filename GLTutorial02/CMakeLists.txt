cmake_minimum_required(VERSION 3.7)

set(NUMBER 02)
project(GLTutorial${NUMBER})

link_directories("../lib")
find_package(SDL2 REQUIRED COMPONENTS SDL2)

add_executable(tutorial${NUMBER} Main.c)
target_include_directories(tutorial${NUMBER} PRIVATE ../include)
target_link_libraries(tutorial${NUMBER} PRIVATE SDL2::SDL2)
target_link_libraries(tutorial${NUMBER} PRIVATE EGL)
target_link_libraries(tutorial${NUMBER} PRIVATE GLESv2)
