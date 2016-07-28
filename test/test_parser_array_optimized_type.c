/*
 * Copyright (c) 2016 Tomasz Sieprawski
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
#include <stdlib.h>
#include <string.h>

#include <ubjs.h>

#include "test_list.h"
#include "test_parser.h"
#include "test_parser_tools.h"

void test_parser_array_optimized_type_null_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 90, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_noop_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 78, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_true_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 84, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_false_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 70, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_uint8_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 85, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_char_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 67, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_int8_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 105, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_int16_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 73, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_int32_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 108, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_int64_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 76, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_str_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 83, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_hpn_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 72, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_array_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 91, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_object_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 123, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_null_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 90, 35, 85, LOTS};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            unsigned int i;
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                }
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_noop_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 78, 35, 85, LOTS};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            unsigned int i;
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_noop(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                }
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_true_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 84, 35, 85, LOTS};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            unsigned int i;
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_true(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                }
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_false_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 36, 70, 35, 85, LOTS};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            unsigned int i;
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_false(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                }
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_uint8_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    uint8_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 261);
    data[0] = 91;
    data[1] = 36;
    data[2] = 85;
    data[3] = 35;
    data[4] =  85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i] = 96;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 261));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALUI(96, v);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_char_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    char v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 261);
    data[0] = 91;
    data[1] = 36;
    data[2] = 67;
    data[3] = 35;
    data[4] =  85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i] = 'r';
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 261));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALC('r', v);
                }
            }
        }
    }


    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_int8_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    int8_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 261);
    data[0] = 91;
    data[1] = 36;
    data[2] = 105;
    data[3] = 35;
    data[4] =  85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i] = 96;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 261));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(96, v);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_int16_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    int16_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 516);
    data[0] = 91;
    data[1] = 36;
    data[2] = 73;
    data[3] = 35;
    data[4] =  85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i * 2] = 129;
        data[7 + i * 2] = 0;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 516));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(129, v);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_int32_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    int32_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1026);
    data[0] = 91;
    data[1] = 36;
    data[2] = 108;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i * 4] = 0;
        data[7 + i * 4] = 129;
        data[8 + i * 4] = 0;
        data[9 + i * 4] = 129;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1026));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(-2130673408, v);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_int64_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    int64_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 2046);
    data[0] = 91;
    data[1] = 36;
    data[2] = 76;
    data[3] = 35;
    data[4] =  85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i * 8] = 1;
        data[7 + i * 8] = 2;
        data[8 + i * 8] = 3;
        data[9 + i * 8] = 4;
        data[10 + i * 8] = 5;
        data[11 + i * 8] = 6;
        data[12 + i * 8] = 7;
        data[13 + i * 8] = 8;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 2046));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALLI(67305985, v);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_str_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    unsigned int text_length;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 516);
    data[0] = 91;
    data[1] = 36;
    data[2] = 83;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i * 2] = 85;
        data[7 + i * 2] = 0;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 516));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_get_length(item, &text_length));
                    TASSERT_EQUALUI(0, text_length);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_hpn_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    unsigned int text_length;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 771);
    data[0] = 91;
    data[1] = 36;
    data[2] = 72;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i * 3] = 85;
        data[7 + i * 3] = 1;
        data[8 + i * 3] = '1';
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 771));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_hpn(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_hpn_get_length(item, &text_length));
                    TASSERT_EQUALUI(1, text_length);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_array_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    unsigned int array_length;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 261);
    data[0] = 91;
    data[1] = 36;
    data[2] = 91;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i] = 93;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 261));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(item, &array_length));
                    TASSERT_EQUALUI(0, array_length);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_type_object_lots()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    ubjs_bool ret;
    unsigned int i;
    unsigned int object_length;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 261);
    data[0] = 91;
    data[1] = 36;
    data[2] = 123;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        data[6 + i] = 125;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 261));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            for (i = 0; i < LOTS; i++)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, i, &item));
                TASSERT_NOT_EQUAL(0, item);

                if (0 != item)
                {
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(item, &object_length));
                    TASSERT_EQUALUI(0, object_length);
                }
            }
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}
