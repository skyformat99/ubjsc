add_library(ubjsc SHARED
    "${CMAKE_CURRENT_BINARY_DIR}/ubjs_exports.h"
    ubjs_common.h ubjs_common_prv.h ubjs_common.c
    ubjs_library.h ubjs_library_prv.h ubjs_library.c
    ubjs_primitives.h ubjs_primitives_prv.h ubjs_primitives.c
    ubjs_parser.h ubjs_parser_prv.h ubjs_parser.c
    ubjs_writer.h ubjs_writer_prv.h ubjs_writer_containers.c ubjs_writer_noncontainers.c
    ubjs.h ubjs.c

    ubjs_glue_dict_list.h ubjs_glue_dict_list_prv.h ubjs_glue_dict_list.c
    ubjs_glue_array_list.h ubjs_glue_array_list_prv.h ubjs_glue_array_list.c

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
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

if (UNIX)
    target_link_libraries(ubjsc m)
endif (UNIX)

install(TARGETS ubjsc
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    COMPONENT libraries
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ubjs_exports.h
    ubjs_common.h
    ubjs_primitives.h
    ubjs_parser.h
    ubjs_writer.h
    ubjs_library.h
    ubjs.h
    DESTINATION include
    COMPONENT headers
)
