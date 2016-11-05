set(SOURCES
    ../include/ubjs.h
    test_frmwrk.h test_frmwrk.c
    test_list.h test_list.c
    test_common.h test_common.c
    test_primitives.h test_primitives.c
    test_parser_tools.h test_parser_tools.c
    test_parser.h test_parser.c
        test_parser_lenghted.c
        test_parser_non_lenghted.c
        test_parser_array.c
        test_parser_array_optimized_type.c
        test_parser_object.c
        test_parser_object_optimized_type.c
    test_writer_tools.h test_writer_tools.c
    test_writer.h test_writer.c
        test_writer_noncontainers.c
        test_writer_array.c
        test_writer_array_optimized_type.c
        test_writer_array_upgrades.c 
        test_writer_object.c
        test_writer_object_optimized_type.c
        test_writer_object_upgrades.c 
)

add_executable(unittests-c ${SOURCES} test_main.c)
target_link_libraries(unittests-c ubjs)
target_include_directories(unittests-c PUBLIC
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_BINARY_DIR}/src")
add_test(NAME unittests-c COMMAND unittests-c)
set_tests_properties(unittests-c PROPERTIES TIMEOUT 30)

#add_executable(unittests++ ${SOURCES} test_main.cpp)
#target_link_libraries(unittests++ ubjs)
#target_include_directories(unittests++ PUBLIC
#    "${CMAKE_SOURCE_DIR}/src"
#    "${CMAKE_BINARY_DIR}/src")
#add_test(NAME unittests++ COMMAND unittests++)
