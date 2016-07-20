add_executable(ubj2js
    ../include/ubjs.h
    ../jansson/include/jansson.h
    ../argtable2/src/argtable2.h
    ubj2js_main.c)
target_link_libraries(ubj2js ubjs jansson argtable2)
target_include_directories(ubj2js PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    "${CMAKE_BINARY_DIR}/jansson/include"
    "${CMAKE_SOURCE_DIR}/argtable2/src")

add_executable(ubjq
    ../include/ubjs.h
    ../argtable2/src/argtable2.h
    ubjq_main.c)
target_link_libraries(ubjq ubjs argtable2)
target_include_directories(ubjq PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    "${CMAKE_SOURCE_DIR}/argtable2/src")

add_executable(js2ubj
    ../include/ubjs.h
    ../jansson/include/jansson.h
    ../argtable2/src/argtable2.h
    js2ubj_main.c)
target_link_libraries(js2ubj ubjs jansson argtable2)
target_include_directories(js2ubj PUBLIC
    "${CMAKE_BINARY_DIR}/src"
    "${CMAKE_BINARY_DIR}/jansson/include"
    "${CMAKE_SOURCE_DIR}/argtable2/src")

install(TARGETS ubj2js
    RUNTIME DESTINATION bin
    COMPONENT ubj2js
)
install(TARGETS ubjq
    RUNTIME DESTINATION bin
    COMPONENT ubjq
)
install(TARGETS js2ubj
    RUNTIME DESTINATION bin
    COMPONENT js2ubj
)
