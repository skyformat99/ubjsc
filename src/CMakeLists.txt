add_library(ubjs SHARED
	../ptrie/include/ptrie.h
	../include/ubjs_common.h ubjs_common.c
	../include/ubjs_primitives.h ubjs_primitives.c
	../include/ubjs_parser.h ubjs_parser_internal.h ubjs_parser.c
	../include/ubjs_writer.h ubjs_writer.c
	../include/ubjs.h ubjs.c)
target_link_libraries(ubjs ptrie ${CONAN_LIBS})
install(TARGETS ubjs
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	COMPONENT library)
