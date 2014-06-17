cmake_minimum_required(VERSION 2.8)

project (SlickDsp)

#set(CMAKE_SUPPRESS_REGENERATION TRUE) # For doing test coverage

file (GLOB SOURCE_HEADERS "src/*.h")

set( KISSFFT_DIR ../kiss_fft130 )
SET(kiss_SRCS ${KISSFFT_DIR}/kiss_fft.c ${KISSFFT_DIR}/kiss_fft.h ${KISSFFT_DIR}/_kiss_fft_guts.h ${KISSFFT_DIR}/tools/kiss_fftr.c ${KISSFFT_DIR}/tools/kiss_fftr.h)
ADD_LIBRARY(kissfft STATIC ${kiss_SRCS} )

set( GOOGLETEST_DIR ../googletest-read-only )
INCLUDE_DIRECTORIES(src ${KISSFFT_DIR} ${KISSFFT_DIR}/tools ${GOOGLETEST_DIR}/include)
add_subdirectory (${GOOGLETEST_DIR} gtest)

AUX_SOURCE_DIRECTORY(test TEST_SOURCES)
add_executable (SlickDspTests ${SOURCE_HEADERS} ${TEST_SOURCES})
target_link_libraries (SlickDspTests kissfft gtest)
