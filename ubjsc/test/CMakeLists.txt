add_subdirectory(api)

if (WITH_PERF_TESTING)
    add_subdirectory(perf)
endif (WITH_PERF_TESTING)
