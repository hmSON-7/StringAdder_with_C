cmake_minimum_required(VERSION 3.29)
project(untitled C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "-fexec-charset-utf-8")

add_executable(untitled stack/main.c stack/char_stack.c stack/char_stack.h)
