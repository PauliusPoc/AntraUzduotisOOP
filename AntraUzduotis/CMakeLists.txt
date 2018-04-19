cmake_minimum_required(VERSION 3.10)
project(AntraUzduotis)

set(CMAKE_CXX_STANDARD 17)

add_executable(AntraUzduotis cpp/main.cpp cpp/Studentas.cpp headers/Studentas.h cpp/DarbasFailai.cpp headers/DarbasFailai.h cpp/Performance.cpp headers/Performance.h)