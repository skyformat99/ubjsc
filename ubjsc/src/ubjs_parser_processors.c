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
#include "ubjs_parser_prv.h"
#include "ubjs_glue_array_array.h"

ubjs_result ubjs_processor_ntype(ubjs_processor *parent, ubjs_prmtv_ntype *ntype,
    ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_ntype *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));

    data=(ubjs_userdata_ntype *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_userdata_ntype));
    data->ntype = ntype;
    data->pos = 0;
    data->glue.userdata = (void *)this;
    data->glue.parent = parent;
    data->glue.give_control_f = ubjs_processor_ntype_give_control;
    data->glue.debug_f = ubjs_processor_ntype_debug;
    data->glue.error_f = ubjs_processor_ntype_error;
    (ntype->parser_processor_new_f)(parent->parser->lib, &(data->glue), &(data->processor));

    this->name = data->processor->name;
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_ntype_got_control;
    this->read_byte = ubjs_processor_ntype_read_byte;
    this->free=ubjs_processor_ntype_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_ntype_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this->userdata;

    (data->ntype->parser_processor_got_control_f)(data->processor, present);
}

void ubjs_processor_ntype_free(ubjs_processor *this)
{
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this->userdata;
    (data->ntype->parser_processor_free_f)(&(data->processor));
    (this->parser->lib->free_f)(data);
    (this->parser->lib->free_f)(this);
}

void ubjs_processor_ntype_read_byte(ubjs_processor *this, unsigned int pos, uint8_t c)
{
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this->userdata;

    data->pos = pos;
    (data->ntype->parser_processor_read_byte_f)(data->processor, c);
}

void ubjs_processor_ntype_give_control(ubjs_prmtv_ntype_parser_glue *this,
    void *parent, void *present)
{
    ubjs_processor *this2 = (ubjs_processor *)this->userdata;
    ubjs_parser_give_control(this2->parser, this2->parent, present);
    ubjs_processor_ntype_free(this2);
}

void ubjs_processor_ntype_debug(ubjs_prmtv_ntype_parser_glue *this,
    unsigned int len, char *msg)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_processor *this2 = (ubjs_processor *)this->userdata;
    if (0 != this2->parser->debug_f)
    {
        ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this2->userdata;
        char *msg2 = 0;
        unsigned int len2 = 0;

        ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 1, "[");
        ubjs_compact_sprintui(this2->parser->lib, &msg2, &len2, data->pos);
        ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 1, "|");
        ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, strlen(this2->name),
            this2->name);
        ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 2, "] ");
        ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, len, msg);
        (this2->parser->debug_f)(this2->parser->userdata, len2, msg2);
        (this2->parser->lib->free_f)(msg2);
    }
#endif
    /* LCOV_EXCL_STOP */
}

void ubjs_processor_ntype_error(ubjs_prmtv_ntype_parser_glue *this,
    unsigned int len, char *msg)
{
    ubjs_processor *this2 = (ubjs_processor *)this->userdata;
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this2->userdata;
    char *msg2 = 0;
    unsigned int len2 = 0;

    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 1, "[");
    ubjs_compact_sprintui(this2->parser->lib, &msg2, &len2, data->pos);
    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 1, "|");
    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, strlen(this2->name),
        this2->name);
    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 2, "] ");
    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, len, msg);
    ubjs_parser_emit_error(this2->parser, len2, msg2);
    (this2->parser->lib->free_f)(msg2);
}

ubjs_result ubjs_processor_char(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "char";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=0;
    this->read_byte = ubjs_processor_char_read_byte;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_char_read_byte(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    uint8_t value[1];
    uint8_t value2[1];
    ubjs_prmtv *ret;
    value[0] = achar;

    ubjs_endian_convert_big_to_native(value, value2, 1);
    ubjs_prmtv_char(this->parser->lib, *((char *)value2), &ret);
    ubjs_parser_give_control(this->parser, this->parent, ret);
    (this->free)(this);
}

void ubjs_processor_longint_free(ubjs_processor *this)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    (this->parser->lib->free_f)(data->data);
    (this->parser->lib->free_f)(this->userdata);
    (this->parser->lib->free_f)(this);
}

