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

#include "ubjs_primitive_noop_prv.h"

ubjs_result ubjs_parser_builder_new(ubjs_library *lib, ubjs_parser_builder **pthis)
{
    ubjs_parser_builder *this = 0;
    if (0 == lib || 0 == pthis)
    {
        return UR_ERROR;
    }

    this = (ubjs_parser_builder *)(lib->alloc_f)(sizeof(struct ubjs_parser_builder));
    this->lib = lib;
    this->userdata = 0;
    this->parsed_f = 0;
    this->error_f = 0;
    this->free_f = 0;
    this->debug_f = 0;
    this->limit_bytes_since_last_callback = 0;
    this->limit_container_length = 0;
    this->limit_string_length = 0;
    this->limit_recursion_level = 0;
    this->silently_ignore_toplevel_noops = UFALSE;

    *pthis = this;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_free(ubjs_parser_builder **pthis)
{
    ubjs_parser_builder *this = 0;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;
    (this->lib->free_f)(this);
    *pthis = 0;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_userdata(ubjs_parser_builder *this, void *value)
{
    if (0 == this || 0 == value)
    {
        return UR_ERROR;
    }

    this->userdata = value;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_parsed_f(ubjs_parser_builder *this,
    ubjs_parser_parsed_f parsed_f)
{
    if (0 == this || 0 == parsed_f)
    {
        return UR_ERROR;
    }

    this->parsed_f = parsed_f;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_error_f(ubjs_parser_builder *this,
    ubjs_parser_error_f error_f)
{
    if (0 == this || 0 == error_f)
    {
        return UR_ERROR;
    }

    this->error_f = error_f;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_debug_f(ubjs_parser_builder *this,
    ubjs_parser_debug_f debug_f)
{
    if (0 == this || 0 == debug_f)
    {
        return UR_ERROR;
    }

    this->debug_f = debug_f;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_free_f(ubjs_parser_builder *this,
    ubjs_parser_free_f free_f)
{
    if (0 == this || 0 == free_f)
    {
        return UR_ERROR;
    }

    this->free_f = free_f;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_limit_bytes_since_last_callback(ubjs_parser_builder *this,
    unsigned int value)
{
    if (0 == this || 0 == value)
    {
        return UR_ERROR;
    }

    this->limit_bytes_since_last_callback = value;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_limit_container_length(ubjs_parser_builder *this,
    unsigned int value)
{
    if (0 == this || 0 == value)
    {
        return UR_ERROR;
    }

    this->limit_container_length = value;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_limit_string_length(ubjs_parser_builder *this,
    unsigned int value)
{
    if (0 == this || 0 == value)
    {
        return UR_ERROR;
    }

    this->limit_string_length = value;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_limit_recursion_level(ubjs_parser_builder *this,
    unsigned int value)
{
    if (0 == this || 0 == value)
    {
        return UR_ERROR;
    }

    this->limit_recursion_level = value;
    return UR_OK;
}

ubjs_result ubjs_parser_builder_set_silently_ignore_toplevel_noops(ubjs_parser_builder *this,
    ubjs_bool value)
{
    if (0 == this)
    {
        return UR_ERROR;
    }

    this->silently_ignore_toplevel_noops = value;
    return UR_OK;
}

ubjs_result ubjs_parser_error_new(ubjs_library *lib, char *message,
    unsigned int len, ubjs_parser_error **pthis)
{
    ubjs_parser_error *this;

    this=(ubjs_parser_error *)(lib->alloc_f)(sizeof(struct ubjs_parser_error));
    this->lib=lib;

    this->message = (char *)(lib->alloc_f)(sizeof(char) * len);
    strncpy(this->message, message, len);
    this->message_length=len;

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_parser_error_free(ubjs_parser_error **pthis)
{
    ubjs_parser_error *this;

    this=*pthis;
    (this->lib->free_f)(this->message);
    (this->lib->free_f)(this);

    *pthis=0;
    return UR_OK;
}

ubjs_result ubjs_parser_error_get_message_length(ubjs_parser_error *this, unsigned int *length)
{
    if (0 == this || 0 == length)
    {
        return UR_ERROR;
    }

    *length=this->message_length;
    return UR_OK;
}

ubjs_result ubjs_parser_error_get_message_text(ubjs_parser_error *this, char *message)
{
    if (0 == this || 0 == message)
    {
        return UR_ERROR;
    }

    strncpy(message, this->message, this->message_length);
    return UR_OK;
}

ubjs_processor_factory ubjs_processor_factory_float32 = {MARKER_FLOAT32, ubjs_processor_float32};
ubjs_processor_factory ubjs_processor_factory_float64 = {MARKER_FLOAT64, ubjs_processor_float64};
ubjs_processor_factory ubjs_processor_factory_char = {MARKER_CHAR, ubjs_processor_char};
ubjs_processor_factory ubjs_processor_factory_str = {MARKER_STR, ubjs_processor_str};
ubjs_processor_factory ubjs_processor_factory_hpn = {MARKER_HPN, ubjs_processor_hpn};
ubjs_processor_factory ubjs_processor_factory_array = {MARKER_ARRAY_BEGIN, ubjs_processor_array};
ubjs_processor_factory ubjs_processor_factory_array_end = \
    {MARKER_ARRAY_END, ubjs_processor_array_end};
ubjs_processor_factory ubjs_processor_factory_array_type = \
    {MARKER_OPTIMIZE_TYPE, ubjs_processor_array_type};
ubjs_processor_factory ubjs_processor_factory_array_count = \
    {MARKER_OPTIMIZE_COUNT, ubjs_processor_array_count};
ubjs_processor_factory ubjs_processor_factory_object = {MARKER_OBJECT_BEGIN, ubjs_processor_object};
ubjs_processor_factory ubjs_processor_factory_object_end = \
    {MARKER_OBJECT_END, ubjs_processor_object_end};
ubjs_processor_factory ubjs_processor_factory_object_type = \
    {MARKER_OPTIMIZE_TYPE, ubjs_processor_object_type};
ubjs_processor_factory ubjs_processor_factory_object_count = \
    {MARKER_OPTIMIZE_COUNT, ubjs_processor_object_count};

void __no_free(void *unused)
{
}

void ubjs_parser_configure_factories(ubjs_parser *this)
{
    ubjs_glue_array_builder *glue_builder;
    unsigned int i;

    this->ntypes_top = 0;
    this->ntypes_int = 0;
    this->ntypes_array_type = 0;
    this->ntypes_array_optimized = 0;
    this->ntypes_array_unoptimized = 0;
    this->ntypes_array_unoptimized_first = 0;
    this->ntypes_object_type = 0;
    this->ntypes_object_optimized = 0;
    this->ntypes_object_unoptimized = 0;
    this->ntypes_object_unoptimized_first = 0;

    this->factories_top = 0;
    this->factories_array_type = 0;
    this->factories_array_optimized = 0;
    this->factories_array_unoptimized = 0;
    this->factories_array_unoptimized_first = 0;
    this->factories_object_type = 0;
    this->factories_object_optimized = 0;
    this->factories_object_unoptimized = 0;
    this->factories_object_unoptimized_first = 0;

    ubjs_glue_array_array_builder_new(this->lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, __no_free);

    (glue_builder->build_f)(glue_builder, &(this->ntypes_top));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_array_unoptimized));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_array_unoptimized_first));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_array_type));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_array_optimized));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_object_unoptimized));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_object_unoptimized_first));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_object_type));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_object_optimized));
    (glue_builder->build_f)(glue_builder, &(this->ntypes_int));

    (glue_builder->build_f)(glue_builder, &(this->factories_top));
    (glue_builder->build_f)(glue_builder, &(this->factories_array_unoptimized));
    (glue_builder->build_f)(glue_builder, &(this->factories_array_unoptimized_first));
    (glue_builder->build_f)(glue_builder, &(this->factories_array_type));
    (glue_builder->build_f)(glue_builder, &(this->factories_array_optimized));
    (glue_builder->build_f)(glue_builder, &(this->factories_object_unoptimized));
    (glue_builder->build_f)(glue_builder, &(this->factories_object_unoptimized_first));
    (glue_builder->build_f)(glue_builder, &(this->factories_object_type));
    (glue_builder->build_f)(glue_builder, &(this->factories_object_optimized));

    (glue_builder->free_f)(&glue_builder);

    for (i = 0; i < ubjs_prmtv_ntypes_len; i++)
    {
        ubjs_prmtv_ntype *intype;
        intype = ubjs_prmtv_ntypes[i];

        (this->ntypes_top->add_last_f)(this->ntypes_top, intype);
        (this->ntypes_array_unoptimized->add_last_f)(this->ntypes_array_unoptimized, intype);
        (this->ntypes_array_unoptimized_first->add_last_f)(this->ntypes_array_unoptimized_first,
            intype);
        (this->ntypes_array_optimized->add_last_f)(this->ntypes_array_optimized, intype);

        if (0 != intype->new_from_int64_f)
        {
            (this->ntypes_object_unoptimized->add_last_f)(this->ntypes_object_unoptimized,
                intype);
            (this->ntypes_object_unoptimized_first->add_last_f)(
                 this->ntypes_object_unoptimized_first,
                intype);
            (this->ntypes_object_optimized->add_last_f)(this->ntypes_object_optimized,
                intype);
            (this->ntypes_int->add_last_f)(this->ntypes_int, intype);
        }
    }

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_float32);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_float32);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_float32);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_float32);
    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_float64);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_float64);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_float64);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_float64);
    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_char);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_char);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_char);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_char);
    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_str);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
         &ubjs_processor_factory_str);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_str);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_str);
    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_hpn);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_hpn);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_hpn);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_hpn);
    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_array);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_array);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_array);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_array);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_array_end);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_array_end);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_array_count);
    (this->factories_array_type->add_last_f)(this->factories_array_type,
        &ubjs_processor_factory_array_count);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_array_type);
    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_object);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_object);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_object);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_object);
    (this->factories_object_unoptimized->add_last_f)(this->factories_object_unoptimized,
        &ubjs_processor_factory_object_end);
    (this->factories_object_unoptimized_first->add_last_f)(this->factories_object_unoptimized_first,
        &ubjs_processor_factory_object_end);
    (this->factories_object_unoptimized_first->add_last_f)(this->factories_object_unoptimized_first,
        &ubjs_processor_factory_object_count);
    (this->factories_object_type->add_last_f)(this->factories_object_type,
        &ubjs_processor_factory_object_count);
    (this->factories_object_unoptimized_first->add_last_f)(this->factories_object_unoptimized_first,
        &ubjs_processor_factory_object_type);
}

