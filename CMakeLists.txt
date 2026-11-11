cmake_minimum_required(VERSION 3.20)
project(compiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(compiler_lib
    token_type.cpp
    lexer.cpp
    ast.cpp
    parser.cpp
)
target_include_directories(compiler_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(compiler main.cpp)
target_link_libraries(compiler PRIVATE compiler_lib)