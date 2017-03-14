set(SOURCES
    test_glue_common.h test_glue_common.c
    test_glue_array_generic.h test_glue_array_generic.c
    test_glue_dict_generic.h test_glue_dict_generic.c
)

add_library(test-frmwrk-perf ${SOURCES})
target_include_directories(test-frmwrk-perf PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/ubjsc/src"
)
if (UNIX)
    target_link_libraries(test-frmwrk-perf test-frmwrk ubjsc m)
else (UNIX)
    target_link_libraries(test-frmwrk-perf test-frmwrk ubjsc)
endif (UNIX)
