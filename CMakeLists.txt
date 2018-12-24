cmake_minimum_required(VERSION 3.13)
project(jnet C)

set(CMAKE_C_STANDARD 99)

add_executable(jnet main.c jnetfileio.c jnetfileio.h cmake-build-debug/jnetstructs.c cmake-build-debug/jnetstructs.h)