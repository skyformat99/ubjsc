cmake_minimum_required(VERSION 2.8)
project(ubjsc)
enable_testing()
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_output_dirs_setup()
conan_flags_setup()
set(CMAKE_MODULE_PATH ${CONAN_CMAKE_MODULE_PATH} ${CMAKE_MODULE_PATH})

find_package(PythonLibs 3 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

find_package(CUnit REQUIRED)

find_program(GCOV_PATH gcov)
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)
find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -fprofile-arcs -ftest-coverage")

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

add_custom_target(coverage
        COMMAND ubjstest ${ARGV3}
        COMMAND ${LCOV_PATH} --rc lcov_branch_coverage=1 --directory . --capture --output-file coverage.info
        COMMAND ${LCOV_PATH} --rc lcov_branch_coverage=1 --remove coverage.info 'test*' '/usr/*' --output-file coverage.info.cleaned
        COMMAND ${GENHTML_PATH} --rc lcov_branch_coverage=1 -o coverage coverage.info.cleaned
        COMMAND ${CMAKE_COMMAND} -E remove coverage}.info coverage.info.cleaned

        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET coverage POST_BUILD
        COMMAND ;
        COMMENT "Open ./coverage/index.html in your browser to view the coverage report."
)