ubjs_result ubjs_parser_builder_build(ubjs_parser_builder *builder, ubjs_parser **pthis)
{
    ubjs_parser *this;

    if (0 == builder || 0 == pthis || 0 == builder->parsed_f)
    {
        return UR_ERROR;
    }

    this = (ubjs_parser *)(builder->lib->alloc_f)(sizeof(struct ubjs_parser));
    this->lib = builder->lib;
    this->userdata = builder->userdata;
    this->parsed_f = builder->parsed_f;
    this->error_f = builder->error_f;
    this->debug_f = builder->debug_f;
    this->free_f = builder->free_f;
    this->limit_bytes_since_last_callback = builder->limit_bytes_since_last_callback;
    this->limit_container_length = builder->limit_container_length;
    this->limit_string_length = builder->limit_string_length;
    this->limit_recursion_level = builder->limit_recursion_level;
    this->silently_ignore_toplevel_noops = builder->silently_ignore_toplevel_noops;

    this->errors=0;
    this->counters.bytes_since_last_callback = 0;
    this->counters.recursion_level = 0;

    ubjs_parser_configure_factories(this);

    ubjs_selfemptying_list_new(this->lib,
        (ubjs_glue_value_free) ubjs_parser_give_control_request_free,
        ubjs_parser_give_control_fifo_callback,
        (void *)this, &(this->give_control_fifo));

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        (this->debug_f)(this->userdata, 13, "### ALIVE ###");
    }
