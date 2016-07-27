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

void test_writer_object_empty()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(2, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(125, call_write->data[1]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(6, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][}]", call_print->data, 6);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;


    ubjs_prmtv_uint8(240, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(7, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(240, call_write->data[5]);
        TASSERT_EQUALUI(125, call_write->data[6]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(29, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][U][240]\n[}]", call_print->data, 29);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_char()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_char('r', &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(7, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(67, call_write->data[4]);
        TASSERT_EQUALUI('r', call_write->data[5]);
        TASSERT_EQUALUI(125, call_write->data[6]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(27, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][C][r]\n[}]", call_print->data, 27);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_int8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_int8(-5, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(7, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(105, call_write->data[4]);
        TASSERT_EQUALUI(251, call_write->data[5]);
        TASSERT_EQUALUI(125, call_write->data[6]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(28, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][i][-5]\n[}]", call_print->data, 28);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_int16(-32512, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(8, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(73, call_write->data[4]);
        TASSERT_EQUALUI(0, call_write->data[5]);
        TASSERT_EQUALUI(129, call_write->data[6]);
        TASSERT_EQUALUI(125, call_write->data[7]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(32, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][I][-32512]\n[}]", call_print->data, 32);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_int32(100000, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(10, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(108, call_write->data[4]);
        TASSERT_EQUALUI(160, call_write->data[5]);
        TASSERT_EQUALUI(134, call_write->data[6]);
        TASSERT_EQUALUI(1, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);
        TASSERT_EQUALUI(125, call_write->data[9]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(32, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][l][100000]\n[}]", call_print->data, 32);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_int64(1048575, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(14, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(76, call_write->data[4]);
        TASSERT_EQUALUI(255, call_write->data[5]);
        TASSERT_EQUALUI(255, call_write->data[6]);
        TASSERT_EQUALUI(15, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);
        TASSERT_EQUALUI(0, call_write->data[9]);
        TASSERT_EQUALUI(0, call_write->data[10]);
        TASSERT_EQUALUI(0, call_write->data[11]);
        TASSERT_EQUALUI(0, call_write->data[12]);
        TASSERT_EQUALUI(125, call_write->data[13]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(33, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][L][1048575]\n[}]", call_print->data, 33);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_float32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_float32((float32_t)65535.949219, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(10, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(100, call_write->data[4]);
        TASSERT_EQUALUI(243, call_write->data[5]);
        TASSERT_EQUALUI(255, call_write->data[6]);
        TASSERT_EQUALUI(127, call_write->data[7]);
        TASSERT_EQUALUI(71, call_write->data[8]);
        TASSERT_EQUALUI(125, call_write->data[9]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(38, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][d][65535.949219]\n[}]", call_print->data, 38);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_float64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_float64(12345.6789, &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(14, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(68, call_write->data[4]);
        TASSERT_EQUALUI(161, call_write->data[5]);
        TASSERT_EQUALUI(248, call_write->data[6]);
        TASSERT_EQUALUI(49, call_write->data[7]);
        TASSERT_EQUALUI(230, call_write->data[8]);
        TASSERT_EQUALUI(214, call_write->data[9]);
        TASSERT_EQUALUI(28, call_write->data[10]);
        TASSERT_EQUALUI(200, call_write->data[11]);
        TASSERT_EQUALUI(64, call_write->data[12]);
        TASSERT_EQUALUI(125, call_write->data[13]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(38, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][D][12345.678900]\n[}]", call_print->data, 38);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_null()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", ubjs_prmtv_null());

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(6, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(90, call_write->data[4]);
        TASSERT_EQUALUI(125, call_write->data[5]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(24, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][Z]\n[}]", call_print->data, 24);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_noop()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", ubjs_prmtv_noop());

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(6, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(78, call_write->data[4]);
        TASSERT_EQUALUI(125, call_write->data[5]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(24, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][N]\n[}]", call_print->data, 24);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_true()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", ubjs_prmtv_true());

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(6, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(84, call_write->data[4]);
        TASSERT_EQUALUI(125, call_write->data[5]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(24, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][T]\n[}]", call_print->data, 24);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_false()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", ubjs_prmtv_false());

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(6, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(70, call_write->data[4]);
        TASSERT_EQUALUI(125, call_write->data[5]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(24, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][F]\n[}]", call_print->data, 24);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_str()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_str(5, "rower", &item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(13, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(83, call_write->data[4]);
        TASSERT_EQUALUI(85, call_write->data[5]);
        TASSERT_EQUALUI(5, call_write->data[6]);
        TASSERT_NSTRING_EQUAL("rower", (char *)call_write->data + 7, 5);
        TASSERT_EQUALUI(125, call_write->data[12]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(37, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][S][U][5][rower]\n[}]", call_print->data, 37);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_array()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_array(&item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(7, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(91, call_write->data[4]);
        TASSERT_EQUALUI(93, call_write->data[5]);
        TASSERT_EQUALUI(125, call_write->data[6]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(27, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][[][]]\n[}]", call_print->data, 27);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_object()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    ubjs_prmtv *item;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_object(&item);
    ubjs_prmtv_object(&obj);
    ubjs_prmtv_object_set(obj, 1, "a", item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(7, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(1, call_write->data[2]);
        TASSERT_EQUALUI('a', call_write->data[3]);
        TASSERT_EQUALUI(123, call_write->data[4]);
        TASSERT_EQUALUI(125, call_write->data[5]);
        TASSERT_EQUALUI(125, call_write->data[6]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(27, call_print->len);
        TASSERT_NSTRING_EQUAL("[{]\n    [U][1][a][{][}]\n[}]", call_print->data, 27);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_count_optimized_uint8()
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
    for (i=0; i<10; i++)
    {
        snprintf(key, 2, "%01u", i);
        ubjs_prmtv_object_set(obj, 1, key,
            0 == i ? ubjs_prmtv_noop() : ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(44, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(10, call_write->data[3]);

        for (i=0; i<10; i++)
        {
            snprintf(key, 2, "%01u", i);
            TASSERT_EQUALUI(85, call_write->data[4 + i * 4]);
            TASSERT_EQUALUI(1, call_write->data[5 + i * 4]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 6 + i * 4, 1);
            TASSERT_EQUALUI(0 == i ? 78 : 90, call_write->data[7 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*188);
        tmp_at += snprintf(tmp, 14, "[{][#][U][10]");
        for (i=0; i<10; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 18, "\n    [U][1][%01u][%c]", i,
                0 == i ? 'N' : 'Z');
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(187, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 187);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_count_optimized_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    char key[5];
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
    for (i=0; i<10000; i++)
    {
        snprintf(key, 5, "%04u", i);
        ubjs_prmtv_object_set(obj, 4, key,
            0 == i ? ubjs_prmtv_noop() : ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(70005, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(73, call_write->data[2]);
        TASSERT_EQUALUI(16, call_write->data[3]);
        TASSERT_EQUALUI(39, call_write->data[4]);

        for (i=0; i<10000; i++)
        {
            snprintf(key, 5, "%04u", i);
            TASSERT_EQUALUI(85, call_write->data[5 + i * 7]);
            TASSERT_EQUALUI(4, call_write->data[6 + i * 7]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 7 + i * 7, 4);
            TASSERT_EQUALUI(0 == i ? 78 : 90, call_write->data[11 + i * 7]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*200021);
        tmp_at += snprintf(tmp, 17, "[{][#][I][10000]");
        for (i=0; i<10000; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 21, "\n    [U][4][%04u][%c]", i,
                0 == i ? 'N' : 'Z');
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(200020, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 200020);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_object_count_optimized_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
    char key[6];
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
    for (i=0; i<100000; i++)
    {
        snprintf(key, 6, "%05u", i);
        ubjs_prmtv_object_set(obj, 5, key,
            0 == i ? ubjs_prmtv_noop() : ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(800007, call_write->len);
        TASSERT_EQUALUI(123, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(108, call_write->data[2]);
        TASSERT_EQUALUI(160, call_write->data[3]);
        TASSERT_EQUALUI(134, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_EQUALUI(0, call_write->data[6]);

        for (i=0; i<100000; i++)
        {
            snprintf(key, 6, "%05u", i);
            TASSERT_EQUALUI(85, call_write->data[7 + i * 8]);
            TASSERT_EQUALUI(5, call_write->data[8 + i * 8]);
            TASSERT_NSTRING_EQUAL(key, (char *)call_write->data + 9 + i * 8, 5);
            TASSERT_EQUALUI(0 == i ? 78 : 90, call_write->data[14 + i * 8]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        unsigned int tmp_at=0;
        tmp=(char *)malloc(sizeof(char)*2100022);
        tmp_at += snprintf(tmp, 18, "[{][#][l][100000]");
        for (i=0; i<100000; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 22, "\n    [U][5][%05u][%c]", i,
                0 == i ? 'N' : 'Z');
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(2100021, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 2100021);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}
