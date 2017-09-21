cmake_minimum_required(VERSION 3.0)
include("cmake/HunterGate.cmake")
HunterGate(
#    URL "https://github.com/ruslo/hunter/archive/v0.16.15.tar.gz"
#    SHA1 "6974c2150fc0d3b09de3ad1efcbf15d360647ffa"
    URL "https://bitbucket.org/tsieprawski/hunter/get/master.tar.gz"
    SHA1 "9e977766ed875e6fd5e6ec1581901588dedd12b8"
)

project(ubjsc0.7)

set(WITH_TESTING OFF CACHE BOOL "")
set(WITH_API_TESTING ON CACHE BOOL "")
set(WITH_STRESS_TESTING OFF CACHE BOOL "")
set(WITH_VALGRIND OFF CACHE BOOL "")

include(GenerateExportHeader)
include(InstallRequiredSystemLibraries)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(CMAKE_DEBUG_POSTFIX "")

find_package(Doxygen)

#hunter_add_package(Jansson)
find_library(Jansson REQUIRED)

hunter_add_package(argtable2)
find_library(argtable2 CONFIG REQUIRED)
include_directories(${ARGTABLE2_ROOT}/include)
link_directories(${ARGTABLE2_ROOT}/lib)

set(CPACK_PACKAGE_NAME libubjsc0.6)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Enterprise grade-wannabe C library for manipulating and streaming data in UBJSON format.")
set(CPACK_PACKAGE_VENDOR "Tomasz Sieprawski")
set(CPACK_PACKAGE_CONTACT "tomasz@sieprawski.eu")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENCE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_VERSION "0.6.0")
set(CPACK_SOURCE_IGNORE_FILES
    "^${PROJECT_SOURCE_DIR}/.hg"
    "^${PROJECT_SOURCE_DIR}/.hgsub$"
    "^${PROJECT_SOURCE_DIR}/.hgsubstate$"
    "^${PROJECT_SOURCE_DIR}/.hgignore$"
    "^${PROJECT_SOURCE_DIR}/.*.bat$"
    "^${PROJECT_SOURCE_DIR}/.*.sh$"
    "^${PROJECT_SOURCE_DIR}/build"
    "^${PROJECT_SOURCE_DIR}/bitbucket-pipelines.yml"
    "^${PROJECT_SOURCE_DIR}/dist"
    "^${PROJECT_SOURCE_DIR}/ptrie"
    "^${PROJECT_SOURCE_DIR}/ubjspy/test/__pycache__"
    "^${PROJECT_SOURCE_DIR}/valgrind.supp"
)
set(CPACK_STRIP_FILES TRUE)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libjansson4")

set(CPACK_COMPONENTS_ALL headers libraries tools documentation)
# set(CPACK_DEB_COMPONENT_INSTALL ON)
# set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)

set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C Headers")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_TOOLS_DISPLAY_NAME "Tools")
set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Documentation")

set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)
set(CPACK_COMPONENT_TOOLS_DEPENDS libraries)
set(CPACK_COMPONENT_DOCUMENTATION_DEPENDS libraries)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(CPack)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fvisibility=hidden")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -fprofile-arcs -ftest-coverage")
endif(UNIX)

if (WITH_TESTING)
    find_package(Criterion REQUIRED)

    enable_testing()
    add_subdirectory(test-frmwrk)
    add_subdirectory(test-frmwrk-glue)
endif (WITH_TESTING)

if (WITH_VALGRIND)
    set(TEST_PREFIX valgrind --log-file=${PROJECT_BINARY_DIR}/memcheck.%p.txt --leak-check=full --show-leak-kinds=all --show-reachable=yes --trace-children=yes)
endif (WITH_VALGRIND)

add_subdirectory(ubjsc)

find_library(PTRIE NAMES ptrie)
if (PTRIE)
    add_subdirectory(ubjsc-glue-dict-ptrie)
endif (PTRIE)

# @todo issue-
# add_subdirectory(ubjspy)
add_subdirectory(tools)

if(DOXYGEN_FOUND)
    configure_file(Doxyfile.man.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.man @ONLY)
    add_custom_target(man
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.man
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        SOURCES Doxyfile.man.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.man
                README.md
    )
    add_dependencies(man ubjsc)
    file(GLOB FILES_MAN3 ${CMAKE_CURRENT_BINARY_DIR}/man/man3/ubjs_*.3)
    install(FILES
        ${FILES_MAN3}
        DESTINATION man/man3
        COMPONENT documentation)

    configure_file(Doxyfile.html.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.html @ONLY)
    add_custom_target(html
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.html
        COMMAND ${CMAKE_COMMAND} -E tar "cf" html.zip --format=zip ${CMAKE_CURRENT_BINARY_DIR}/html
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        SOURCES Doxyfile.html.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.html
                README.md
    )
    file(GLOB FILES_MD docs/*.md)
    install(FILES
        ${FILES_MD}
        ${CMAKE_CURRENT_BINARY_DIR}/html.zip
        DESTINATION share/doc/libubjsc0.7
        COMPONENT documentation)
endif(DOXYGEN_FOUND)

install(FILES
    LICENSE.md
    DESTINATION share/doc/libubjsc0.7
    COMPONENT documentation)
