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

    test_glue_common.h test_glue_common.c
    test_glue_dict_generic.h test_glue_dict_generic.c
    test_glue_dict_list.c
    test_glue_array_generic.h test_glue_array_generic.c
    test_glue_array_array.c
)
add_executable(test-ubjsc ${SOURCES})

if (UNIX)
    target_link_libraries(test-ubjsc ubjsc test-frmwrk m)
else (UNIX)
    target_link_libraries(test-ubjsc ubjsc test-frmwrk)
endif (UNIX)

target_include_directories(test-ubjsc PUBLIC
    "${CMAKE_SOURCE_DIR}/test"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src")
add_test(NAME test-ubjsc COMMAND test-ubjsc)

