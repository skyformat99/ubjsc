add_executable(ubj2js
    ../ubjsc/src/ubjs.h
    ${JANSSON_INCLUDES}
    ${ARGTABLE_INCLUDES}
    ubj2js_main.c)
target_link_libraries(ubj2js ubjsc jansson argtable2)
target_include_directories(ubj2js PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    ${JANSSON_INCLUDE_DIRS}
    ${ARGTABLE_INCLUDE_DIRS})

add_executable(ubjq
    ../ubjsc/src/ubjs.h
    ${ARGTABLE2_INCLUDES}
    ubjq_main.c)
target_link_libraries(ubjq ubjsc argtable2)
target_include_directories(ubjq PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    ${ARGTABLE_INCLUDE_DIRS})

add_executable(js2ubj
    ../ubjsc/src/ubjs.h
    ${JANSSON_INCLUDES}
    ${ARGTABLE_INCLUDES}
    js2ubj_main.c)
target_link_libraries(js2ubj ubjsc jansson argtable2)
target_include_directories(js2ubj PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    ${JANSSON_INCLUDE_DIRS}
    ${ARGTABLE2_INCLUDE_DIRS})

install(TARGETS ubj2js
    RUNTIME DESTINATION bin
    COMPONENT tools
)
install(TARGETS ubjq
    RUNTIME DESTINATION bin
    COMPONENT tools
)
install(TARGETS js2ubj
    RUNTIME DESTINATION bin
    COMPONENT tools
)

if (WITH_TESTING AND WITH_API_TESTING)
    file(GLOB_RECURSE TEST_SHS
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/test
        ${CMAKE_CURRENT_SOURCE_DIR}/test-*.sh)
    foreach(TEST_SH ${TEST_SHS})
        string(REPLACE "/" "_" TEST_SH_NAME ${TEST_SH})
        add_test(NAME test-tools-${TEST_SH_NAME}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${TEST_PREFIX} ${CMAKE_CURRENT_SOURCE_DIR}/test/${TEST_SH})
        set_tests_properties(test-tools-${TEST_SH_NAME} PROPERTIES
            DEPENDS ubj2js ubjq js2ubj)
    endforeach()
endif (WITH_TESTING AND WITH_API_TESTING)
