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
#include "ubjs_primitives_prv.h"
#include "ubjs_common_prv.h"
#include "ubjs_library_prv.h"

ubjs_result ubjs_prmtv_get_type(ubjs_prmtv *this, ubjs_prmtv_type *ptype)
{
    if (0 == this || 0 == ptype)
    {
        return UR_ERROR;
    }

    *ptype = this->type;
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
    switch (this->type)
    {
    case UOT_NULL:
    case UOT_NOOP:
    case UOT_TRUE:
    case UOT_FALSE:
        break;

    case UOT_INT8:
    case UOT_UINT8:
    case UOT_INT16:
    case UOT_INT32:
    case UOT_INT64:
    case UOT_FLOAT32:
    case UOT_FLOAT64:
    case UOT_CHAR:
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
    ubjs_int8 *i8this = 0;
    ubjs_uint8 *u8this = 0;
    ubjs_int16 *i16this = 0;
    ubjs_int32 *i32this = 0;
    ubjs_int64 *i64this = 0;
    ubjs_float32 *f32this = 0;
    ubjs_float64 *f64this = 0;
    ubjs_char *cthis = 0;
    ubjs_str *sthis = 0;
    ubjs_hpn *hthis = 0;
    unsigned int len = 0;
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

    switch (this->type)
    {
    case UOT_NULL:
    case UOT_NOOP:
    case UOT_TRUE:
        *plen=4;
        break;

    case UOT_FALSE:
        *plen=5;
        break;

    case UOT_INT8:
        i8this = (ubjs_int8 *)this;
        *plen = sprintf(buf, "int8 %d", i8this->value);
        break;

    case UOT_UINT8:
        u8this = (ubjs_uint8 *)this;
        *plen = sprintf(buf, "uint8 %u", u8this->value);
        break;

    case UOT_INT16:
        i16this = (ubjs_int16 *)this;
        *plen = sprintf(buf, "int16 %d", i16this->value);
        break;

    case UOT_INT32:
        i32this = (ubjs_int32 *)this;
        *plen = sprintf(buf, "int32 %d", i32this->value);
        break;

    case UOT_INT64:
        i64this = (ubjs_int64 *)this;
        *plen = sprintf(buf, "int64 %ld", i64this->value);
        break;

    case UOT_FLOAT32:
        f32this = (ubjs_float32 *)this;
        *plen = sprintf(buf, "float32 %f", f32this->value);
        break;

    case UOT_FLOAT64:
        f64this = (ubjs_float64 *)this;
        *plen = sprintf(buf, "float64 %f", f64this->value);
        break;

    case UOT_CHAR:
        cthis = (ubjs_char *)this;
        *plen = sprintf(buf, "char %c", cthis->value);
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
        ubjs_prmtv_array_get_length(this, &len);
        *plen = sprintf(buf, "array %u", len);
        break;

    case UOT_OBJECT:
        ubjs_prmtv_object_get_length(this, &len);
        *plen = sprintf(buf, "object %u", len);
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
    ubjs_int8 *i8this = 0;
    ubjs_uint8 *u8this = 0;
    ubjs_int16 *i16this = 0;
    ubjs_int32 *i32this = 0;
    ubjs_int64 *i64this = 0;
    ubjs_float32 *f32this = 0;
    ubjs_float64 *f64this = 0;
    ubjs_char *cthis = 0;
    ubjs_str *sthis = 0;
    ubjs_hpn *hthis = 0;
    unsigned int len = 0;

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

    switch (this->type)
    {
    case UOT_NULL:
        sprintf(str, "null");
        break;

    case UOT_NOOP:
        sprintf(str, "noop");
        break;

    case UOT_TRUE:
        sprintf(str, "true");
        break;

    case UOT_FALSE:
        sprintf(str, "false");
        break;

    case UOT_INT8:
        i8this = (ubjs_int8 *)this;
        sprintf(str, "int8 %d", i8this->value);
        break;

    case UOT_UINT8:
        u8this = (ubjs_uint8 *)this;
        sprintf(str, "uint8 %u", u8this->value);
        break;

    case UOT_INT16:
        i16this = (ubjs_int16 *)this;
        sprintf(str, "int16 %d", i16this->value);
        break;

    case UOT_INT32:
        i32this = (ubjs_int32 *)this;
        sprintf(str, "int32 %d", i32this->value);
        break;

    case UOT_INT64:
        i64this = (ubjs_int64 *)this;
        sprintf(str, "int64 %ld", i64this->value);
        break;

    case UOT_FLOAT32:
        f32this = (ubjs_float32 *)this;
        sprintf(str, "float32 %f", f32this->value);
        break;

    case UOT_FLOAT64:
        f64this = (ubjs_float64 *)this;
        sprintf(str, "float64 %f", f64this->value);
        break;

    case UOT_CHAR:
        cthis = (ubjs_char *)this;
        sprintf(str, "char %c", cthis->value);
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
        ubjs_prmtv_array_get_length(this, &len);
        sprintf(str, "array %u", len);
        break;

    case UOT_OBJECT:
        ubjs_prmtv_object_get_length(this, &len);
        sprintf(str, "object %u", len);
        break;
    default:
        break;
    }
    /* LCOV_EXCL_STOP */
#endif
    return UR_OK;
}

ubjs_result ubjs_prmtv_convert_marker_to_type(unsigned int marker, ubjs_prmtv_type *ptype)
{
    switch (marker)
    {
        case MARKER_NULL: *ptype = UOT_NULL; break;
        case MARKER_NOOP: *ptype = UOT_NOOP; break;
        case MARKER_TRUE: *ptype = UOT_TRUE; break;
        case MARKER_FALSE: *ptype = UOT_FALSE; break;
        case MARKER_UINT8: *ptype = UOT_UINT8; break;
        case MARKER_INT8: *ptype = UOT_INT8; break;
        case MARKER_INT16: *ptype = UOT_INT16; break;
        case MARKER_INT32: *ptype = UOT_INT32; break;
        case MARKER_INT64: *ptype = UOT_INT64; break;
        case MARKER_FLOAT32: *ptype = UOT_FLOAT32; break;
        case MARKER_FLOAT64: *ptype = UOT_FLOAT64; break;
        case MARKER_STR: *ptype = UOT_STR; break;
        case MARKER_CHAR: *ptype = UOT_CHAR; break;
        case MARKER_HPN: *ptype = UOT_HPN; break;
        case MARKER_ARRAY_BEGIN: *ptype = UOT_ARRAY; break;
        case MARKER_OBJECT_BEGIN: *ptype = UOT_OBJECT; break;
        default: return UR_ERROR;
    }
    return UR_OK;
}
