/*
 * Copyright (c) 2016 Tomasz Sieprawski
 *
 * Permission is hereby granted, free of strge, to any person obtaining a copy
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
 *  \brief No-operation.
 *
 *  ubjson.org says that "when parsed by the receiver, the no-op valu$
 *  and carry know meaningful value with them.". I've decided to leav$
 *  and because of that, no-ops are parsed always and passed to the u$
 *
 *  For ubjsc these two arrays are NOT equal on the parse/write level:
 *
 *  - ["foo", "bar", "baz"]
 *  - ["foo", no-op, "bar", no-op, no-op, no-op, "baz", no-op, no-op]
 * \since 0.7
 */

#ifndef HAVE_UBJS_PRIMITIVE_ARRAY
#define HAVE_UBJS_PRIMITIVE_ARRAY

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs_library.h>
#include <ubjs_primitives.h>


/*! Struct for array's iterator. */
struct ubjs_array_iterator;

/*! Struct for array's iterator. */
typedef struct ubjs_array_iterator ubjs_array_iterator;

/*!
 * \since 0.7
 */
UBJS_EXPORT extern ubjs_prmtv_ntype ubjs_prmtv_array_ntype;

/*! \brief Returns str primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array(ubjs_library *lib, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_with_length(ubjs_library *lib, unsigned int length,
    ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *this, unsigned int *length);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_first(ubjs_prmtv *this, ubjs_prmtv **pitem);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_last(ubjs_prmtv *this, ubjs_prmtv **pitem);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_at(ubjs_prmtv *this, unsigned int pos,
    ubjs_prmtv **pitem);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_first(ubjs_prmtv *this, ubjs_prmtv *item);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_last(ubjs_prmtv *this, ubjs_prmtv *item);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_add_at(ubjs_prmtv *this, unsigned int pos,
    ubjs_prmtv *item);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_first(ubjs_prmtv *this);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_last(ubjs_prmtv *this);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_delete_at(ubjs_prmtv *this, unsigned int pos);
UBJS_EXPORT ubjs_result ubjs_prmtv_array_iterate(ubjs_prmtv *this, ubjs_array_iterator **iterator);
UBJS_EXPORT ubjs_result ubjs_array_iterator_next(ubjs_array_iterator *this);
UBJS_EXPORT ubjs_result ubjs_array_iterator_get(ubjs_array_iterator *this, ubjs_prmtv **item);
UBJS_EXPORT ubjs_result ubjs_array_iterator_delete(ubjs_array_iterator *this);

/*!
 * \since 0.7
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_array_get_length(ubjs_prmtv *, unsigned int *);

#ifdef __cplusplus
}
#endif

#endif
