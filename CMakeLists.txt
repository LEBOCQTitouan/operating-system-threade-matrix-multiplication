cmake_minimum_required(VERSION 3.25)
project(operating_system_threaded_matrix_multiplication C)

set(CMAKE_C_STANDARD 11)

add_executable(operating_system_threaded_matrix_multiplication main.c matrix/matrix.c matrix/matrix.h test/test.c test/test.h)