#endif
    /* LCOV_EXCL_STOP */

    ubjs_processor_top(this);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_parser_free(ubjs_parser **pthis)
{
    ubjs_parser *this;
    ubjs_processor *processor;
    ubjs_processor *parent_processor;

    if (0 == pthis || 0 == *pthis)
    {
        return UR_ERROR;
    }

    this = *pthis;

    for (processor=this->processor; 0 != processor;)
    {
        parent_processor = processor->parent;
        (processor->free)(processor);
        processor=parent_processor;
    }

    ubjs_selfemptying_list_free(&(this->give_control_fifo));

    (this->ntypes_top->free_f)(&(this->ntypes_top));
    (this->ntypes_array_optimized->free_f)(&(this->ntypes_array_optimized));
    (this->ntypes_array_unoptimized->free_f)(&(this->ntypes_array_unoptimized));
    (this->ntypes_array_unoptimized_first->free_f)(&(this->ntypes_array_unoptimized_first));
    (this->ntypes_array_type->free_f)(&(this->ntypes_array_type));
    (this->ntypes_object_optimized->free_f)(&(this->ntypes_object_optimized));
    (this->ntypes_object_unoptimized->free_f)(&(this->ntypes_object_unoptimized));
    (this->ntypes_object_unoptimized_first->free_f)(&(this->ntypes_object_unoptimized_first));
    (this->ntypes_object_type->free_f)(&(this->ntypes_object_type));
    (this->ntypes_int->free_f)(&(this->ntypes_int));

    (this->factories_top->free_f)(&(this->factories_top));
    (this->factories_array_optimized->free_f)(&(this->factories_array_optimized));
    (this->factories_array_unoptimized->free_f)(&(this->factories_array_unoptimized));
    (this->factories_array_unoptimized_first->free_f)(&(this->factories_array_unoptimized_first));
    (this->factories_array_type->free_f)(&(this->factories_array_type));
    (this->factories_object_optimized->free_f)(&(this->factories_object_optimized));
    (this->factories_object_unoptimized->free_f)(&(this->factories_object_unoptimized));
    (this->factories_object_unoptimized_first->free_f)(&(this->factories_object_unoptimized_first));
    (this->factories_object_type->free_f)(&(this->factories_object_type));

    if (0 != this->free_f)
    {
        (this->free_f)(this->userdata);
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        (this->debug_f)(this->userdata, 15, "### D E A D ###");
    }
#endif
    /* LCOV_EXCL_STOP */

    (this->lib->free_f)(this);
    (*pthis)=0;

    return UR_OK;
}

