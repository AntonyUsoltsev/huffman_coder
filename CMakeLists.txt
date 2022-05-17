cmake_minimum_required(VERSION 3.20)
project(lab5_Huffman C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}-fsanitize=address")


add_executable(lab5_Huffman main.c queue&tree_func.h code.h decode.h buff_func.h)
