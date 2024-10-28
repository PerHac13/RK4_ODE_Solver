cmake_minimum_required(VERSION 3.10)
project(RK4Solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp)

add_executable(${project} ${SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(RK4Solver Threads::Threads)
