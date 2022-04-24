cmake_minimum_required(VERSION 3.21)
project(ex1 C)

set(CMAKE_C_STANDARD 99)


add_executable(ex1 tool/main.c RLEList.c tool/AsciiArtTool.c)
#add_executable(ex1 RLEList_example_test.c RLEList.c )