ubjs_result ubjs_parser_get_userdata(ubjs_parser *this, void **puserdata)
{
    if (0 == this || 0 == puserdata)
    {
        return UR_ERROR;
    }

    *puserdata=this->userdata;
    return UR_OK;
}

ubjs_result ubjs_parser_parse(ubjs_parser *this, uint8_t *data, unsigned int length)
{
    unsigned int i;

    if (0 == this || 0 == data)
    {
        return UR_ERROR;
    }

    if (0 == length)
    {
        return UR_OK;
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        char *message = 0;
        unsigned int len = 0;
        ubjs_compact_sprints(this->lib, &message, &len, 20, "ubjs_parser_parse() ");
        ubjs_compact_sprintui(this->lib, &message, &len, length);
        ubjs_compact_sprints(this->lib, &message, &len, 6, " bytes");
        (this->debug_f)(this->userdata, len, message);
        (this->lib->free_f)(message);
    }
#endif
    /* LCOV_EXCL_STOP */

    for (i=0; i<length; i++)
    {
        this->errors=0;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->debug_f)
        {
            char *message = 0;
            unsigned int len = 0;
            ubjs_compact_sprints(this->lib, &message, &len, 21, "ubjs_parser_parser() ");
            ubjs_compact_sprintui(this->lib, &message, &len, i + 1);
            ubjs_compact_sprints(this->lib, &message, &len, 1, "/");
            ubjs_compact_sprintui(this->lib, &message, &len, length);
            ubjs_compact_sprints(this->lib, &message, &len, 14, " in processor ");
            ubjs_compact_sprints(this->lib, &message, &len, strlen(this->processor->name),
                this->processor->name);
            (this->debug_f)(this->userdata, len, message);
            (this->lib->free_f)(message);
        }
#endif

        if (0 == this->processor->read_byte)
        {
            ubjs_parser_emit_error(this, 39,
                "Unexpected data cause parser corruption");
            return UR_ERROR;
        }
        /* LCOV_EXCL_STOP */

        (this->processor->read_byte)(this->processor, i, data[i]);
        if (0 < this->errors)
        {
            return UR_ERROR;
        }

        if (this->limit_bytes_since_last_callback > 0)
        {
            this->counters.bytes_since_last_callback++;

            /* LCOV_EXCL_START */
#ifndef NDEBUG
            if (0 != this->debug_f)
            {
                char *message = 0;
                unsigned int len = 0;
                ubjs_compact_sprints(this->lib, &message, &len, 47,
                    "ubjs_parser_parse() bytes since last callback: ");
                ubjs_compact_sprintui(this->lib, &message, &len,
                    this->counters.bytes_since_last_callback);
                ubjs_compact_sprints(this->lib, &message, &len, 1, "/");
                ubjs_compact_sprintui(this->lib, &message, &len,
                    this->limit_bytes_since_last_callback);
                (this->debug_f)(this->userdata, len, message);
                (this->lib->free_f)(message);
            }
#endif
           /* LCOV_EXCL_STOP */

            if (this->limit_bytes_since_last_callback <=
                this->counters.bytes_since_last_callback)
            {
                ubjs_parser_emit_error(this, 42, "Reached limit of bytes since last callback");
                return UR_ERROR;
            }
        }
    }

    return UR_OK;
}

