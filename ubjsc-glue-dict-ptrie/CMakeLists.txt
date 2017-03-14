add_subdirectory(src)

if (WITH_TESTING AND WITH_PERF_TESTING)
    add_subdirectory(test)
endif (WITH_TESTING AND WITH_PERF_TESTING)
