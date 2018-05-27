cmake_minimum_required(VERSION 3.10)
project(AntraUzduotis)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Release)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS_DEBUG "-g")
message(STATUS "Flags: ${CMAKE_CXX_FLAGS_RELEASE}")

add_executable(AntraUzduotis cpp/main.cpp cpp/Studentas.cpp headers/Studentas.h cpp/DarbasFailai.cpp headers/DarbasFailai.h cpp/Performance.cpp headers/Performance.h headers/Timer.h StrongVector.h)