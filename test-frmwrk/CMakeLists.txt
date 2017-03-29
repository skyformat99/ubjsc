set(SOURCES
    test_frmwrk.h test_frmwrk.c
    test_list.h test_list.c
)

add_library(test-frmwrk ${SOURCES})
target_include_directories(test-frmwrk PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(test-frmwrk criterion)