ubjs_result ubjs_processor_int64(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)(parent->parser->lib->alloc_f)(sizeof(uint8_t) * 8);
    data->done=0;
    this->name = "int64";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_byte = ubjs_processor_int64_read_byte;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_int64_read_byte(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (8 <= data->done)
    {
        uint8_t value2[8];
        int64_t *v64;

        ubjs_endian_convert_big_to_native(data->data, value2, 8);
        v64 = (int64_t *)value2;
        ubjs_prmtv_int64(this->parser->lib, v64[0], &ret);
        ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }
}

ubjs_result ubjs_processor_float32(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)(parent->parser->lib->alloc_f)(sizeof(uint8_t) * 4);
    data->done=0;
    this->name = "float32";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_byte = ubjs_processor_float32_read_byte;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_float32_read_byte(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (4 <= data->done)
    {
        uint8_t value2[4];
        float32_t *v32;

        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        v32 = (float32_t *)value2;
        ubjs_prmtv_float32(this->parser->lib, v32[0], &ret);
        ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }
}

ubjs_result ubjs_processor_float64(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)(parent->parser->lib->alloc_f)(sizeof(uint8_t) * 8);
    data->done=0;
    this->name = "float64";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_byte = ubjs_processor_float64_read_byte;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_float64_read_byte(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (8 <= data->done)
    {
        uint8_t value2[8];
        float64_t *v64;

        ubjs_endian_convert_big_to_native(data->data, value2, 8);
        v64 = (float64_t *)value2;
        ubjs_prmtv_float64(this->parser->lib, v64[0], &ret);
        ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }
}

ubjs_result ubjs_processor_str(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_str *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_str *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_userdata_str));
    data->have_length=UFALSE;
    data->length=-1;
    data->data=0;
    data->done=0;
    this->name = "str";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_str_got_control;
    this->read_byte = ubjs_processor_str_read_byte;
    this->free=ubjs_processor_str_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_str_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_userdata_str *data=(ubjs_userdata_str *)this->userdata;

    if (0 != present)
    {
        unsigned int length = 0;

        if (UR_ERROR == ubjs_processor_child_produced_length(this, present, &length))
        {
            return;
        }

        if (this->parser->limit_string_length > 0 &&
            this->parser->limit_string_length < length)
        {
            ubjs_parser_emit_error(this->parser, 30,
                "Reached limit of string length");
            return;
        }

        this->name = "str with length";
        data->have_length = UTRUE;
        data->length=length;
        data->data=(char *)(this->parser->lib->alloc_f)(sizeof(char) * length);
        if (0 == length)
        {
            ubjs_processor_str_complete(this);
            return;
        }
    }

    if (UFALSE == data->have_length)
    {
        ubjs_processor_ints(this);
    }
}

void ubjs_processor_str_free(ubjs_processor *this)
{
    ubjs_userdata_str *data=(ubjs_userdata_str *)this->userdata;

    if (UTRUE == data->have_length)
    {
        (this->parser->lib->free_f)(data->data);
    }

    (this->parser->lib->free_f)(data);
    (this->parser->lib->free_f)(this);
}

void ubjs_processor_str_read_byte(ubjs_processor *this, unsigned int pos, uint8_t c)
{
    ubjs_userdata_str *data=(ubjs_userdata_str *)this->userdata;
    data->data[data->done++] = (char)c;

    if (data->done == data->length)
    {
        ubjs_processor_str_complete(this);
    }
}

void ubjs_processor_str_complete(ubjs_processor *this)
{
    ubjs_userdata_str *data=(ubjs_userdata_str *)this->userdata;
    ubjs_prmtv *product;

    ubjs_prmtv_str(this->parser->lib, data->done, data->data, &product);

    ubjs_parser_give_control(this->parser, this->parent, product);
    (this->free)(this);
}

ubjs_result ubjs_processor_hpn(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_hpn *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_hpn *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_userdata_hpn));
    data->have_length=UFALSE;
    data->length=-1;
    data->data=0;
    data->done=0;
    this->name = "hpn";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_hpn_got_control;
    this->read_byte = ubjs_processor_hpn_read_byte;
    this->free=ubjs_processor_hpn_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_hpn_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_userdata_hpn *data=(ubjs_userdata_hpn *)this->userdata;

    if (0 != present)
    {
        unsigned int length = 0;

        if (UR_ERROR == ubjs_processor_child_produced_length(this, present, &length))
        {
            return;
        }

        if (this->parser->limit_string_length > 0 &&
            this->parser->limit_string_length < length)
        {
            ubjs_parser_emit_error(this->parser, 30,
                "Reached limit of string length");
            return;
        }

        this->name = "hpn with length";
        data->have_length = UTRUE;
        data->length=length;
        data->data=(char *)(this->parser->lib->alloc_f)(sizeof(char) * length);
        if (0 == length)
        {
            ubjs_processor_hpn_complete(this);
            return;
        }
    }

    if (UFALSE == data->have_length)
    {
        ubjs_processor_ints(this);
    }
}

