cmake_minimum_required(VERSION 3.20)
project(DisablePrivateChat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDK 根目录（与 .github 同级）
set(LL_SDK "${CMAKE_SOURCE_DIR}/SDK")

# 添加头文件搜索路径（关键：必须包含 LiteLoader/include）
include_directories(
    ${LL_SDK}/LiteLoader/include
)

# 添加库文件搜索路径
link_directories(${LL_SDK}/LiteLoader/lib)

# 编译选项
add_compile_options(/utf-8)
add_compile_definitions(
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_WARNINGS
    _AMD64_
    _WIN64
)

# 插件源文件（必须带 .cpp 扩展名）
add_library(DisablePrivateChat SHARED src/Plugin.cpp)

# 自动链接 SDK/lib 下所有的 .lib 文件（确保不遗漏）
file(GLOB LL_LIB_FILES "${LL_SDK}/LiteLoader/lib/*.lib")
if(LL_LIB_FILES)
    target_link_libraries(DisablePrivateChat PRIVATE ${LL_LIB_FILES})
endif()

# 输出目录
set_target_properties(DisablePrivateChat PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
