cmake_minimum_required(VERSION 3.11)

project(
    friendly-umm
    VERSION 0.1
    DESCRIPTION "Compiler for FriendlyUmmLang"
    LANGUAGES CXX
)

set(OUTPUT_DIRECTORY artifact)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/lib)
set(CMAKE_TEST_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/bin)

add_subdirectory(apps/FriendlyUmmCompiler)
add_subdirectory(modules/CodeGenerator)
add_subdirectory(modules/Parser)
add_subdirectory(modules/Scanner)
add_subdirectory(modules/SymbolTable)
