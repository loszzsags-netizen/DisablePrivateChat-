cmake_minimum_required(VERSION 3.20)
project(DisablePrivateChat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LL_SDK "${CMAKE_SOURCE_DIR}/SDK")

include_directories(
    ${LL_SDK}/LiteLoader/include
    ${LL_SDK}/LiteLoader/include/llapi
    ${LL_SDK}/LiteLoader/include/llapi/mc
)

link_directories(${LL_SDK}/LiteLoader/lib)

add_compile_options(/utf-8)
add_compile_definitions(
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_WARNINGS
)

add_library(DisablePrivateChat SHARED src/Plugin.cpp)

file(GLOB LL_LIB_FILES "${LL_SDK}/LiteLoader/lib/*.lib")
if(LL_LIB_FILES)
    target_link_libraries(DisablePrivateChat PRIVATE ${LL_LIB_FILES})
endif()

set_target_properties(DisablePrivateChat PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release
)
