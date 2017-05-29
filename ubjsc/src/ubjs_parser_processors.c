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
#include "ubjs_primitive_str.h"

ubjs_result ubjs_processor_ntype(ubjs_processor *parent, ubjs_prmtv_ntype *ntype,
    ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_ntype *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));

    data=(ubjs_userdata_ntype *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_userdata_ntype));
    data->ntype = ntype;
    data->glue.userdata = (void *)this;
    data->glue.parent = parent;
    data->glue.return_control_f = ubjs_processor_ntype_return_control;
    data->glue.want_marker_f = ubjs_processor_ntype_want_marker;
    data->glue.want_child_f = ubjs_processor_ntype_want_child;
    data->glue.debug_f = ubjs_processor_ntype_debug;
    data->glue.error_f = ubjs_processor_ntype_error;
    data->glue.limit_container_length = parent->parser->limit_container_length;
    data->glue.limit_string_length = parent->parser->limit_string_length;
    data->glue.limit_recursion_level = parent->parser->limit_recursion_level;
    data->glue.recursion_level = parent->recursion_level + 1;
    (ntype->parser_processor_new_f)(parent->parser->lib, &(data->glue), &(data->processor));

    this->name = data->processor->name;
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_ntype_got_control;
    this->read_byte = ubjs_processor_ntype_read_byte;
    this->free=ubjs_processor_ntype_free;
    this->recursion_level=parent->recursion_level + 1;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_ntype_got_control(ubjs_processor *this, ubjs_parser_give_control_request *req)
{
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this->userdata;
    ubjs_result go_on = UR_OK;

    {
        char *msg = 0;
        unsigned int len = 0;
        ubjs_compact_sprints(this->parser->lib, &msg, &len, 52,
            "ubjs_processor_ntype_got_control() before present: ");
        ubjs_compact_sprints(this->parser->lib, &msg, &len, strlen(this->name),
                this->name);
        ubjs_processor_ntype_debug(&(data->glue), len, msg);
        (this->parser->lib->free_f)(msg);

    }
    if (UR_ERROR == go_on)
    {
        return;
    }
    if (0 != req->present)
    {
        if (0 == data->ntype->parser_processor_got_present_f)
        {
            char *msg = 0;
            unsigned int len = 0;
            char *dtext = 0;
            unsigned int dlen = 0;
            ubjs_library_alloc_f alloc_f;

            ubjs_library_get_alloc_f(this->parser->lib, &alloc_f);

            ubjs_prmtv_debug_string_get_length(req->present, &dlen);
            dtext = (char *)(alloc_f)(sizeof(char) * (dlen + 1));
            ubjs_prmtv_debug_string_copy(req->present, dtext);

            ubjs_compact_sprints(this->parser->lib, &msg, &len, 22, "Got unexpected present ");
            ubjs_compact_sprints(this->parser->lib, &msg, &len, dlen, dtext);
            (this->parser->lib->free_f)(dtext);

            ubjs_compact_sprints(this->parser->lib, &msg, &len, 21, " in parser processor ");
            ubjs_compact_sprints(this->parser->lib, &msg, &len, strlen(this->name),
                this->name);
            ubjs_processor_ntype_error(&(data->glue), len, msg);
            (this->parser->lib->free_f)(msg);
        }
        else
        {
            go_on = (data->ntype->parser_processor_got_present_f)(data->processor, req->present);
        }
    }

    if (UR_ERROR == go_on)
    {
        return;
    }
    {
        char *msg = 0;
        unsigned int len = 0;
        ubjs_compact_sprints(this->parser->lib, &msg, &len, 51,
            "ubjs_processor_ntype_got_control() before marker: ");
        ubjs_compact_sprints(this->parser->lib, &msg, &len, strlen(this->name),
                this->name);
        ubjs_processor_ntype_debug(&(data->glue), len, msg);
        (this->parser->lib->free_f)(msg);

    }

    if (0 != req->marker)
    {
        if (0 == data->ntype->parser_processor_got_marker_f)
        {
            char *msg = 0;
            unsigned int len = 0;

            ubjs_compact_sprints(this->parser->lib, &msg, &len, 21, "Got unexpected marker ");
            ubjs_compact_sprintp(this->parser->lib, &msg, &len, (unsigned int *)req->marker);

            ubjs_compact_sprints(this->parser->lib, &msg, &len, 21, " in parser processor ");
            ubjs_compact_sprints(this->parser->lib, &msg, &len, strlen(this->name),
                this->name);
            ubjs_processor_ntype_error(&(data->glue), len, msg);
            (this->parser->lib->free_f)(msg);
        }
        else
        {
            go_on = (data->ntype->parser_processor_got_marker_f)(data->processor, req->marker);
        }
    }
    if (UR_ERROR == go_on)
    {
        return;
    }
    {
        char *msg = 0;
        unsigned int len = 0;
        ubjs_compact_sprints(this->parser->lib, &msg, &len, 52,
            "ubjs_processor_ntype_got_control() before control: ");
        ubjs_compact_sprints(this->parser->lib, &msg, &len, strlen(this->name),
                this->name);
        ubjs_processor_ntype_debug(&(data->glue), len, msg);
        (this->parser->lib->free_f)(msg);

    }
    if (UR_ERROR == go_on)
    {
        return;
    }

    (data->ntype->parser_processor_got_control_f)(data->processor);
}

