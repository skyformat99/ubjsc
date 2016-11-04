find_package(PythonInterp 3.4)
find_package(PythonLibs 3.4)

if (${PYTHONLIBS_FOUND})
    set(PY_CFLAGS "")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(PY_CFLAGS "${PY_CFLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    
    add_custom_command(OUTPUT ubjspy-setuppy
        COMMAND ${CMAKE_COMMAND} -E env CFLAGS=${PY_CFLAGS}
                ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/setup.py
                bdist_wheel --dist-dir=${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    add_custom_target(ubjspy ALL
        DEPENDS ubjs ubjspy-setuppy
        SOURCES setup.py ubjspy.h ubjspy.c test/unittests.py tests_venv.py
    )

    add_test(NAME unittests-py
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/setup.py
                test ${CMAKE_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    set_tests_properties(unittests-py PROPERTIES
        DEPENDS ubjspy)
    add_test(NAME venv-py
        COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests_venv.py
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    set_tests_properties(venv-py PROPERTIES
        DEPENDS ubjspy)
else (${PYTHONLIBS_FOUND})
    message(WARNING "Not building python wrappers, as Python nor libs nor interpreter were found")
endif (${PYTHONLIBS_FOUND})

