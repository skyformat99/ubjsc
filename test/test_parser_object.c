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

void test_parser_object_unknown_marker()
{
    uint8_t data[] = {123, 0};
    sp_verify_error(2, data, "At 1 [0] unknown marker");
}

void __test_parser_object_empty(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(0, len);
}

void test_parser_object_empty()
{
    uint8_t data[]= {123, 125};
    sp_verify_parsed(2, data, __test_parser_object_empty);
}

void __test_parser_object_null(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_null()
{
    uint8_t data[]= {123, 85, 1, 'a', 90, 125};
    sp_verify_parsed(6, data, __test_parser_object_null);
}

void __test_parser_object_noop(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_noop(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_noop()
{
    uint8_t data[]= {123, 85, 1, 'a', 78, 125};
    sp_verify_parsed(6, data, __test_parser_object_noop);
}

void __test_parser_object_true(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_true(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_true()
{
    uint8_t data[]= {123, 85, 1, 'a', 84, 125};
    sp_verify_parsed(6, data, __test_parser_object_true);
}

void __test_parser_object_false(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_false(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_false()
{
    uint8_t data[]= {123, 85, 1, 'a', 70, 125};
    sp_verify_parsed(6, data, __test_parser_object_false);
}

void __test_parser_object_uint8(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_uint8()
{
    uint8_t data[]= {123, 85, 1, 'a', 85, 0, 125};
    sp_verify_parsed(7, data, __test_parser_object_uint8);
}

void __test_parser_object_int8(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_int8()
{
    uint8_t data[]= {123, 85, 1, 'a', 105, 0, 125};
    sp_verify_parsed(7, data, __test_parser_object_int8);
}

void __test_parser_object_int16(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_int16()
{
    uint8_t data[]= {123, 85, 1, 'a', 73, 0, 0, 125};
    sp_verify_parsed(8, data, __test_parser_object_int16);
}

void __test_parser_object_int32(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_int32()
{
    uint8_t data[]= {123, 85, 1, 'a', 108, 0, 0, 0, 0, 125};
    sp_verify_parsed(10, data, __test_parser_object_int32);
}

void __test_parser_object_int64(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_int64()
{
    uint8_t data[]= {123, 85, 1, 'a', 76, 0, 0, 0, 0, 0, 0, 0, 0, 125};
    sp_verify_parsed(14, data, __test_parser_object_int64);
}

void __test_parser_object_float32(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_float32()
{
    uint8_t data[]= {123, 85, 1, 'a', 100, 0, 0, 0, 0, 125};
    sp_verify_parsed(10, data, __test_parser_object_float32);
}

void __test_parser_object_float64(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_float64()
{
    uint8_t data[]= {123, 85, 1, 'a', 68, 0, 0, 0, 0, 0, 0, 0, 0, 125};
    sp_verify_parsed(14, data, __test_parser_object_float64);
}

void __test_parser_object_char(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_char()
{
    uint8_t data[]= {123, 85, 1, 'a', 67, 'r', 125};
    sp_verify_parsed(7, data, __test_parser_object_char);
}

void __test_parser_object_str(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_str()
{
    uint8_t data[]= {123, 85, 1, 'a', 83, 85, 0, 125};
    sp_verify_parsed(8, data, __test_parser_object_str);
}

void __test_parser_object_hpn(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_hpn(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_hpn()
{
    uint8_t data[]= {123, 85, 1, 'a', 72, 85, 1, '1', 125};
    sp_verify_parsed(9, data, __test_parser_object_hpn);
}

void __test_parser_object_array(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_array()
{
    uint8_t data[]= {123, 85, 1, 'a', 91, 93, 125};
    sp_verify_parsed(7, data, __test_parser_object_array);
}

void __test_parser_object_object(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    char key[2];
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(1, len);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_next(it));
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key));
    TASSERT_NSTRING_EQUAL("a", key, 1);
    TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(item, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    ubjs_object_iterator_free(&it);
}

void test_parser_object_object()
{
    uint8_t data[]= {123, 85, 1, 'a', 123, 125, 125};
    sp_verify_parsed(7, data, __test_parser_object_object);
}

void __test_parser_object_optimized_count_uint8(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(10, len);

    if (10 == len)
    {
        unsigned int i;
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        for (i=0; i<10; i++)
        {
            ubjs_result ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);
            if (UR_OK == ret2)
            {
                char key[2];
                char key2[2];

                snprintf(key, 2, "%01u", i);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
                TASSERT_EQUALI(1, len);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 1);
            }
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }
}

void test_parser_object_optimized_count_uint8()
{
    uint8_t data[44];
    unsigned int i;

    data[0] = 123;
    data[1] = 35;
    data[2] = 85;
    data[3] = 10;
    for (i=0; i<10; i++)
    {
        data[4 + i * 4] = 85;
        data[5 + i * 4] = 1;
        snprintf(data + 6 + i * 4, 2, "%01u", i);
        data[7 + i * 4] = (i == 0 ? 78 : 90);
    }
    sp_verify_parsed(44, data, __test_parser_object_optimized_count_uint8);
}

void test_parser_object_optimized_count_int8()
{
    uint8_t data[44];
    unsigned int i;

    data[0] = 123;
    data[1] = 35;
    data[2] = 105;
    data[3] = 10;
    for (i=0; i<10; i++)
    {
        data[4 + i * 4] = 85;
        data[5 + i * 4] = 1;
        snprintf(data + 6 + i * 4, 2, "%01u", i);
        data[7 + i * 4] = (i == 0 ? 78 : 90);
    }
    sp_verify_parsed(44, data, __test_parser_object_optimized_count_uint8);
}

void __test_parser_object_optimized_count_int16(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(10000, len);

    if (10000 == len)
    {
        unsigned int i;
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        for (i=0; i<10000; i++)
        {
            ubjs_result ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);
            if (UR_OK == ret2)
            {
                char key2[5];
                char key[5];
                snprintf(key, 5, "%04u", i);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
                TASSERT_EQUALI(4, len);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 4);
            }
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }
}

void test_parser_object_optimized_count_int16()
{
    uint8_t data[70005];
    unsigned int i;

    data[0] = 123;
    data[1] = 35;
    data[2] = 73;
    data[3] = 16;
    data[4] = 39;
    for (i=0; i<10000; i++)
    {
        data[5 + i * 7] = 85;
        data[6 + i * 7] = 4;
        snprintf(data + 7 + i * 7, 5, "%04u", i);
        data[11 + i * 7] = (i == 0 ? 78 : 90);
    }
    sp_verify_parsed(70005, data, __test_parser_object_optimized_count_int16);
}

void __test_parser_object_optimized_count_int32(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(100000, len);

    if (100000 == len)
    {
        unsigned int i;
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_iterate(obj, &it));
        for (i=0; i<100000; i++)
        {
            ubjs_result ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);
            if (UR_OK == ret2)
            {
                char key2[6];
                char key[6];
                snprintf(key, 6, "%05u", i);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &len));
                TASSERT_EQUALI(5, len);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 5);
            }
        }
        TASSERT_EQUALI(UR_OK, ubjs_object_iterator_free(&it));
    }
}

void test_parser_object_optimized_count_int32()
{
    uint8_t data[800007];
    unsigned int i;

    data[0] = 123;
    data[1] = 35;
    data[2] = 108;
    data[3] = 160;
    data[4] = 134;
    data[5] = 1;
    data[6] = 0;
    for (i=0; i<100000; i++)
    {
        data[7 + i * 8] = 85;
        data[8 + i * 8] = 5;
        snprintf(data + 9 + i * 8, 6, "%05u", i);
        data[14 + i * 8] = (i == 0 ? 78 : 90);
    }
    sp_verify_parsed(800007, data, __test_parser_object_optimized_count_int32);
}

void test_parser_object_optimized_count_null()
{
    uint8_t data[]= {123, 35, 90};
    sp_verify_error(3, data, "At 2 [90] unknown marker");
}

void test_parser_object_optimized_count_noop()
{
    uint8_t data[]= {123, 35, 78};
    sp_verify_error(3, data, "At 2 [78] unknown marker");
}

void test_parser_object_optimized_count_true()
{
    uint8_t data[]= {123, 35, 84};
    sp_verify_error(3, data, "At 2 [84] unknown marker");
}

void test_parser_object_optimized_count_false()
{
    uint8_t data[]= {123, 35, 70};
    sp_verify_error(3, data, "At 2 [70] unknown marker");
}

void test_parser_object_optimized_count_char()
{
    uint8_t data[]= {123, 35, 67};
    sp_verify_error(3, data, "At 2 [67] unknown marker");
}

void test_parser_object_optimized_count_int64()
{
    uint8_t data[]= {123, 35, 76};
    sp_verify_error(3, data, "At 2 [76] unknown marker");
}

void test_parser_object_optimized_count_str()
{
    uint8_t data[]= {123, 35, 83};
    sp_verify_error(3, data, "At 2 [83] unknown marker");
}

void test_parser_object_optimized_count_hpn()
{
    uint8_t data[]= {123, 35, 72};
    sp_verify_error(3, data, "At 2 [72] unknown marker");
}

void test_parser_object_optimized_count_array()
{
    uint8_t data[]= {123, 35, 91};
    sp_verify_error(3, data, "At 2 [91] unknown marker");
}

void test_parser_object_optimized_count_object()
{
    uint8_t data[]= {123, 35, 123};
    sp_verify_error(3, data, "At 2 [123] unknown marker");
}

void test_parser_object_optimized_count_int8_negative()
{
    uint8_t data[]= {123, 35, 105, 255};
    sp_verify_error(4, data, "Got int8 negative length");
}

void test_parser_object_optimized_count_int16_negative()
{
    uint8_t data[]= {123, 35, 73, 0, 255};
    sp_verify_error(5, data, "Got int16 negative length");
}

void test_parser_object_optimized_count_int32_negative()
{
    uint8_t data[] = {123, 35, 108, 0, 0, 0, 255};
    sp_verify_error(7, data, "Got int32 negative length");
}

void test_parser_security_limit_container_length_object_unoptimized_below()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[13];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 3;
    context.security.limit_string_length = 0;
    context.security.limit_recursion_level = 0;

    ubjs_parser_new(&parser, &context);

    data[0] = 123;

    data[1] = 85;
    data[2] = 1;
    data[3] = 'a';
    data[4] = 90;

    data[5] = 85;
    data[6] = 1;
    data[7] = 'b';
    data[8] = 90;

    data[9] = 85;
    data[10] = 1;
    data[11] = 'c';
    data[12] = 90;
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 13));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_security_limit_container_length_object_unoptimized_above()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[14];
    unsigned int len;
    char *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 3;
    context.security.limit_string_length = 0;
    context.security.limit_recursion_level = 0;

    ubjs_parser_new(&parser, &context);

    data[0] = 123;

    data[1] = 85;
    data[2] = 1;
    data[3] = 'a';
    data[4] = 90;

    data[5] = 85;
    data[6] = 1;
    data[7] = 'b';
    data[8] = 90;

    data[9] = 85;
    data[10] = 1;
    data[11] = 'c';
    data[12] = 90;

    data[13] = 85;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 14));
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
}

void test_parser_security_limit_container_length_object_optimized_below()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[5];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 3;
    context.security.limit_string_length = 0;
    context.security.limit_recursion_level = 0;

    ubjs_parser_new(&parser, &context);

    data[0] = 123;
    data[1] = 35;
    data[2] = 85;
    data[3] = 3;
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_security_limit_container_length_object_optimized_above()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[5];
    unsigned int len;
    char *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 3;
    context.security.limit_string_length = 0;
    context.security.limit_recursion_level = 0;

    ubjs_parser_new(&parser, &context);

    data[0] = 123;
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
}

void test_parser_security_limit_recursion_level_object_below()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[12];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 0;
    context.security.limit_string_length = 0;
    context.security.limit_recursion_level = 3;

    ubjs_parser_new(&parser, &context);

    data[0] = 123;
    data[1] = 85;
    data[2] = 1;
    data[3] = 'a';
    data[4] = 123;
    data[5] = 85;
    data[6] = 1;
    data[7] = 'a';
    data[8] = 123;
    data[9] = 85;
    data[10] = 1;
    data[11] = 'a';
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 12));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_security_limit_recursion_level_object_above()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[13];
    unsigned int len;
    char *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    context.security.limit_bytes_since_last_callback = 0;
    context.security.limit_container_length = 0;
    context.security.limit_string_length = 0;
    context.security.limit_recursion_level = 3;

    ubjs_parser_new(&parser, &context);

    data[0] = 123;
    data[1] = 85;
    data[2] = 1;
    data[3] = 'a';
    data[4] = 123;
    data[5] = 85;
    data[6] = 1;
    data[7] = 'a';
    data[8] = 123;
    data[9] = 85;
    data[10] = 1;
    data[11] = 'a';
    data[12] = 123;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 13));
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
}
