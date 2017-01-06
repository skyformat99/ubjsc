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
#include "ubjs_primitives_prv.h"
#include "ubjs_glue_array_array.h"

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

ubjs_processor_factory ubjs_processor_factory_null = {MARKER_NULL, ubjs_processor_null};
ubjs_processor_factory ubjs_processor_factory_noop = {MARKER_NOOP, ubjs_processor_noop};
ubjs_processor_factory ubjs_processor_factory_true = {MARKER_TRUE, ubjs_processor_true};
ubjs_processor_factory ubjs_processor_factory_false = {MARKER_FALSE, ubjs_processor_false};
ubjs_processor_factory ubjs_processor_factory_int8 = {MARKER_INT8, ubjs_processor_int8};
ubjs_processor_factory ubjs_processor_factory_uint8 = {MARKER_UINT8, ubjs_processor_uint8};
ubjs_processor_factory ubjs_processor_factory_int16 = {MARKER_INT16, ubjs_processor_int16};
ubjs_processor_factory ubjs_processor_factory_int32 = {MARKER_INT32, ubjs_processor_int32};
ubjs_processor_factory ubjs_processor_factory_int64 = {MARKER_INT64, ubjs_processor_int64};
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

void ubjs_processor_factory_free(void *unused)
{
}

ubjs_result ubjs_parser_new(ubjs_library *lib, ubjs_parser_settings *settings,
    ubjs_parser_context *context, ubjs_parser **pthis)
{
    ubjs_parser *this;
    ubjs_glue_array_builder *glue_builder;

    if (0 == lib || 0 == pthis || 0 == context)
    {
        return UR_ERROR;
    }

    if (0 == context->parsed || 0 == context->free || 0 == context->error)
    {
        return UR_ERROR;
    }

    this = (ubjs_parser *)(lib->alloc_f)(sizeof(struct ubjs_parser));
    this->lib = lib;
    this->context = context;
    this->settings = settings;
    this->errors=0;
    this->counters.bytes_since_last_callback = 0;
    this->counters.recursion_level = 0;
    this->factories_top = 0;
    this->factories_int = 0;
    this->factories_array_type = 0;
    this->factories_array_optimized = 0;
    this->factories_array_unoptimized = 0;
    this->factories_array_unoptimized_first = 0;
    this->factories_object_type = 0;
    this->factories_object_optimized = 0;
    this->factories_object_unoptimized = 0;
    this->factories_object_unoptimized_first = 0;

    ubjs_glue_array_array_builder_new(lib, &glue_builder);
    (glue_builder->set_value_free_f)(glue_builder, ubjs_processor_factory_free);

    (glue_builder->build_f)(glue_builder, &(this->factories_top));
    (glue_builder->build_f)(glue_builder, &(this->factories_array_unoptimized));
    (glue_builder->build_f)(glue_builder, &(this->factories_array_unoptimized_first));
    (glue_builder->build_f)(glue_builder, &(this->factories_array_type));
    (glue_builder->build_f)(glue_builder, &(this->factories_array_optimized));
    (glue_builder->build_f)(glue_builder, &(this->factories_object_unoptimized));
    (glue_builder->build_f)(glue_builder, &(this->factories_object_unoptimized_first));
    (glue_builder->build_f)(glue_builder, &(this->factories_object_type));
    (glue_builder->build_f)(glue_builder, &(this->factories_object_optimized));
    (glue_builder->build_f)(glue_builder, &(this->factories_int));

    (glue_builder->free_f)(&glue_builder);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_null);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_null);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_null);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_null);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_noop);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_noop);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_noop);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_noop);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_true);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_true);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_true);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_true);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_false);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_false);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_false);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_false);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_uint8);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_uint8);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_uint8);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_uint8);
    (this->factories_object_unoptimized->add_last_f)(this->factories_object_unoptimized,
        &ubjs_processor_factory_uint8);
    (this->factories_object_unoptimized_first->add_last_f)(this->factories_object_unoptimized_first,
        &ubjs_processor_factory_uint8);
    (this->factories_object_optimized->add_last_f)(this->factories_object_optimized,
        &ubjs_processor_factory_uint8);
    (this->factories_int->add_last_f)(this->factories_int, &ubjs_processor_factory_uint8);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_int8);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_int8);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_int8);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_int8);
    (this->factories_object_unoptimized->add_last_f)(this->factories_object_unoptimized,
        &ubjs_processor_factory_int8);
    (this->factories_object_unoptimized_first->add_last_f)(
        this->factories_object_unoptimized_first, &ubjs_processor_factory_int8);
    (this->factories_object_optimized->add_last_f)(this->factories_object_optimized,
        &ubjs_processor_factory_int8);
    (this->factories_int->add_last_f)(this->factories_int, &ubjs_processor_factory_int8);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_int16);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_int16);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_int16);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_int16);
    (this->factories_object_unoptimized->add_last_f)(this->factories_object_unoptimized,
        &ubjs_processor_factory_int16);
    (this->factories_object_unoptimized_first->add_last_f)(this->factories_object_unoptimized_first,
        &ubjs_processor_factory_int16);
    (this->factories_object_optimized->add_last_f)(this->factories_object_optimized,
        &ubjs_processor_factory_int16);
    (this->factories_int->add_last_f)(this->factories_int, &ubjs_processor_factory_int16);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_int32);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_int32);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_int32);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_int32);
    (this->factories_object_unoptimized->add_last_f)(this->factories_object_unoptimized,
        &ubjs_processor_factory_int32);
    (this->factories_object_unoptimized_first->add_last_f)(
        this->factories_object_unoptimized_first, &ubjs_processor_factory_int32);
    (this->factories_object_optimized->add_last_f)(this->factories_object_optimized,
        &ubjs_processor_factory_int32);
    (this->factories_int->add_last_f)(this->factories_int, &ubjs_processor_factory_int32);

    (this->factories_top->add_last_f)(this->factories_top, &ubjs_processor_factory_int64);
    (this->factories_array_unoptimized->add_last_f)(this->factories_array_unoptimized,
        &ubjs_processor_factory_int64);
    (this->factories_array_unoptimized_first->add_last_f)(this->factories_array_unoptimized_first,
        &ubjs_processor_factory_int64);
    (this->factories_array_optimized->add_last_f)(this->factories_array_optimized,
        &ubjs_processor_factory_int64);

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

    ubjs_selfemptying_list_new(lib, (ubjs_glue_value_free) ubjs_parser_give_control_request_free,
        ubjs_parser_give_control_fifo_callback,
        (void *)this, &(this->give_control_fifo));

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_parser_debug(this, 13, "### ALIVE ###");
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
    (this->factories_top->free_f)(&(this->factories_top));
    (this->factories_array_optimized->free_f)(&(this->factories_array_optimized));
    (this->factories_array_unoptimized->free_f)(&(this->factories_array_unoptimized));
    (this->factories_array_unoptimized_first->free_f)(&(this->factories_array_unoptimized_first));
    (this->factories_array_type->free_f)(&(this->factories_array_type));
    (this->factories_object_optimized->free_f)(&(this->factories_object_optimized));
    (this->factories_object_unoptimized->free_f)(&(this->factories_object_unoptimized));
    (this->factories_object_unoptimized_first->free_f)(&(this->factories_object_unoptimized_first));
    (this->factories_object_type->free_f)(&(this->factories_object_type));
    (this->factories_int->free_f)(&(this->factories_int));

    (this->context->free)(this->context);

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    ubjs_parser_debug(this, 15, "### D E A D ###");
#endif
    /* LCOV_EXCL_STOP */

    (this->lib->free_f)(this);
    (*pthis)=0;

    return UR_OK;
}

