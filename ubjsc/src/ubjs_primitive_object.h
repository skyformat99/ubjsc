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

#ifndef HAVE_UBJS_PRIMITIVE_OBJECT
#define HAVE_UBJS_PRIMITIVE_OBJECT

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs_library.h>
#include <ubjs_primitives.h>


/*! Struct for array's iterator. */
struct ubjs_object_iterator;

/*! Struct for array's iterator. */
typedef struct ubjs_object_iterator ubjs_object_iterator;

/*!
 * \since 0.7
 */
UBJS_EXPORT extern ubjs_prmtv_ntype ubjs_prmtv_object_ntype;

UBJS_EXPORT extern ubjs_prmtv_ntype ubjs_prmtv_object_end_ntype;
UBJS_EXPORT extern ubjs_prmtv_ntype ubjs_prmtv_object_type_ntype;
UBJS_EXPORT extern ubjs_prmtv_ntype ubjs_prmtv_object_count_ntype;

/*! \brief Returns str primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_object(ubjs_library *lib, ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_with_length(ubjs_library *lib, unsigned int,
    ubjs_prmtv **pthis);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_get_length(ubjs_prmtv *this, unsigned int *length);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_get(ubjs_prmtv *this, unsigned int, char *,
    ubjs_prmtv **pitem);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_set(ubjs_prmtv *this, unsigned int, char *,
    ubjs_prmtv *item);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_delete(ubjs_prmtv *this, unsigned int, char *);
UBJS_EXPORT ubjs_result ubjs_prmtv_object_iterate(ubjs_prmtv *this,
    ubjs_object_iterator **iterator);
UBJS_EXPORT ubjs_result ubjs_object_iterator_next(ubjs_object_iterator *this);
UBJS_EXPORT ubjs_result ubjs_object_iterator_get_value(ubjs_object_iterator *this,
    ubjs_prmtv **item);
UBJS_EXPORT ubjs_result ubjs_object_iterator_get_key_length(ubjs_object_iterator *this,
    unsigned int *);
UBJS_EXPORT ubjs_result ubjs_object_iterator_copy_key(ubjs_object_iterator *this, char *);
UBJS_EXPORT ubjs_result ubjs_object_iterator_delete(ubjs_object_iterator *this);
UBJS_EXPORT ubjs_result ubjs_object_iterator_free(ubjs_object_iterator **this);

#ifdef __cplusplus
}
#endif

#endif
