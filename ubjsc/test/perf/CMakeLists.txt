set(SOURCES
    test_glue_dict_list.c
    test_glue_array_array.c
)
add_executable(test-perf-ubjsc ${SOURCES})
target_link_libraries(test-perf-ubjsc ubjsc test-frmwrk-perf)

target_include_directories(test-perf-ubjsc PUBLIC
    "${CMAKE_SOURCE_DIR}/test-frmwrk"
    "${CMAKE_SOURCE_DIR}/test-frmwrk-perf"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../api"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../src"
)
add_test(NAME test-perf-ubjsc COMMAND test-perf-ubjsc --verbose)