ubjs_result ubjs_parser_up_recursion_level(ubjs_parser *this)
{
    if (this->limit_recursion_level > 0)
    {
        this->counters.recursion_level++;

        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->debug_f)
        {
            char *message = 0;
            unsigned int len = 0;
            ubjs_compact_sprints(this->lib, &message, &len, 50,
                "ubjs_parser_up_recursion_level() recursion level: ");
            ubjs_compact_sprintui(this->lib, &message, &len, this->counters.recursion_level);
            ubjs_compact_sprints(this->lib, &message, &len, 1, "/");
            ubjs_compact_sprintui(this->lib, &message, &len, this->limit_recursion_level);
            (this->debug_f)(this->userdata, len, message);
            (this->lib->free_f)(message);
        }
#endif
        /* LCOV_EXCL_STOP */

        if (this->limit_recursion_level < this->counters.recursion_level)
        {
            ubjs_parser_emit_error(this, 32, "Reached limit of recursion level");
            return UR_ERROR;
        }
    }
    return UR_OK;
}

ubjs_result ubjs_parser_down_recursion_level(ubjs_parser *this)
{
    if (this->limit_recursion_level > 0)
    {
        this->counters.recursion_level--;

        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (0 != this->debug_f)
        {
            char *message = 0;
            unsigned int len = 0;
            ubjs_compact_sprints(this->lib, &message, &len, 52,
                "ubjs_parser_down_recursion_level() recursion level: ");
            ubjs_compact_sprintui(this->lib, &message, &len, this->counters.recursion_level);
            ubjs_compact_sprints(this->lib, &message, &len, 1, "/");
            ubjs_compact_sprintui(this->lib, &message, &len, this->limit_recursion_level);
            (this->debug_f)(this->userdata, len, message);
            (this->lib->free_f)(message);
        }
#endif
        /* LCOV_EXCL_STOP */
    }
    return UR_OK;
}

