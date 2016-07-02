/*
 * Copyright (c) 2016 Tomasz Sieprawski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **/

#ifndef HAVE_UBJS_COMMON
#define HAVE_UBJS_COMMON

#include <stdint.h>

typedef float float32_t;
typedef double float64_t;

typedef enum ubjs_bool ubjs_bool;
typedef enum ubjs_result ubjs_result;
typedef enum ubjs_endian_host_type ubjs_endian_host_type;

enum ubjs_bool
{
    UFALSE,
    UTRUE
};

enum ubjs_result
{
    UR_OK,
    UR_ERROR
};

enum ubjs_endian_host_type
{
    UEFT_DEFAULT,
    UEFT_LITTLE,
    UEFT_BIG
};

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
ubjs_result ubjs_endian_convert_big_to_native(uint8_t *, uint8_t *, int);
ubjs_result ubjs_endian_convert_native_to_big(uint8_t *, uint8_t *, int);

ubjs_result ubjs_compact_sprintf(char **, unsigned int *, char *format, ...);

#endif