void ubjs_processor_ntype_free(ubjs_processor *this)
{
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this->userdata;

    {
        char *msg = 0;
        unsigned int len = 0;
        ubjs_compact_sprints(this->parser->lib, &msg, &len, 29,
            "ubjs_processor_ntype_free(): ");
        ubjs_compact_sprints(this->parser->lib, &msg, &len, strlen(this->name),
                this->name);
        ubjs_processor_ntype_debug(&(data->glue), len, msg);
        (this->parser->lib->free_f)(msg);
    }

    (data->ntype->parser_processor_free_f)(&(data->processor));
    (this->parser->lib->free_f)(data);
    (this->parser->lib->free_f)(this);
}

void ubjs_processor_ntype_read_byte(ubjs_processor *this, unsigned int pos, uint8_t c)
{
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this->userdata;
    {
        char *msg = 0;
        unsigned int len = 0;
        ubjs_compact_sprints(this->parser->lib, &msg, &len, 52,
            "ubjs_processor_ntype_read_byte()  ");
        ubjs_compact_sprintui(this->parser->lib, &msg, &len, c);
        ubjs_processor_ntype_debug(&(data->glue), len, msg);
        (this->parser->lib->free_f)(msg);
    }

    (data->ntype->parser_processor_read_byte_f)(data->processor, c);
}

void ubjs_processor_ntype_return_control(ubjs_prmtv_ntype_parser_glue *this,
    void *present)
{
    ubjs_processor *this2 = (ubjs_processor *)this->userdata;
    ubjs_parser_give_control(this2->parser, this2->parent, present, 0);
    ubjs_processor_ntype_free(this2);
}

ubjs_result ubjs_processor_ntype_want_marker_selected_factory_ntype(ubjs_processor *this,
    ubjs_prmtv_ntype *ntype)
{
    ubjs_userdata_ntype *this2=(ubjs_userdata_ntype *)this->userdata;

    if (0 == this2->ntype->parser_processor_got_present_f)
    {
        char *msg = 0;
        unsigned int len = 0;
        ubjs_compact_sprints(this->parser->lib, &msg, &len, 22, "Got unexpected marker ");
        ubjs_compact_sprintui(this->parser->lib, &msg, &len, *((unsigned int *)ntype));
        ubjs_compact_sprints(this->parser->lib, &msg, &len, 21, " in parser processor ");
        ubjs_compact_sprints(this->parser->lib, &msg, &len, strlen(this->name),
            this->name);
        ubjs_processor_ntype_error(&(this2->glue), len, msg);
        (this->parser->lib->free_f)(msg);
        return UR_ERROR;
    }

    ubjs_parser_give_control(this->parser, this, 0, ntype);
    return UR_OK;
}

void ubjs_processor_ntype_want_marker(ubjs_prmtv_ntype_parser_glue *this,
    ubjs_glue_array *ntypes)
{
    ubjs_processor *this2 = (ubjs_processor *)this->userdata;
    ubjs_processor *nxt = 0;
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this2->userdata;

    if (0 == ntypes)
    {
        ntypes = this2->parser->ntypes_top;
    }

    ubjs_processor_ntype_debug(&(data->glue), 11, "Want marker");

    ubjs_processor_next_object(this2,
        ntypes,
        ubjs_processor_ntype_want_marker_selected_factory_ntype,
        0,
        0,
        &nxt);
    ubjs_parser_give_control(this2->parser, nxt, 0, 0);
}

