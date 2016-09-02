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


void test_parser_object_null()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 90, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));

    }
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 78, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_noop(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));

    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_true()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 84, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_true(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 70, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_false(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_uint8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 85, 130, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    uint8_t vu8;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(other, &vu8));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(130, vu8);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_int8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 105, 2, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    int8_t v8;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(other, &v8));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(2, v8);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_int16()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 73, 0, 129, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    int16_t v16;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 8));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(other, &v16));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUAL(-32512, v16);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_int32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 108, 0, 129, 0, 129, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    int32_t v32;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(other, &v32));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUAL(-2130673408, v32);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 76, 1, 2, 3, 4, 5, 6, 7, 8, 125};
    unsigned int length;
    ubjs_prmtv *obj=0;
    ubjs_prmtv *other=0;
    ubjs_object_iterator *it;
    ubjs_bool ret=UTRUE;
    int64_t v64=0;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(other, &v64));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(67305985, v64);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_float32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 100, 0, 0, 128, 64, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    float32_t v32;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_float32_get(other, &v32));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(4, v32);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_float64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 68, 0, 0, 0, 0, 0, 0, 128, 64, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    float64_t v64;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_float64_get(other, &v64));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(512.0, v64);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 67, 'r', 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;
    char v;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(other, &v));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUAL('r', v);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_str()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 83, 85, 5, 'r', 'o', 'w', 'e', 'r', 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 13));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_get_length(other, &length));
            TASSERT_EQUALI(5, length);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_copy_text(other, akey));
            TASSERT_NSTRING_EQUAL("rower", akey, 5);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_hpn()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 72, 85, 5, '1', '2', '3', '4', '5', 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 13));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[2];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_hpn(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_hpn_get_length(other, &length));
            TASSERT_EQUALI(5, length);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_hpn_copy_text(other, akey));
            TASSERT_NSTRING_EQUAL("12345", akey, 5);
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_array()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 91, 93, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[10];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(other, &length));
            TASSERT_EQUALI(0, length);;
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_object()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 85, 1, 'a', 123, 125, 125};
    unsigned int length;
    ubjs_prmtv *obj;
    ubjs_prmtv *other;
    ubjs_object_iterator *it;
    ubjs_bool ret;

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
        ubjs_result ret2;
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(1, length);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        ret2=ubjs_object_iterator_next(it);

        TASSERT_EQUALI(UR_OK, ret2);
        if (UR_OK == ret2)
        {
            char akey[10];
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
            TASSERT_EQUALI(1, length);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, akey));
            TASSERT_NSTRING_EQUAL("a", akey, 1);
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &other));
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(other, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(other, &length));
            TASSERT_EQUALI(0, length);;
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_count_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[] = {123, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_count_uint8()
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
    char key[2];
    ubjs_object_iterator *it;

    data=(uint8_t *)malloc(sizeof(uint8_t) * 44);
    data[0] = 123;
    data[1] = 35;
    data[2] = 85;
    data[3] = 10;

    for (i=0; i<10; i++)
    {
        snprintf(key, 2, "%01u", i);
        data[4 + i * 4] = 85;
        data[5 + i * 4] = 1;
        strncpy((char *)data + 6 + i * 4, key, 1);
        data[7 + i * 4] = 90;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 44));
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
        TASSERT_EQUALUI(10, length);

        if (10 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<10; i++)
            {
                ubjs_result ret2 = ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);
                if (UR_OK == ret2)
                {
                    char key2[2];
                    snprintf(key, 2, "%01u", i);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
                    TASSERT_EQUALI(1, length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 1);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}


void test_parser_object_optimized_count_int8()
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
    char key[2];
    ubjs_object_iterator *it;

    data=(uint8_t *)malloc(sizeof(uint8_t) * 44);
    data[0] = 123;
    data[1] = 35;
    data[2] = 105;
    data[3] = 10;

    for (i=0; i<10; i++)
    {
        snprintf(key, 2, "%01u", i);
        data[4 + i * 4] = 85;
        data[5 + i * 4] = 1;
        strncpy((char *)data + 6 + i * 4, key, 1);
        data[7 + i * 4] = 90;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 44));
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
        TASSERT_EQUALUI(10, length);

        if (10 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<10; i++)
            {
                ubjs_result ret2 = ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);
                if (UR_OK == ret2)
                {
                    char key2[2];
                    snprintf(key, 2, "%01u", i);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
                    TASSERT_EQUALI(1, length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 1);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_count_int16()
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
    char key[5];
    ubjs_object_iterator *it;

    data=(uint8_t *)malloc(sizeof(uint8_t) * 70005);
    data[0] = 123;
    data[1] = 35;
    data[2] = 73;
    data[3] = 16;
    data[4] = 39;

    for (i=0; i<10000; i++)
    {
        snprintf(key, 5, "%04u", i);
        data[5 + i * 7] = 85;
        data[6 + i * 7] = 4;
        strncpy((char *)data + 7 + i * 7, key, 4);
        data[11 + i * 7] = 90;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 70005));
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
        TASSERT_EQUALI(10000, length);

        if (10000 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<10000; i++)
            {
                ubjs_result ret2 = ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);
                if (UR_OK == ret2)
                {
                    char key2[5];
                    snprintf(key, 5, "%04u", i);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
                    TASSERT_EQUALI(4, length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 4);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_count_int32()
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
    char key[6];
    ubjs_object_iterator *it;

    data=(uint8_t *)malloc(sizeof(uint8_t) * 800007);
    data[0] = 123;
    data[1] = 35;
    data[2] = 108;
    data[3] = 160;
    data[4] = 134;
    data[5] = 1;
    data[6] = 0;

    for (i=0; i<100000; i++)
    {
        snprintf(key, 6, "%05u", i);
        data[7 + i * 8] = 85;
        data[8 + i * 8] = 5;
        strncpy((char *)data + 9 + i * 8, key, 5);
        data[14 + i * 8] = 90;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 800007));
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
        TASSERT_EQUALI(100000, length);

        if (100000 == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<100000; i++)
            {
                ubjs_result ret2 = ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);
                if (UR_OK == ret2)
                {
                    char key2[6];
                    snprintf(key, 6, "%05u", i);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &length));
                    TASSERT_EQUALI(5, length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 5);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_count_null()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 90};
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

void test_parser_object_optimized_count_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 78};
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

void test_parser_object_optimized_count_true()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 84};
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

void test_parser_object_optimized_count_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 70};
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

void test_parser_object_optimized_count_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 67};
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

void test_parser_object_optimized_count_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 76};
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

void test_parser_object_optimized_count_str()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 83};
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

void test_parser_object_optimized_count_hpn()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 72};
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
        TASSERT_STRING_EQUAL("At 2 [72] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_count_array()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 91};
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

void test_parser_object_optimized_count_object()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 123};
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

void test_parser_object_optimized_count_int8_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 35, 105, 255};
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

void test_parser_object_optimized_count_int16_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[] = {123, 35, 73, 0, 255};
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

void test_parser_object_optimized_count_int32_negative()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[] = {123, 35, 108, 0, 0, 0, 255};
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
