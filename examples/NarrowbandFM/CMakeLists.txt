cmake_minimum_required(VERSION 2.8)

project (NarrowbandFM)

file (GLOB SOURCE_HEADERS "../../src/*.h")

set( KISSFFT_DIR ../../../kiss_fft130 )
SET(kiss_SRCS ${KISSFFT_DIR}/kiss_fft.c ${KISSFFT_DIR}/kiss_fft.h ${KISSFFT_DIR}/_kiss_fft_guts.h ${KISSFFT_DIR}/tools/kiss_fftr.c ${KISSFFT_DIR}/tools/kiss_fftr.h)
ADD_LIBRARY(kissfft STATIC ${kiss_SRCS} )

INCLUDE_DIRECTORIES(../../src ${KISSFFT_DIR} ${KISSFFT_DIR}/tools)

AUX_SOURCE_DIRECTORY(src APP_SOURCES)
add_executable (NarrowbandFm ${SOURCE_HEADERS} ${APP_SOURCES})
target_link_libraries (NarrowbandFm kissfft)
