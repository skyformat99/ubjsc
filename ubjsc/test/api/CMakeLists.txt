add_executable(test-api-ubjsc
    test_common.h test_common.c
    test_glue_mock.h test_glue_mock.c

    test_library.c
    test_primitives.h test_primitives.c
        test_primitive_null.c
        test_primitive_noop.c
        test_primitive_true.c
        test_primitive_false.c
        test_primitive_uint8.c
        test_primitive_int8.c
        test_primitive_int16.c
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
        test_writer_free_primitives_early.c
)
target_link_libraries(test-api-ubjsc ubjsc test-frmwrk test-frmwrk-glue)
target_include_directories(test-api-ubjsc PUBLIC
    "${CMAKE_SOURCE_DIR}/test-frmwrk"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src")
add_test(NAME test-api-ubjsc COMMAND test-api-ubjsc --verbose)

add_executable(test-api-ubjsc-glue
    test_glue_array_array.c
    test_glue_dict_list.c
)
target_link_libraries(test-api-ubjsc-glue ubjsc test-frmwrk test-frmwrk-glue)
target_include_directories(test-api-ubjsc-glue PUBLIC
    "${CMAKE_SOURCE_DIR}/test-frmwrk"
    "${CMAKE_SOURCE_DIR}/test-frmwrk-glue"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src")
add_test(NAME test-api-ubjsc-glue COMMAND test-api-ubjsc-glue --verbose)

add_test(NAME test-nm-ubjsc
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-nm.sh
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
set_tests_properties(test-nm-ubjsc PROPERTIES
    DEPENDS ubjsc)
