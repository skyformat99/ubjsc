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
#include "ubjs_primitive_char_prv.h"
#include "ubjs_common_prv.h"

ubjs_prmtv_ntype ubjs_prmtv_char_ntype =
{
    67,

    ubjs_prmtv_char_free,

    0,
    0,

    ubjs_prmtv_char_debug_string_get_length,
    ubjs_prmtv_char_debug_string_copy,

    ubjs_prmtv_char_parser_processor_new,
    ubjs_prmtv_char_parser_processor_free,
    ubjs_prmtv_char_parser_processor_got_control,
    ubjs_prmtv_char_parser_processor_read_byte,

    ubjs_prmtv_char_writer_new,
    ubjs_prmtv_char_writer_free,
    ubjs_prmtv_char_writer_get_length,
    ubjs_prmtv_char_writer_do,

    ubjs_prmtv_char_printer_new,
    ubjs_prmtv_char_printer_free,
    ubjs_prmtv_char_printer_get_length,
    ubjs_prmtv_char_printer_do
};

ubjs_result ubjs_prmtv_char(ubjs_library *lib, char value, ubjs_prmtv **pthis)
{
    ubjs_prmtv_char_t *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == pthis || value < 0)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_char_t *)(alloc_f)(sizeof(struct ubjs_prmtv_char_t));
    this->super.lib = lib;
    this->super.type = 0;
    this->super.ntype = &ubjs_prmtv_char_ntype;
    this->value = value;

    *pthis = (ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_free(ubjs_prmtv **pthis)
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

ubjs_result ubjs_prmtv_char_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_prmtv_char_t *thisv;
    char tmp[11];

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_char_t *)this;
    *plen = sprintf(tmp, "char(%c)", thisv->value);
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_debug_string_copy(ubjs_prmtv *this, char *str)
{
    ubjs_prmtv_char_t *thisv;
    char tmp[11];

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_char_t *)this;
    sprintf(tmp, "char(%c)", thisv->value);
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_parser_processor_new(ubjs_library *lib,
     ubjs_prmtv_ntype_parser_glue *glue, ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_char_parser_processor *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_char_parser_processor *)(alloc_f)(sizeof(
        struct ubjs_prmtv_char_parser_processor));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_char_ntype;
    this->super.name = "char";
    this->super.glue = glue;
    this->super.userdata = 0;
    this->did_read = UFALSE;
    *pthis = (ubjs_prmtv_ntype_parser_processor *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_parser_processor_free(
    ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_char_parser_processor *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_char_parser_processor *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_char_parser_processor_got_control(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv *present)
{
    if (0 != present)
    {
        (this->glue->error_f)(this->glue, 18,
            "Unexpected present");
        return;
    }
}

void ubjs_prmtv_char_parser_processor_read_byte(
    ubjs_prmtv_ntype_parser_processor *this, uint8_t achr)
{
    ubjs_prmtv_char_parser_processor *this2;
    ubjs_prmtv *ret;

    this2 = (ubjs_prmtv_char_parser_processor *)this;
    if (UTRUE == this2->did_read)
    {
        (this->glue->error_f)(this->glue, 19,
            "Too much bytes read");
        return;
    }

    this2->did_read = UTRUE;

    ubjs_prmtv_char(this->lib, (char)achr, &ret);
    (this->glue->return_control_f)(this->glue, ret);
}

ubjs_result ubjs_prmtv_char_writer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_writer_glue *glue, ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_ntype_writer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_char_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_ntype_writer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_writer));
    this->lib = lib;
    this->ntype = &ubjs_prmtv_char_ntype;
    this->name = "char";
    this->glue = glue;
    this->userdata = 0;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_writer_free(ubjs_prmtv_ntype_writer **pthis)
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

void ubjs_prmtv_char_writer_get_length(ubjs_prmtv_ntype_writer *this,
    unsigned int *plen)
{
    *plen = 1;
}

void ubjs_prmtv_char_writer_do(ubjs_prmtv_ntype_writer *this, uint8_t *data)
{
    ubjs_prmtv_char_t *thisv;
    thisv = (ubjs_prmtv_char_t *)this->glue->prmtv;
    data[0] = (uint8_t)thisv->value;
}

ubjs_result ubjs_prmtv_char_printer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_printer_glue *glue,
    ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_ntype_printer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_char_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_ntype_printer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_printer));
    this->lib = lib;
    this->ntype = &ubjs_prmtv_char_ntype;
    this->name = "char";
    this->glue = glue;
    this->userdata = 0;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_printer_free(ubjs_prmtv_ntype_printer **pthis)
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

void ubjs_prmtv_char_printer_get_length(ubjs_prmtv_ntype_printer *this,
    unsigned int *plen)
{
    *plen = 3;
}

void ubjs_prmtv_char_printer_do(ubjs_prmtv_ntype_printer *this, char *data)
{
    ubjs_prmtv_char_t *thisv = (ubjs_prmtv_char_t *)this->glue->prmtv;
    data[0] = '[';
    data[1] = thisv->value;
    data[2] = ']';
}

ubjs_result ubjs_prmtv_char_get(ubjs_prmtv *this, char *pvalue)
{
    ubjs_prmtv_char_t *thisv;

    if (0 == this || 0 == pvalue || &ubjs_prmtv_char_ntype != this->ntype)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_char_t *)this;
    *pvalue = thisv->value;
    return UR_OK;
}

ubjs_result ubjs_prmtv_char_set(ubjs_prmtv *this, char value)
{
    ubjs_prmtv_char_t *thisv;

    if (0 == this || &ubjs_prmtv_char_ntype != this->ntype || 0 > value)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_char_t *)this;
    thisv->value = value;
    return UR_OK;
}
