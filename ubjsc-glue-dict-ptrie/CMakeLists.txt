add_subdirectory(src)

if (WITH_TESTING AND WITH_STRESS_TESTING)
    add_subdirectory(test)
endif (WITH_TESTING AND WITH_STRESS_TESTING)
