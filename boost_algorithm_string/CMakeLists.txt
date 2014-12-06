cmake_minimum_required (VERSION 2.6)
project (boost_algorithm_string)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

add_executable(boost_algorithm_string main.cpp)
set_property(TARGET boost_algorithm_string PROPERTY PROJECT_LABEL "boost_algorithm_string")