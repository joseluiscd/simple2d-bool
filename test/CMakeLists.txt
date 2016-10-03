include_directories(${SIMPLE2DBOOL_SOURCE_DIR})

add_executable(tinclusion.out triangle_inclusion.cpp)
target_link_libraries(tinclusion.out simple2dbool)
add_test(TriangleInclusion tinclusion.out)

add_executable(pinclusion.out polygon_inclusion.cpp)
target_link_libraries(pinclusion.out simple2dbool)
add_test(PolygonInclusion pinclusion.out)
