cmake_minimum_required (VERSION 2.6)
project (simple2d_bool)

file(GLOB SOURCES "*.cpp")
add_executable(main ${SOURCES})
add_library(simple2dbool SHARED ${SOURCES})
add_library(simple2dbool_static STATIC ${SOURCES})
