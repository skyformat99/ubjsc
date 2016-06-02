set(FILES
	../include/ubjs.h
	test.h test.c
	test_list.h test_list.c
	test_common.c
	test_objects.c
	test_parser_tools.h test_parser_tools.c test_parser.c
	test_writer_tools.h test_writer_tools.c test_writer.c)

add_executable(testci ${FILES} test_main.c)
target_link_libraries(testci ubjs cunit)
add_test(NAME testci COMMAND testci)

add_executable(testui ${FILES} test_ui.c)
target_link_libraries(testui ubjs cunit)
