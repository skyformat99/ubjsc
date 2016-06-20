set(FILES
	../include/ptrie.h
	test.h test.c
)
add_executable(unittest ${FILES} test_main.c)
target_link_libraries(unittest ptrie cunit)
add_test(NAME unittest COMMAND unittest)