void ubjs_processor_hpn_free(ubjs_processor *this)
{
    ubjs_userdata_hpn *data=(ubjs_userdata_hpn *)this->userdata;

    if (UTRUE == data->have_length)
    {
        (this->parser->lib->free_f)(data->data);
    }

    (this->parser->lib->free_f)(data);
    (this->parser->lib->free_f)(this);
}

void ubjs_processor_hpn_read_byte(ubjs_processor *this, unsigned int pos, uint8_t c)
{
    ubjs_userdata_hpn *data=(ubjs_userdata_hpn *)this->userdata;
    data->data[data->done++] = (char)c;

    if (data->done == data->length)
    {
        ubjs_processor_hpn_complete(this);
    }
}

void ubjs_processor_hpn_complete(ubjs_processor *this)
{
    ubjs_userdata_hpn *data=(ubjs_userdata_hpn *)this->userdata;
    ubjs_prmtv *product;

    if (UR_ERROR == ubjs_prmtv_hpn(this->parser->lib, data->done, data->data, &product))
    {
        ubjs_parser_emit_error(this->parser, 39, "Syntax error for high-precision number.");
        return;
    }

    ubjs_parser_give_control(this->parser, this->parent, product);
    (this->free)(this);
}

ubjs_result ubjs_processor_array(ubjs_processor *parent, ubjs_processor **pthis)
{
    if (UR_ERROR == ubjs_parser_up_recursion_level(parent->parser))
    {
        return UR_ERROR;
    }

    ubjs_processor *this;
    ubjs_userdata_array *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_array *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_userdata_array));
    data->array=0;
    data->real_length=0;
    data->have_length=UFALSE;
    data->have_type=UFALSE;
    data->length=-1;
    data->type_create=0;
    data->ntype=0;

    this->name = "array";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_array_got_control;
    this->read_byte = 0;
    this->free=ubjs_processor_array_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_array_end(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "array end";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=ubjs_processor_array_end_got_control;
    this->read_byte = 0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_array_count(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "optimized by count";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=ubjs_processor_array_count_got_control;
    this->read_byte=0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_array_type_selected_factory(ubjs_processor *this,
    ubjs_processor_factory_create create)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;
    ubjs_processor *next;

    data->have_type=UTRUE;
    data->type_create = create;
    data->ntype=0;

    ubjs_processor_next_object(this,
        this->parser->ntypes_array_type, ubjs_processor_top_selected_factory_ntype,
        this->parser->factories_array_type,
        ubjs_processor_top_selected_factory, &next);
    ubjs_parser_give_control(this->parser, next, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_array_type_selected_factory_ntype(ubjs_processor *this,
    ubjs_prmtv_ntype *ntype)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;
    ubjs_processor *next;

    data->have_type=UTRUE;
    data->type_create = 0;
    data->ntype=ntype;

    ubjs_processor_next_object(this,
        this->parser->ntypes_array_type, ubjs_processor_top_selected_factory_ntype,
        this->parser->factories_array_type,
        ubjs_processor_top_selected_factory, &next);
    ubjs_parser_give_control(this->parser, next, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_array_type(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this = 0;
    ubjs_processor_next_object(parent,
        parent->parser->ntypes_top, ubjs_processor_array_type_selected_factory_ntype,
        parent->parser->factories_top,
        ubjs_processor_array_type_selected_factory, &this);
    *pthis = this;
    ubjs_parser_give_control(this->parser, this, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_array_selected_factory(ubjs_processor *this,
    ubjs_processor_factory_create create)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;

    if (this->parser->limit_container_length > 0 &&
        create != ubjs_processor_array_end &&
        this->parser->limit_container_length <= data->real_length)
    {
        ubjs_parser_emit_error(this->parser, 33,
            "Reached limit of container length");
        return UR_ERROR;
    }

    return ubjs_processor_top_selected_factory(this, create);
}

ubjs_result ubjs_processor_array_selected_factory_ntype(ubjs_processor *this,
    ubjs_prmtv_ntype *ntype)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;

    if (this->parser->limit_container_length > 0 &&
/*@todo        create != ubjs_processor_array_end && */
        this->parser->limit_container_length <= data->real_length)
    {
        ubjs_parser_emit_error(this->parser, 33,
            "Reached limit of container length");
        return UR_ERROR;
    }

    return ubjs_processor_top_selected_factory_ntype(this, ntype);
}

void ubjs_processor_array_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->parser->debug_f)
        {
            (this->parser->debug_f)(this->parser->userdata, 46,
                "ubjs_processor_array_got_control: have present");
        }
#endif
        /* LCOV_EXCL_STOP */

        if (0 == data->array)
        {
            /* LCOV_EXCL_START */
#ifndef NDEBUG
            if (0 != this->parser->debug_f)
            {
                (this->parser->debug_f)(this->parser->userdata, 54,
                    "ubjs_processor_array_got_control: lazily build array");
            }
#endif
            /* LCOV_EXCL_STOP */

            ubjs_prmtv_array(this->parser->lib, &(data->array));
        }

        ubjs_prmtv_array_add_last(data->array, present);
        data->real_length++;

        if (UTRUE == data->have_length &&
            data->real_length == data->length)
        {
            /* LCOV_EXCL_START */
#ifndef NDEBUG
            if (0 != this->parser->debug_f)
            {
                (this->parser->debug_f)(this->parser->userdata, 37,
                    "ubjs_processor_array_got_control: end");
            }
#endif
            /* LCOV_EXCL_STOP */

            ubjs_processor_array_child_produced_end(this);
            return;
        }
    }

    if (UTRUE == data->have_type)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->parser->debug_f)
        {
            (this->parser->debug_f)(this->parser->userdata, 44,
                "ubjs_processor_array_got_control: next typed");
        }
#endif
        /* LCOV_EXCL_STOP */

        if (0 != data->type_create)
        {
            (data->type_create)(this, &nxt);
        }
        else
        {
             ubjs_processor_ntype(this, data->ntype, &nxt);
        }
        ubjs_parser_give_control(this->parser, nxt, 0);
        return;
    }

    if (UTRUE == data->have_length)
    {
        ubjs_processor_next_object(this,
            this->parser->ntypes_array_optimized, ubjs_processor_top_selected_factory_ntype,
            this->parser->factories_array_optimized,
            ubjs_processor_top_selected_factory, &nxt);
    }
    else
    {
        if (0 == data->real_length)
        {
            ubjs_processor_next_object(this,
                this->parser->ntypes_array_unoptimized_first,
                ubjs_processor_array_selected_factory_ntype,
                this->parser->factories_array_unoptimized_first,
                ubjs_processor_array_selected_factory, &nxt);
        }
        else
        {
            ubjs_processor_next_object(this,
                this->parser->ntypes_array_unoptimized,
                ubjs_processor_array_selected_factory_ntype,
                this->parser->factories_array_unoptimized,
                ubjs_processor_array_selected_factory, &nxt);
        }
    }
    ubjs_parser_give_control(this->parser, nxt, 0);
}

