if (WITH_API_TESTING)
    add_executable(test-api-ubjsc-glue-dict-ptrie test_api.c)
    target_link_libraries(test-api-ubjsc-glue-dict-ptrie test-frmwrk-glue ubjsc-glue-dict-ptrie)
    target_include_directories(test-api-ubjsc-glue-dict-ptrie PUBLIC
        "${CMAKE_SOURCE_DIR}/test-frmwrk"
        "${CMAKE_SOURCE_DIR}/test-frmwrk-glue"
        "${CMAKE_BINARY_DIR}/ubjsc/src"
        "${CMAKE_SOURCE_DIR}/ubjsc/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
        "${CMAKE_CURRENT_BINARY_DIR}/../src"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    add_test(NAME test-api-ubjsc-glue-dict-ptrie COMMAND test-api-ubjsc-glue-dict-ptrie --verbose)
endif (WITH_API_TESTING)

if (WITH_STRESS_TESTING)
    add_executable(test-glue-ubjsc-glue-dict-ptrie test_stress.c)
    target_link_libraries(test-glue-ubjsc-glue-dict-ptrie test-frmwrk-glue ubjsc-glue-dict-ptrie)
    target_include_directories(test-glue-ubjsc-glue-dict-ptrie PUBLIC
        "${CMAKE_SOURCE_DIR}/test-frmwrk"
        "${CMAKE_SOURCE_DIR}/test-frmwrk-glue"
        "${CMAKE_BINARY_DIR}/ubjsc/src"
        "${CMAKE_SOURCE_DIR}/ubjsc/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/../src"
        "${CMAKE_CURRENT_BINARY_DIR}/../src"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    )
    add_test(NAME test-glue-ubjsc-glue-dict-ptrie COMMAND test-glue-ubjsc-glue-dict-ptrie --verbose)
endif (WITH_STRESS_TESTING)

add_test(NAME test-nm-ubjsc-glue-dict-ptrie
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-nm.sh
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
set_tests_properties(test-nm-ubjsc-glue-dict-ptrie PROPERTIES
    DEPENDS ubjsc-glue-dict-ptrie)

