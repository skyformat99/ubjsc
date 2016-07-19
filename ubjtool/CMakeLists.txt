add_executable(ubjtool
    ../include/ubjs.h
    ubjtool_main.c)
target_link_libraries(ubjtool ubjs)
target_include_directories(ubjtool PUBLIC "${PROJECT_BINARY_DIR}/src")

install(TARGETS ubjtool
    RUNTIME DESTINATION bin
    COMPONENT ubjtool
)
