add_library(ptrie SHARED
	../include/ptrie.h ptrie.c)
target_link_libraries(ptrie ${CONAN_LIBS})
install(TARGETS ptrie
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	COMPONENT library)

