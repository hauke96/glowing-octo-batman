#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8)
#Name your project here
project(glowing-octo-batman)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories("include/")

add_definitions(-std=c++14)

add_executable(batman "main.cpp" ${SOURCES})

