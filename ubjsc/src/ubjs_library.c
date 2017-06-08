/*
 * Copyright (c) 2016-2017 Tomasz Sieprawski
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
#include "ubjs_glue_array_array.h"

#include <ubjs_primitive_null.h>
#include <ubjs_primitive_noop.h>
#include <ubjs_primitive_true.h>
#include <ubjs_primitive_false.h>
#include <ubjs_primitive_char.h>
#include <ubjs_primitive_uint8.h>
#include <ubjs_primitive_int8.h>
#include <ubjs_primitive_int16.h>
#include <ubjs_primitive_int32.h>
#include <ubjs_primitive_float32.h>
#include <ubjs_primitive_int64.h>
#include <ubjs_primitive_float64.h>
#include <ubjs_primitive_str.h>
#include <ubjs_primitive_hpn.h>
#include <ubjs_primitive_array.h>
#include <ubjs_primitive_object.h>

struct ubjs_library
{
    ubjs_library_alloc_f alloc_f;
    ubjs_library_free_f free_f;
    ubjs_glue_array_builder_new_f glue_array_builder;
    ubjs_glue_dict_builder_new_f glue_dict_builder;

    ubjs_glue_array *ntypes;
};

ubjs_result ubjs_library_builder_init(ubjs_library_builder *this)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    this->alloc_f = 0;
    this->free_f = 0;
    this->glue_array_builder = 0;
    this->glue_dict_builder = 0;
    return UR_OK;
}

ubjs_result ubjs_library_builder_set_alloc_f(ubjs_library_builder *this,
    ubjs_library_alloc_f alloc_f)
{
    if (0 == this || 0 == alloc_f)
    {
        return UR_ERROR;
    }

    this->alloc_f = alloc_f;
    return UR_OK;
}

ubjs_result ubjs_library_builder_set_free_f(ubjs_library_builder *this,
    ubjs_library_free_f free_f)
{
    if (0 == this || 0 == free_f)
    {
        return UR_ERROR;
    }

    this->free_f = free_f;
    return UR_OK;
}

ubjs_result ubjs_library_builder_set_glue_array_builder(ubjs_library_builder *this,
    ubjs_glue_array_builder_new_f builder)
{
    if (0 == this || 0 == builder)
    {
        return UR_ERROR;
    }

    this->glue_array_builder = builder;
    return UR_OK;
}

ubjs_result ubjs_library_builder_set_glue_dict_builder(ubjs_library_builder *this,
    ubjs_glue_dict_builder_new_f builder)
{
    if (0 == this || 0 == builder)
    {
        return UR_ERROR;
    }

    this->glue_dict_builder = builder;
    return UR_OK;
}

ubjs_result ubjs_library_builder_build(ubjs_library_builder *this,
    ubjs_library **plib)
{
    ubjs_library *lib = 0;
    ubjs_library_alloc_f alloc_f;

    if (0 == this || 0 == plib || 0 != (*plib))
    {
        return UR_ERROR;
    }

    alloc_f = 0 != this->alloc_f ? this->alloc_f : malloc;
    lib = (ubjs_library *)(alloc_f)(sizeof(struct ubjs_library));
    lib->alloc_f = alloc_f;
    lib->free_f = 0 != this->free_f ? this->free_f : free;
    lib->glue_array_builder = 0 != this->glue_array_builder ?
        this->glue_array_builder : ubjs_glue_array_array_builder_new;
    lib->glue_dict_builder = 0 != this->glue_dict_builder ?
        this->glue_dict_builder : ubjs_glue_dict_list_builder_new;

    {
        ubjs_glue_array_builder *bldr = 0;
        ubjs_glue_array_array_builder_new(lib, &bldr);
        (bldr->build_f)(bldr, &(lib->ntypes));
        (bldr->free_f)(&bldr);

        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_null_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_noop_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_true_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_false_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_char_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_uint8_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_int8_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_int16_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_int32_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_float32_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_int64_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_float64_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_str_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_hpn_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_array_ntype);
        (lib->ntypes->add_last_f)(lib->ntypes, &ubjs_prmtv_object_ntype);
    }

    *plib = lib;
    return UR_OK;
}

ubjs_result ubjs_library_new_stdlib(ubjs_library **pthis)
{
    ubjs_library_builder builder;

    if (0 == pthis || 0 != (*pthis))
    {
        return UR_ERROR;
    }

    ubjs_library_builder_init(&builder);
    ubjs_library_builder_build(&builder, pthis);
    return UR_OK;
}

ubjs_result ubjs_library_get_alloc_f(ubjs_library *this, ubjs_library_alloc_f *palloc_f)
{
    if (0 == this || 0 == palloc_f)
    {
        return UR_ERROR;
    }

    *palloc_f = this->alloc_f;
    return UR_OK;
}

ubjs_result ubjs_library_get_free_f(ubjs_library *this, ubjs_library_free_f *pfree_f)
{
    if (0 == this || 0 == pfree_f)
    {
        return UR_ERROR;
    }

    *pfree_f = this->free_f;
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
    (this->ntypes->free_f)(&(this->ntypes));
    (this->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_library_get_ntypes(ubjs_library *this, ubjs_glue_array **parr)
{
    if (0 == this || 0 == parr)
    {
        return UR_ERROR;
    }

    *parr = this->ntypes;
    return UR_OK;
}

ubjs_result ubjs_library_get_glue_array_builder(ubjs_library *this,
    ubjs_glue_array_builder_new_f *pbuilder_new_f)
{
    if (0 == this || 0 == pbuilder_new_f)
    {
        return UR_ERROR;
    }

    *pbuilder_new_f = this->glue_array_builder;
    return UR_OK;
}

ubjs_result ubjs_library_get_glue_dict_builder(ubjs_library *this,
    ubjs_glue_dict_builder_new_f *pbuilder_new_f)
{
    if (0 == this || 0 == pbuilder_new_f)
    {
        return UR_ERROR;
    }

    *pbuilder_new_f = this->glue_dict_builder;
    return UR_OK;
}
