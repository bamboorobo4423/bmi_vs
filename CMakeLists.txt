# CMake minimum version
cmake_minimum_required(VERSION 3.0)

# project name and languages
project(bmi CXX RC)

# bmi.exe
add_executable(bmi WIN32 bmi.cpp bmi_res.rc)
target_link_libraries(bmi comctl32)
