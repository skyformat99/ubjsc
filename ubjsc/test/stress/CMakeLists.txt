set(SOURCES
    test_glue_dict_list.c
    test_glue_array_array.c
    test_primitive_reserialization.c
)
add_executable(test-stress-ubjsc ${SOURCES})
target_link_libraries(test-stress-ubjsc ubjsc test-frmwrk test-frmwrk-glue)

target_include_directories(test-stress-ubjsc PUBLIC
    "${CMAKE_SOURCE_DIR}/test-frmwrk"
    "${CMAKE_SOURCE_DIR}/test-frmwrk-stress"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../api"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src"
)
add_test(NAME test-stress-ubjsc COMMAND test-stress-ubjsc --verbose)

