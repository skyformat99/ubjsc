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

void test_writer_object_type_optimized_null()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_object_set(obj, 1, key, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(15, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(90, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 3]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 3]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 3, 1);
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
        tmp_at += snprintf(tmp, 19, "[{][$][Z][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 15, "\n    [U][1][%01u]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(64, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 64);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_noop()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_object_set(obj, 1, key, ubjs_prmtv_noop());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(15, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(78, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 3]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 3]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 3, 1);
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
        tmp_at += snprintf(tmp, 19, "[{][$][N][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 15, "\n    [U][1][%01u]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(64, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 64);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_true()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_object_set(obj, 1, key, ubjs_prmtv_true());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(15, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(84, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 3]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 3]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 3, 1);
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
        tmp_at += snprintf(tmp, 19, "[{][$][T][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 15, "\n    [U][1][%01u]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(64, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 64);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_false()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_object_set(obj, 1, key, ubjs_prmtv_false());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(15, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(70, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 3]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 3]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 3, 1);
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
        tmp_at += snprintf(tmp, 19, "[{][$][F][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 15, "\n    [U][1][%01u]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(64, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 64);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_uint8(96, &item);
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(18, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 4]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 4]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 4, 1);
            TASSERT_EQUALUI(96, call_write->data[9 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*77);
        tmp_at += snprintf(tmp, 19, "[{][$][U][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 19, "\n    [U][1][%01u][96]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(76, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 76);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_char()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_char('r', &item);
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(18, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(67, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 4]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 4]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 4, 1);
            TASSERT_EQUALC('r', call_write->data[9 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*74);
        tmp_at += snprintf(tmp, 19, "[{][$][C][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 18, "\n    [U][1][%01u][r]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(73, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 73);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_int8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_int8(-5, &item);
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(18, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(105, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 4]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 4]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 4, 1);
            TASSERT_EQUALUI(251, call_write->data[9 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*77);
        tmp_at += snprintf(tmp, 19, "[{][$][i][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 19, "\n    [U][1][%01u][-5]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(76, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 76);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_int16(10000, &item);
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(21, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(73, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 5]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 5]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 5, 1);
            TASSERT_EQUALUI(16, call_write->data[9 + i * 5]);
            TASSERT_EQUALUI(39, call_write->data[10 + i * 5]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*86);
        tmp_at += snprintf(tmp, 19, "[{][$][I][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][1][%01u][10000]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(85, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 85);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_int32(100000, &item);
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
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(108, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 7]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 7]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 7, 1);
            TASSERT_EQUALUI(160, call_write->data[9 + i * 7]);
            TASSERT_EQUALUI(134, call_write->data[10 + i * 7]);
            TASSERT_EQUALUI(1, call_write->data[11 + i * 7]);
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
        tmp=(char *)malloc(sizeof(char)*89);
        tmp_at += snprintf(tmp, 19, "[{][$][l][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 23, "\n    [U][1][%01u][100000]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(88, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 88);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_int64(1048575, &item);
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
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(76, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 11]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 11]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 11, 1);
            TASSERT_EQUALUI(255, call_write->data[9 + i * 11]);
            TASSERT_EQUALUI(255, call_write->data[10 + i * 11]);
            TASSERT_EQUALUI(15, call_write->data[11 + i * 11]);
            TASSERT_EQUALUI(0, call_write->data[12 + i * 11]);
            TASSERT_EQUALUI(0, call_write->data[13 + i * 11]);
            TASSERT_EQUALUI(0, call_write->data[14 + i * 11]);
            TASSERT_EQUALUI(0, call_write->data[15 + i * 11]);
            TASSERT_EQUALUI(0, call_write->data[16 + i * 11]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*92);
        tmp_at += snprintf(tmp, 19, "[{][$][L][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 24, "\n    [U][1][%01u][1048575]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(91, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 91);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_str()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_str(0, "", &item);
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(21, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(83, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 5]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 5]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 5, 1);
            TASSERT_EQUALUI(85, call_write->data[9 + i * 5]);
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
        tmp=(char *)malloc(sizeof(char)*89);
        tmp_at += snprintf(tmp, 19, "[{][$][S][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 23, "\n    [U][1][%01u][U][0][]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(88, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 88);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_array()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_array(&item);
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(18, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(91, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 4]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 4]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 4, 1);
            TASSERT_EQUALUI(93, call_write->data[9 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*74);
        tmp_at += snprintf(tmp, 19, "[{][$][[][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 18, "\n    [U][1][%01u][]]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(73, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 73);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_type_optimized_object()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;
    char key[2];
    unsigned int i;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    for (i=0; i<3; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_object(&item);
        ubjs_prmtv_object_set(obj, 1, key, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(18, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(123, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);

        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[6 + i * 4]);
            TASSERT_EQUALUI(1, call_write->data[7 + i * 4]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 8 + i * 4, 1);
            TASSERT_EQUALUI(125, call_write->data[9 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*74);
        tmp_at += snprintf(tmp, 19, "[{][$][{][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 18, "\n    [U][1][%01u][}]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(73, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 73);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}
