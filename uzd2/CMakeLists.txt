cmake_minimum_required(VERSION 3.8)
project(uzd2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES cpp/main.cpp headers/KolegosFaile.h cpp/KolegosFaile.cpp headers/Skaiciavimai.h cpp/Skaiciavimai.cpp headers/DarbasKonsole.h cpp/DarbasKonsole.cpp)
add_executable(uzd2 ${SOURCE_FILES})