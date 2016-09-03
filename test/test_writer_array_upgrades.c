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

void test_writer_array_upgraded_from_uint8_to_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(16, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(73, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(5, call_write->data[5]);
        for (i=0; i<5; i++)
        {
            TASSERT_EQUALUI(0 == i ? 66 : 69, call_write->data[6 + i * 2]);
            TASSERT_EQUALUI(0, call_write->data[7 + i * 2]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*68);
        tmp_at += snprintf(tmp, 19, "[[][$][I][#][U][5]");
        for (i=0; i<5; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 10, "\n    [%u]", 0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(67, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 67);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_upgraded_from_int8_to_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<5; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_int8(66, &item);
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(16, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(73, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(5, call_write->data[5]);
        for (i=0; i<5; i++)
        {
            TASSERT_EQUALUI(0 == i ? 66 : 69, call_write->data[6 + i * 2]);
            TASSERT_EQUALUI(0, call_write->data[7 + i * 2]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*68);
        tmp_at += snprintf(tmp, 19, "[[][$][I][#][U][5]");
        for (i=0; i<5; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 100, "\n    [%u]", 0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(67, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 67);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_to_int16_too_little()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<4; i++)
    {
        if (i == 0)
        {
            ubjs_prmtv_uint8(66, &item);
        }
        else
        {
            ubjs_prmtv_int16(69, &item);
        }
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(15, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(4, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(73, call_write->data[6 + i * 3]);
            TASSERT_EQUALUI(69, call_write->data[7 + i * 3]);
            TASSERT_EQUALUI(0, call_write->data[8 + i * 3]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*65);
        tmp_at += snprintf(tmp, 13, "[[][#][U][4]");
        for (i=0; i<4; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "\n    [%c][%u]",
                0 == i ? 'U' : 'I',
                0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(64, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 64);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_to_int16_are_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<5; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(20, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(5, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        TASSERT_EQUALUI(108, call_write->data[6]);
        TASSERT_EQUALUI(96, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);
        TASSERT_EQUALUI(0, call_write->data[9]);
        TASSERT_EQUALUI(0, call_write->data[10]);

        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(73, call_write->data[11 + i * 3]);
            TASSERT_EQUALUI(69, call_write->data[12 + i * 3]);
            TASSERT_EQUALUI(0, call_write->data[13 + i * 3]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(76, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][#][U][5]\n    [U][66]\n    [l][96]\n    [I][69]\n    [I][69]"
            "\n    [I][69]\n[]]", call_print->data, 76);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_to_int16_are_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<5; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(24, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(5, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        TASSERT_EQUALUI(76, call_write->data[6]);
        TASSERT_EQUALUI(96, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);
        TASSERT_EQUALUI(0, call_write->data[9]);
        TASSERT_EQUALUI(0, call_write->data[10]);
        TASSERT_EQUALUI(0, call_write->data[11]);
        TASSERT_EQUALUI(0, call_write->data[12]);
        TASSERT_EQUALUI(0, call_write->data[13]);
        TASSERT_EQUALUI(0, call_write->data[14]);

        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(73, call_write->data[15 + i * 3]);
            TASSERT_EQUALUI(69, call_write->data[16 + i * 3]);
            TASSERT_EQUALUI(0, call_write->data[17 + i * 3]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(76, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][#][U][5]\n    [U][66]\n    [L][96]\n    [I][69]\n    [I][69]"
            "\n    [I][69]\n[]]", call_print->data, 76);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_to_int16_are_other_types()
{

    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<5; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(16, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(5, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        TASSERT_EQUALUI(90, call_write->data[6]);

        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(73, call_write->data[7 + i * 3]);
            TASSERT_EQUALUI(69, call_write->data[8 + i * 3]);
            TASSERT_EQUALUI(0, call_write->data[9 + i * 3]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(72, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][#][U][5]\n    [U][66]\n    [Z]\n    [I][69]\n    [I][69]"
            "\n    [I][69]\n[]]", call_print->data, 72);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_upgraded_from_int8_int16_to_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<9; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(42, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(108, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(9, call_write->data[5]);

        for (i=0; i<9; i++)
        {
            TASSERT_EQUALUI(0 == i ? 66 : (1 == i ? 67 : 68), call_write->data[6 + i * 4]);
            TASSERT_EQUALUI(0, call_write->data[7 + i * 4]);
            TASSERT_EQUALUI(0, call_write->data[8 + i * 4]);
            TASSERT_EQUALUI(0, call_write->data[9 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*104);
        tmp_at += snprintf(tmp, 19, "[[][$][l][#][U][9]");
        for (i=0; i<9; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 10, "\n    [%u]", 0 == i ? 66 : (1 == i ? 67 : 68));
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(103, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 103);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_upgraded_from_uint8_int16_to_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<9; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(42, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(108, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(9, call_write->data[5]);

        for (i=0; i<9; i++)
        {
            TASSERT_EQUALUI(0 == i ? 66 : (1 == i ? 67 : 68), call_write->data[6 + i * 4]);
            TASSERT_EQUALUI(0, call_write->data[7 + i * 4]);
            TASSERT_EQUALUI(0, call_write->data[8 + i * 4]);
            TASSERT_EQUALUI(0, call_write->data[9 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*104);
        tmp_at += snprintf(tmp, 19, "[[][$][l][#][U][9]");
        for (i=0; i<9; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 10, "\n    [%u]", 0 == i ? 66 : (1 == i ? 67 : 68));
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(103, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 103);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_int16_to_int32_too_little()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<8; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(39, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(8, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        TASSERT_EQUALUI(73, call_write->data[6]);
        TASSERT_EQUALUI(67, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);

        for (i=0; i<6; i++)
        {
            TASSERT_EQUALUI(108, call_write->data[9 + i * 5]);
            TASSERT_EQUALUI(68, call_write->data[10 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[11 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[13 + i * 5]);
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
        tmp_at += snprintf(tmp, 37, "[[][#][U][8]\n    [U][66]\n    [I][67]");
        for (i=0; i<6; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "\n    [l][68]");
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(112, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 112);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_int16_to_int32_are_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<10; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(53, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(10, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        TASSERT_EQUALUI(73, call_write->data[6]);
        TASSERT_EQUALUI(67, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);

        TASSERT_EQUALUI(76, call_write->data[9]);
        TASSERT_EQUALUI(69, call_write->data[10]);
        TASSERT_EQUALUI(0, call_write->data[11]);
        TASSERT_EQUALUI(0, call_write->data[12]);
        TASSERT_EQUALUI(0, call_write->data[13]);
        TASSERT_EQUALUI(0, call_write->data[14]);
        TASSERT_EQUALUI(0, call_write->data[15]);
        TASSERT_EQUALUI(0, call_write->data[16]);
        TASSERT_EQUALUI(0, call_write->data[17]);

        for (i=0; i<7; i++)
        {
            TASSERT_EQUALUI(108, call_write->data[18 + i * 5]);
            TASSERT_EQUALUI(68, call_write->data[19 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[20 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[21 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[22 + i * 5]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*138);
        tmp_at += snprintf(tmp, 50, "[[][#][U][10]\n    [U][66]\n    [I][67]\n    [L][69]");
        for (i=0; i<7; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "\n    [l][68]");
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(137, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 137);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_int16_to_int32_are_other_types()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<10; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(45, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(10, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        TASSERT_EQUALUI(73, call_write->data[6]);
        TASSERT_EQUALUI(67, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);

        TASSERT_EQUALUI(90, call_write->data[9]);

        for (i=0; i<7; i++)
        {
            TASSERT_EQUALUI(108, call_write->data[10 + i * 5]);
            TASSERT_EQUALUI(68, call_write->data[11 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[13 + i * 5]);
            TASSERT_EQUALUI(0, call_write->data[14 + i * 5]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*134);
        tmp_at += snprintf(tmp, 46, "[[][#][U][10]\n    [U][66]\n    [I][67]\n    [Z]");
        for (i=0; i<7; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "\n    [l][68]");
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(133, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 133);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_upgraded_from_uint8_int16_int32_to_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<21; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(174, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
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

            TASSERT_EQUALUI(expected_first, call_write->data[6 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[7 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[8 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[9 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[10 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[11 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[13 + i * 8]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*213);
        tmp_at += snprintf(tmp, 20, "[[][$][L][#][U][21]");
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
            tmp_at += snprintf(tmp + tmp_at, 10, "\n    [%u]", expected);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(212, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 212);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_upgraded_from_int8_int16_int32_to_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<21; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(174, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
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

            TASSERT_EQUALUI(expected_first, call_write->data[6 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[7 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[8 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[9 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[10 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[11 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 8]);
            TASSERT_EQUALUI(0, call_write->data[13 + i * 8]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*213);
        tmp_at += snprintf(tmp, 20, "[[][$][L][#][U][21]");
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
            tmp_at += snprintf(tmp + tmp_at, 10, "\n    [%u]", expected);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(212, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 212);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_too_little()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<20; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(167, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(20, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        TASSERT_EQUALUI(73, call_write->data[6]);
        TASSERT_EQUALUI(67, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);

        TASSERT_EQUALUI(108, call_write->data[9]);
        TASSERT_EQUALUI(68, call_write->data[10]);
        TASSERT_EQUALUI(0, call_write->data[11]);
        TASSERT_EQUALUI(0, call_write->data[12]);
        TASSERT_EQUALUI(0, call_write->data[13]);

        for (i=0; i<17; i++)
        {
            TASSERT_EQUALUI(76, call_write->data[14 + i * 9]);
            TASSERT_EQUALUI(69, call_write->data[15 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[16 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[17 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[18 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[19 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[20 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[21 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[22 + i * 9]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*258);
        tmp_at += snprintf(tmp, 50, "[[][#][U][20]\n    [U][66]\n    [I][67]\n    [l][68]");
        for (i=0; i<17; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "\n    [L][69]");
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(257, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 257);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_are_other_types()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&obj);
    for (i=0; i<21; i++)
    {
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
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(168, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(21, call_write->data[3]);

        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(66, call_write->data[5]);

        TASSERT_EQUALUI(73, call_write->data[6]);
        TASSERT_EQUALUI(67, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);

        TASSERT_EQUALUI(108, call_write->data[9]);
        TASSERT_EQUALUI(68, call_write->data[10]);
        TASSERT_EQUALUI(0, call_write->data[11]);
        TASSERT_EQUALUI(0, call_write->data[12]);
        TASSERT_EQUALUI(0, call_write->data[13]);

        TASSERT_EQUALUI(90, call_write->data[14]);

        for (i=0; i<17; i++)
        {
            TASSERT_EQUALUI(76, call_write->data[15 + i * 9]);
            TASSERT_EQUALUI(69, call_write->data[16 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[17 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[18 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[19 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[20 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[21 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[22 + i * 9]);
            TASSERT_EQUALUI(0, call_write->data[23 + i * 9]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*266);
        tmp_at += snprintf(tmp, 58, "[[][#][U][21]\n    [U][66]\n    [I][67]\n    [l][68]"
            "\n    [Z]");
        for (i=0; i<17; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "\n    [L][69]");
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(265, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 265);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}
