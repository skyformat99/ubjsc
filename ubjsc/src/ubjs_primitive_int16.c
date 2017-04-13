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
#include <stdlib.h>

#include "ubjs_primitives_prv.h"
#include "ubjs_primitive_int16_prv.h"
#include "ubjs_common_prv.h"

ubjs_prmtv_ntype ubjs_prmtv_int16_ntype =
{
    73,

    ubjs_prmtv_int16_free,

    ubjs_prmtv_int16_new_from_int64,
    ubjs_prmtv_int16_get_value_int64,
    ubjs_prmtv_int16_set_value_int64,

    ubjs_prmtv_int16_debug_string_get_length,
    ubjs_prmtv_int16_debug_string_copy,

    ubjs_prmtv_int16_parser_processor_new,
    ubjs_prmtv_int16_parser_processor_free,
    ubjs_prmtv_int16_parser_processor_got_control,
    ubjs_prmtv_int16_parser_processor_read_byte,

    ubjs_prmtv_int16_writer_new,
    ubjs_prmtv_int16_writer_free,
    ubjs_prmtv_int16_writer_get_length,
    ubjs_prmtv_int16_writer_do,

    ubjs_prmtv_int16_printer_new,
    ubjs_prmtv_int16_printer_free,
    ubjs_prmtv_int16_printer_get_length,
    ubjs_prmtv_int16_printer_do
};

