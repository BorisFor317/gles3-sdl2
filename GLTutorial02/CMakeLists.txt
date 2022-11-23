cmake_minimum_required(VERSION 3.18)

set(NUMBER 02)
project(GLTutorial${NUMBER})

link_directories("../lib")
find_package(SDL2 REQUIRED COMPONENTS SDL2)

add_executable(tutorial${NUMBER} Main.c Shader.c)
target_include_directories(tutorial${NUMBER} PRIVATE ../include)
target_link_libraries(tutorial${NUMBER} PRIVATE SDL2::SDL2)
target_link_libraries(tutorial${NUMBER} PRIVATE EGL)
target_link_libraries(tutorial${NUMBER} PRIVATE GLESv2)
configure_file(Simple2D.frag Simple2D.frag COPYONLY)
configure_file(Simple2D.vert Simple2D.vert COPYONLY)
configure_file(Gradient2D.vert Gradient2D.vert COPYONLY)
