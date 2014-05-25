cmake_minimum_required(VERSION 2.8)

project (SmartDsp)

AUX_SOURCE_DIRECTORY(src LIB_SOURCES)
# add_library (SmartDsp ${LIB_SOURCES})

set( GOOGLETEST_DIR ../googletest-read-only )
INCLUDE_DIRECTORIES(src ${GOOGLETEST_DIR}/include)
add_subdirectory (${GOOGLETEST_DIR} gtest)

AUX_SOURCE_DIRECTORY(test TEST_SOURCES)
add_executable (SmartDspTests ${LIB_SOURCES} ${TEST_SOURCES})
target_link_libraries (SmartDspTests gtest)
