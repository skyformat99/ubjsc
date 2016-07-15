set(SOURCES
	../include/ubjs.h
	test_frmwrk.h test_frmwrk.c
	test_list.h test_list.c
	test_common.h test_common.c
	test_primitives.h test_primitives.c
	test_parser_tools.h test_parser_tools.c
	test_parser.h test_parser.c
	test_writer_tools.h test_writer_tools.c
	test_writer.h test_writer.c)

add_executable(unittests ${SOURCES} test_main.c)
target_link_libraries(unittests ubjs)
target_include_directories(unittests PUBLIC "${PROJECT_BINARY_DIR}/src")
add_test(NAME unittests COMMAND unittests)

add_executable(unittests++ ${SOURCES} test_main.cpp)
target_link_libraries(unittests++ ubjs)
target_include_directories(unittests++ PUBLIC "${PROJECT_BINARY_DIR}/src")
add_test(NAME unittests++ COMMAND unittests++)
