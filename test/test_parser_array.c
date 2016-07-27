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

void test_parser_array_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 93};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_uint8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 85, 5, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    uint8_t vu8;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(item, &vu8));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALUI(5, vu8);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_int8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 105, 255, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    int8_t v8;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(item, &v8));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUAL(-1, v8);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}


void test_parser_array_int16()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 73, 0, 129, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    int16_t v16;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);


    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(item, &v16));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUAL(-32512, v16);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_int32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 108, 0, 129, 0, 129, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    int32_t v32;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 7));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(item, &v32));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUAL(-2130673408, v32);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 76, 1, 2, 3, 4, 5, 6, 7, 8, 93};
    unsigned int length;
    ubjs_prmtv *obj=0;
    ubjs_prmtv *item=0;
    ubjs_bool ret=UTRUE;
    int64_t v64=0;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 11));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(item, &v64));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(67305985, v64);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_float32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 100, 0, 0, 128, 64, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    float32_t v32;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 7));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_float32_get(item, &v32));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(4, v32);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_float64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 68, 0, 0, 0, 0, 0, 0, 128, 64, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    float64_t v64;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 11));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_float64_get(item, &v64));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(512, v64);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_null()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 90, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 3));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 78, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 3));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_noop(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_true()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 84, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 3));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_true(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 70, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 3));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_false(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 67, (uint8_t)'r', 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    char v;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {

            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(item, &v));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUAL('r', v);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_str()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 83, 85, 5, 'r', 'o', 'w', 'e', 'r', 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 10));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {

            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                char text[5];
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);

                TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_get_length(item, &length));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(5, length);

                TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_copy_text(item, text));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_NSTRING_EQUAL("rower", text, 5);
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_array()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 91, 93, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {

            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);

                TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(item, &length));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(0, length);;
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_object()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 123, 125, 93};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));
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
        TASSERT_EQUALI(1, length);

        if (1 == length)
        {

            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
            TASSERT_NOT_EQUAL(0, item);

            if (0 != item)
            {
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);

                TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(item, &length));
                TASSERT_EQUALI(UTRUE, ret);
                TASSERT_EQUALI(0, length);;
            }
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 85, 0};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));
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

void test_parser_array_optimized_count_null()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 90};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [90] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 78};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [78] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_true()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 84};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [84] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 70};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [70] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 67};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [67] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_uint8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 85, 10, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 14));
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
        TASSERT_EQUALUI(10, length);

        if (10 == length)
        {
            unsigned int i;
            for (i = 0; i < 10; i++)
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

void test_parser_array_optimized_count_int8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 105, 10, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 14));
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
        TASSERT_EQUALUI(10, length);

        if (10 == length)
        {
            unsigned int i;
            for (i = 0; i < 10; i++)
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

void test_parser_array_optimized_count_int8_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 105, 255};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("Got int8 negative length", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_int16()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 10005);
    data[0] = 91;
    data[1] = 35;
    data[2] = 73;
    data[3] = 16;
    data[4] = 39;
    for (i=0; i<10000; i++)
    {
        data[5 + i] = 90;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 10005));
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
        TASSERT_EQUALI(10000, length);

        if (10000 == length)
        {
            for (i = 0; i < 10000; i++)
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

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_int16_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[] = {91, 35, 73, 0, 255};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("Got int16 negative length", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_int32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t *data;
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *item=0;
    ubjs_bool ret;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 100007);
    data[0] = 91;
    data[1] = 35;
    data[2] = 108;
    data[3] = 160;
    data[4] = 134;
    data[5] = 1;
    data[6] = 0;
    for (i=0; i<100000; i++)
    {
        data[7 + i] = 90;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 100007));
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
        TASSERT_EQUALI(100000, length);

        if (100000 == length)
        {
            for (i = 0; i < 100000; i++)
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

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_int32_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[] = {91, 35, 108, 0, 0, 0, 255};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 7));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("Got int32 negative length", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 76};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [76] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_str()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 83};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [83] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_array()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 91};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [91] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_array_optimized_count_object()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {91, 35, 123};
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 2 [123] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}
