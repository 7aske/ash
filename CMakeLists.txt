cmake_minimum_required(VERSION 3.19)
project(ash C)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)

include_directories(${PROJECT_NAME} include)

add_subdirectory(include/ash)

target_link_directories(${PROJECT_NAME} PRIVATE include/ash)

target_link_libraries(${PROJECT_NAME} ashlib)

