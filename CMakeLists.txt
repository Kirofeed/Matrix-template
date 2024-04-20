cmake_minimum_required(VERSION 3.27)
project(Matrix_template)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Matrix_template
        main.cpp
        Matrix.h)