void ubjs_processor_array_child_produced_end(ubjs_processor *this)
{
    ubjs_userdata_array *data;
    data=(ubjs_userdata_array *)this->userdata;

    if (0 == data->array)
    {
        ubjs_prmtv_array(this->parser->lib, &(data->array));
    }

    ubjs_parser_down_recursion_level(this->parser);
    ubjs_parser_give_control(this->parser, this->parent, data->array);
    data->array=0;
    (this->free)(this);
}

void ubjs_processor_array_end_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_processor_array_child_produced_end(this->parent);
    (this->free)(this);
}

void ubjs_processor_array_count_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    if (0 == present)
    {
        ubjs_processor_ints(this);
        return;
    }

    unsigned int length = 0;
    ubjs_processor *parent = this->parent;
    ubjs_userdata_array *data;

    if (UR_ERROR == ubjs_processor_child_produced_length(this, present, &length))
    {
        return;
    }

    if (this->parser->limit_container_length > 0 &&
        this->parser->limit_container_length < length)
    {
        ubjs_parser_emit_error(this->parser, 33,
            "Reached limit of container length");
        return;
    }

    data = (ubjs_userdata_array *)parent->userdata;
    data->have_length = UTRUE;
    data->length=length;

    if (UTRUE == data->have_type)
    {
        ubjs_prmtv_array_with_length(this->parser->lib, data->length,
            &(data->array));
    }
    else
    {
        ubjs_prmtv_array_with_length(this->parser->lib, data->length, &(data->array));
    }

    if (0 == length)
    {
        ubjs_processor_array_child_produced_end(parent);
    }
    else
    {
        ubjs_parser_give_control(this->parser, parent, 0);
    }

    (this->free)(this);
}

