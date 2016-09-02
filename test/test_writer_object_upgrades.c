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
#include "test_writer.h"
#include "test_writer_tools.h"

void test_writer_object_upgraded_from_int8_to_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<5; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(66, &item);
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(31, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(73, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(5, call_write->data[5]);

        for (i=0; i<5; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 5]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 5]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 5, 1);
            TASSERT_EQUALUI(0 == i ? 66 : 69, call_write->data[9 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[10 + i * 5]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*113);
        tmp_at += snprintf(tmp, 19, "[{][$][I][#][U][5]");
        for (i=0; i<5; i++)
        {
            snprintf(key, 2, "%01u", i);
            tmp_at += snprintf(tmp + tmp_at, 19, "\n    [U][1][%s][%u]", key, 0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(112, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 112);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_upgraded_from_uint8_to_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<5; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(31, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(73, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(5, call_write->data[5]);

        for (i=0; i<5; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 5]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 5]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 5, 1);
            TASSERT_EQUALUI(0 == i ? 66 : 69, call_write->data[9 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[10 + i * 5]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*113);
        tmp_at += snprintf(tmp, 19, "[{][$][I][#][U][5]");
        for (i=0; i<5; i++)
        {
            snprintf(key, 2, "%01u", i);
            tmp_at += snprintf(tmp + tmp_at, 19, "\n    [U][1][%s][%u]", key, 0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(112, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 112);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_to_int16_too_little()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<4; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(27, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(4, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("0", (char *)call_write->data + 6, 1);
        TASSERT_EQUALUI(85, call_write->data[7]);
        TASSERT_EQUALUI(66, call_write->data[8]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 1);
            TASSERT_EQUALUI(85, call_write->data[9 + i * 6]);
            TASSERT_EQUALUI(1, call_write->data[10 + i * 6]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 11 + i * 6, 1);
            TASSERT_EQUALUI(73, call_write->data[12 + i * 6]);
            TASSERT_EQUALUI(69, call_write->data[13 + i * 6]);
            TASSERT_EQUALUI(0, call_write->data[14 + i * 6]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*101);
        tmp_at += snprintf(tmp, 34, "[{][#][U][4]\n    [U][1][0][U][66]");
        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 1);
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][1][%s][I][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(100, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 100);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_to_int16_are_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<5; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int32(96, &item);
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(35, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(5, call_write->data[3]);
        
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("0", (char *)call_write->data + 6, 1);
        TASSERT_EQUALUI(85, call_write->data[7]);
        TASSERT_EQUALUI(66, call_write->data[8]);

        TASSERT_EQUALUI(85, call_write->data[9]);
        TASSERT_EQUALUI(1, call_write->data[10]);
        TASSERT_NSTRING_EQUAL("1", (char *)call_write->data + 11, 1);
        TASSERT_EQUALUI(108, call_write->data[12]);
        TASSERT_EQUALUI(96, call_write->data[13]);
        TASSERT_EQUALUI(0, call_write->data[14]);
        TASSERT_EQUALUI(0, call_write->data[15]);
        TASSERT_EQUALUI(0, call_write->data[16]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            TASSERT_EQUALUI(85, call_write->data[17 + i * 6]);
            TASSERT_EQUALUI(1, call_write->data[18 + i * 6]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 19 + i * 6, 1);
            TASSERT_EQUALUI(73, call_write->data[20 + i * 6]);
            TASSERT_EQUALUI(69, call_write->data[21 + i * 6]);
            TASSERT_EQUALUI(0, call_write->data[22 + i * 6]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*122);
        tmp_at += snprintf(tmp, 55, "[{][#][U][5]\n    [U][1][0][U][66]\n    [U][1][1][l][96]");
        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][1][%s][I][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(121, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 121);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_to_int16_are_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<5; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int64(96, &item);
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(39, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(5, call_write->data[3]);
        
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("0", (char *)call_write->data + 6, 1);
        TASSERT_EQUALUI(85, call_write->data[7]);
        TASSERT_EQUALUI(66, call_write->data[8]);

        TASSERT_EQUALUI(85, call_write->data[9]);
        TASSERT_EQUALUI(1, call_write->data[10]);
        TASSERT_NSTRING_EQUAL("1", (char *)call_write->data + 11, 1);
        TASSERT_EQUALUI(76, call_write->data[12]);
        TASSERT_EQUALUI(96, call_write->data[13]);
        TASSERT_EQUALUI(0, call_write->data[14]);
        TASSERT_EQUALUI(0, call_write->data[15]);
        TASSERT_EQUALUI(0, call_write->data[16]);
        TASSERT_EQUALUI(0, call_write->data[17]);
        TASSERT_EQUALUI(0, call_write->data[18]);
        TASSERT_EQUALUI(0, call_write->data[19]);
        TASSERT_EQUALUI(0, call_write->data[20]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            TASSERT_EQUALUI(85, call_write->data[21 + i * 6]);
            TASSERT_EQUALUI(1, call_write->data[22 + i * 6]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 23 + i * 6, 1);
            TASSERT_EQUALUI(73, call_write->data[24 + i * 6]);
            TASSERT_EQUALUI(69, call_write->data[25 + i * 6]);
            TASSERT_EQUALUI(0, call_write->data[26 + i * 6]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*122);
        tmp_at += snprintf(tmp, 55, "[{][#][U][5]\n    [U][1][0][U][66]\n    [U][1][1][L][96]");
        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][1][%s][I][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(121, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 121);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_to_int16_are_other_types()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<5; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            item = ubjs_prmtv_null();
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(31, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(5, call_write->data[3]);
        
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("0", (char *)call_write->data + 6, 1);
        TASSERT_EQUALUI(85, call_write->data[7]);
        TASSERT_EQUALUI(66, call_write->data[8]);

        TASSERT_EQUALUI(85, call_write->data[9]);
        TASSERT_EQUALUI(1, call_write->data[10]);
        TASSERT_NSTRING_EQUAL("1", (char *)call_write->data + 11, 1);
        TASSERT_EQUALUI(90, call_write->data[12]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            TASSERT_EQUALUI(85, call_write->data[13 + i * 6]);
            TASSERT_EQUALUI(1, call_write->data[14 + i * 6]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 15 + i * 6, 1);
            TASSERT_EQUALUI(73, call_write->data[16 + i * 6]);
            TASSERT_EQUALUI(69, call_write->data[17 + i * 6]);
            TASSERT_EQUALUI(0, call_write->data[18 + i * 6]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*118);
        tmp_at += snprintf(tmp, 51, "[{][#][U][5]\n    [U][1][0][U][66]\n    [U][1][1][Z]");
        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][1][%s][I][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(117, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 117);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_upgraded_from_uint8_int16_to_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<9; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else
        {
            ubjs_prmtv_int32(68, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(69, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(108, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(9, call_write->data[5]);

        for (i=0; i<9; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 7]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 7]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 7, 1);
            TASSERT_EQUALUI(0 == i ? 66 : (1 == i ? 67 : 68), call_write->data[9 + i * 7]);
            TASSERT_EQUALUI(0, call_write->data[10 + i * 7]);
            TASSERT_EQUALUI(0, call_write->data[11 + i * 7]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 7]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*185);
        tmp_at += snprintf(tmp, 19, "[{][$][l][#][U][9]");
        for (i=0; i<9; i++)
        {
            snprintf(key, 2, "%01u", i);
            tmp_at += snprintf(tmp + tmp_at, 19, "\n    [U][1][%s][%u]",
                key, 0 == i ? 66 : (1 == i ? 67 : 68));
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(184, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 184);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_upgraded_from_int8_int16_to_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<9; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else
        {
            ubjs_prmtv_int32(68, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(69, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(108, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(9, call_write->data[5]);

        for (i=0; i<9; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 7]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 7]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 7, 1);
            TASSERT_EQUALUI(0 == i ? 66 : (1 == i ? 67 : 68), call_write->data[9 + i * 7]);
            TASSERT_EQUALUI(0, call_write->data[10 + i * 7]);
            TASSERT_EQUALUI(0, call_write->data[11 + i * 7]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 7]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*185);
        tmp_at += snprintf(tmp, 19, "[{][$][l][#][U][9]");
        for (i=0; i<9; i++)
        {
            snprintf(key, 2, "%01u", i);
            tmp_at += snprintf(tmp + tmp_at, 19, "\n    [U][1][%s][%u]",
                key, 0 == i ? 66 : (1 == i ? 67 : 68));
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(184, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 184);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_int16_to_int32_too_little()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<8; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else
        {
            ubjs_prmtv_int32(68, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(63, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(8, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("0", (char *)call_write->data + 6, 1);
        TASSERT_EQUALUI(85, call_write->data[7]);
        TASSERT_EQUALUI(66, call_write->data[8]);

        TASSERT_EQUALUI(85, call_write->data[9]);
        TASSERT_EQUALUI(1, call_write->data[10]);
        TASSERT_NSTRING_EQUAL("1", (char *)call_write->data + 11, 1);
        TASSERT_EQUALUI(73, call_write->data[12]);
        TASSERT_EQUALUI(67, call_write->data[13]);
        TASSERT_EQUALUI(0, call_write->data[14]);

        for (i=0; i<6; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            TASSERT_EQUALUI(85, call_write->data[15 + i * 8]);
            TASSERT_EQUALUI(1, call_write->data[16 + i * 8]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 17 + i * 8, 1);
            TASSERT_EQUALUI(108, call_write->data[18 + i * 8]);
            TASSERT_EQUALUI(68, call_write->data[19 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[20 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[21 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[22 + i * 8]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*185);
        tmp_at += snprintf(tmp, 55, "[{][#][U][8]\n    [U][1][0][U][66]\n    [U][1][1][I][67]");
        for (i=0; i<6; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][1][%s][l][68]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(184, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 184);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_int16_to_int32_are_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<10; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int64(69, &item);
        }
        else
        {
            ubjs_prmtv_int32(68, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(83, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(10, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("0", (char *)call_write->data + 6, 1);
        TASSERT_EQUALUI(85, call_write->data[7]);
        TASSERT_EQUALUI(66, call_write->data[8]);

        TASSERT_EQUALUI(85, call_write->data[9]);
        TASSERT_EQUALUI(1, call_write->data[10]);
        TASSERT_NSTRING_EQUAL("1", (char *)call_write->data + 11, 1);
        TASSERT_EQUALUI(73, call_write->data[12]);
        TASSERT_EQUALUI(67, call_write->data[13]);
        TASSERT_EQUALUI(0, call_write->data[14]);
        
        TASSERT_EQUALUI(85, call_write->data[15]);
        TASSERT_EQUALUI(1, call_write->data[16]);
        TASSERT_NSTRING_EQUAL("2", (char *)call_write->data + 17, 1);
        TASSERT_EQUALUI(76, call_write->data[18]);
        TASSERT_EQUALUI(69, call_write->data[19]);
        TASSERT_EQUALUI(0, call_write->data[20]);
        TASSERT_EQUALUI(0, call_write->data[21]);
        TASSERT_EQUALUI(0, call_write->data[22]);
        TASSERT_EQUALUI(0, call_write->data[23]);
        TASSERT_EQUALUI(0, call_write->data[24]);
        TASSERT_EQUALUI(0, call_write->data[25]);
        TASSERT_EQUALUI(0, call_write->data[26]);

        for (i=0; i<7; i++)
        {
            snprintf(key, 2, "%01u", i + 3);
            TASSERT_EQUALUI(85, call_write->data[27 + i * 8]);
            TASSERT_EQUALUI(1, call_write->data[28 + i * 8]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 29 + i * 8, 1);
            TASSERT_EQUALUI(108, call_write->data[30 + i * 8]);
            TASSERT_EQUALUI(68, call_write->data[31 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[32 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[33 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[34 + i * 8]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*228);
        tmp_at += snprintf(tmp, 77, "[{][#][U][10]\n    [U][1][0][U][66]\n    [U][1][1][I][67]"
            "\n    [U][1][2][L][69]");
        for (i=0; i<7; i++)
        {
            snprintf(key, 2, "%01u", i + 3);
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][1][%s][l][68]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(227, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 227);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_int16_to_int32_are_other_types()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[2];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<10; i++)
    {
        snprintf(key, 2, "%01u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else if (i == 2)
        {
            item = ubjs_prmtv_null();
        }
        else
        {
            ubjs_prmtv_int32(68, &item);
        }
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(75, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(10, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("0", (char *)call_write->data + 6, 1);
        TASSERT_EQUALUI(85, call_write->data[7]);
        TASSERT_EQUALUI(66, call_write->data[8]);

        TASSERT_EQUALUI(85, call_write->data[9]);
        TASSERT_EQUALUI(1, call_write->data[10]);
        TASSERT_NSTRING_EQUAL("1", (char *)call_write->data + 11, 1);
        TASSERT_EQUALUI(73, call_write->data[12]);
        TASSERT_EQUALUI(67, call_write->data[13]);
        TASSERT_EQUALUI(0, call_write->data[14]);
        
        TASSERT_EQUALUI(85, call_write->data[15]);
        TASSERT_EQUALUI(1, call_write->data[16]);
        TASSERT_NSTRING_EQUAL("2", (char *)call_write->data + 17, 1);
        TASSERT_EQUALUI(90, call_write->data[18]);

        for (i=0; i<7; i++)
        {
            snprintf(key, 2, "%01u", i + 3);
            TASSERT_EQUALUI(85, call_write->data[19 + i * 8]);
            TASSERT_EQUALUI(1, call_write->data[20 + i * 8]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 21 + i * 8, 1);
            TASSERT_EQUALUI(108, call_write->data[22 + i * 8]);
            TASSERT_EQUALUI(68, call_write->data[23 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[24 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[25 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[26 + i * 8]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*224);
        tmp_at += snprintf(tmp, 73, "[{][#][U][10]\n    [U][1][0][U][66]\n    [U][1][1][I][67]"
            "\n    [U][1][2][Z]");
        for (i=0; i<7; i++)
        {
            snprintf(key, 2, "%01u", i + 3);
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][1][%s][l][68]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(223, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 223);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_upgraded_from_uint8_int16_int32_to_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[3];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<21; i++)
    {
        snprintf(key, 3, "%02u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(68, &item);
        }
        else
        {
            ubjs_prmtv_int64(69, &item);
        }
        ubjs_prmtv_object_set(obj, 2, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(258, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(76, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(21, call_write->data[5]);

        for (i=0; i<21; i++)
        {
            unsigned int expected_first;
            switch (i)
            {
                case 0:
                    expected_first = 66;
                    break;
                case 1:
                    expected_first = 67;
                    break;
                case 2:
                    expected_first = 68;
                    break;
                default:
                    expected_first = 69;
                    break;
            }

            snprintf(key, 3, "%02u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 12]);
            TASSERT_EQUALUI(2, call_write->data[7 + i * 12]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 12, 2);
            TASSERT_EQUALUI(expected_first, call_write->data[10 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[11 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[13 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[14 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[15 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[16 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[17 + i * 12]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*423);
        tmp_at += snprintf(tmp, 20, "[{][$][L][#][U][21]");
        for (i=0; i<21; i++)
        {
            unsigned int expected;
            switch (i)
            {
                case 0:
                    expected = 66;
                    break;
                case 1:
                    expected = 67;
                    break;
                case 2:
                    expected = 68;
                    break;
                default:
                    expected = 69;
                    break;
            }

            snprintf(key, 3, "%02u", i);
            tmp_at += snprintf(tmp + tmp_at, 20, "\n    [U][2][%s][%u]", key, expected);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(422, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 422);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_upgraded_from_int8_int16_int32_to_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[3];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<21; i++)
    {
        snprintf(key, 3, "%02u", i);
        if (i == 0)
        {
            ubjs_prmtv_int8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(68, &item);
        }
        else
        {
            ubjs_prmtv_int64(69, &item);
        }
        ubjs_prmtv_object_set(obj, 2, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(258, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(76, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(21, call_write->data[5]);

        for (i=0; i<21; i++)
        {
            unsigned int expected_first;
            switch (i)
            {
                case 0:
                    expected_first = 66;
                    break;
                case 1:
                    expected_first = 67;
                    break;
                case 2:
                    expected_first = 68;
                    break;
                default:
                    expected_first = 69;
                    break;
            }

            snprintf(key, 3, "%02u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 12]);
            TASSERT_EQUALUI(2, call_write->data[7 + i * 12]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 12, 2);
            TASSERT_EQUALUI(expected_first, call_write->data[10 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[11 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[13 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[14 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[15 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[16 + i * 12]);
            TASSERT_EQUALUI(0, call_write->data[17 + i * 12]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*423);
        tmp_at += snprintf(tmp, 20, "[{][$][L][#][U][21]");
        for (i=0; i<21; i++)
        {
            unsigned int expected;
            switch (i)
            {
                case 0:
                    expected = 66;
                    break;
                case 1:
                    expected = 67;
                    break;
                case 2:
                    expected = 68;
                    break;
                default:
                    expected = 69;
                    break;
            }

            snprintf(key, 3, "%02u", i);
            tmp_at += snprintf(tmp + tmp_at, 20, "\n    [U][2][%s][%u]", key, expected);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(422, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 422);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_too_little()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[3];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<20; i++)
    {
        snprintf(key, 3, "%02u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(68, &item);
        }
        else
        {
            ubjs_prmtv_int64(69, &item);
        }
        ubjs_prmtv_object_set(obj, 2, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(247, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(20, call_write->data[3]);
        
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(2, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("00", (char *)call_write->data + 6, 2);
        TASSERT_EQUALUI(85, call_write->data[8]);
        TASSERT_EQUALUI(66, call_write->data[9]);

        TASSERT_EQUALUI(85, call_write->data[10]);
        TASSERT_EQUALUI(2, call_write->data[11]);
        TASSERT_NSTRING_EQUAL("01", (char *)call_write->data + 12, 2);
        TASSERT_EQUALUI(73, call_write->data[14]);
        TASSERT_EQUALUI(67, call_write->data[15]);
        TASSERT_EQUALUI(0, call_write->data[16]);

        TASSERT_EQUALUI(85, call_write->data[17]);
        TASSERT_EQUALUI(2, call_write->data[18]);
        TASSERT_NSTRING_EQUAL("02", (char *)call_write->data + 19, 2);
        TASSERT_EQUALUI(108, call_write->data[21]);
        TASSERT_EQUALUI(68, call_write->data[22]);
        TASSERT_EQUALUI(0, call_write->data[23]);
        TASSERT_EQUALUI(0, call_write->data[24]);
        TASSERT_EQUALUI(0, call_write->data[25]);

        for (i=0; i<17; i++)
        {
            snprintf(key, 3, "%02u", i + 3);
            TASSERT_EQUALUI(85, call_write->data[26 + i * 13]);
            TASSERT_EQUALUI(2, call_write->data[27 + i * 13]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 28 + i * 13, 2);
            TASSERT_EQUALUI(76, call_write->data[30 + i * 13]);
            TASSERT_EQUALUI(69, call_write->data[31 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[32 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[33 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[34 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[35 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[36 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[37 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[38 + i * 13]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*458);
        tmp_at += snprintf(tmp, 80, "[{][#][U][20]\n    [U][2][00][U][66]\n    [U][2][01][I][67]"
            "\n    [U][2][02][l][68]");
        for (i=0; i<17; i++)
        {
            snprintf(key, 3, "%02u", i + 3);
            tmp_at += snprintf(tmp + tmp_at, 23, "\n    [U][2][%s][L][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(457, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 457);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_are_other_types()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;
    char key[3];

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<22; i++)
    {
        snprintf(key, 3, "%02u", i);
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else if (i == 1)
        {
            ubjs_prmtv_int16(67, &item);
        }
        else if (i == 2)
        {
            ubjs_prmtv_int32(68, &item);
        }
        else if (i == 3)
        {
            item = ubjs_prmtv_null();
        }
        else
        {
            ubjs_prmtv_int64(69, &item);
        }
        ubjs_prmtv_object_set(obj, 2, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(265, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(22, call_write->data[3]);
        
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(2, call_write->data[5]);
        TASSERT_NSTRING_EQUAL("00", (char *)call_write->data + 6, 2);
        TASSERT_EQUALUI(85, call_write->data[8]);
        TASSERT_EQUALUI(66, call_write->data[9]);

        TASSERT_EQUALUI(85, call_write->data[10]);
        TASSERT_EQUALUI(2, call_write->data[11]);
        TASSERT_NSTRING_EQUAL("01", (char *)call_write->data + 12, 2);
        TASSERT_EQUALUI(73, call_write->data[14]);
        TASSERT_EQUALUI(67, call_write->data[15]);
        TASSERT_EQUALUI(0, call_write->data[16]);

        TASSERT_EQUALUI(85, call_write->data[17]);
        TASSERT_EQUALUI(2, call_write->data[18]);
        TASSERT_NSTRING_EQUAL("02", (char *)call_write->data + 19, 2);
        TASSERT_EQUALUI(108, call_write->data[21]);
        TASSERT_EQUALUI(68, call_write->data[22]);
        TASSERT_EQUALUI(0, call_write->data[23]);
        TASSERT_EQUALUI(0, call_write->data[24]);
        TASSERT_EQUALUI(0, call_write->data[25]);

        TASSERT_EQUALUI(85, call_write->data[26]);
        TASSERT_EQUALUI(2, call_write->data[27]);
        TASSERT_NSTRING_EQUAL("03", (char *)call_write->data + 28, 2);
        TASSERT_EQUALUI(90, call_write->data[30]);

        for (i=0; i<18; i++)
        {
            snprintf(key, 3, "%02u", i + 4);
            TASSERT_EQUALUI(85, call_write->data[31 + i * 13]);
            TASSERT_EQUALUI(2, call_write->data[32 + i * 13]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 33 + i * 13, 2);
            TASSERT_EQUALUI(76, call_write->data[35 + i * 13]);
            TASSERT_EQUALUI(69, call_write->data[36 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[37 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[38 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[39 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[40 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[41 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[42 + i * 13]);
            TASSERT_EQUALUI(0, call_write->data[43 + i * 13]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*498);
        tmp_at += snprintf(tmp, 98, "[{][#][U][22]\n    [U][2][00][U][66]\n    [U][2][01][I][67]"
            "\n    [U][2][02][l][68]\n    [U][2][03][Z]");
        for (i=0; i<18; i++)
        {
            snprintf(key, 3, "%02u", i + 4);
            tmp_at += snprintf(tmp + tmp_at, 23, "\n    [U][2][%s][L][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(497, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 497);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}
