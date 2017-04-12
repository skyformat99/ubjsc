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

#ifndef HAVE_UBJS_PRIMITIVE_UINT8
#define HAVE_UBJS_PRIMITIVE_UINT8

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs_common.h>
#include <ubjs_library.h>
#include <ubjs_primitives.h>

/*!
 * \since 0.7
 */
UBJS_EXPORT extern ubjs_prmtv_ntype ubjs_prmtv_uint8_ntype;

/*! \brief Returns uint8 primitive.
 *
 * This is a singleton and ubj_prmtv_free do nothing.
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8(ubjs_library *, uint8_t,
    ubjs_prmtv **);

/*!
 * \since 0.7
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8_get(ubjs_prmtv *, uint8_t *);
/*!
 * \since 0.7
 */
UBJS_EXPORT ubjs_result ubjs_prmtv_uint8_set(ubjs_prmtv *, uint8_t);

#ifdef __cplusplus
}
#endif

#endif
