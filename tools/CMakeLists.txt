add_executable(ubj2js
    ../ubjsc/src/ubjs.h
    ${JANSSON_INCLUDES}
    ${ARGTABLE_INCLUDES}
    ubj2js_main.c)
target_link_libraries(ubj2js ubjsc ubjsc-glue-dict-ptrie jansson argtable2)
target_include_directories(ubj2js PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    ${JANSSON_INCLUDE_DIRS}
    ${ARGTABLE_INCLUDE_DIRS})

add_executable(ubjq
    ../ubjsc/src/ubjs.h
    ${ARGTABLE2_INCLUDES}
    ubjq_main.c)
target_link_libraries(ubjq ubjsc ubjsc-glue-dict-ptrie argtable2)
target_include_directories(ubjq PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    ${ARGTABLE_INCLUDE_DIRS})

add_executable(js2ubj
    ../ubjsc/src/ubjs.h
    ${JANSSON_INCLUDES}
    ${ARGTABLE_INCLUDES}
    js2ubj_main.c)
target_link_libraries(js2ubj ubjsc ubjsc-glue-dict-ptrie jansson argtable2)
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