ubjs_result ubjs_parser_get_context(ubjs_parser *this, ubjs_parser_context **pcontext)
{
    if (0 == this || 0 == pcontext)
    {
        return UR_ERROR;
    }

    *pcontext=this->context;
    return UR_OK;
}

ubjs_result ubjs_parser_get_settings(ubjs_parser *this, ubjs_parser_settings **psettings)
{
    if (0 == this || 0 == psettings)
    {
        return UR_ERROR;
    }

    *psettings=this->settings;
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
    if (this->settings != 0 &&
        UTRUE == this->settings->debug)
    {
        char *message = 0;
        unsigned int len = 0;
        ubjs_compact_sprintf(this->lib, &message, &len, "ubjs_parser_parse() %u bytes", length);
        ubjs_parser_debug(this, len, message);
        (this->lib->free_f)(message);
    }
#endif
    /* LCOV_EXCL_STOP */

    for (i=0; i<length; i++)
    {
        this->errors=0;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (this->settings != 0 &&
            UTRUE == this->settings->debug)
        {
            char *message = 0;
            unsigned int len = 0;
            ubjs_compact_sprintf(this->lib, &message, &len,
                "ubjs_parser_parse() %u/%u [%u] in processor %s",
                i + 1, length, data[i], this->processor->name);
            ubjs_parser_debug(this, len, message);
            (this->lib->free_f)(message);
        }
#endif

        if (0 == this->processor->read_char)
        {
            ubjs_parser_emit_error(this, 39,
                "Unexpected data cause parser corruption");
            return UR_ERROR;
        }
        /* LCOV_EXCL_STOP */

        (this->processor->read_char)(this->processor, i, data[i]);
        if (0 < this->errors)
        {
            return UR_ERROR;
        }

        if (this->settings != 0 &&
            this->settings->limit_bytes_since_last_callback > 0)
        {
            this->counters.bytes_since_last_callback++;

            /* LCOV_EXCL_START */
#ifndef NDEBUG
            if (this->settings != 0 &&
                UTRUE == this->settings->debug)
            {
                char *message = 0;
                unsigned int len = 0;
                ubjs_compact_sprintf(this->lib, &message, &len,
                    "ubjs_parser_parse() bytes since last callback: %u/%u",
                    this->counters.bytes_since_last_callback,
                    this->settings->limit_bytes_since_last_callback);
                ubjs_parser_debug(this, len, message);
                (this->lib->free_f)(message);
            }
#endif
           /* LCOV_EXCL_STOP */

            if (this->settings->limit_bytes_since_last_callback <=
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
    if (this->settings != 0 &&
        this->settings->limit_recursion_level > 0)
    {
        this->counters.recursion_level++;

        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (this->settings != 0 &&
            UTRUE == this->settings->debug)
        {
            char *message = 0;
            unsigned int len = 0;
            ubjs_compact_sprintf(this->lib, &message, &len,
                "ubjs_parser_up_recursion_level() recursion level: %u/%u",
                this->counters.recursion_level,
                this->settings->limit_recursion_level);
            ubjs_parser_debug(this, len, message);
            (this->lib->free_f)(message);
        }
#endif
        /* LCOV_EXCL_STOP */

        if (this->settings->limit_recursion_level < this->counters.recursion_level)
        {
            ubjs_parser_emit_error(this, 32, "Reached limit of recursion level");
            return UR_ERROR;
        }
    }
    return UR_OK;
}

ubjs_result ubjs_parser_down_recursion_level(ubjs_parser *this)
{
    if (this->settings != 0 &&
        this->settings->limit_recursion_level > 0)
    {
        this->counters.recursion_level--;

        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (this->settings != 0 &&
            UTRUE == this->settings->debug)
        {
            char *message = 0;
            unsigned int len = 0;
            ubjs_compact_sprintf(this->lib, &message, &len,
                "ubjs_parser_up_recursion_level() recursion level: %u/%u",
                this->counters.recursion_level,
                this->settings->limit_recursion_level);
            ubjs_parser_debug(this, len, message);
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
    if (parser->settings != 0 &&
        UTRUE == parser->settings->debug)
    {
        char *message = 0;
        unsigned int len = 0;
        ubjs_compact_sprintf(this->lib, &message, &len,
            "ubjs_parser_give_control_fifo_callback() to %s (%d)",
            robj->processor->name, robj->processor->got_control);
        if (0 != robj->present)
        {
            char *dtext = 0;
            unsigned int dlen = 0;

            ubjs_prmtv_debug_string_get_length(robj->present, &dlen);
            dtext = (char *)(parser->lib->alloc_f)(sizeof(char) * (dlen + 1));
            ubjs_prmtv_debug_string_copy(robj->present, dtext);

            ubjs_compact_sprintf(this->lib, &message, &len, " with present: %.*s",
                dlen, dtext);
            (parser->lib->free_f)(dtext);
        }

        ubjs_parser_debug(parser, len, message);
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

    obj = (ubjs_parser_give_control_request *)(this->lib->alloc_f)(
        sizeof(struct ubjs_parser_give_control_request));
    obj->processor=processor;
    obj->present=present;
    obj->lib=this->lib;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (this->settings != 0 &&
        UTRUE == this->settings->debug)
    {
        char *message = 0;
        unsigned int len = 0;
        ubjs_compact_sprintf(this->lib, &message, &len, "ubjs_parser_give_control() to %s",
            processor->name);
        if (0 != present)
        {
            char *dtext = 0;
            unsigned int dlen = 0;

            ubjs_prmtv_debug_string_get_length(present, &dlen);
            dtext = (char *)(this->lib->alloc_f)(sizeof(char) * (dlen + 1));
            ubjs_prmtv_debug_string_copy(present, dtext);

            ubjs_compact_sprintf(this->lib, &message, &len, " with present: %.*s",
                dlen, dtext);
            (this->lib->free_f)(dtext);
        }

        ubjs_parser_debug(this, len, message);
        (this->lib->free_f)(message);
    }
#endif
    /* LCOV_EXCL_STOP */

    ubjs_selfemptying_list_add(this->give_control_fifo, obj);
}

void ubjs_parser_debug(ubjs_parser *this, unsigned int len, char *message)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (0 == this || 0 == len || 0 == message)
    {
        /* We do not need error reporting here. */
        return;
    }

    if (this->settings == 0 ||
        UFALSE == this->settings->debug)
    {
        return;
    }

    fprintf(stderr, "[P %p] %.*s\n", this, len, message);
#endif
    /* LCOV_EXCL_STOP */
}

void ubjs_parser_emit_error(ubjs_parser *this, unsigned int len, char *message)
{
    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (this->settings != 0 &&
        UTRUE == this->settings->debug)
    {
        char *message2 = 0;
        unsigned int len2 = 0;
        ubjs_compact_sprintf(this->lib, &message2, &len2,
            "ubjs_parser_emit_error() %.*s", len, message);
        ubjs_parser_debug(this, len2, message2);
        (this->lib->free_f)(message2);
    }
#endif
    /* LCOV_EXCL_STOP */

    ubjs_parser_error *error;
    ubjs_parser_error_new(this->lib, message, len, &error);
    (this->context->error)(this->context, error);
    ubjs_parser_error_free(&error);
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
    this->read_char = 0;
    this->free=(ubjs_processor_free)(parser->lib->free_f);
    parser->processor = this;

    /* Always processor_top, they have control */
    ubjs_parser_give_control(this->parser, this, 0);
}

ubjs_result ubjs_processor_top_selected_factory(ubjs_processor *this,
    ubjs_processor_factory *factory)
{
    ubjs_processor *next = 0;
    if (UR_ERROR == (factory->create)(this, &next))
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
        (this->parser->context->parsed)(this->parser->context, present);
        this->parser->counters.bytes_since_last_callback = 0;
    }

    ubjs_processor_next_object(this, this->parser->factories_top,
        ubjs_processor_top_selected_factory, &nxt);
    ubjs_parser_give_control(this->parser, nxt, 0);
}

void ubjs_processor_ints(ubjs_processor *this)
{
    ubjs_processor *nxt = 0;
    ubjs_processor_next_object(this, this->parser->factories_int,
        ubjs_processor_top_selected_factory, &nxt);
    ubjs_parser_give_control(this->parser, nxt, 0);
}

ubjs_result ubjs_processor_next_object(ubjs_processor *parent, ubjs_glue_array *factories,
    ubjs_processor_next_object_selected_factory selected_factory, ubjs_processor **pthis)
{
    ubjs_processor_next_objext *this;
    unsigned int length;
    unsigned int factories_len;
    char *name = 0;
    char *name_template = "next object from %u factories";

    (factories->get_length_f)(factories, &factories_len);
    length=snprintf(0, 0, name_template, factories_len);
    name=(char *)(parent->parser->lib->alloc_f)(sizeof(char)*(length + 1));
    snprintf(name, length + 1, name_template, factories_len);

    this = (ubjs_processor_next_objext *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_processor_next_objext));
    this->super.name = name;
    this->super.parent=parent;
    this->super.parser=parent->parser;
    this->super.userdata=0;
    this->super.got_control=0;
    this->super.read_char = ubjs_processor_next_object_read_char;
    this->super.free=ubjs_processor_next_object_free;
    this->factories=factories;
    this->selected_factory=selected_factory;

    *pthis=(ubjs_processor *)this;
    return UR_OK;
}

void ubjs_processor_next_object_free(ubjs_processor *this)
{
    (this->parser->lib->free_f)(this->name);
    (this->parser->lib->free_f)(this);
}

void ubjs_processor_next_object_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t c)
{
    ubjs_processor_next_objext *sub=(ubjs_processor_next_objext *)this;

    char *message = 0;
    unsigned int message_length = 0;
    ubjs_glue_array_iterator *it = 0;

    (sub->factories->iterate_f)(sub->factories, &it);
    while (UR_OK == (it->next_f)(it))
    {
        ubjs_processor_factory *pf = 0;
        (it->get_f)(it, (void **)&pf);

        if (pf->marker == c)
        {
            ubjs_result ret = (sub->selected_factory)(this->parent, pf);
            if (UR_OK == ret)
            {
                (this->free)(this);
            }
            (it->free_f)(&it);
            return;
        }
    }
    (it->free_f)(&it);

    ubjs_compact_sprintf(this->parser->lib, &message, &message_length,
        "At %d [%d] unknown marker", pos, c);
    ubjs_parser_emit_error(this->parser, message_length, message);
    (this->parser->lib->free_f)(message);
}

ubjs_result ubjs_processor_child_produced_length(ubjs_processor *this, ubjs_prmtv *obj,
    unsigned int *plength)
{
    char *message = 0;
    ubjs_prmtv_type type;

    int8_t v8;
    uint8_t vu8;
    int16_t v16;
    int32_t v32;

    ubjs_bool got_length=UFALSE;
    unsigned int length=0;

    ubjs_prmtv_get_type(obj, &type);
    if (UOT_INT8 == type)
    {
        ubjs_prmtv_int8_get(obj, &v8);
        if (0 <= v8)
        {
            got_length=UTRUE;
            length=(unsigned int)v8;
        }
        else
        {
            message = "Got int8 negative length";
        }
    }
    else if (UOT_UINT8 == type)
    {
        ubjs_prmtv_uint8_get(obj, &vu8);
        got_length=UTRUE;
        length=(unsigned int)vu8;
    }
    else if (UOT_INT16 == type)
    {
        ubjs_prmtv_int16_get(obj, &v16);
        if (0 <= v16)
        {
            got_length=UTRUE;
            length=(unsigned int)v16;
        }
        else
        {
            message = "Got int16 negative length";
        }
    }
    else if (UOT_INT32 == type)
    {
        ubjs_prmtv_int32_get(obj, &v32);
        if (0 <= v32)
        {
            got_length=UTRUE;
            length=(unsigned int)v32;
        }
        else
        {
            message = "Got int32 negative length";
        }
    }

    ubjs_prmtv_free(&obj);

    if (UTRUE == got_length)
    {
        /* LCOV_EXCL_START */
#ifndef NDEBUG
        if (this->parser->settings != 0 &&
            UTRUE == this->parser->settings->debug)
        {
            char *message2 = 0;
            unsigned int len2 = 0;
            ubjs_compact_sprintf(this->parser->lib, &message2, &len2,
                "ubjs_processor_child_produced_length() %u", length);
            ubjs_parser_debug(this->parser, len2, message2);
            (this->parser->lib->free_f)(message2);
        }
#endif
        /* LCOV_EXCL_STOP */

        *plength = length;
        return UR_OK;
    }

    ubjs_parser_emit_error(this->parser, (unsigned int)strlen(message), message);
    return UR_ERROR;
}

ubjs_result ubjs_processor_null(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "null";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_prmtv_null();
    this->got_control=ubjs_processor_no_length_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_noop(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "noop";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_prmtv_noop();
    this->got_control=ubjs_processor_no_length_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_true(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "true";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_prmtv_true();
    this->got_control=ubjs_processor_no_length_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_false(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "false";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=ubjs_prmtv_false();
    this->got_control=ubjs_processor_no_length_got_control;
    this->read_char = 0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_no_length_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_prmtv *ret=(ubjs_prmtv *)this->userdata;

    ubjs_parser_give_control(this->parser, this->parent, ret);
    (this->free)(this);
}

ubjs_result ubjs_processor_int8(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "int8";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=0;
    this->read_char = ubjs_processor_int8_read_char;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_int8_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    uint8_t value[1];
    uint8_t value2[1];
    ubjs_prmtv *ret;
    value[0] = achar;

    ubjs_endian_convert_big_to_native(value, value2, 1);
    ubjs_prmtv_int8(this->parser->lib, *((int8_t *)value2), &ret);
    ubjs_parser_give_control(this->parser, this->parent, ret);
    (this->free)(this);
}

ubjs_result ubjs_processor_uint8(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    this->name = "uint8";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=0;
    this->got_control=0;
    this->read_char = ubjs_processor_uint8_read_char;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_uint8_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    uint8_t value[1];
    uint8_t value2[1];
    ubjs_prmtv *ret;

    value[0] = achar;

    ubjs_endian_convert_big_to_native(value, value2, 1);
    ubjs_prmtv_uint8(this->parser->lib, *((uint8_t *)value2), &ret);
    ubjs_parser_give_control(this->parser, this->parent, ret);
    (this->free)(this);
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
    this->read_char = ubjs_processor_char_read_char;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_char_read_char(ubjs_processor *this, unsigned int pos,
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

ubjs_result ubjs_processor_int16(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)(parent->parser->lib->alloc_f)(sizeof(uint8_t) * 2);
    data->done=0;
    this->name = "int16";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_char = ubjs_processor_int16_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_int16_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (2 <= data->done)
    {
        uint8_t value2[2];
        ubjs_endian_convert_big_to_native(data->data, value2, 2);
        ubjs_prmtv_int16(this->parser->lib, *((int16_t *)value2), &ret);
        ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }
}

void ubjs_processor_longint_free(ubjs_processor *this)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    (this->parser->lib->free_f)(data->data);
    (this->parser->lib->free_f)(this->userdata);
    (this->parser->lib->free_f)(this);
}

ubjs_result ubjs_processor_int32(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_userdata_longint *data;

    this = (ubjs_processor *)(parent->parser->lib->alloc_f)(sizeof(struct ubjs_processor));
    data=(ubjs_userdata_longint *)(parent->parser->lib->alloc_f)(
        sizeof(struct ubjs_userdata_longint));
    data->data=(uint8_t *)(parent->parser->lib->alloc_f)(sizeof(uint8_t) * 4);
    data->done=0;
    this->name = "int32";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=0;
    this->read_char = ubjs_processor_int32_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_int32_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (4 <= data->done)
    {
        uint8_t value2[4];
        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        ubjs_prmtv_int32(this->parser->lib, *((int32_t *)value2), &ret);
        ubjs_parser_give_control(this->parser, this->parent, ret);
        (this->free)(this);
    }
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
    this->read_char = ubjs_processor_int64_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_int64_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (8 <= data->done)
    {
        uint8_t value2[8];
        ubjs_endian_convert_big_to_native(data->data, value2, 8);
        ubjs_prmtv_int64(this->parser->lib, *((int64_t *)value2), &ret);
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
    this->read_char = ubjs_processor_float32_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_float32_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (4 <= data->done)
    {
        uint8_t value2[4];
        ubjs_endian_convert_big_to_native(data->data, value2, 4);
        ubjs_prmtv_float32(this->parser->lib, *((float32_t *)value2), &ret);
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
    this->read_char = ubjs_processor_float64_read_char;
    this->free=ubjs_processor_longint_free;

    *pthis=this;
    return UR_OK;
}

void ubjs_processor_float64_read_char(ubjs_processor *this, unsigned int pos,
    uint8_t achar)
{
    ubjs_userdata_longint *data=(ubjs_userdata_longint *)this->userdata;
    ubjs_prmtv *ret;

    data->data[data->done++] = achar;
    if (8 <= data->done)
    {
        uint8_t value2[8];
        ubjs_endian_convert_big_to_native(data->data, value2, 8);
        ubjs_prmtv_float64(this->parser->lib, *((float64_t *)value2), &ret);
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
    this->read_char = ubjs_processor_str_read_char;
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

        if (this->parser->settings != 0 &&
            this->parser->settings->limit_string_length > 0 &&
            this->parser->settings->limit_string_length < length)
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

void ubjs_processor_str_read_char(ubjs_processor *this, unsigned int pos, uint8_t c)
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
    this->read_char = ubjs_processor_hpn_read_char;
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

        if (this->parser->settings &&
            this->parser->settings->limit_string_length > 0 &&
            this->parser->settings->limit_string_length < length)
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

void ubjs_processor_hpn_read_char(ubjs_processor *this, unsigned int pos, uint8_t c)
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
    data->type_factory=0;
    ubjs_prmtv_array(parent->parser->lib, &(data->array));
    this->name = "array";
    this->parent=parent;
    this->parser=parent->parser;
    this->userdata=data;
    this->got_control=ubjs_processor_array_got_control;
    this->read_char = 0;
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
    this->read_char = 0;
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
    this->read_char=0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_array_type_selected_factory(ubjs_processor *this,
    ubjs_processor_factory *factory)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;
    ubjs_processor *next;

    data->have_type=UTRUE;
    data->type_factory = factory;

    ubjs_processor_next_object(this, this->parser->factories_array_type,
        ubjs_processor_top_selected_factory, &next);
    ubjs_parser_give_control(this->parser, next, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_array_type(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this = 0;
    ubjs_processor_next_object(parent, parent->parser->factories_top,
        ubjs_processor_array_type_selected_factory, &this);
    *pthis = this;
    ubjs_parser_give_control(this->parser, this, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_array_selected_factory(ubjs_processor *this,
    ubjs_processor_factory *factory)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;

    if (this->parser->settings != 0 &&
        this->parser->settings->limit_container_length > 0 &&
        factory->marker != MARKER_ARRAY_END &&
        this->parser->settings->limit_container_length <= data->real_length)
    {
        ubjs_parser_emit_error(this->parser, 33,
            "Reached limit of container length");
        return UR_ERROR;
    }

    return ubjs_processor_top_selected_factory(this, factory);
}

void ubjs_processor_array_got_control(ubjs_processor *this, ubjs_prmtv *present)
{
    ubjs_userdata_array *data=(ubjs_userdata_array *)this->userdata;
    ubjs_processor *nxt = 0;

    if (0 != present)
    {
        ubjs_prmtv_array_add_last(data->array, present);
        data->real_length++;

        if (UTRUE == data->have_length &&
            data->real_length == data->length)
        {
            ubjs_processor_array_child_produced_end(this);
            return;
        }
    }

    if (UTRUE == data->have_type)
    {
        (data->type_factory->create)(this, &nxt);
        ubjs_parser_give_control(this->parser, nxt, 0);
        return;
    }

    if (UTRUE == data->have_length)
    {
        ubjs_processor_next_object(this, this->parser->factories_array_optimized,
            ubjs_processor_top_selected_factory, &nxt);
    }
    else
    {
        if (0 == data->real_length)
        {
            ubjs_processor_next_object(this, this->parser->factories_array_unoptimized_first,
                ubjs_processor_array_selected_factory, &nxt);
        }
        else
        {
            ubjs_processor_next_object(this, this->parser->factories_array_unoptimized,
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
        ubjs_prmtv_array_with_length(this->parser->lib, 0, &(data->array));
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

    if (this->parser->settings &&
        this->parser->settings->limit_container_length > 0 &&
        this->parser->settings->limit_container_length < length)
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
        ubjs_prmtv_type type = UOT_MAX;
        ubjs_prmtv_convert_marker_to_type(data->type_factory->marker, &type);
        ubjs_prmtv_array_with_length_and_type(this->parser->lib, type, data->length,
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
    data->type_factory=0;
    ubjs_prmtv_object(parent->parser->lib, &(data->object));
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
    this->read_char=0;
    this->free=(ubjs_processor_free)(parent->parser->lib->free_f);

    *pthis=this;
    return UR_OK;
}

ubjs_result ubjs_processor_object_type_selected_factory(ubjs_processor *this,
    ubjs_processor_factory *factory)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;
    ubjs_processor *next;

    data->have_type=UTRUE;
    data->type_factory = factory;

    ubjs_processor_next_object(this, this->parser->factories_object_type,
        ubjs_processor_top_selected_factory, &next);
    ubjs_parser_give_control(this->parser, next, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_object_type(ubjs_processor *parent, ubjs_processor **pthis)
{
    ubjs_processor *this;
    ubjs_processor_next_object(parent, parent->parser->factories_top,
                ubjs_processor_object_type_selected_factory, &this);
    *pthis = this;
    ubjs_parser_give_control(this->parser, this, 0);
    return UR_OK;
}

ubjs_result ubjs_processor_object_selected_factory(ubjs_processor *this,
    ubjs_processor_factory *factory)
{
    ubjs_userdata_object *data=(ubjs_userdata_object *)this->userdata;

    if (this->parser->settings != 0 &&
        this->parser->settings->limit_container_length > 0 &&
        factory->marker != MARKER_OBJECT_END &&
        this->parser->settings->limit_container_length <= data->real_length)
    {
        ubjs_parser_emit_error(this->parser, 33,
            "Reached limit of container length");
        return UR_ERROR;
    }

    return ubjs_processor_top_selected_factory(this, factory);
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
            ubjs_processor_next_object(this, this->parser->factories_object_optimized,
                ubjs_processor_top_selected_factory, &nxt);
        }
        else
        {
            if (0 == data->real_length)
            {
                ubjs_processor_next_object(this, this->parser->factories_object_unoptimized_first,
                    ubjs_processor_object_selected_factory, &nxt);
            }
            else
            {
                ubjs_processor_next_object(this, this->parser->factories_object_unoptimized,
                    ubjs_processor_object_selected_factory, &nxt);
            }
        }
        break;

    case WANT_VALUE:
        if (UTRUE == data->have_type)
        {
            (data->type_factory->create)(this, &nxt);
        }
        else
        {
            ubjs_processor_next_object(this, this->parser->factories_top,
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

    if (this->parser->settings != 0 &&
        this->parser->settings->limit_container_length > 0 &&
        this->parser->settings->limit_container_length < length)
    {
        ubjs_parser_emit_error(this->parser, 33, "Reached limit of container length");
        return;
    }

    data = (ubjs_userdata_object *)parent->userdata;
    data->have_length = UTRUE;
    data->length=length;

    /* LCOV_EXCL_START */
#ifndef NDEBUG
    if (this->parser->settings != 0 &&
        UTRUE == this->parser->settings->debug)
    {
        char *message = 0;
        unsigned int len = 0;
        ubjs_compact_sprintf(this->parser->lib, &message, &len,
            "length %u", length);
        ubjs_parser_debug(this->parser, len, message);
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
