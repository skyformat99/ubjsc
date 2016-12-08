set(SOURCES
    test_common.h test_common.c
    test_main.c
)

add_executable(test-ubjsc-glue-dict-ptrie ${SOURCES})
target_link_libraries(test-ubjsc-glue-dict-ptrie test-frmwrk)
target_include_directories(test-ubjsc-glue-dict-ptrie PUBLIC
    "${CMAKE_SOURCE_DIR}/test"
    "${CMAKE_BINARY_DIR}/ubjsc/src"
    "${CMAKE_SOURCE_DIR}/ubjsc/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
    "${CMAKE_CURRENT_BINARY_DIR}/../src"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
add_test(NAME test-ubjsc-glue-dict-ptrie COMMAND test-ubjsc-glue-dict-ptrie)
