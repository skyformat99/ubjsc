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

#include "test_common.h"
ubjs_library *instance_lib = 0;

ubjs_result ubjs_prmtv_mock_free(ubjs_prmtv **);
ubjs_result ubjs_prmtv_mock_debug_string_get_length(ubjs_prmtv *, unsigned int *);
ubjs_result ubjs_prmtv_mock_debug_string_copy(ubjs_prmtv *, char *);

ubjs_result ubjs_prmtv_mock_parser_processor_new_generic(ubjs_library *,
     ubjs_prmtv_ntype_parser_glue *, ubjs_prmtv_ntype *,
    ubjs_prmtv_ntype_parser_processor **);
ubjs_result ubjs_prmtv_mock_parser_processor_new1(ubjs_library *,
     ubjs_prmtv_ntype_parser_glue *, ubjs_prmtv_ntype_parser_processor **);
ubjs_result ubjs_prmtv_mock_parser_processor_new2(ubjs_library *,
     ubjs_prmtv_ntype_parser_glue *, ubjs_prmtv_ntype_parser_processor **);
ubjs_result ubjs_prmtv_mock_parser_processor_free(
    ubjs_prmtv_ntype_parser_processor **);
void ubjs_prmtv_mock_parser_processor_got_control(
    ubjs_prmtv_ntype_parser_processor *);
void ubjs_prmtv_mock_parser_processor_read_byte(
    ubjs_prmtv_ntype_parser_processor *, uint8_t);

ubjs_result ubjs_prmtv_mock_writer_new_generic(ubjs_library *,
    ubjs_prmtv_ntype_writer_glue *, ubjs_prmtv_ntype *,
    ubjs_prmtv_ntype_writer **);
ubjs_result ubjs_prmtv_mock_writer_new1(ubjs_library *,
    ubjs_prmtv_ntype_writer_glue *, ubjs_prmtv_ntype_writer **);
ubjs_result ubjs_prmtv_mock_writer_new2(ubjs_library *,
    ubjs_prmtv_ntype_writer_glue *, ubjs_prmtv_ntype_writer **);
ubjs_result ubjs_prmtv_mock_writer_free(ubjs_prmtv_ntype_writer **);
void ubjs_prmtv_mock_writer_get_length(ubjs_prmtv_ntype_writer *,
    unsigned int *);
void ubjs_prmtv_mock_writer_do(ubjs_prmtv_ntype_writer *, uint8_t *);

ubjs_result ubjs_prmtv_mock_printer_new_generic(ubjs_library *,
    ubjs_prmtv_ntype_printer_glue *, ubjs_prmtv_ntype *,
    ubjs_prmtv_ntype_printer **);
ubjs_result ubjs_prmtv_mock_printer_new1(ubjs_library *,
    ubjs_prmtv_ntype_printer_glue *, ubjs_prmtv_ntype_printer **);
ubjs_result ubjs_prmtv_mock_printer_new2(ubjs_library *,
    ubjs_prmtv_ntype_printer_glue *, ubjs_prmtv_ntype_printer **);
ubjs_result ubjs_prmtv_mock_printer_free(ubjs_prmtv_ntype_printer **);
void ubjs_prmtv_mock_printer_get_length(ubjs_prmtv_ntype_printer *,
    unsigned int *);
void ubjs_prmtv_mock_printer_do(ubjs_prmtv_ntype_printer *, char *);

ubjs_prmtv_ntype mock_prmtv_ntype1 =
{
    32,

    ubjs_prmtv_mock_free,

    0,
    0,

    ubjs_prmtv_mock_debug_string_get_length,
    ubjs_prmtv_mock_debug_string_copy,

    ubjs_prmtv_mock_parser_processor_new1,
    ubjs_prmtv_mock_parser_processor_free,

    0,
    0,
    ubjs_prmtv_mock_parser_processor_got_control,

    ubjs_prmtv_mock_parser_processor_read_byte,

    ubjs_prmtv_mock_writer_new1,
    ubjs_prmtv_mock_writer_free,
    ubjs_prmtv_mock_writer_get_length,
    ubjs_prmtv_mock_writer_do,

    ubjs_prmtv_mock_printer_new1,
    ubjs_prmtv_mock_printer_free,
    ubjs_prmtv_mock_printer_get_length,
    ubjs_prmtv_mock_printer_do
};

ubjs_prmtv_ntype mock_prmtv_ntype2 =
{
    33,

    ubjs_prmtv_mock_free,

    0,
    0,

    ubjs_prmtv_mock_debug_string_get_length,
    ubjs_prmtv_mock_debug_string_copy,

    ubjs_prmtv_mock_parser_processor_new1,
    ubjs_prmtv_mock_parser_processor_free,

    0,
    0,
    ubjs_prmtv_mock_parser_processor_got_control,

    ubjs_prmtv_mock_parser_processor_read_byte,

    ubjs_prmtv_mock_writer_new2,
    ubjs_prmtv_mock_writer_free,
    ubjs_prmtv_mock_writer_get_length,
    ubjs_prmtv_mock_writer_do,

    ubjs_prmtv_mock_printer_new2,
    ubjs_prmtv_mock_printer_free,
    ubjs_prmtv_mock_printer_get_length,
    ubjs_prmtv_mock_printer_do
};

