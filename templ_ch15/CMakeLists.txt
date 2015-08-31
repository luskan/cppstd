cmake_minimum_required (VERSION 2.6)
project (templ_ch15)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

file(GLOB templ_ch15_SRC
    "*.h"
    "*.cpp"
)

add_executable(templ_ch15 ${templ_ch15_SRC})
