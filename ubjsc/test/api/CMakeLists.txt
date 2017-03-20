set(SOURCES
    test_common.h test_common.c
    test_glue_mock.h test_glue_mock.c

    test_library.c
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
        test_writer_free_primitives_early.c
)
add_executable(test-api-ubjsc ${SOURCES})
target_link_libraries(test-api-ubjsc ubjsc test-frmwrk)

target_include_directories(test-api-ubjsc PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src")
add_test(NAME test-api-ubjsc COMMAND test-api-ubjsc --verbose)

