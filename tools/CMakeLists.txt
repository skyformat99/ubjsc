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

add_test(NAME test-tools
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.sh
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
set_tests_properties(test-tools PROPERTIES
    DEPENDS ubj2js ubjq js2ubj)

