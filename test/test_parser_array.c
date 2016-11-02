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

void __test_parser_array_empty(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(0, len);
}

void test_parser_array_empty()
{
    uint8_t data[] = {91, 93};
    sp_verify_parsed(2, data, __test_parser_array_empty);
}

void test_parser_array_unknown_marker()
{
    uint8_t data[] = {91, 0};
    sp_verify_error(2, data, "At 1 [0] unknown marker");
}

void __test_parser_array_uint8(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    uint8_t value;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(item, &value));
            TASSERT_EQUALUI(5, value);
        }
    }
}

void test_parser_array_uint8()
{
    uint8_t data[] = {91, 85, 5, 93};
    sp_verify_parsed(4, data, __test_parser_array_uint8);
}

void __test_parser_array_int8(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    int8_t value;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(item, &value));
            TASSERT_EQUALI(-1, value);
        }
    }
}

void test_parser_array_int8()
{
    uint8_t data[] = {91, 105, 255, 93};
    sp_verify_parsed(4, data, __test_parser_array_int8);
}

void __test_parser_array_int16(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    int16_t value;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(item, &value));
            TASSERT_EQUALI(-32512, value);
        }
    }
}

void test_parser_array_int16()
{
    uint8_t data[] = {91, 73, 0, 129, 93};
    sp_verify_parsed(5, data, __test_parser_array_int16);
}

void __test_parser_array_int32(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    int32_t value;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(item, &value));
            TASSERT_EQUAL(-2130673408, value);
        }
    }
}

void test_parser_array_int32()
{
    uint8_t data[] = {91, 108, 0, 129, 0, 129, 93};
    sp_verify_parsed(7, data, __test_parser_array_int32);
}

void __test_parser_array_int64(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    int64_t value = 0;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(item, &value));
            TASSERT_EQUAL(578437695752307201, value);
        }
    }
}

void test_parser_array_int64()
{
    uint8_t data[]= {91, 76, 1, 2, 3, 4, 5, 6, 7, 8, 93};
    sp_verify_parsed(11, data, __test_parser_array_int64);
}

void __test_parser_array_float32(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    float32_t value;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_float32_get(item, &value));
            TASSERT_EQUAL(4, value);
        }
    }
}

void test_parser_array_float32()
{
    uint8_t data[] = {91, 100, 0, 0, 128, 64, 93};
    sp_verify_parsed(7, data, __test_parser_array_float32);
}

void __test_parser_array_float64(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    float64_t value;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_float64_get(item, &value));
            TASSERT_EQUAL(512.0, value);
        }
    }
}

void test_parser_array_float64()
{
    uint8_t data[]= {91, 68, 0, 0, 0, 0, 0, 0, 128, 64, 93};
    sp_verify_parsed(11, data, __test_parser_array_float64);
}

void __test_parser_array_null(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
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

void test_parser_array_null()
{
    uint8_t data[]= {91, 90, 93};
    sp_verify_parsed(3, data, __test_parser_array_null);
}

void __test_parser_array_noop(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
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

void test_parser_array_noop()
{
    uint8_t data[]= {91, 78, 93};
    sp_verify_parsed(3, data, __test_parser_array_noop);
}

void __test_parser_array_true(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
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

void test_parser_array_true()
{
    uint8_t data[]= {91, 84, 93};
    sp_verify_parsed(3, data, __test_parser_array_true);
}

void __test_parser_array_false(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
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

void test_parser_array_false()
{
    uint8_t data[]= {91, 70, 93};
    sp_verify_parsed(3, data, __test_parser_array_false);
}

void __test_parser_array_char(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char value;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(item, &value));
            TASSERT_EQUALC('r', value);
        }
    }
}

void test_parser_array_char()
{
    uint8_t data[]= {91, 67, 'r', 93};
    sp_verify_parsed(4, data, __test_parser_array_char);
}

void __test_parser_array_str(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            char text[2];
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_get_length(item, &len));
            TASSERT_EQUALI(1, len);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_str_copy_text(item, text));
            TASSERT_NSTRING_EQUAL("r", text, 1);
        }
    }
}

void test_parser_array_str()
{
    uint8_t data[]= {91, 83, 85, 1, 'r', 93};
    sp_verify_parsed(6, data, __test_parser_array_str);
}

void __test_parser_array_hpn(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            char text[2];
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_hpn(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_hpn_get_length(item, &len));
            TASSERT_EQUALI(1, len);
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_hpn_copy_text(item, text));
            TASSERT_NSTRING_EQUAL("1", text, 1);
        }
    }
}

void test_parser_array_hpn()
{
    uint8_t data[]= {91, 72, 85, 1, '1', 93};
    sp_verify_parsed(6, data, __test_parser_array_hpn);
}

void __test_parser_array_array(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
        }
    }
}

void test_parser_array_array()
{
    uint8_t data[]= {91, 91, 93, 93};
    sp_verify_parsed(4, data, __test_parser_array_array);
}

void __test_parser_array_object(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_array_get_at(obj, 0, &item));
        TASSERT_NOT_EQUAL(0, item);

        if (0 != item)
        {
            TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(item, &ret));
            TASSERT_EQUALI(UTRUE, ret);
        }
    }
}

void test_parser_array_object()
{
    uint8_t data[]= {91, 123, 125, 93};
    sp_verify_parsed(4, data, __test_parser_array_object);
}

