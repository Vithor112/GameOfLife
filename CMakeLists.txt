cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(GameOfLife LANGUAGES C)
# add_library(libs 
# 	STATIC
# 	param.h)


add_executable(GameOfLife src/main.c)
# target_link_libraries(GameOfLife libs)
target_link_libraries(GameOfLife ncurses)

add_compile_definitions(DEBUG)