void ubjs_processor_ntype_want_child(ubjs_prmtv_ntype_parser_glue *this,
    ubjs_prmtv_ntype *ntype)
{
    ubjs_processor *this2 = (ubjs_processor *)this->userdata;
    ubjs_userdata_ntype *data=(ubjs_userdata_ntype *)this2->userdata;

    ubjs_processor_ntype_debug(&(data->glue), 10, "Want child");
    ubjs_processor_top_selected_factory_ntype(this2, ntype);
}

void ubjs_processor_ntype_debug(ubjs_prmtv_ntype_parser_glue *this,
    unsigned int len, char *msg)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_processor *this2 = (ubjs_processor *)this->userdata;
    if (0 != this2->parser->debug_f)
    {
        char *msg2 = 0;
        unsigned int len2 = 0;

        ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 20, "In parser processor ");
        ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, strlen(this2->name),
            this2->name);
        ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 2, ": ");
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
    char *msg2 = 0;
    unsigned int len2 = 0;

    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 20, "In parser processor ");
    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, strlen(this2->name),
        this2->name);
    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, 2, ": ");
    ubjs_compact_sprints(this2->parser->lib, &msg2, &len2, len, msg);
    ubjs_parser_emit_error(this2->parser, len2, msg2);
    (this2->parser->lib->free_f)(msg2);
}

ubjs_result ubjs_processor_object(ubjs_processor *parent, ubjs_processor **pthis)
{
/*    if (UR_ERROR == ubjs_parser_up_recursion_level(parent->parser))
    {
        return UR_ERROR;
    }*/

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
    this->recursion_level = parent->recursion_level + 1;
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
    this->recursion_level = parent->recursion_level + 1;

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
    this->recursion_level = parent->recursion_level + 1;

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
    ubjs_parser_give_control(this->parser, next, 0, 0);
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
    ubjs_parser_give_control(this->parser, next, 0, 0);
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
    ubjs_parser_give_control(this->parser, this, 0, 0);
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

void ubjs_processor_object_got_control(ubjs_processor *this,
    ubjs_parser_give_control_request *req)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;
    ubjs_processor *nxt = 0;

    if (0 != req->present)
    {
        switch (data->state)
        {
        case WANT_KEY_LENGTH:
            data->state=WANT_KEY;
            ubjs_processor_ntype(this, &ubjs_prmtv_str_ntype, &nxt);
            ubjs_parser_give_control(this->parser, nxt, req->present, 0);
            return;

        case WANT_KEY:
            ubjs_prmtv_str_get_length(req->present, &(data->key_length));
            data->key=(char *)(this->parser->lib->alloc_f)(sizeof(char)*(data->key_length));
            ubjs_prmtv_str_copy_text(req->present, data->key);
            ubjs_prmtv_free(&req->present);
            data->state=WANT_VALUE;
            break;

        case WANT_VALUE:
            if (0 == data->object)
            {
                ubjs_prmtv_object(this->parser->lib, &(data->object));
            }

            ubjs_prmtv_object_set(data->object, data->key_length, data->key, req->present);
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

    ubjs_parser_give_control(this->parser, nxt, 0, 0);
}

void ubjs_processor_object_child_produced_end(ubjs_processor *this)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;

    if (0 == data->object)
    {
        ubjs_prmtv_object(this->parser->lib, &(data->object));
    }

    /*ubjs_parser_down_recursion_level(this->parser);*/
    ubjs_parser_give_control(this->parser, this->parent, data->object, 0);
    data->object=0;
    (this->free)(this);
}

void ubjs_processor_object_end_got_control(ubjs_processor *this,
    ubjs_parser_give_control_request *req)
{
    ubjs_processor_object_child_produced_end(this->parent);
    (this->free)(this);
}

void ubjs_processor_object_count_got_control(ubjs_processor *this,
    ubjs_parser_give_control_request *req)
{
    if (0 == req->present)
    {
        ubjs_processor_ints(this);
        return;
    }

    unsigned int length = 0;
    ubjs_processor *parent = this->parent;
    ubjs_userdata_object *data;

    if (UR_ERROR == ubjs_processor_child_produced_length(this, req->present, &length))
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
        ubjs_parser_give_control(this->parser, parent, 0, 0);
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
