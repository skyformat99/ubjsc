cmake_minimum_required(VERSION 2.8)
project(ubjsc)
enable_testing()

find_library(Xml2 REQUIRED)

find_program(GCOV_PATH gcov)
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)
find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -fprofile-arcs -ftest-coverage")

add_compile_options(-Wall -pedantic)

INCLUDE(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME libubjsc)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Enterprise-grade C library for manipulating UBJSON")
set(CPACK_PACKAGE_VENDOR "Tomasz Sieprawski")
set(CPACK_PACKAGE_CONTACT "tomasz@sieprawski.eu")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENCE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_GENERATOR "TBZ2;ZIP;DEB")
set(CPACK_SOURCE_GENERATOR "TBZ2;ZIP;DEB")
set(CPACK_SOURCE_IGNORE_FILES "/.hg/" ".hgignore" "/build/" "/dist/" "~$" ".orig$")
set(CPACK_STRIP_FILES "lib/libubjson.so")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")
include(CPack)

add_subdirectory(ptrie/include)
add_subdirectory(ptrie/src)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

add_custom_target(coverage
        COMMAND unittests ${ARGV3}
        COMMAND ${LCOV_PATH} --rc lcov_branch_coverage=1 --directory src --capture --output-file coverage.info
        COMMAND ${LCOV_PATH} --rc lcov_branch_coverage=1 --remove coverage.info 'test*' '/usr/*' --output-file coverage.info.cleaned
        COMMAND ${GENHTML_PATH} --rc lcov_branch_coverage=1 -o coverage coverage.info.cleaned
        COMMAND ${CMAKE_COMMAND} -E remove coverage.info coverage.info.cleaned

	COMMAND ${GCOVR_PATH} -x -r ${CMAKE_SOURCE_DIR} -e 'test' -o coverage.xml

        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET coverage POST_BUILD
        COMMAND ;
        COMMENT "Open ./coverage/index.html in your browser to view the coverage report."
)

