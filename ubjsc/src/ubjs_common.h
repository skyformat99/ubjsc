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
/*! \brief Marker "S" that precedes a string.
 *
 * \since 0.2
 */
#define MARKER_STR 83
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

#ifdef __cplusplus
}
#endif

#endif
