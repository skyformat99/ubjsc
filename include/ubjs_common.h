#ifndef HAVE_UBJS_COMMON
#define HAVE_UBJS_COMMON

#include <stdint.h>

typedef float float32_t;
typedef double float64_t;

typedef enum {
    UFALSE,
    UTRUE
} ubjs_bool;

typedef enum
{
    UR_OK,
    UR_ERROR
} ubjs_result;

typedef enum {
    UEFT_DEFAULT,
    UEFT_LITTLE,
    UEFT_BIG
} ubjs_endian_host_type ;

#define MARKER_OPTIMIZE_COUNT 35
#define MARKER_CHAR 67
#define MARKER_FLOAT64 68
#define MARKER_FALSE 70
#define MARKER_INT16 73
#define MARKER_INT64 76
#define MARKER_NOOP 78
#define MARKER_STR 83
#define MARKER_TRUE 84
#define MARKER_UINT8 85
#define MARKER_NULL 90
#define MARKER_ARRAY_BEGIN 91
#define MARKER_ARRAY_END 93
#define MARKER_FLOAT32 100
#define MARKER_INT8 105
#define MARKER_INT32 108
#define MARKER_OBJECT_BEGIN 123
#define MARKER_OBJECT_END 125

ubjs_result ubjs_endian_is_big(ubjs_bool *);

ubjs_result ubjs_endian_host_type_get(ubjs_endian_host_type *);
ubjs_result ubjs_endian_host_type_set(ubjs_endian_host_type);
ubjs_result ubjs_endian_convert_big_to_native(uint8_t *,uint8_t *,int);
ubjs_result ubjs_endian_convert_native_to_big(uint8_t *,uint8_t *,int);

ubjs_result ubjs_compact_sprintf(char **, unsigned int *,char *format, ...);

#endif

