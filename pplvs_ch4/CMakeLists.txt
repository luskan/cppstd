cmake_minimum_required (VERSION 2.6)
project (pplvs_ch4)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
	ADD_DEFINITIONS( "-D_MSC_PLATFORM_TOOLSET=$(PlatformToolsetVersion)" )
ENDIF()

file(GLOB pplvs_ch4_SRC
    "*.h"
    "*.cpp"
	"../common/ppl_common.h"
	"../common/ppl_common.cpp"
)

add_executable(pplvs_ch4 ${pplvs_ch4_SRC})
