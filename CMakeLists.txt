cmake_minimum_required(VERSION 3.5.2)
project(riscv)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-O2)
add_executable(code main.cpp init.h IF.h ID.h EX.h MEM.h WB.h)