ubjs_result ubjs_prmtv_int16(ubjs_library *lib, int16_t value, ubjs_prmtv **pthis)
{
    ubjs_prmtv_int16_t *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_int16_t *)(alloc_f)(sizeof(struct ubjs_prmtv_int16_t));
    this->super.lib = lib;
    this->super.type = 0;
    this->super.ntype = &ubjs_prmtv_int16_ntype;
    this->value = value;

    *pthis = (ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_new_from_int64(ubjs_library *lib, int64_t value, ubjs_prmtv **pthis)
{
    if (0 == lib || 0 == pthis || value < INT16_MIN || value > INT16_MAX)
    {
        return UR_ERROR;
    }
    return ubjs_prmtv_int16(lib, (int16_t)value, pthis);
}

ubjs_result ubjs_prmtv_int16_free(ubjs_prmtv **pthis)
{
    ubjs_prmtv *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;
    ubjs_library_get_free_f(this->lib, &free_f);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_prmtv_int16_t *thisv;
    char tmp[14];

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_int16_t *)this;
    *plen = sprintf(tmp, "int16(%d)", thisv->value);
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_debug_string_copy(ubjs_prmtv *this, char *str)
{
    ubjs_prmtv_int16_t *thisv;
    char tmp[14];

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_int16_t *)this;
    sprintf(tmp, "int16(%d)", thisv->value);
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_parser_processor_new(ubjs_library *lib,
     ubjs_prmtv_ntype_parser_glue *glue, ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_int16_parser_processor *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_int16_parser_processor *)(alloc_f)(sizeof(
        struct ubjs_prmtv_int16_parser_processor));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_int16_ntype;
    this->super.name = "int16";
    this->super.glue = glue;
    this->super.userdata = 0;
    this->data = (uint8_t *)(alloc_f)(sizeof(uint8_t) * 2);
    this->read = 0;
    *pthis = (ubjs_prmtv_ntype_parser_processor *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_parser_processor_free(
    ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_int16_parser_processor *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_int16_parser_processor *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);
    (free_f)(this->data);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_int16_parser_processor_got_control(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv *present)
{
    if (0 != present)
    {
        (this->glue->error_f)(this->glue, 18,
            "Unexpected present");
        return;
    }
}

void ubjs_prmtv_int16_parser_processor_read_byte(
    ubjs_prmtv_ntype_parser_processor *this, uint8_t achr)
{
    ubjs_prmtv_int16_parser_processor *this2;
    uint8_t value[2];
    ubjs_prmtv *ret;

    this2 = (ubjs_prmtv_int16_parser_processor *)this;

    this2->data[this2->read++] = achr;
    if (2 != this2->read)
    {
        return;
    }

    ubjs_endian_convert_big_to_native(this2->data, value, sizeof(uint8_t) * 2);
    ubjs_prmtv_int16(this->lib, *((int16_t *)value), &ret);
    (this->glue->give_control_f)(this->glue, this->glue->parent, ret);
}

ubjs_result ubjs_prmtv_int16_writer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_writer_glue *glue, ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_ntype_writer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_int16_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_ntype_writer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_writer));
    this->lib = lib;
    this->ntype = &ubjs_prmtv_int16_ntype;
    this->name = "int16";
    this->glue = glue;
    this->userdata = 0;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_writer_free(ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_ntype_writer *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;
    ubjs_library_get_free_f(this->lib, &free_f);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_int16_writer_get_length(ubjs_prmtv_ntype_writer *this,
    unsigned int *plen)
{
    *plen = 2;
}

void ubjs_prmtv_int16_writer_do(ubjs_prmtv_ntype_writer *this, uint8_t *data)
{
    ubjs_prmtv_int16_t *thisv;
    uint8_t value1[2];
    uint8_t value2[2];

    thisv = (ubjs_prmtv_int16_t *)this->glue->prmtv;
    memcpy(value1, (void *)&(thisv->value), sizeof(int16_t));
    ubjs_endian_convert_native_to_big(value1, value2, 2);
    memcpy(data, value2, 2);
}

ubjs_result ubjs_prmtv_int16_printer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_printer_glue *glue,
    ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_ntype_printer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_int16_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_ntype_printer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_printer));
    this->lib = lib;
    this->ntype = &ubjs_prmtv_int16_ntype;
    this->name = "int16";
    this->glue = glue;
    this->userdata = 0;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_printer_free(ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_ntype_printer *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;
    ubjs_library_get_free_f(this->lib, &free_f);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_int16_printer_get_length(ubjs_prmtv_ntype_printer *this,
    unsigned int *plen)
{
    ubjs_prmtv_int16_t *thisv;
    char tmp[9];

    thisv = (ubjs_prmtv_int16_t *)this->glue->prmtv;
    *plen = sprintf(tmp, "[%d]", thisv->value);
}

void ubjs_prmtv_int16_printer_do(ubjs_prmtv_ntype_printer *this, char *data)
{
    ubjs_prmtv_int16_t *thisv;
    char tmp[9];

    thisv = (ubjs_prmtv_int16_t *)this->glue->prmtv;
    sprintf(tmp, "[%d]", thisv->value);
    memcpy(data, tmp, strlen(tmp) * sizeof(char));
}

ubjs_result ubjs_prmtv_int16_get(ubjs_prmtv *this, int16_t *pvalue)
{
    ubjs_prmtv_int16_t *thisv;

    if (0 == this || 0 == pvalue || &ubjs_prmtv_int16_ntype != this->ntype)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_int16_t *)this;
    *pvalue = thisv->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_set(ubjs_prmtv *this, int16_t value)
{
    ubjs_prmtv_int16_t *thisv;

    if (0 == this || &ubjs_prmtv_int16_ntype != this->ntype)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_int16_t *)this;
    thisv->value = value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_get_value_int64(ubjs_prmtv *this, int64_t *pvalue)
{
    ubjs_prmtv_int16_t *thisv;

    if (0 == this || 0 == pvalue || &ubjs_prmtv_int16_ntype != this->ntype)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_int16_t *)this;
    *pvalue = (int64_t) thisv->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_int16_set_value_int64(ubjs_prmtv *this, int64_t value)
{
    ubjs_prmtv_int16_t *thisv;

    if (0 == this || &ubjs_prmtv_int16_ntype != this->ntype || INT16_MIN > value || value > INT16_MAX)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_int16_t *)this;
    thisv->value = (int16_t) value;
    return UR_OK;

}
