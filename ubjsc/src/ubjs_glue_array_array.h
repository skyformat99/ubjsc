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
 *  \brief Default glue for array - doubly linked list.
 *
 * This has very funny complexities, like O(n) for get/add/delete.
 *
 * \since 0.5
 */

#ifndef HAVE_UBJS_GLUE_ARRAY_ARRAY
#define HAVE_UBJS_GLUE_ARRAY_ARRAY

#ifdef __cplusplus
extern "C"
{
#endif

#include <ubjs_library.h>

/*! \brief Array glue that links to naive double-linked list implementation.
 *
 * \since 0.5
 */
UBJS_EXPORT ubjs_result ubjs_glue_array_array_builder_new(ubjs_library *, ubjs_glue_array_builder **);

#ifdef __cplusplus
}
#endif

#endif
