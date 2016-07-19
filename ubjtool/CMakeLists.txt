add_executable(ubj2js
    ../include/ubjs.h
    ubj2js_main.c)
target_link_libraries(ubj2js ubjs)
target_include_directories(ubj2js PUBLIC "${PROJECT_BINARY_DIR}/src")

add_executable(js2ubj
    ../include/ubjs.h
    js2ubj_main.c)
target_link_libraries(js2ubj ubjs)
target_include_directories(js2ubj PUBLIC "${PROJECT_BINARY_DIR}/src")

install(TARGETS ubj2js
    RUNTIME DESTINATION bin
    COMPONENT ubj2js
)
install(TARGETS js2ubj
    RUNTIME DESTINATION bin
    COMPONENT js2ubj
)