void ubjs_parser_give_control_request_free(ubjs_parser_give_control_request *this)
{
    (this->lib->free_f)(this);
}

void ubjs_parser_give_control_fifo_callback(ubjs_selfemptying_list *this, void *obj)
{
    ubjs_parser_give_control_request *robj = (ubjs_parser_give_control_request *)obj;
    ubjs_parser *parser = (ubjs_parser *)this->userdata;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != parser->debug_f)
    {
        char *message = 0;
        unsigned int len = 0;

        ubjs_compact_sprints(parser->lib, &message, &len, 44,
            "ubjs_parser_give_control_fifo_callback() to ");
        ubjs_compact_sprints(parser->lib, &message, &len, strlen(robj->processor->name),
           robj->processor->name);

        if (0 != robj->present)
        {
            char *dtext = 0;
            unsigned int dlen = 0;

            ubjs_prmtv_debug_string_get_length(robj->present, &dlen);
            dtext = (char *)(parser->lib->alloc_f)(sizeof(char) * (dlen + 1));
            ubjs_prmtv_debug_string_copy(robj->present, dtext);

            ubjs_compact_sprints(parser->lib, &message, &len, 15,
                ", with present ");
            ubjs_compact_sprints(parser->lib, &message, &len, dlen, dtext);
            (parser->lib->free_f)(dtext);
        }

        (parser->debug_f)(parser->userdata, len, message);
        (this->lib->free_f)(message);
    }
#endif
    /* LCOV_EXCL_STOP */

    parser->processor=robj->processor;
    if (0 != robj->processor->got_control)
    {
        (robj->processor->got_control)(robj->processor, robj->present);
    }
}

void ubjs_parser_give_control(ubjs_parser *this, ubjs_processor *processor,
    ubjs_prmtv *present)
{
    ubjs_parser_give_control_request *obj;

#ifndef NDEBUG
    ubjs_bool was_noop = UFALSE;
#endif

    obj = (ubjs_parser_give_control_request *)(this->lib->alloc_f)(
        sizeof(struct ubjs_parser_give_control_request));
    obj->processor=processor;
    obj->present=present;
    obj->lib=this->lib;

    if (0 != obj->present && UTRUE == this->silently_ignore_toplevel_noops)
    {
        ubjs_prmtv_ntype *ntype = 0;
        ubjs_prmtv_get_ntype(obj->present, &ntype);
        if (&ubjs_prmtv_noop_ntype == ntype)
        {
            ubjs_prmtv_free(&(obj->present));

#ifndef NDEBUG
            was_noop = UTRUE;
#endif
        }
    }

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        char *message = 0;
        unsigned int len = 0;

        ubjs_compact_sprints(this->lib, &message, &len, 30,
            "ubjs_parser_give_control() to ");
        ubjs_compact_sprints(this->lib, &message, &len, strlen(processor->name),
            processor->name);

        if (0 != obj->present)
        {
            char *dtext = 0;
            unsigned int dlen = 0;

            ubjs_prmtv_debug_string_get_length(obj->present, &dlen);
            dtext = (char *)(this->lib->alloc_f)(sizeof(char) * (dlen + 1));
            ubjs_prmtv_debug_string_copy(obj->present, dtext);

            ubjs_compact_sprints(this->lib, &message, &len, 15,
                ", with present ");
            ubjs_compact_sprints(this->lib, &message, &len, dlen, dtext);
            (this->lib->free_f)(dtext);
        }
        else if (UTRUE == was_noop)
        {
            ubjs_compact_sprints(this->lib, &message, &len, 23,
                ", present ignored: NOOP");
        }

        (this->debug_f)(this->userdata, len, message);
        (this->lib->free_f)(message);
    }
