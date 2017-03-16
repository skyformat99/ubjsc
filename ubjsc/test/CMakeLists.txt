if (WITH_API_TESTING)
    add_subdirectory(api)
endif (WITH_API_TESTING)

if (WITH_PERF_TESTING)
    add_subdirectory(perf)
endif (WITH_PERF_TESTING)
