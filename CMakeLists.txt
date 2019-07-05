cmake_minimum_required(VERSION 3.14)
project(riscv)

set(CMAKE_CXX_STANDARD 11)

add_executable(riscv main.cpp init.h IF.h ID.h EX.h MEM.h WB.h)