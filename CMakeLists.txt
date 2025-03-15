cmake_minimum_required(VERSION 3.15...3.31)
set(CMAKE_CXX_STANDARD 17) 

project(ChessEngine LANGUAGES CXX)

add_executable(chess 
        board_representation.h
        render.h
        board_representation.cpp
        main.cpp
        render.cpp)