void ubjs_processor_array_free(ubjs_processor *this)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;

    ubjs_prmtv_free(&(data->array));
    (this->parser->lib->free_f)(data);
    (this->parser->lib->free_f)(this);
}

ubjs_result ubjs_processor_object(ubjs_processor *parent, ubjs_processor **pthis)
{
    if (UR_ERROR == ubjs_parser_up_recursion_level(parent->parser))
    {
        return UR_ERROR;
    }

    ubjs_processor *this;
    ubjs_userdata_object *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_object *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_userdata_object));
    data->object=0;
    data->real_length=0;
    data->have_length=UFALSE;
    data->length=-1;
    data->have_type=UFALSE;
    data->type_create=0;
    data->ntype=0;

    data->key_length=0;
    data->key=0;
    data->state=WANT_KEY_LENGTH;
    this->name = "object";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_object_got_control;
    this->free=ubjs_processor_object_free;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_object_end(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "object end";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=ubjs_processor_object_end_got_control;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_object_count(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "optimized by count";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=ubjs_processor_object_count_got_control;
    this->read_byte=0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_object_type_selected_factory(ubjs_processor *this,
    ubjs_processor_factory_create create)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;
    ubjs_processor *next;

    data->have_type=UTRUE;
    data->type_create = create;
    data->ntype=0;

    ubjs_processor_next_object(this,
        this->parser->ntypes_object_type,
        ubjs_processor_top_selected_factory_ntype,
        this->parser->factories_object_type,
        ubjs_processor_top_selected_factory, &next);
    ubjs_parser_give_control(this->parser, next, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_object_type_selected_factory_ntype(ubjs_processor *this,
    ubjs_prmtv_ntype *ntype)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;
    ubjs_processor *next;

    data->have_type=UTRUE;
    data->type_create = 0;
    data->ntype=ntype;

    ubjs_processor_next_object(this,
        this->parser->ntypes_object_type,
        ubjs_processor_top_selected_factory_ntype,
        this->parser->factories_object_type,
        ubjs_processor_top_selected_factory, &next);
    ubjs_parser_give_control(this->parser, next, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_object_type(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_processor_next_object(parent,
        parent->parser->ntypes_top,
        ubjs_processor_object_type_selected_factory_ntype,
        parent->parser->factories_top,
        ubjs_processor_object_type_selected_factory, &this);
    *pthis = this;
    ubjs_parser_give_control(this->parser, this, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_object_selected_factory(ubjs_processor *this,
    ubjs_processor_factory_create create)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;

    if (this->parser->limit_container_length > 0 &&
        create != ubjs_processor_object_end &&
        this->parser->limit_container_length <= data->real_length)
    {
        ubjs_parser_emit_error(this->parser, 33,
            "Reached limit of container length");
        return UR_ERROR;
    }

    return ubjs_processor_top_selected_factory(this, create);
}

ubjs_result ubjs_processor_object_selected_factory_ntype(ubjs_processor *this,
    ubjs_prmtv_ntype *ntype)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;

    if (this->parser->limit_container_length > 0 &&
/*        create != ubjs_processor_object_end && */
        this->parser->limit_container_length <= data->real_length)
    {
        ubjs_parser_emit_error(this->parser, 33,
            "Reached limit of container length");
        return UR_ERROR;
    }

    return ubjs_processor_top_selected_factory_ntype(this, ntype);
}

void ubjs_processor_object_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        switch (data->state)
        {
        case WANT_KEY_LENGTH:
            data->state=WANT_KEY;
            ubjs_processor_str(this, &nxt);
            ubjs_parser_give_control(this->parser, nxt, present);
            return;

        case WANT_KEY:
            ubjs_prmtv_str_get_length(present, &(data->key_length));
            data->key=(char *)(this->parser->lib->alloc_f)(sizeof(char)*(data->key_length));
            ubjs_prmtv_str_copy_text(present, data->key);
            ubjs_prmtv_free(&present);
            data->state=WANT_VALUE;
            break;

        case WANT_VALUE:
            if (0 == data->object)
            {
                ubjs_prmtv_object(this->parser->lib, &(data->object));
            }

            ubjs_prmtv_object_set(data->object, data->key_length, data->key, present);
            (this->parser->lib->free_f)(data->key);
            data->key=0;
            data->key_length=0;
            data->state=WANT_KEY_LENGTH;
            data->real_length++;

            if (UTRUE == data->have_length)
            {
                if (data->real_length == data->length)
                {
                    ubjs_processor_object_child_produced_end(this);
                    return;
                }
            }
            break;
        }
    }

    switch (data->state)
    {
    case WANT_KEY_LENGTH:
        if (UTRUE == data->have_length)
        {
            ubjs_processor_next_object(this,
                this->parser->ntypes_object_optimized,
                ubjs_processor_top_selected_factory_ntype,
                this->parser->factories_object_optimized,
                ubjs_processor_top_selected_factory, &nxt);
        }
        else
        {
            if (0 == data->real_length)
            {
                ubjs_processor_next_object(this,
                    this->parser->ntypes_object_unoptimized_first,
                    ubjs_processor_object_selected_factory_ntype,
                    this->parser->factories_object_unoptimized_first,
                    ubjs_processor_object_selected_factory, &nxt);
            }
            else
            {
                ubjs_processor_next_object(this,
                    this->parser->ntypes_object_unoptimized,
                    ubjs_processor_object_selected_factory_ntype,
                    this->parser->factories_object_unoptimized,
                    ubjs_processor_object_selected_factory, &nxt);
            }
        }
        break;

    case WANT_VALUE:
        if (UTRUE == data->have_type)
        {
            if (0 != data->type_create)
            {
                (data->type_create)(this, &nxt);
            }
            else
            {
                 ubjs_processor_ntype(this, data->ntype, &nxt);
            }
        }
        else
        {
            ubjs_processor_next_object(this,
                this->parser->ntypes_top,
                ubjs_processor_top_selected_factory_ntype,
                this->parser->factories_top,
                ubjs_processor_top_selected_factory, &nxt);
        }
        break;
    default:
        break;
    }

    ubjs_parser_give_control(this->parser, nxt, 0);
}

void ubjs_processor_object_child_produced_end(ubjs_processor *this)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;

    if (0 == data->object)
    {
        ubjs_prmtv_object(this->parser->lib, &(data->object));
    }

    ubjs_parser_down_recursion_level(this->parser);
    ubjs_parser_give_control(this->parser, this->parent, data->object);
    data->object=0;
    (this->free)(this);
}

void ubjs_processor_object_end_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_processor_object_child_produced_end(this->parent);
    (this->free)(this);
}

