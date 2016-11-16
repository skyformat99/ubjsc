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

void test_parser_object_optimized_type_unknown_marker(void **state)
{
    uint8_t data[] = {123, 36, 0};
    sp_verify_error((ubjs_library *)*state, 3, data, "At 2 [0] unknown marker");
}

void __test_parser_object_optimized_type_empty(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(0, len);
}

void test_parser_object_optimized_type_null_empty(void **state)
{
    uint8_t data[]= {123, 36, 90, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_noop_empty(void **state)
{
    uint8_t data[]= {123, 36, 78, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_true_empty(void **state)
{
    uint8_t data[]= {123, 36, 84, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_false_empty(void **state)
{
    uint8_t data[]= {123, 36, 70, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_uint8_empty(void **state)
{
    uint8_t data[]= {123, 36, 85, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_char_empty(void **state)
{
    uint8_t data[]= {123, 36, 67, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_int8_empty(void **state)
{
    uint8_t data[]= {123, 36, 105, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_int16_empty(void **state)
{
    uint8_t data[]= {123, 36, 73, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_int32_empty(void **state)
{
    uint8_t data[]= {123, 36, 108, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_int64_empty(void **state)
{
    uint8_t data[]= {123, 36, 76, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_float32_empty(void **state)
{
    uint8_t data[]= {123, 36, 100, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_float64_empty(void **state)
{
    uint8_t data[]= {123, 36, 68, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_str_empty(void **state)
{
    uint8_t data[]= {123, 36, 83, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_hpn_empty(void **state)
{
    uint8_t data[]= {123, 36, 72, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_array_empty(void **state)
{
    uint8_t data[]= {123, 36, 91, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void test_parser_object_optimized_type_object_empty(void **state)
{
    uint8_t data[]= {123, 36, 123, 35, 85, 0};
    sp_verify_parsed((ubjs_library *)*state, 6, data, __test_parser_object_optimized_type_empty);
}

void __test_parser_object_optimized_type_null(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                char key2[4];
                unsigned int key_length;
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_null(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_null_lots(void **state)
{
    uint8_t *data;
    char key[5];
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
    sp_verify_parsed((ubjs_library *)*state, 1281, data, __test_parser_object_optimized_type_null);
    free(data);
}

void __test_parser_object_optimized_type_noop(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                char key2[4];
                unsigned int key_length;
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_noop(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_noop_lots(void **state)
{
    uint8_t *data;
    char key[5];
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
    sp_verify_parsed((ubjs_library *)*state, 1281, data, __test_parser_object_optimized_type_noop);
    free(data);
}

void __test_parser_object_optimized_type_true(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                char key2[4];
                unsigned int key_length;
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_true(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_true_lots(void **state)
{
    uint8_t *data;
    unsigned int i;
    char key[5];

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
    sp_verify_parsed((ubjs_library *)*state, 1281, data, __test_parser_object_optimized_type_true);
    free(data);
}

void __test_parser_object_optimized_type_false(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
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

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_false_lots(void **state)
{
    uint8_t *data;
    char key[5];
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
    sp_verify_parsed((ubjs_library *)*state, 1281, data, __test_parser_object_optimized_type_false);
    free(data);
}

void __test_parser_object_optimized_type_uint8(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_uint8_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
        data[11 + i * 6] = 0;
    }
    sp_verify_parsed((ubjs_library *)*state, 1536, data, __test_parser_object_optimized_type_uint8);
    free(data);
}

void __test_parser_object_optimized_type_int8(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_int8_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
        data[11 + i * 6] = 0;
    }
    sp_verify_parsed((ubjs_library *)*state, 1536, data, __test_parser_object_optimized_type_int8);
    free(data);
}

void __test_parser_object_optimized_type_char(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_char_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
        data[11 + i * 6] = '0';
    }
    sp_verify_parsed((ubjs_library *)*state, 1536, data, __test_parser_object_optimized_type_char);
    free(data);
}

void __test_parser_object_optimized_type_int16(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}


void __test_parser_object_optimized_type_int32(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_int16_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
    sp_verify_parsed((ubjs_library *)*state, 1791, data, __test_parser_object_optimized_type_int16);
    free(data);
}

void test_parser_object_optimized_type_int32_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
    sp_verify_parsed((ubjs_library *)*state, 2301, data, __test_parser_object_optimized_type_int32);
    free(data);
}

void __test_parser_object_optimized_type_int64(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_int64_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
    sp_verify_parsed((ubjs_library *)*state, 3321, data, __test_parser_object_optimized_type_int64);
    free(data);
}

void __test_parser_object_optimized_type_float32(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_float32_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 2301);
    data[0] = 123;
    data[1] = 36;
    data[2] = 100;
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
    sp_verify_parsed((ubjs_library *)*state, 2301, data,
        __test_parser_object_optimized_type_float32);
    free(data);
}

void __test_parser_object_optimized_type_float64(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_float64_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 3321);
    data[0] = 123;
    data[1] = 36;
    data[2] = 68;
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
    sp_verify_parsed((ubjs_library *)*state, 3321, data,
        __test_parser_object_optimized_type_float64);
    free(data);
}

void __test_parser_object_optimized_type_str(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_str(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_str_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
    sp_verify_parsed((ubjs_library *)*state, 1791, data, __test_parser_object_optimized_type_str);
    free(data);
}

void __test_parser_object_optimized_type_hpn(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_hpn(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_hpn_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
    sp_verify_parsed((ubjs_library *)*state, 2046, data, __test_parser_object_optimized_type_hpn);
    free(data);
}

void __test_parser_object_optimized_type_array(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_array_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
    sp_verify_parsed((ubjs_library *)*state, 1536, data, __test_parser_object_optimized_type_array);
    free(data);
}

void __test_parser_object_optimized_type_object(ubjs_prmtv *obj)
{
    unsigned int len;
    ubjs_bool ret;
    ubjs_prmtv *item;
    ubjs_object_iterator *it;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_object_get_length(obj, &len));
    TASSERT_EQUALI(LOTS, len);

    if (LOTS == len)
    {
        unsigned int i;
        ubjs_prmtv_object_iterate(obj, &it);
        for (i=0; i<LOTS; i++)
        {
            ubjs_result ret2;
            char key[5];
            snprintf(key, 4, "%03u", i);
            ret2 = ubjs_object_iterator_next(it);
            TASSERT_EQUALI(UR_OK, ret2);

            if (UR_OK == ret2)
            {
                unsigned int key_length;
                char key2[4];
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_key_length(it, &key_length));
                TASSERT_EQUALUI(3, key_length);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_copy_key(it, key2));
                TASSERT_NSTRING_EQUAL(key, key2, 3);
                TASSERT_EQUALI(UR_OK, ubjs_object_iterator_get_value(it, &item));
                TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_object(item, &ret));
                TASSERT_EQUALI(UTRUE, ret);
            }
        }

        ubjs_object_iterator_free(&it);
    }
}

void test_parser_object_optimized_type_object_lots(void **state)
{
    uint8_t *data;
    char key[5];
    unsigned int i;

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
    sp_verify_parsed((ubjs_library *)*state, 1536, data,
        __test_parser_object_optimized_type_object);
    free(data);
}
