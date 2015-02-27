cmake_minimum_required (VERSION 2.6.4)
project (cppstd)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

add_subdirectory (boost_algorithm_string)
add_subdirectory (regex)

add_subdirectory (ch10)
add_subdirectory (ch10_1)

add_subdirectory (templ_ch2)
add_subdirectory (templ_ch3)
add_subdirectory (templ_ch4)
add_subdirectory (templ_ch5)
add_subdirectory (templ_ch6)
add_subdirectory (templ_ch8)
add_subdirectory (templ_ch9)
add_subdirectory (templ_ch10)

