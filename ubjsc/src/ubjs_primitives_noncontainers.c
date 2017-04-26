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

#include <stdio.h>
#include <string.h>

#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"

#include "ubjs_primitives_prv.h"

ubjs_result ubjs_prmtv_int(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis)
{
    ubjs_glue_array *ntypes = 0;
    ubjs_glue_array_iterator *it = 0;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_ntypes(lib, &ntypes);
    (ntypes->iterate_f)(ntypes, &it);
    while (UR_OK == (it->next_f)(it))
    {
        ubjs_prmtv_ntype *ntype;
        (it->get_f)(it, (void **)&ntype);
        if (0 != ntype->new_from_int64_f)
        {
            ubjs_result ret = (ntype->new_from_int64_f)(lib, value, pthis);
            if (UR_OK == ret)
            {
                (it->free_f)(&it);
                return ret;
            }
        }
    }
    (it->free_f)(&it);
    return UR_ERROR;
}

ubjs_result ubjs_prmtv_uint(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis)
{
    if (0 == lib || 0 > value)
    {
        return UR_ERROR;
    }

    return ubjs_prmtv_int(lib, value, pthis);
}

ubjs_result ubjs_prmtv_int_get(ubjs_prmtv *this, int64_t *pvalue)
{
    if (0 == this || 0 == pvalue)
    {
        return UR_ERROR;
    }

    if (0 != this->ntype && 0 != this->ntype->get_value_int64_f)
    {
        return (this->ntype->get_value_int64_f)(this, pvalue);
    }

    return UR_ERROR;
}

ubjs_result ubjs_prmtv_is_int(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->ntype != 0 && 0 != this->ntype->new_from_int64_f)
        ? UTRUE : UFALSE;

    return UR_OK;
}

ubjs_result ubjs_prmtv_float64(ubjs_library *lib, float64_t value, ubjs_prmtv **pthis)
{
    ubjs_float64 *this;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this=(ubjs_float64 *)(lib->alloc_f)(sizeof(struct ubjs_float64));
    this->super.lib=lib;
    this->super.type=UOT_FLOAT64;
    this->super.ntype=0;
    this->value = value;

    *pthis=(ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_is_float64(ubjs_prmtv *this, ubjs_bool *result)
{
    if (0 == this || 0 == result)
    {
        return UR_ERROR;
    }

    *result = (this->type == UOT_FLOAT64) ? UTRUE : UFALSE;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float64_get(ubjs_prmtv *this, float64_t *result)
{
    ubjs_float64 *rthis;

    if (0 == this || UOT_FLOAT64 != this->type || 0 == result)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_float64 *)this;
    (*result) = rthis->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_float64_set(ubjs_prmtv *this, float64_t value)
{
    ubjs_float64 *rthis;
    if (0 == this || UOT_FLOAT64 != this->type)
    {
        return UR_ERROR;
    }

    rthis=(ubjs_float64 *)this;
    rthis->value=value;
    return UR_OK;
}
