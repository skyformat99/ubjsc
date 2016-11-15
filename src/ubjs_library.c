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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ubjs_glue_dict_ptrie.h>
#include "ubjs_library_prv.h"

ubjs_result ubjs_library_new(ubjs_library_alloc_f alloc_f, ubjs_library_free_f free_f,
    ubjs_glue_dict_factory glue_dict_factory, ubjs_library **pthis)
{
    ubjs_library *this;

    if (0 == pthis || 0 == alloc_f || 0 == glue_dict_factory || 0 == free_f)
    {
        return UR_ERROR;
    }

    this = (alloc_f)(sizeof(struct ubjs_library));
    this->alloc_f=alloc_f;
    this->free_f=free_f;
    this->glue_dict_factory=glue_dict_factory;
    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_library_new_stdlib(ubjs_library **pthis)
{
    return ubjs_library_new((ubjs_library_alloc_f) malloc, (ubjs_library_free_f) free,
        (ubjs_glue_dict_factory)ubjs_glue_dict_ptrie_factory, pthis);
}

ubjs_result ubjs_library_free(ubjs_library **pthis)
{
    ubjs_library *this;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    (this->free_f)(this);

    *pthis=0;
    return UR_OK;
}
