add_library(ubjsc SHARED
    ../ptrie/include/ptrie.h
    "${CMAKE_CURRENT_BINARY_DIR}/ubjs_exports.h"
    ../include/ubjs_common.h ubjs_common_prv.h ubjs_common.c
    ../include/ubjs_primitives.h ubjs_primitives_prv.h ubjs_primitives.c
    ../include/ubjs_parser.h ubjs_parser_prv.h ubjs_parser.c
    ../include/ubjs_writer.h ubjs_writer_prv.h ubjs_writer_containers.c ubjs_writer_noncontainers.c
    ../include/ubjs.h ubjs.c

    ubjs_list_prv.h ubjs_list.c
    ubjs_selfemptying_list_prv.h ubjs_selfemptying_list.c
)
generate_export_header(ubjsc
    BASE_NAME ubjsc
    EXPORT_MACRO_NAME UBJS_EXPORT
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/ubjs_exports.h
    STATIC_DEFINE UBJS_EXPORTS_BUILT_AS_STATIC
)
target_include_directories(ubjsc PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/ptrie/include"
    "${CMAKE_BINARY_DIR}/ptrie/src")

if (UNIX)
    target_link_libraries(ubjsc ptrie m)
else (UNIX)
    target_link_libraries(ubjsc ptrie)
endif (UNIX)

install(TARGETS ubjsc
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    COMPONENT libraries
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ubjs_exports.h
    DESTINATION include
    COMPONENT headers
)
