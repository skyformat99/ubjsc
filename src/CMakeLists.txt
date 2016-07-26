add_library(ubjs SHARED
    ../ptrie/include/ptrie.h
    "${CMAKE_CURRENT_BINARY_DIR}/ubjs_exports.h"
    ../include/ubjs_common.h ubjs_common.c
    ../include/ubjs_primitives.h ubjs_primitives_prv.h ubjs_primitives.c
    ../include/ubjs_parser.h ubjs_parser_prv.h ubjs_parser.c
    ../include/ubjs_writer.h ubjs_writer_prv.h ubjs_writer.c
    ../include/ubjs.h ubjs.c)
generate_export_header(ubjs
    BASE_NAME ubjs
    EXPORT_MACRO_NAME UBJS_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/ubjs_exports.h
    STATIC_DEFINE UBJS_EXPORTS_BUILT_AS_STATIC
)
target_include_directories(ubjs PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/ptrie/include"
    "${CMAKE_BINARY_DIR}/ptrie/src")
target_link_libraries(ubjs ptrie)
if (LINUX)
    target_link_libraries(ubjs m)
endif (LINUX)
install(TARGETS ubjs
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    COMPONENT ubjs
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ubjs_exports.h
    DESTINATION include
)
