cmake_minimum_required(VERSION 3.0.0)
project(operating-systems VERSION 0.0.0)

add_executable(task2 Task_2.c)
add_executable(task3 Task_3.c)
add_executable(task5 Task_5.c)
add_executable(task6 Task_6.c)

SET ( CMAKE_C_FLAGS "-std=gnu99 -pthread" )
