add_executable(ubjstest
	../ubjs/ubjs.h
	test.h test.c
	test_list.h test_list.c
	test_common.c
	test_objects.c
	test_parser_tools.h test_parser_tools.c test_parser.c 
	test_writer_tools.h test_writer_tools.c test_writer.c)
target_link_libraries(ubjstest ubjs cunit)

add_test(NAME ubjstest COMMAND ubjstest)

