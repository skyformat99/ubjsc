set(FILES
	../include/ubjs.h
	test.h test.c
	test_list.h test_list.c
	test_common.h test_common.c
	test_primitives.h test_primitives.c
	test_parser_tools.h test_parser_tools.c
	test_parser.h test_parser.c
	test_writer_tools.h test_writer_tools.c
	test_writer.h test_writer.c)

add_executable(unittest ${FILES} test_main.c)
target_link_libraries(unittest ubjs cunit)
add_test(NAME unittest COMMAND unittest)

