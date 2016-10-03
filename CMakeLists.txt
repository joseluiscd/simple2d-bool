cmake_minimum_required (VERSION 2.6)
project (SIMPLE2DBOOL)

file(GLOB SOURCES "*.cpp")
add_executable(main ${SOURCES})
add_library(simple2dbool SHARED ${SOURCES})
add_library(simple2dbool_static STATIC ${SOURCES})

#Tests
enable_testing()
add_subdirectory(test)
