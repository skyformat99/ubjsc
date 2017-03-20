if (WITH_API_TESTING)
    add_subdirectory(api)
endif (WITH_API_TESTING)

if (WITH_STRESS_TESTING)
    add_subdirectory(stress)
endif (WITH_STRESS_TESTING)
