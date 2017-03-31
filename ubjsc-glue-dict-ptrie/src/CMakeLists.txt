add_library(ubjsc-glue-dict-ptrie SHARED
    "${CMAKE_CURRENT_BINARY_DIR}/ubjs_glue_dict_ptrie_exports.h"
    ubjs_glue_dict_ptrie.h ubjs_glue_dict_ptrie_prv.h ubjs_glue_dict_ptrie.c
)
generate_export_header(ubjsc-glue-dict-ptrie
    BASE_NAME ubjsc-glue-dict-ptrie
    EXPORT_MACRO_NAME UBJS_EXPORT
    NO_EXPORT_MACRO_NAME UBJS_NO_EXPORT
    DEPRECATED_MACRO_NAME UBJS_DEPRECATED
    EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/ubjs_glue_dict_ptrie_exports.h
    STATIC_DEFINE UBJS_EXPORTS_BUILT_AS_STATIC
)
target_include_directories(ubjsc-glue-dict-ptrie PUBLIC
    "${CMAKE_BINARY_DIR}/ubjsc/src"
    "${CMAKE_SOURCE_DIR}/ubjsc/src"
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)
set_target_properties(ubjsc-glue-dict-ptrie PROPERTIES COMPILE_FLAGS "-ansi")

target_link_libraries(ubjsc-glue-dict-ptrie ptrie ubjsc)
install(TARGETS ubjsc-glue-dict-ptrie
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    COMPONENT libraries
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ubjs_glue_dict_ptrie_exports.h
    ubjs_glue_dict_ptrie.h

    DESTINATION include
    COMPONENT headers
)
