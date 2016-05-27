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

#define MARKER_FALSE 70
#define MARKER_INT16 73
#define MARKER_INT64 76
#define MARKER_NOOP 78
#define MARKER_TRUE 84
#define MARKER_UINT8 85
#define MARKER_NULL 90
#define MARKER_FLOAT32 100
#define MARKER_INT8 105
#define MARKER_INT32 108

ubjs_result ubjs_endian_is_big(ubjs_bool *);

ubjs_result ubjs_endian_host_type_get(ubjs_endian_host_type *);
ubjs_result ubjs_endian_host_type_set(ubjs_endian_host_type);
ubjs_result ubjs_endian_convert_big_to_native(uint8_t *,uint8_t *,int);
ubjs_result ubjs_endian_convert_native_to_big(uint8_t *,uint8_t *,int);

#endif

