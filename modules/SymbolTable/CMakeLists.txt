project(
    symbol-table
    DESCRIPTION "Symbol tables"
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG "10.1.1"
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG "v1.12.0"
)
FetchContent_MakeAvailable(spdlog)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(${PROJECT_NAME} ${LIBRARY_TYPE} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_options(${PROJECT_NAME} PRIVATE LINKER:-no_warn_duplicate_libraries)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt spdlog common)

add_dependencies(${PROJECT_NAME} common)

add_subdirectory(test)
