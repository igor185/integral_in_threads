cmake_minimum_required(VERSION 3.16.3)
project(integral)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package( Threads )

add_executable(integral src/main.cpp src/functions.h src/single.h src/parallel.h src/help.h)

target_link_libraries( integral ${CMAKE_THREAD_LIBS_INIT} )