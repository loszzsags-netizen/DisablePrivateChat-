cmake_minimum_required(VERSION 3.20)

project(DisablePrivateChat)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDK指向解压出来的SDK文件夹
set(LLSDK_ROOT "${CMAKE_SOURCE_DIR}/SDK")

include("${LLSDK_ROOT}/LeviLamina.cmake")

add_library(${PROJECT_NAME} SHARED
    src/Plugin.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE LeviLamina)
