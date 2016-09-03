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


void test_parser_object_optimized_type_unknown_marker()
{
    ubjs_parser *parser=0;
    unsigned int len;
    char *error;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 0};

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
        TASSERT_STRING_EQUAL("At 2 [0] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}


void test_parser_object_optimized_type_null_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 90, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_noop_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 78, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_true_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 84, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_false_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 70, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_uint8_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 85, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_char_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 67, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_int8_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 105, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_int16_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 73, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_int32_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 108, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_int64_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 76, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_str_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 83, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_hpn_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 72, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_array_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 91, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_object_empty()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {123, 36, 123, 35, 85, 0};
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(0, length);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_null_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1281);
    data[0] = 123;
    data[1] = 36;
    data[2] = 90;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 5] = 85;
        data[7 + i * 5] = 3;
        strncpy((char *) data + 8 + i * 5, key, 3);
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1281));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));

            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
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

void test_parser_object_optimized_type_noop_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1281);
    data[0] = 123;
    data[1] = 36;
    data[2] = 78;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 5] = 85;
        data[7 + i * 5] = 3;
        strncpy((char *) data + 8 + i * 5, key, 3);
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1281));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));

            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_noop(item, &ret));
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

void test_parser_object_optimized_type_true_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1281);
    data[0] = 123;
    data[1] = 36;
    data[2] = 84;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 5] = 85;
        data[7 + i * 5] = 3;
        strncpy((char *) data + 8 + i * 5, key, 3);
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1281));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));

            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_true(item, &ret));
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

void test_parser_object_optimized_type_false_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1281);
    data[0] = 123;
    data[1] = 36;
    data[2] = 70;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 5] = 85;
        data[7 + i * 5] = 3;
        strncpy((char *) data + 8 + i * 5, key, 3);
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1281));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));

            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_false(item, &ret));
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

void test_parser_object_optimized_type_uint8_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    uint8_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1536);
    data[0] = 123;
    data[1] = 36;
    data[2] = 85;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 6] = 85;
        data[7 + i * 6] = 3;
        strncpy((char *) data + 8 + i * 6, key, 3);
        data[11 + i * 6] = 96;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1536));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));

            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALUI(96, v);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_char_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    char v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1536);
    data[0] = 123;
    data[1] = 36;
    data[2] = 67;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 6] = 85;
        data[7 + i * 6] = 3;
        strncpy((char *) data + 8 + i * 6, key, 3);
        data[11 + i * 6] = 'r';
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1536));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));

            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALC('r', v);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_int8_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    int8_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1536);
    data[0] = 123;
    data[1] = 36;
    data[2] = 105;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 6] = 85;
        data[7 + i * 6] = 3;
        strncpy((char *) data + 8 + i * 6, key, 3);
        data[11 + i * 6] = 255;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1536));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));

            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(-1, v);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_int16_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    int16_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1791);
    data[0] = 123;
    data[1] = 36;
    data[2] = 73;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 7] = 85;
        data[7 + i * 7] = 3;
        strncpy((char *) data + 8 + i * 7, key, 3);
        data[11 + i * 7] = 129;
        data[12 + i * 7] = 0;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1791));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(129, v);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_int32_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    int32_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 2301);
    data[0] = 123;
    data[1] = 36;
    data[2] = 108;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 9] = 85;
        data[7 + i * 9] = 3;
        strncpy((char *) data + 8 + i * 9, key, 3);
        data[11 + i * 9] = 0;
        data[12 + i * 9] = 129;
        data[13 + i * 9] = 0;
        data[14 + i * 9] = 129;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 2301));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(-2130673408, v);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_int64_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    int64_t v;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 3321);
    data[0] = 123;
    data[1] = 36;
    data[2] = 76;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 13] = 85;
        data[7 + i * 13] = 3;
        strncpy((char *) data + 8 + i * 13, key, 3);
        data[11 + i * 13] = 1;
        data[12 + i * 13] = 2;
        data[13 + i * 13] = 3;
        data[14 + i * 13] = 4;
        data[15 + i * 13] = 5;
        data[16 + i * 13] = 6;
        data[17 + i * 13] = 7;
        data[18 + i * 13] = 8;
    }

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 3321));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(item, &v));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALLI(67305985, v);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_str_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    unsigned int item_length;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1791);
    data[0] = 123;
    data[1] = 36;
    data[2] = 83;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 7] = 85;
        data[7 + i * 7] = 3;
        strncpy((char *) data + 8 + i * 7, key, 3);
        data[11 + i * 7] = 85;
        data[12 + i * 7] = 0;
    }
    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1791));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));

                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_get_length(item, &item_length));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALUI(0, item_length);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_hpn_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    unsigned int item_length;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 2046);
    data[0] = 123;
    data[1] = 36;
    data[2] = 72;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 8] = 85;
        data[7 + i * 8] = 3;
        strncpy((char *) data + 8 + i * 8, key, 3);
        data[11 + i * 8] = 85;
        data[12 + i * 8] = 1;
        data[13 + i * 8] = '1';
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
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &length));
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);

                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));

                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_hpn(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_hpn_get_length(item, &item_length));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALUI(1, item_length);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_array_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    unsigned int item_length;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1536);
    data[0] = 123;
    data[1] = 36;
    data[2] = 91;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 6] = 85;
        data[7 + i * 6] = 3;
        strncpy((char *) data + 8 + i * 6, key, 3);
        data[11 + i * 6] = 93;
    }
    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1536));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);
                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));

                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(item, &item_length));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALUI(0, item_length);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_object_optimized_type_object_lots()
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
    unsigned int key_length;
    char key[4];
    ubjs_object_iterator *it = 0;
    unsigned int i;
    unsigned int item_length;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 1536);
    data[0] = 123;
    data[1] = 36;
    data[2] = 123;
    data[3] = 35;
    data[4] = 85;
    data[5] = LOTS;
    for (i=0; i<LOTS; i++)
    {
        snprintf(key, 4, "%03u", i);
        data[6 + i * 6] = 85;
        data[7 + i * 6] = 3;
        strncpy((char *) data + 8 + i * 6, key, 3);
        data[11 + i * 6] = 125;
    }
    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1536));
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
        TASSERT_EQUALI(LOTS, length);

        if (LOTS == length)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
            for (i=0; i<LOTS; i++)
            {
                ubjs_result ret2;
                snprintf(key, 4, "%03u", i);
                ret2=ubjs_object_iterator_next(it);
                TASSERT_EQUALI(UR_OK, ret2);
                if (UR_OK == ret2)
                {
                    char key2[4];
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));

                    TASSERT_EQUALUI(3, key_length);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                    TASSERT_NSTRING_EQUAL(key, key2, 3);
                    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(item, &ret));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(item, &item_length));
                    TASSERT_EQUALI(UTRUE, ret);
                    TASSERT_EQUALUI(0, item_length);
                }
            }
            TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
        }
    }

    free(data);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}
