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
#include "ubjs_primitive_str_prv.h"
#include "ubjs_common_prv.h"

ubjs_prmtv_ntype ubjs_prmtv_str_ntype =
{
    83,

    ubjs_prmtv_str_free,

    0,
    0,

    ubjs_prmtv_str_debug_string_get_length,
    ubjs_prmtv_str_debug_string_copy,

    ubjs_prmtv_str_parser_processor_new,
    ubjs_prmtv_str_parser_processor_free,

    ubjs_prmtv_str_parser_processor_got_present,
    ubjs_prmtv_str_parser_processor_got_marker,
    ubjs_prmtv_str_parser_processor_got_control,

    ubjs_prmtv_str_parser_processor_read_byte,

    ubjs_prmtv_str_writer_new,
    ubjs_prmtv_str_writer_free,
    ubjs_prmtv_str_writer_get_length,
    ubjs_prmtv_str_writer_do,

    ubjs_prmtv_str_printer_new,
    ubjs_prmtv_str_printer_free,
    ubjs_prmtv_str_printer_get_length,
    ubjs_prmtv_str_printer_do
};

ubjs_result ubjs_prmtv_str(ubjs_library *lib, unsigned int len, char *value, ubjs_prmtv **pthis)
{
    ubjs_prmtv_str_t *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == pthis || 0 == value)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_str_t *)(alloc_f)(sizeof(struct ubjs_prmtv_str_t));
    this->super.lib = lib;
    this->super.type = 0;
    this->super.ntype = &ubjs_prmtv_str_ntype;
    this->len = len;
    this->value = (char *)(alloc_f)(sizeof(char) * len);
    memcpy(this->value, value, len * sizeof(char));

    *pthis = (ubjs_prmtv *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_free(ubjs_prmtv **pthis)
{
    ubjs_prmtv_str_t *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_str_t *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);
    (free_f)(this->value);
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_debug_string_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_prmtv_str_t *thisv;
    char tmp[30];

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_str_t *)this;

    /* "str(%u, " + %s + ")"*/
    *plen = sprintf(tmp, "str(%u, )", thisv->len);
    *plen += thisv->len;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_debug_string_copy(ubjs_prmtv *this, char *str)
{
    ubjs_prmtv_str_t *thisv;

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_str_t *)this;
    sprintf(str, "str(%u, %.*s)", thisv->len, thisv->len, thisv->value);
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_parser_processor_new(ubjs_library *lib,
     ubjs_prmtv_ntype_parser_glue *glue, ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_str_parser_processor *this;
    ubjs_library_alloc_f alloc_f;

    if (0 == lib || 0 == glue || 0 == pthis)
    {
        return UR_ERROR;
    }

    ubjs_library_get_alloc_f(lib, &alloc_f);
    this = (ubjs_prmtv_str_parser_processor *)(alloc_f)(sizeof(
        struct ubjs_prmtv_str_parser_processor));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_str_ntype;
    this->super.name = "str";
    this->super.glue = glue;
    this->super.userdata = 0;
    this->len = -1;
    this->read = 0;
    this->data = 0;
    this->phase = UPSPPP_INIT;
    this->number_marker = 0;
    *pthis = (ubjs_prmtv_ntype_parser_processor *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_parser_processor_free(
    ubjs_prmtv_ntype_parser_processor **pthis)
{
    ubjs_prmtv_str_parser_processor *this;
    ubjs_library_free_f free_f;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_str_parser_processor *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);
    if (0 != this->data)
    {
        (free_f)(this->data);
    }
    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_str_parser_processor_got_present(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv *present)
{
    ubjs_prmtv_str_parser_processor *this2 = (ubjs_prmtv_str_parser_processor *)this;
    ubjs_library_alloc_f alloc_f;

    switch (this2->phase)
    {
        case UPSPPP_INIT:
        case UPSPPP_WANT_NUMBER_CHILD:
            if (0 == present)
            {
                this2->phase = UPSPPP_DONE;
                (this->glue->error_f)(this->glue, 9,
                    "No number");
                return;
            }
            {
                int64_t len = 0;
                if (UR_ERROR == ubjs_prmtv_int_get(present, &len) || 0 > len)
                {
                    this2->phase = UPSPPP_DONE;
                    ubjs_prmtv_free(&present);
                    (this->glue->error_f)(this->glue, 14,
                    "Invalid length");
                    return;
                }

                ubjs_prmtv_free(&present);

                if (this->glue->limit_string_length > 0 &&
                    this->glue->limit_string_length < len)
                {
                    this2->phase = UPSPPP_DONE;
                    (this->glue->error_f)(this->glue, 30,
                        "Reached limit of string length");
                    return;
                }

                this2->phase = UPSPPP_GATHERING_BYTES;
                ubjs_library_get_alloc_f(this->lib, &alloc_f);
                this2 = (ubjs_prmtv_str_parser_processor *)this;
                this2->len = len;
                this2->read = 0;
                this2->data = (char *)(alloc_f)(len * sizeof(char));
            }
            break;

        default:
            this2->phase = UPSPPP_DONE;
            (this->glue->error_f)(this->glue, 22,
                "Unexpected got present");
            break;
    }
}

void ubjs_prmtv_str_parser_processor_got_marker(
    ubjs_prmtv_ntype_parser_processor *this, ubjs_prmtv_ntype *marker)
{
    ubjs_prmtv_str_parser_processor *this2 = (ubjs_prmtv_str_parser_processor *)this;

    switch (this2->phase)
    {
        case UPSPPP_WANT_NUMBER_MARKER:
            this2->number_marker = marker;
            this2->phase = UPSPPP_GOT_NUMBER_MARKER;
            break;

        default:
            this2->phase = UPSPPP_DONE;
            (this->glue->error_f)(this->glue, 21,
                "Unexpected got marker");
            break;
    }
}

void ubjs_prmtv_str_parser_processor_got_control(
    ubjs_prmtv_ntype_parser_processor *this)
{
    ubjs_prmtv_str_parser_processor *this2 = (ubjs_prmtv_str_parser_processor *)this;

    switch (this2->phase)
    {
        case UPSPPP_INIT:
            this2->phase = UPSPPP_WANT_NUMBER_MARKER;
            (this->glue->want_marker_f)(this->glue);
            break;

        case UPSPPP_GOT_NUMBER_MARKER:
            if (0 == this2->number_marker)
            {
                this2->phase = UPSPPP_DONE;
                (this->glue->error_f)(this->glue, 9,
                    "No marker");
                break;
            }

            if (0 == this2->number_marker->new_from_int64_f)
            {
                this2->phase = UPSPPP_DONE;
                (this->glue->error_f)(this->glue, 14,
                    "Invalid marker");
                break;
            }

            this2->phase = UPSPPP_WANT_NUMBER_CHILD;
            (this->glue->want_child_f)(this->glue, this2->number_marker);
            break;

        case UPSPPP_GATHERING_BYTES:
            if (0 == this2->len && 0 == this2->read)
            {
                this2->phase = UPSPPP_DONE;
                ubjs_prmtv *ret = 0;
                ubjs_prmtv_str(this->lib, 0, "", &ret);
                (this->glue->return_control_f)(this->glue, ret);
                break;
            }
            break;

        default:
            this2->phase = UPSPPP_DONE;
            (this->glue->error_f)(this->glue, 22,
                "Unexpected got control");
            break;
    }
}

void ubjs_prmtv_str_parser_processor_read_byte(
    ubjs_prmtv_ntype_parser_processor *this, uint8_t achr)
{
    ubjs_prmtv_str_parser_processor *this2;
    ubjs_prmtv *ret;

    this2 = (ubjs_prmtv_str_parser_processor *)this;
    if (this2->read == this2->len)
    {
        (this->glue->error_f)(this->glue, 19,
            "Too much bytes read");
        return;
    }

    this2->data[this2->read++] = achr;
    if (this2->read < this2->len)
    {
        return;
    }

    this2->phase = UPSPPP_DONE;
    ubjs_prmtv_str(this->lib, this2->len, this2->data, &ret);
    (this->glue->return_control_f)(this->glue, ret);
}

ubjs_result ubjs_prmtv_str_writer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_writer_glue *glue, ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_str_writer *this;
    ubjs_library_alloc_f alloc_f;
    ubjs_prmtv_str_t *pstr;
    ubjs_prmtv_ntype *length_ntype = 0;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_str_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    pstr = (ubjs_prmtv_str_t *)glue->prmtv;
    ubjs_library_get_alloc_f(lib, &alloc_f);

    this = (ubjs_prmtv_str_writer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_str_writer));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_str_ntype;
    this->super.name = "str";
    this->super.glue = glue;
    this->super.userdata = 0;
    this->length_writer = 0;

    this->length_glue = (ubjs_prmtv_ntype_writer_glue *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_writer_glue));
    this->length_glue->prmtv = 0;
    this->length_glue->debug_f = 0;
    this->length_glue->userdata = 0;

    ubjs_prmtv_int(lib, pstr->len, &(this->length_glue->prmtv));
    ubjs_prmtv_get_ntype(this->length_glue->prmtv, &length_ntype);
    (length_ntype->writer_new_f)(lib, this->length_glue, &(this->length_writer));

    *pthis = (ubjs_prmtv_ntype_writer *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_writer_free(ubjs_prmtv_ntype_writer **pthis)
{
    ubjs_prmtv_str_writer *this;
    ubjs_library_free_f free_f;
    ubjs_prmtv_ntype *length_ntype = 0;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_str_writer *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);

    ubjs_prmtv_get_ntype(this->length_writer->glue->prmtv, &length_ntype);
    ubjs_prmtv_free(&(this->length_writer->glue->prmtv));
    (free_f)(this->length_writer->glue);
    (length_ntype->writer_free_f)(&this->length_writer);

    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_str_writer_get_length(ubjs_prmtv_ntype_writer *this,
    unsigned int *plen)
{
    ubjs_prmtv_str_writer *this2 = (ubjs_prmtv_str_writer *)this;;
    ubjs_prmtv_str_t *pstr = (ubjs_prmtv_str_t *)this->glue->prmtv;
    ubjs_prmtv_ntype *length_ntype = 0;

    ubjs_prmtv_get_ntype(this2->length_writer->glue->prmtv, &length_ntype);
    (length_ntype->writer_get_length_f)(this2->length_writer, plen);
    *plen += pstr->len + 1;
}

void ubjs_prmtv_str_writer_do(ubjs_prmtv_ntype_writer *this, uint8_t *data)
{
    ubjs_prmtv_str_writer *this2 = (ubjs_prmtv_str_writer *)this;;
    ubjs_prmtv_str_t *pstr = (ubjs_prmtv_str_t *)this->glue->prmtv;
    ubjs_prmtv_ntype *length_ntype = 0;
    unsigned int len_len = 0;

    ubjs_prmtv_get_ntype(this2->length_writer->glue->prmtv, &length_ntype);
    data[0] = length_ntype->marker;
    (length_ntype->writer_get_length_f)(this2->length_writer, &len_len);
    (length_ntype->writer_do_f)(this2->length_writer, data + 1);
    memcpy(data + 1 + len_len, pstr->value, pstr->len * sizeof(char));
}

ubjs_result ubjs_prmtv_str_printer_new(ubjs_library *lib,
    ubjs_prmtv_ntype_printer_glue *glue, ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_str_printer *this;
    ubjs_library_alloc_f alloc_f;
    ubjs_prmtv_str_t *pstr = 0;
    ubjs_prmtv_ntype *length_ntype = 0;

    if (0 == lib || 0 == glue || 0 == glue->prmtv
        || &ubjs_prmtv_str_ntype != glue->prmtv->ntype || 0 == pthis)
    {
        return UR_ERROR;
    }

    pstr = (ubjs_prmtv_str_t *)glue->prmtv;
    ubjs_library_get_alloc_f(lib, &alloc_f);

    this = (ubjs_prmtv_str_printer *)(alloc_f)(sizeof(
        struct ubjs_prmtv_str_printer));
    this->super.lib = lib;
    this->super.ntype = &ubjs_prmtv_str_ntype;
    this->super.name = "str";
    this->super.glue = glue;
    this->super.userdata = 0;
    this->length_printer = 0;

    this->length_glue = (ubjs_prmtv_ntype_printer_glue *)(alloc_f)(sizeof(
        struct ubjs_prmtv_ntype_printer_glue));
    this->length_glue->prmtv = 0;
    this->length_glue->debug_f = 0;
    this->length_glue->userdata = 0;

    ubjs_prmtv_int(lib, pstr->len, &(this->length_glue->prmtv));
    ubjs_prmtv_get_ntype(this->length_glue->prmtv, &length_ntype);
    (length_ntype->printer_new_f)(lib, this->length_glue, &(this->length_printer));

    *pthis = (ubjs_prmtv_ntype_printer *)this;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_printer_free(ubjs_prmtv_ntype_printer **pthis)
{
    ubjs_prmtv_str_printer *this;
    ubjs_library_free_f free_f;
    ubjs_prmtv_ntype *length_ntype = 0;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_prmtv_str_printer *)*pthis;
    ubjs_library_get_free_f(this->super.lib, &free_f);

    ubjs_prmtv_get_ntype(this->length_printer->glue->prmtv, &length_ntype);
    ubjs_prmtv_free(&(this->length_printer->glue->prmtv));
    (free_f)(this->length_printer->glue);
    (length_ntype->printer_free_f)(&this->length_printer);

    (free_f)(this);
    *pthis = 0;
    return UR_OK;
}

void ubjs_prmtv_str_printer_get_length(ubjs_prmtv_ntype_printer *this,
    unsigned int *plen)
{
    ubjs_prmtv_str_printer *this2 = (ubjs_prmtv_str_printer *)this;;
    ubjs_prmtv_str_t *pstr = (ubjs_prmtv_str_t *)this->glue->prmtv;
    ubjs_prmtv_ntype *length_ntype = 0;

    ubjs_prmtv_get_ntype(this2->length_printer->glue->prmtv, &length_ntype);
    (length_ntype->printer_get_length_f)(this2->length_printer, plen);
    *plen += pstr->len + 5;
}

void ubjs_prmtv_str_printer_do(ubjs_prmtv_ntype_printer *this, char *data)
{
    ubjs_prmtv_str_printer *this2 = (ubjs_prmtv_str_printer *)this;;
    ubjs_prmtv_str_t *pstr = (ubjs_prmtv_str_t *)this->glue->prmtv;
    ubjs_prmtv_ntype *length_ntype = 0;
    unsigned int len_len = 0;

    ubjs_prmtv_get_ntype(this2->length_printer->glue->prmtv, &length_ntype);
    data[0] = '[';
    data[1] = length_ntype->marker;
    data[2] = ']';
    (length_ntype->printer_get_length_f)(this2->length_printer, &len_len);
    (length_ntype->printer_do_f)(this2->length_printer, data + 3);
    data[3 + len_len] = '[';
    memcpy(data + 3 + len_len + 1, pstr->value, pstr->len * sizeof(char));
    data[3 + len_len + 1 + pstr->len] = ']';
}

ubjs_result ubjs_prmtv_str_get_length(ubjs_prmtv *this, unsigned int *plen)
{
    ubjs_prmtv_str_t *thisv;

    if (0 == this || 0 == plen)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_str_t *)this;
    *plen = thisv->len;
    return UR_OK;
}

ubjs_result ubjs_prmtv_str_copy_text(ubjs_prmtv *this, char *str)
{
    ubjs_prmtv_str_t *thisv;

    if (0 == this || 0 == str)
    {
        return UR_ERROR;
    }

    thisv = (ubjs_prmtv_str_t *)this;
    memcpy(str, thisv->value, sizeof(char) * thisv->len);
    return UR_OK;
}