#endif
    /* LCOV_EXCL_STOP */

    ubjs_selfemptying_list_add(this->give_control_fifo, obj);
}

void ubjs_parser_emit_error(ubjs_parser *this, unsigned int len, char *message)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->debug_f)
    {
        char *message2 = 0;
        unsigned int len2 = 0;

        ubjs_compact_sprints(this->lib, &message2, &len2, 25, "ubjs_parser_emit_error() ");
        ubjs_compact_sprints(this->lib, &message2, &len2, len, message);

        (this->debug_f)(this->userdata, len2, message2);
        (this->lib->free_f)(message2);
    }
#endif
    /* LCOV_EXCL_STOP */

    if (0 != this->error_f)
    {
        ubjs_parser_error *error;
        ubjs_parser_error_new(this->lib, message, len, &error);
        (this->error_f)(this->userdata, error);
        ubjs_parser_error_free(&error);
    }

    this->errors += 1;
}

void ubjs_processor_top(ubjs_parser *parser)
{
    ubjs_processor *this;

    this = (ubjs_processor *)(parser->lib->alloc_f)(
        sizeof(struct ubjs_processor));
    this->name = "top";
    this->parent=0;
    this->userdata=0;
    this->parser=parser;
    this->got_control=ubjs_processor_top_got_control;
    this->read_byte = 0;
    this->free=(ubjs_processor_free)(parser->lib->free_f);
    parser->processor = this;

    /* Always processor_top, they have control */
    ubjs_parser_give_control(this->parser, this, 0);
}

ubjs_result ubjs_processor_top_selected_factory(ubjs_processor *this,
    ubjs_processor_factory_create create)
{
    ubjs_processor *next = 0;
    if (UR_ERROR == (create)(this, &next))
    {
        return UR_ERROR;
    }

    ubjs_parser_give_control(this->parser, next, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_top_selected_factory_ntype(ubjs_processor *this,
    ubjs_prmtv_ntype *ntype)
{
    ubjs_processor *next = 0;
    if (UR_ERROR == ubjs_processor_ntype(this, ntype, &next))
    {
        return UR_ERROR;
    }

    ubjs_parser_give_control(this->parser, next, 0);
    return UR_OK;
}

void ubjs_processor_top_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        (this->parser->parsed_f)(this->parser->userdata, present);
        this->parser->counters.bytes_since_last_callback = 0;
    }

    ubjs_processor_next_object(this,
        this->parser->ntypes_top, ubjs_processor_top_selected_factory_ntype,
        this->parser->factories_top,
        ubjs_processor_top_selected_factory, &nxt);
    ubjs_parser_give_control(this->parser, nxt, 0);
}

void ubjs_processor_ints(ubjs_processor *this)
{
    ubjs_processor *nxt = 0;
    ubjs_processor_next_object(this,
        this->parser->ntypes_int, ubjs_processor_top_selected_factory_ntype,
        0, 0, &nxt);
    ubjs_parser_give_control(this->parser, nxt, 0);
}

ubjs_result ubjs_processor_next_object(ubjs_processor *parent,
    ubjs_glue_array *ntypes,
    ubjs_processor_next_object_selected_factory_ntype selected_factory_ntype,
    ubjs_glue_array *factories,
    ubjs_processor_next_object_selected_factory selected_factory, ubjs_processor **pthis)
{
    ubjs_processor_next_objext *this;
    unsigned int ntypes_len = 0;
    unsigned int factories_len = 0;
    char name[48];
    unsigned int name_len;
    char *name_template = "next object from %u ntypes and %u factories";

    (ntypes->get_length_f)(ntypes, &ntypes_len);
    if (0 != factories)
    {
        (factories->get_length_f)(factories, &factories_len);
    }
    name_len = sprintf(name, name_template, ntypes_len, factories_len);

    this = (ubjs_processor_next_objext *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_processor_next_objext));

    this->super.name = (char *)(parent->parser->lib->alloc_f)(sizeof(char) * (name_len + 1));
    memcpy(this->super.name, name, name_len + 1);

    this->super.parent=parent;
    this->super.parser=parent->parser;
    this->super.userdata=0;
    this->super.got_control=0;
    this->super.read_byte = ubjs_processor_next_object_read_byte;
    this->super.free=ubjs_processor_next_object_free;
    this->ntypes=ntypes;
    this->factories=factories;
    this->selected_factory_ntype=selected_factory_ntype;
    this->selected_factory=selected_factory;

    *pthis=(ubjs_processor *)this;
    return UR_OK;
}

