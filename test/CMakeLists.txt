project(test)
include_directories(${SIMPLE2DBOOL_SOURCE_DIR})
macro(add_unit_test name source)
    add_executable(${source}.out ${source})
    target_link_libraries(${source}.out simple2dbool)
    add_test(${name} ${source}.out)
endmacro(add_unit_test)


add_unit_test(TriangleInclusion triangle_inclusion.cpp)
add_unit_test(PolygonInclusion polygon_inclusion.cpp)
