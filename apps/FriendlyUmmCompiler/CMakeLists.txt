project(
    friendly-umm-compiler
    LANGUAGES CXX
)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_options(${PROJECT_NAME} PRIVATE LINKER:-no_warn_duplicate_libraries)
target_link_libraries(${PROJECT_NAME} PUBLIC common scanner parser code-generator symbol-table log-manager)

add_dependencies(${PROJECT_NAME} common scanner parser code-generator symbol-table log-manager)
