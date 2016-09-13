cmake_minimum_required(VERSION 2.8)
project(ubjsc)

enable_testing()

include(GenerateExportHeader)
include(InstallRequiredSystemLibraries)

set(JANSSON_EXPORT_DIR "" CACHE STRING "Where exports for jansson library lie.")
set(ARGTABLE2_EXPORT_DIR "" CACHE STRING "Where exports for argtable2 library lie.")

find_package(Doxygen)

if ("${JANSSON_EXPORT_DIR}" STREQUAL "")
    message("Jansson not supplied, will find'em.")
    find_library(jansson REQUIRED)
else ("${JANSSON_EXPORT_DIR}" STREQUAL "")
    message("Jansson supplied: <${JANSSON_EXPORT_DIR}>")
    set(JANSSON_WITHOUT_TESTS ON)
    include("${JANSSON_EXPORT_DIR}/cmake/JanssonConfig.cmake")
    include_directories(${JANSSON_INCLUDE_DIRS})
    get_target_property(JANSSON_LOCATION jansson LOCATION)
    install(FILES ${JANSSON_LOCATION} DESTINATION bin)
endif ("${JANSSON_EXPORT_DIR}" STREQUAL "")

if ("${ARGTABLE2_EXPORT_DIR}" STREQUAL "")
    message("Argtable2 not supplied, will find'em.")
    find_library(jansson REQUIRED)
else ("${ARGTABLE2_EXPORT_DIR}" STREQUAL "")
    message("Argtable2 supplied: <${ARGTABLE2_EXPORT_DIR}>")
    include_directories(${ARGTABLE2_EXPORT_DIR}/include)
    include("${ARGTABLE2_EXPORT_DIR}/cmake/argtable2-exports.cmake")
endif ("${ARGTABLE2_EXPORT_DIR}" STREQUAL "")

set(CPACK_PACKAGE_NAME libubjsc)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Enterprise-grade C library for manipulating UBJSON")
set(CPACK_PACKAGE_VENDOR "Tomasz Sieprawski")
set(CPACK_PACKAGE_CONTACT "tomasz@sieprawski.eu")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENCE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_SOURCE_IGNORE_FILES "/.hg/" ".hgignore" "/build/" "/dist/" "~$" ".orig$" ".sh$" "/.hgsub"
    "/.hgsubstate" "/.sonar" "/sonar-project.properties")
set(CPACK_STRIP_FILES "lib/libubjson.so;lib/libptrie.so")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
include(CPack)

if(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS_DEBUG "-g -O0 -fprofile-arcs -ftest-coverage")
endif(UNIX)

add_subdirectory(ptrie/include)
add_subdirectory(ptrie/src)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

add_subdirectory(tools)

if(DOXYGEN_FOUND)
    configure_file(Doxyfile.man.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.man @ONLY)
    add_custom_target(man
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.man
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        SOURCES Doxyfile.man.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.man
                docs/index.md
    )
    add_dependencies(man ubjs)
    file(GLOB FILES_MAN3 ${CMAKE_CURRENT_BINARY_DIR}/man/man3/ubjs_*.3)
    install(FILES ${FILES_MAN3} DESTINATION man/man3)

    configure_file(Doxyfile.html.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.html @ONLY)
    add_custom_target(html
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.html
        COMMAND ${CMAKE_COMMAND} -E tar "cf" html.zip --format=zip ${CMAKE_CURRENT_BINARY_DIR}/html
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        SOURCES Doxyfile.html.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.html
                docs/index.md
    )
    add_dependencies(html ubjs)
    file(GLOB FILES_MD docs/*.md)
    install(FILES ${FILES_MD} ${CMAKE_CURRENT_BINARY_DIR}/html.zip DESTINATION share/doc/libubjsc)
endif(DOXYGEN_FOUND)

install(FILES LICENSE.md DESTINATION share/doc/libubjsc)
