cmake_minimum_required(VERSION 2.8)

project (SmartDsp)

file (GLOB SOURCE_HEADERS "src/*.h")

set( GOOGLETEST_DIR ../googletest-read-only )
INCLUDE_DIRECTORIES(src ${GOOGLETEST_DIR}/include)
add_subdirectory (${GOOGLETEST_DIR} gtest)

AUX_SOURCE_DIRECTORY(test TEST_SOURCES)
add_executable (SmartDspTests ${SOURCE_HEADERS} ${TEST_SOURCES})
target_link_libraries (SmartDspTests gtest)
