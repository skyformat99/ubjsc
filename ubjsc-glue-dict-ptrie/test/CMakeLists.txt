set(SOURCES
    test_main.c
)

add_executable(test-stress-ubjsc-glue-dict-ptrie ${SOURCES})
target_link_libraries(test-stress-ubjsc-glue-dict-ptrie test-frmwrk-stress ubjsc-glue-dict-ptrie)
target_include_directories(test-stress-ubjsc-glue-dict-ptrie PUBLIC
    "${CMAKE_SOURCE_DIR}/test-frmwrk"
    "${CMAKE_SOURCE_DIR}/test-frmwrk-stress"
    "${CMAKE_BINARY_DIR}/ubjsc/src"
    "${CMAKE_SOURCE_DIR}/ubjsc/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
    "${CMAKE_CURRENT_BINARY_DIR}/../src"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
add_test(NAME test-stress-ubjsc-glue-dict-ptrie COMMAND test-stress-ubjsc-glue-dict-ptrie --verbose)