void ubjs_processor_object_count_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    if (0 == present)
    {
        ubjs_processor_ints(this);
        return;
    }

    unsigned int length = 0;
    ubjs_processor *parent = this->parent;
    ubjs_userdata_object *data;

    if (UR_ERROR == ubjs_processor_child_produced_length(this, present, &length))
    {
        return;
    }

    if (this->parser->limit_container_length > 0 &&
        this->parser->limit_container_length < length)
    {
        ubjs_parser_emit_error(this->parser, 33, "Reached limit of container length");
        return;
    }

    data = (ubjs_userdata_object *)parent->userdata;
    data->have_length = UTRUE;
    data->length=length;

    if (UTRUE == data->have_type)
    {
        ubjs_prmtv_object_with_length(this->parser->lib, data->length,
            &(data->object));
    }
    else
    {
        ubjs_prmtv_object_with_length(this->parser->lib, data->length, &(data->object));
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->parser->debug_f)
    {
        char *message = 0;
        unsigned int len = 0;

        ubjs_compact_sprints(this->parser->lib, &message, &len, 7, "length ");
        ubjs_compact_sprintui(this->parser->lib, &message, &len, length);

        (this->parser->debug_f)(this->parser->userdata, len, message);
        (this->parser->lib->free_f)(message);
    }
#endif
    /* LCOV_EXCL_STOP */

    if (0 == length)
    {
        ubjs_processor_object_child_produced_end(parent);
    }
    else
    {
        ubjs_parser_give_control(this->parser, parent, 0);
    }

    (this->free)(this);
}

void ubjs_processor_object_free(ubjs_processor *this)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;

    ubjs_prmtv_free(&(data->object));
    (this->parser->lib->free_f)(data->key);
    (this->parser->lib->free_f)(data);
    (this->parser->lib->free_f)(this);
}
