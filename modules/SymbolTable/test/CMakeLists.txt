project(
    symbol-table_test
    DESCRIPTION "symbol-table test suites"
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG "release-1.12.1"
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE gmock gtest_main symbol-table)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_TEST_OUTPUT_DIRECTORY}/${PROJECT_NAME}")