void test_parser_array_optimized_count_empty()
{
    uint8_t data[]= {91, 35, 85, 0};
    sp_verify_parsed(4, data, __test_parser_array_empty);
}

void test_parser_array_optimized_count_null()
{
    uint8_t data[]= {91, 35, 90};
    sp_verify_error(3, data, "At 2 [90] unknown marker");
}

void test_parser_array_optimized_count_noop()
{
    uint8_t data[]= {91, 35, 78};
    sp_verify_error(3, data, "At 2 [78] unknown marker");
}

void test_parser_array_optimized_count_true()
{
    uint8_t data[]= {91, 35, 84};
    sp_verify_error(3, data, "At 2 [84] unknown marker");
}

void test_parser_array_optimized_count_false()
{
    uint8_t data[]= {91, 35, 70};
    sp_verify_error(3, data, "At 2 [70] unknown marker");
}

void test_parser_array_optimized_count_char()
{
    uint8_t data[]= {91, 35, 67};
    sp_verify_error(3, data, "At 2 [67] unknown marker");
}

void test_parser_array_optimized_count_uint8()
{
    uint8_t data[]= {91, 35, 85, 0};
    sp_verify_parsed(4, data, __test_parser_array_empty);
}

void test_parser_array_optimized_count_int8()
{
    uint8_t data[]= {91, 35, 105, 0};
    sp_verify_parsed(4, data, __test_parser_array_empty);
}

void test_parser_array_optimized_count_int8_negative()
{
    uint8_t data[]= {91, 35, 105, 255};
    sp_verify_error(4, data, "Got int8 negative length");
}

void test_parser_array_optimized_count_int16()
{
    uint8_t data[]= {91, 35, 73, 0, 0};
    sp_verify_parsed(5, data, __test_parser_array_empty);
}

void test_parser_array_optimized_count_int16_negative()
{
    uint8_t data[]= {91, 35, 73, 0, 255};
    sp_verify_error(5, data, "Got int16 negative length");
}

void test_parser_array_optimized_count_int32()
{
    uint8_t data[]= {91, 35, 108, 0, 0, 0, 0};
    sp_verify_parsed(7, data, __test_parser_array_empty);
}

void test_parser_array_optimized_count_int32_negative()
{
    uint8_t data[]= {91, 35, 108, 0, 0, 0, 255};
    sp_verify_error(7, data, "Got int32 negative length");
}

void test_parser_array_optimized_count_int64()
{
    uint8_t data[]= {91, 35, 76};
    sp_verify_error(3, data, "At 2 [76] unknown marker");
}

void test_parser_array_optimized_count_str()
{
    uint8_t data[]= {91, 35, 83};
    sp_verify_error(3, data, "At 2 [83] unknown marker");
}

void test_parser_array_optimized_count_hpn()
{
    uint8_t data[]= {91, 35, 72};
    sp_verify_error(3, data, "At 2 [72] unknown marker");
}

void test_parser_array_optimized_count_array()
{
    uint8_t data[]= {91, 35, 91};
    sp_verify_error(3, data, "At 2 [91] unknown marker");
}

void test_parser_array_optimized_count_object()
{
    uint8_t data[]= {91, 35, 123};
    sp_verify_error(3, data, "At 2 [123] unknown marker");
}

void test_parser_settings_limit_container_length_array_unoptimized_below()
{
    ubjs_library *lib=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[5];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 3;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_library_new_stdlib(&lib);
    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 90;
    data[2] = 90;
    data[3] = 90;
    data[4] = 93;
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
    ubjs_library_free(&lib);
}

void test_parser_settings_limit_container_length_array_unoptimized_above()
{
    ubjs_library *lib = 0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[5];
    unsigned int len;
    char *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 3;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_library_new_stdlib(&lib);
    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 90;
    data[2] = 90;
    data[3] = 90;
    data[4] = 90;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&real_error);
        TASSERT_STRING_EQUAL("Reached limit of container length",
            real_error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
    ubjs_library_free(&lib);
}

void test_parser_settings_limit_container_length_array_optimized_below()
{
    ubjs_library *lib = 0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[5];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 3;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_library_new_stdlib(&lib);
    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 35;
    data[2] = 85;
    data[3] = 3;
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
    ubjs_library_free(&lib);
}

void test_parser_settings_limit_container_length_array_optimized_above()
{
    ubjs_library *lib = 0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[5];
    ubjs_parser_settings settings;
    unsigned int len;
    char *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 3;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_library_new_stdlib(&lib);
    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 35;
    data[2] = 85;
    data[3] = 4;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&real_error);
        TASSERT_STRING_EQUAL("Reached limit of container length",
            real_error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
    ubjs_library_free(&lib);
}

void test_parser_settings_limit_recursion_level_array_below()
{
    ubjs_library *lib = 0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[6];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 3;
    settings.debug = UFALSE;

    ubjs_library_new_stdlib(&lib);
    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 91;
    data[2] = 91;
    data[3] = 93;
    data[4] = 93;
    data[5] = 93;
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
    ubjs_library_free(&lib);
}

void test_parser_settings_limit_recursion_level_array_above()
{
    ubjs_library *lib = 0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[4];
    unsigned int len;
    char *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 3;
    settings.debug = UFALSE;

    ubjs_library_new_stdlib(&lib);
    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 91;
    data[2] = 91;
    data[3] = 91;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&real_error);
        TASSERT_STRING_EQUAL("Reached limit of recursion level",
            real_error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
    ubjs_library_free(&lib);
}
