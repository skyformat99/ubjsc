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

#include "ubjs_library_prv.h"
#include "ubjs_glue_dict_list.h"

ubjs_result ubjs_library_builder_new(ubjs_library_builder **pthis)
{
    ubjs_library_builder *this;

    if (0 == pthis || 0 != (*pthis))
    {
        return UR_ERROR;
    }

    this = (ubjs_library_builder *)malloc(sizeof(struct ubjs_library));
    ubjs_library_new(&(this->lib));
    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_library_builder_free(ubjs_library_builder **pthis)
{
    ubjs_library_builder *this;

    if (0 == pthis || 0 == (*pthis))
    {
        return UR_ERROR;
    }

    this = *pthis;
    free(this);

    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_library_builder_set_alloc_f(ubjs_library_builder *this,
    ubjs_library_alloc_f alloc_f)
{
    if (0 == this || 0 == alloc_f)
    {
        return UR_ERROR;
    }

    this->lib->alloc_f = alloc_f;
    return UR_OK;
}

ubjs_result ubjs_library_builder_set_free_f(ubjs_library_builder *this,
    ubjs_library_free_f free_f)
{
    if (0 == this || 0 == free_f)
    {
        return UR_ERROR;
    }

    this->lib->free_f = free_f;
    return UR_OK;
}

ubjs_result ubjs_library_builder_set_glue_array_factory(ubjs_library_builder *this,
    ubjs_glue_array_factory factory)
{
    if (0 == this || 0 == factory)
    {
        return UR_ERROR;
    }

    this->lib->glue_array_factory = factory;
    return UR_OK;
}

ubjs_result ubjs_library_builder_set_glue_dict_factory(ubjs_library_builder *this,
    ubjs_glue_dict_factory factory)
{
    if (0 == this || 0 == factory)
    {
        return UR_ERROR;
    }

    this->lib->glue_dict_factory = factory;
    return UR_OK;
}

ubjs_result ubjs_library_builder_build(ubjs_library_builder *this,
    ubjs_library **plib)
{
    if (0 == this || 0 == plib || 0 != (*plib))
    {
        return UR_ERROR;
    }

    *plib = this->lib;
    return UR_OK;
}

ubjs_result ubjs_library_new(ubjs_library **pthis)
{
    ubjs_library *this;
    this = (ubjs_library *)malloc(sizeof(struct ubjs_library));
    this->alloc_f=malloc;
    this->free_f=free;
    this->glue_dict_factory=ubjs_glue_dict_list_factory;
    this->glue_array_factory=0; /* @todo ubjs_glue_array_list_factory; */
    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_library_new_stdlib(ubjs_library **pthis)
{
    ubjs_library_builder *builder=0;

    if (0 == pthis || 0 != (*pthis))
    {
        return UR_ERROR;
    }

    ubjs_library_builder_new(&builder);
    ubjs_library_builder_build(builder, pthis);
    ubjs_library_builder_free(&builder);
    return UR_OK;
}

ubjs_result ubjs_library_free(ubjs_library **pthis)
{
    ubjs_library *this;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this=*pthis;
    free(this);

    *pthis=0;
    return UR_OK;
}
