cmake_minimum_required (VERSION 2.6)
project (pplvs_ch2)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

file(GLOB pplvs_ch2_SRC
    "*.h"
    "*.cpp"
)

add_executable(pplvs_ch2 ${pplvs_ch2_SRC})