ubjs_result mock_prmtv(ubjs_library *lib, ubjs_prmtv_ntype *ntype, ubjs_prmtv **pthis)
{
    ubjs_prmtv *this;
    ubjs_library_alloc_f alloc_f;
    ubjs_library_get_alloc_f(lib, &alloc_f);

    this = (ubjs_prmtv *)(alloc_f)(sizeof(struct ubjs_prmtv));
    this->lib = lib;
    this->ntype = ntype;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_mock_free(ubjs_prmtv **pthis)
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

ubjs_result ubjs_prmtv_mock_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    *plen = 4;
    return UR_OK;
}

ubjs_result ubjs_prmtv_mock_debug_string_copy(ubjs_prmtv *this, char *str)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    memcpy(str, "mock", sizeof(char) * 4);
    return UR_OK;
}

ubjs_result ubjs_prmtv_mock_parser_processor_new_generic(ubjs_library *lib,
     ubjs_prmtv_ntype_parser_glue *glue, ubjs_prmtv_ntype *ntype,
    ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_ntype_parser_processor *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_ntype_parser_processor *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_parser_processor));
    this->lib = lib;
    this->ntype = ntype;
    this->name = "mock";
    this->glue = glue;
    this->userdata = 0;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_mock_parser_processor_new1(ubjs_library *lib,
     ubjs_prmtv_ntype_parser_glue *glue, ubjs_prmtv_ntype_parser_processor **pthis)
{
    return ubjs_prmtv_mock_parser_processor_new_generic(lib, glue,
        &mock_prmtv_ntype1, pthis);
}

ubjs_result ubjs_prmtv_mock_parser_processor_new2(ubjs_library *lib,
     ubjs_prmtv_ntype_parser_glue *glue, ubjs_prmtv_ntype_parser_processor **pthis)
{
    return ubjs_prmtv_mock_parser_processor_new_generic(lib, glue,
        &mock_prmtv_ntype2, pthis);
}

ubjs_result ubjs_prmtv_mock_parser_processor_free(
    ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_ntype_parser_processor *this;
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

void ubjs_prmtv_mock_parser_processor_got_control(
    ubjs_prmtv_ntype_parser_processor *this)
{
    (this->glue->return_control_f)(this->glue, ubjs_prmtv_null());
}

void ubjs_prmtv_mock_parser_processor_read_byte(
    ubjs_prmtv_ntype_parser_processor *this, uint8_t c)
{
    ubjs_prmtv *ret = 0;
    mock_prmtv(this->lib, this->ntype, &ret);
    (this->glue->return_control_f)(this->glue, ret);
}

ubjs_result ubjs_prmtv_mock_writer_new_generic(ubjs_library *lib,
    ubjs_prmtv_ntype_writer_glue *glue, ubjs_prmtv_ntype *ntype,
    ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_ntype_writer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_ntype_writer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_writer));
    this->lib = lib;
    this->ntype = ntype;
    this->name = "mock";
    this->glue = glue;
    this->userdata = 0;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_mock_writer_new1(ubjs_library *lib,
    ubjs_prmtv_ntype_writer_glue *glue, ubjs_prmtv_ntype_writer **pthis)
{
    return ubjs_prmtv_mock_writer_new_generic(lib, glue,
        &mock_prmtv_ntype1, pthis);
}

ubjs_result ubjs_prmtv_mock_writer_new2(ubjs_library *lib,
    ubjs_prmtv_ntype_writer_glue *glue, ubjs_prmtv_ntype_writer **pthis)
{
    return ubjs_prmtv_mock_writer_new_generic(lib, glue,
        &mock_prmtv_ntype2, pthis);
}

ubjs_result ubjs_prmtv_mock_writer_free(ubjs_prmtv_ntype_writer **pthis)
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

void ubjs_prmtv_mock_writer_get_length(ubjs_prmtv_ntype_writer *this,
    unsigned int *plen)
{
    *plen = 1;
}

void ubjs_prmtv_mock_writer_do(ubjs_prmtv_ntype_writer *this, uint8_t *data)
{
    data[0] = 'r';
}

ubjs_result ubjs_prmtv_mock_printer_new_generic(ubjs_library *lib,
    ubjs_prmtv_ntype_printer_glue *glue, ubjs_prmtv_ntype *ntype,
    ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_ntype_printer *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_ntype_printer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_printer));
    this->lib = lib;
    this->ntype = ntype;
    this->name = "mock";
    this->glue = glue;
    this->userdata = 0;
    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_mock_printer_new1(ubjs_library *lib,
    ubjs_prmtv_ntype_printer_glue *glue,
    ubjs_prmtv_ntype_printer **pthis)
{
    return ubjs_prmtv_mock_printer_new_generic(lib, glue,
        &mock_prmtv_ntype1, pthis);
}

ubjs_result ubjs_prmtv_mock_printer_new2(ubjs_library *lib,
    ubjs_prmtv_ntype_printer_glue *glue,
    ubjs_prmtv_ntype_printer **pthis)
{
    return ubjs_prmtv_mock_printer_new_generic(lib, glue,
        &mock_prmtv_ntype2, pthis);
}

ubjs_result ubjs_prmtv_mock_printer_free(ubjs_prmtv_ntype_printer **pthis)
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

void ubjs_prmtv_mock_printer_get_length(ubjs_prmtv_ntype_printer *this,
    unsigned int *plen)
{
    *plen = 9;;
}

void ubjs_prmtv_mock_printer_do(ubjs_prmtv_ntype_printer *this, char *data)
{
    memcpy(data, "[<rower>]", 9);
}
