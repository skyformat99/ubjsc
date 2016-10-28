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
/*! \file
 *  \brief Definitions of common types, ubjson markers and some utilities.
 *
 * \since 0.2
 */
 
#ifndef HAVE_UBJS_COMMON
#define HAVE_UBJS_COMMON

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <inttypes.h>
#include "ubjs_exports.h"


/*! \brief Typedef to have consistency in naming all int/float types.
 *
 * \since 0.2
 */
typedef float float32_t;

/*! \brief Typedef to have consistency in naming all int/float types.
 *
 * \since 0.2
 */
typedef double float64_t;

/*! \brief Wrapper around regular C-like booleans.
 *
 * Created for consistency and readibility.
 *
 * \since 0.2
 */
typedef enum ubjs_bool
{
    UFALSE, /*!< False. */
    UTRUE /*!< True. */
} ubjs_bool;

/*! \brief Enum that defines the result of a method.
 *
 * About 99% methods in ubjs API return ubjs_result, with every output being passed
 * by parameters via pointers. This way every method easily tells whether its operation
 * succeded.
 *
 * \since 0.2
 */
typedef enum ubjs_result
{
    UR_OK, /*!< Operation succeded competely. */
    UR_ERROR /*!< Invalid input or otherwise errorness result. */
} ubjs_result;

/*! \brief Enum that defines the endiannes of this platform.
 *
 * Ubjson numbers need to be parsed/written in big endian, and thus we need a way to know
 * whether we need to convert from our little endian platform or not.
 *
 * \since 0.2
 */
typedef enum ubjs_endian_host_type
{
    UEFT_DEFAULT, /*!< Default endianness. Aka you do not care which one it is. */
    UEFT_LITTLE, /*!< Little endian - conversion needed. */
    UEFT_BIG /*!< Big endian. */
} ubjs_endian_host_type;

/*! \brief Marker "#" that precedes length of a optimized container.
 *
 * \since 0.2
 */
#define MARKER_OPTIMIZE_COUNT 35
/*! \brief Marker "$" that precedes type of a optimized container.
 *
 * \since 0.2
 */
#define MARKER_OPTIMIZE_TYPE 36
/*! \brief Marker "C" that precedes a character.
 *
 * \since 0.2
 */
#define MARKER_CHAR 67
/*! \brief Marker "D" that precedes a float64 number
 *
 * \since 0.2
 */
#define MARKER_FLOAT64 68
/*! \brief Marker "F" that signals a false value.
 *
 * \since 0.2
 */
#define MARKER_FALSE 70
/*! \brief Marker "H" that precedes an high-precision number.
 *
 * \since 0.2
 */
#define MARKER_HPN 72
/*! \brief Marker "I" that precedes an int16 number.
 *
 * \since 0.2
 */
#define MARKER_INT16 73
/*! \brief Marker "L" that precedes an int64 number.
 *
 * \since 0.2
 */
#define MARKER_INT64 76
/*! \brief Marker "N" that signals a no-operation.
 *
 * \since 0.2
 */
#define MARKER_NOOP 78
/*! \brief Marker "S" that precedes a string.
 *
 * \since 0.2
 */
#define MARKER_STR 83
/*! \brief Marker "T" that signals a true value.
 *
 * \since 0.2
 */
#define MARKER_TRUE 84
/*! \brief Marker "L" that precedes an uint8 number.
 *
 * \since 0.2
 */
#define MARKER_UINT8 85
/*! \brief Marker "Z" that signals a null value.
 *
 * \since 0.2
 */
#define MARKER_NULL 90
/*! \brief Marker "[" that signals beginning of an array.
 *
 * \since 0.2
 */
#define MARKER_ARRAY_BEGIN 91
/*! \brief Marker "]" that signals end of an unoptimized array.
 *
 * \since 0.2
 */
#define MARKER_ARRAY_END 93
/*! \brief Marker "d" that precedes a float32 number
 *
 * \since 0.2
 */
#define MARKER_FLOAT32 100
/*! \brief Marker "i" that precedes an int8 number.
 *
 * \since 0.2
 */
#define MARKER_INT8 105
/*! \brief Marker "l" that precedes an int32 number.
 *
 * \since 0.2
 */
#define MARKER_INT32 108
/*! \brief Marker "[" that signals beginning of an object.
 *
 * \since 0.2
 */
#define MARKER_OBJECT_BEGIN 123
/*! \brief Marker "]" that signals end of an unoptimized object.
 *
 * \since 0.2
 */
#define MARKER_OBJECT_END 125

