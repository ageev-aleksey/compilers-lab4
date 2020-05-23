cmake_minimum_required(VERSION 3.15)

project(lab4)
set(CMAKE_CXX_STANDARD 17)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)


add_executable(lab4 ${SRC})
target_include_directories(lab4 PUBLIC ${INCLUDE_DIR})