add_library(ubjs
	ubjs_common.h ubjs_common.c
	ubjs_objects.h ubjs_objects.c
	ubjs_parser.h ubjs_parser_internal.h ubjs_parser.c
	ubjs_writer.h ubjs_writer.c
	ubjs.h ubjs.c)
target_link_libraries(ubjs ${CONAN_LIBS})

add_library(ubjspy
	ubjs.h
	ubjspy.h
	ubjspy.c)
target_link_libraries(ubjspy ubjs ${PYTHON_LIBRARY})