/*! \brief Check whether this platform is big endian.
 *
 *  After this returns UR_OK, it is guaranteed that (*pret) gets a value UTRUE or UFALSE.
 *  \param pret Pointer under which to put whether this platform is big endian.
 *  \return UR_ERROR if pret == 0, otherwise UR_OK.
 *
 * \since 0.2
 */
UBJS_EXPORT ubjs_result ubjs_endian_is_big(ubjs_bool *pret);

/*! \brief Gets this platform's endianness status, whethever forced or not.
 *
 *  This is used mostly in unittests, where you can "force" the library to recognize
 *  current platform as other endian.
 *
 *  By default, the value is UEFT_DEFAULT.
 *
 *  After this returns UR_OK, it is guaranteed that (*ptype) gets a value UEFT_DEFAULT,
 *  UEFT_BIG or UEFT_LITTLE.
 *  \param ptype Pointer under which to put this platform's endianness.
 *  \return UR_ERROR if ptype == 0, otherwise UR_OK.
 *
 * \since 0.2
 */
UBJS_EXPORT ubjs_result ubjs_endian_host_type_get(ubjs_endian_host_type *ptype);

/*! \brief Sets this platform's endianness status, to forced or not.
 *
 *  This is used mostly in unittests, where you can "force" the library to recognize
 *  current platform as other endian.
 *
 *  After this returns UR_OK, all int/float ubjson objects will be formatted to this
 *  specified endianness, when parsed or written.
 *
 *  \param type Desired platform endianness.
 *  \return UR_ERROR if ptype is not a valid value from ubjs_endian_host_type, otherwise UR_OK.
 *
 * \since 0.2
 */
UBJS_EXPORT ubjs_result ubjs_endian_host_type_set(ubjs_endian_host_type type);

/*! \brief Converts bytes from network order endianness to native one.
 *
 *  How this works is affected by current platform's endianness, especially due to
 *  ubjs_endian_host_type_set calls:
 *
 *  - if ubjs_endian_is_big() returns UTRUE, this method merely copies bytes from input array
 *    to output one,
 *  - otherwise the regular byteswap occurs.
 *
 *  After this returns UR_OK, it is guaranteed that out array gets filled from 0 to (len-1) byte.
 *  \param in Input array of length len.
 *  \param out Output array of length len.
 *  \param len Length of both arrays.
 *  \return UR_ERROR if any of in/out is 0, otherwise UR_OK.
 *
 * \since 0.2
 */
UBJS_EXPORT ubjs_result ubjs_endian_convert_big_to_native(uint8_t *in, uint8_t *out,
    unsigned int len);

/*! \brief Converts bytes from native order endianness to network one.
 *
 *  How this works is affected by current platform's endianness, especially due to
 *  ubjs_endian_host_type_set calls:
 *
 *  - if ubjs_endian_is_big() returns UTRUE, this method merely copies bytes from input array
 *    to output one,
 *  - otherwise the regular byteswap occurs.
 *
 *  After this returns UR_OK, it is guaranteed that out array gets filled from 0 to (len-1) byte.
 *  \param in Input array of length len.
 *  \param out Input array of length len.
 *  \param len Length of both arrays.
 *  \return UR_ERROR if any of in/out is 0, otherwise UR_OK.
 *
 * \since 0.2
 */
UBJS_EXPORT ubjs_result ubjs_endian_convert_native_to_big(uint8_t *in, uint8_t *out,
    unsigned int len);

/*! \brief Utility that preallocates just enough memory for sprintf().
 *
 *  After this returns UR_OK, it is guaranteed that pthis points to already sprintf()-ed string.
 *  This string is null-terminated.
 *
 *  You need to free() (*pthis)
 *  \param pthis Pointer to where put new string.
 *  \param plen Pointer to where put new string's length.
 *  \param format Format for sprintf().
 *  \return For now always UR_OK, but still always check for the value.
 *
 * \since 0.2
 */
UBJS_EXPORT ubjs_result ubjs_compact_sprintf(char **pthis, unsigned int *plen, char *format, ...);

typedef void *(*ubjs_library_alloc_f)(unsigned int);
typedef void (*ubjs_library_free_f)(void *);

typedef struct ubjs_library ubjs_library;
struct ubjs_library;

UBJS_EXPORT ubjs_result ubjs_library_new(ubjs_library_alloc_f alloc, ubjs_library_free_f free,
    ubjs_library **pthis);
UBJS_EXPORT ubjs_result ubjs_library_free(ubjs_library **pthis);

#ifdef __cplusplus
}
#endif

#endif