void ubjs_processor_next_object_free(ubjs_processor *this)
{
    (this->parser->lib->free_f)(this->name);
    (this->parser->lib->free_f)(this);
}

void ubjs_processor_next_object_read_byte(ubjs_processor *this, unsigned int pos,
    uint8_t c)
{
    ubjs_processor_next_objext *sub=(ubjs_processor_next_objext *)this;

    char *message = 0;
    unsigned int message_length = 0;
    ubjs_glue_array_iterator *it = 0;

    (sub->ntypes->iterate_f)(sub->ntypes, &it);
    while (UR_OK == (it->next_f)(it))
    {
        ubjs_prmtv_ntype *ntype = 0;
        (it->get_f)(it, (void **)&ntype);

        if (ntype->marker == c)
        {
            ubjs_result ret = (sub->selected_factory_ntype)(this->parent, ntype);
            if (UR_OK == ret)
            {
                (this->free)(this);
            }
            (it->free_f)(&it);
            return;
        }
    }
    (it->free_f)(&it);

    if (0 != sub->factories)
    {
        (sub->factories->iterate_f)(sub->factories, &it);
        while (UR_OK == (it->next_f)(it))
        {
            ubjs_processor_factory *pf = 0;
            (it->get_f)(it, (void **)&pf);

            if (pf->marker == c)
            {
                ubjs_result ret = (sub->selected_factory)(this->parent, pf->create);
                if (UR_OK == ret)
                {
                    (this->free)(this);
                }
                (it->free_f)(&it);
                return;
            }
        }
        (it->free_f)(&it);
    }

    ubjs_compact_sprints(this->parser->lib, &message, &message_length, 3, "At ");
    ubjs_compact_sprintui(this->parser->lib, &message, &message_length, pos);
    ubjs_compact_sprints(this->parser->lib, &message, &message_length, 2, " [");
    ubjs_compact_sprintui(this->parser->lib, &message, &message_length, c);
    ubjs_compact_sprints(this->parser->lib, &message, &message_length, 16, "] unknown marker");

    ubjs_parser_emit_error(this->parser, message_length, message);
    (this->parser->lib->free_f)(message);
}

ubjs_result ubjs_processor_child_produced_length(ubjs_processor *this, ubjs_prmtv *obj,
    unsigned int *plength)
{
    int64_t v64 = -1;
    unsigned int length = 0;

    ubjs_prmtv_int_get(obj, &v64);
    ubjs_prmtv_free(&obj);

    if (0 > v64)
    {
        char *message = "Got negative length";
        ubjs_parser_emit_error(this->parser, (unsigned int)strlen(message), message);
        return UR_ERROR;
    }

    /* Yeah, we blindly downcast 64 to 32bit.
       This should be level up, that we ignore all int64-s. */
    length = (unsigned int) v64;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 != this->parser->debug_f)
    {
        char *message2 = 0;
        unsigned int len2 = 0;

        ubjs_compact_sprints(this->parser->lib, &message2, &len2, 39,
            "ubjs_processor_child_produced_length() ");
        ubjs_compact_sprintui(this->parser->lib, &message2, &len2, length);

        (this->parser->debug_f)(this->userdata, len2, message2);
        (this->parser->lib->free_f)(message2);
    }
#endif
    /* LCOV_EXCL_STOP */

    *plength = length;
    return UR_OK;
}
