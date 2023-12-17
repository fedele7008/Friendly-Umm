cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_COMPILER clang++)

project(
    friendly-umm
    VERSION 0.1
    DESCRIPTION "Compiler for FriendlyUmmLang"
    LANGUAGES CXX
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/cmake)

set(BUILD_DOC ON CACHE BOOL "Build doxygen documentation (require Doxygen)")
set(UML ON CACHE BOOL "Build doxygen documentation with UML diagram (require Doxygen and Graphviz)")

set(LIBRARY_TYPE STATIC)
set(OUTPUT_DIRECTORY artifact)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/lib)
set(CMAKE_TEST_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/bin)

add_subdirectory(apps/FriendlyUmmCompiler)
add_subdirectory(modules/Common)
add_subdirectory(modules/LogManager)
add_subdirectory(modules/CodeGenerator)
add_subdirectory(modules/Parser)
add_subdirectory(modules/Scanner)
add_subdirectory(modules/SymbolTable)

if(BUILD_DOC)
    include(BuildDoc)

    if (UML)
        set(DRAW_UML YES)
    endif()

    set(DOC_EXCLUDE_PATTERN "*/build/* ${CMAKE_BINARY_DIR}/* ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}/*")

    BuildDoxygen(${CMAKE_SOURCE_DIR}/doxygen/Doxyfile.in
    DEST_DIR              ${CMAKE_SOURCE_DIR}/${OUTPUT_DIRECTORY}
    INPUT_ROOT_DIR        ${CMAKE_SOURCE_DIR}
    EXCLUDE_PATTERNS_DIR  ${DOC_EXCLUDE_PATTERN}
    )
endif()
