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

ubjs_result ubjs_prmtv_get_type(ubjs_prmtv *this, ubjs_prmtv_type *ptype)
{
    if (0 == this || 0 == ptype)
    {
        return UR_ERROR;
    }

    *ptype = this->type;
    return UR_OK;
}

ubjs_result ubjs_prmtv_get_ntype(ubjs_prmtv *this, ubjs_prmtv_ntype **pntype)
{
    if (0 == this || 0 == pntype)
    {
        return UR_ERROR;
    }

    *pntype = this->ntype;
    return UR_OK;
}

ubjs_result ubjs_prmtv_free(ubjs_prmtv **pthis)
{
    ubjs_prmtv *this;
    ubjs_str *sthis;
    ubjs_hpn *hthis;
    ubjs_array *athis;
    ubjs_object *oit;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;

    if (0 != this->ntype)
    {
        return (this->ntype->free_f)(pthis);
    }

    switch (this->type)
    {
    case UOT_FLOAT32:
    case UOT_FLOAT64:
        (this->lib->free_f)(this);
        break;

    case UOT_STR:
        sthis=(ubjs_str *)this;
        (this->lib->free_f)(sthis->text);
        (this->lib->free_f)(sthis);
        break;

    case UOT_HPN:
        hthis=(ubjs_hpn *)this;
        (this->lib->free_f)(hthis->text);
        (this->lib->free_f)(hthis);
        break;

    case UOT_ARRAY:
        athis=(ubjs_array *)this;
        (athis->glue->free_f)(&(athis->glue));
        (this->lib->free_f)(athis);
        break;

    case UOT_OBJECT:
        oit=(ubjs_object *)this;
        (oit->glue->free_f)(&(oit->glue));
        (this->lib->free_f)(oit);
        break;
    default:
        return UR_ERROR;
    }

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_prmtv_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_float32 *f32this = 0;
    ubjs_float64 *f64this = 0;
    ubjs_str *sthis = 0;
    ubjs_hpn *hthis = 0;
    /*
     * Max of them all. See ubjs_writer_noncontainers.c. +20.
     */
    char buf[1215];
#endif

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

#ifndef NDEBUG
    if (0 != this->ntype)
    {
        return (this->ntype->debug_string_get_length_f)(this, plen);
    }

    switch (this->type)
    {
    case UOT_FLOAT32:
        f32this = (ubjs_float32 *)this;
        *plen = sprintf(buf, "float32 %f", f32this->value);
        break;

    case UOT_FLOAT64:
        f64this = (ubjs_float64 *)this;
        *plen = sprintf(buf, "float64 %f", f64this->value);
        break;

    case UOT_STR:
        sthis = (ubjs_str *)this;
        *plen = sprintf(buf, "str %u <%.*s>", sthis->length,
            sthis->length, sthis->text);
        break;

    case UOT_HPN:
        hthis = (ubjs_hpn *)this;
        *plen = sprintf(buf, "hpn %u <%.*s>", hthis->length,
            hthis->length, hthis->text);
        break;

    case UOT_ARRAY:
        *plen = sprintf(buf, "array");
        break;

    case UOT_OBJECT:
        *plen = sprintf(buf, "object");
        break;
    default:
        break;
    }
    /* LCOV_EXCL_STOP */
#else
    *plen = 0;
#endif
    return UR_OK;
}

ubjs_result ubjs_prmtv_debug_string_copy(ubjs_prmtv *this, char *str)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_float32 *f32this = 0;
    ubjs_float64 *f64this = 0;
    ubjs_str *sthis = 0;
    ubjs_hpn *hthis = 0;

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

    if (0 != this->ntype)
    {
        return (this->ntype->debug_string_copy_f)(this, str);
    }

    switch (this->type)
    {
    case UOT_FLOAT32:
        f32this = (ubjs_float32 *)this;
        sprintf(str, "float32 %f", f32this->value);
        break;

    case UOT_FLOAT64:
        f64this = (ubjs_float64 *)this;
        sprintf(str, "float64 %f", f64this->value);
        break;

    case UOT_STR:
        sthis = (ubjs_str *)this;
        sprintf(str, "str %u <%.*s>", sthis->length,
            sthis->length, sthis->text);
        break;

    case UOT_HPN:
        hthis = (ubjs_hpn *)this;
        sprintf(str, "hpn %u <%.*s>", hthis->length,
            hthis->length, hthis->text);
        break;

    case UOT_ARRAY:
        sprintf(str, "array");
        break;

    case UOT_OBJECT:
        sprintf(str, "object");
        break;
    default:
        break;
    }
    /* LCOV_EXCL_STOP */
#endif
    return UR_OK;
}
