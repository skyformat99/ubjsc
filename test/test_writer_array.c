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

void test_writer_array_empty()
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

    ubjs_prmtv_array(&obj);
    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));

    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(2, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(93, call_write->data[1]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(6, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][]]", call_print->data, 6);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_uint8()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(4, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(240, call_write->data[2]);
        TASSERT_EQUALUI(93, call_write->data[3]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(20, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [U][240]\n[]]", call_print->data, 20);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_char()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(4, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(67, call_write->data[1]);
        TASSERT_EQUALUI('r', call_write->data[2]);
        TASSERT_EQUALUI(93, call_write->data[3]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(18, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [C][r]\n[]]", call_print->data, 18);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_int8()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(4, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(105, call_write->data[1]);
        TASSERT_EQUALUI(251, call_write->data[2]);
        TASSERT_EQUALUI(93, call_write->data[3]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(19, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [i][-5]\n[]]", call_print->data, 19);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_int16()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(5, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(73, call_write->data[1]);
        TASSERT_EQUALUI(0, call_write->data[2]);
        TASSERT_EQUALUI(129, call_write->data[3]);
        TASSERT_EQUALUI(93, call_write->data[4]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(23, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [I][-32512]\n[]]", call_print->data, 23);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_int32()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(7, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(108, call_write->data[1]);
        TASSERT_EQUALUI(160, call_write->data[2]);
        TASSERT_EQUALUI(134, call_write->data[3]);
        TASSERT_EQUALUI(1, call_write->data[4]);
        TASSERT_EQUALUI(0, call_write->data[5]);
        TASSERT_EQUALUI(93, call_write->data[6]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(23, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [l][100000]\n[]]", call_print->data, 23);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_int64()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(11, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(76, call_write->data[1]);
        TASSERT_EQUALUI(255, call_write->data[2]);
        TASSERT_EQUALUI(255, call_write->data[3]);
        TASSERT_EQUALUI(15, call_write->data[4]);
        TASSERT_EQUALUI(0, call_write->data[5]);
        TASSERT_EQUALUI(0, call_write->data[6]);
        TASSERT_EQUALUI(0, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);
        TASSERT_EQUALUI(0, call_write->data[9]);
        TASSERT_EQUALUI(93, call_write->data[10]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(24, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [L][1048575]\n[]]", call_print->data, 24);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_float32()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(7, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(100, call_write->data[1]);
        TASSERT_EQUALUI(243, call_write->data[2]);
        TASSERT_EQUALUI(255, call_write->data[3]);
        TASSERT_EQUALUI(127, call_write->data[4]);
        TASSERT_EQUALUI(71, call_write->data[5]);
        TASSERT_EQUALUI(93, call_write->data[6]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(29, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [d][65535.949219]\n[]]", call_print->data, 29);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_float64()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(11, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(68, call_write->data[1]);
        TASSERT_EQUALUI(161, call_write->data[2]);
        TASSERT_EQUALUI(248, call_write->data[3]);
        TASSERT_EQUALUI(49, call_write->data[4]);
        TASSERT_EQUALUI(230, call_write->data[5]);
        TASSERT_EQUALUI(214, call_write->data[6]);
        TASSERT_EQUALUI(28, call_write->data[7]);
        TASSERT_EQUALUI(200, call_write->data[8]);
        TASSERT_EQUALUI(64, call_write->data[9]);
        TASSERT_EQUALUI(93, call_write->data[10]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(29, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [D][12345.678900]\n[]]", call_print->data, 29);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_null()
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

    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null());

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(3, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(90, call_write->data[1]);
        TASSERT_EQUALUI(93, call_write->data[2]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(15, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [Z]\n[]]", call_print->data, 15);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_noop()
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

    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_noop());

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(3, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(78, call_write->data[1]);
        TASSERT_EQUALUI(93, call_write->data[2]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(15, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [N]\n[]]", call_print->data, 15);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_true()
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


    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_true());

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(3, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(84, call_write->data[1]);
        TASSERT_EQUALUI(93, call_write->data[2]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(15, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [T]\n[]]", call_print->data, 15);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_false()
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

    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_false());

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(3, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(70, call_write->data[1]);
        TASSERT_EQUALUI(93, call_write->data[2]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(15, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [F]\n[]]", call_print->data, 15);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_str()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(10, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(83, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(5, call_write->data[3]);
        TASSERT_NSTRING_EQUAL("rower", (char *)call_write->data + 4, 5);
        TASSERT_EQUALUI(93, call_write->data[9]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(28, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [S][U][5][rower]\n[]]", call_print->data, 28);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_array()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(4, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(91, call_write->data[1]);
        TASSERT_EQUALUI(93, call_write->data[2]);
        TASSERT_EQUALUI(93, call_write->data[3]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(18, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [[][]]\n[]]", call_print->data, 18);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_object()
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
    ubjs_prmtv_array(&obj);
    ubjs_prmtv_array_add_last(obj, item);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(4, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(123, call_write->data[1]);
        TASSERT_EQUALUI(125, call_write->data[2]);
        TASSERT_EQUALUI(93, call_write->data[3]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(18, call_print->len);
        TASSERT_NSTRING_EQUAL("[[]\n    [{][}]\n[]]", call_print->data, 18);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_count_optimized_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
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
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_noop());
    for (i=1; i<10; i++)
    {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(4+10, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(10, call_write->data[3]);
        TASSERT_EQUALUI(78, call_write->data[4]);
        for (i=1; i<10; i++)
        {
            TASSERT_EQUALUI(90, call_write->data[4+i]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        unsigned int tmp_at=0;
        char *tmp;
        tmp=(char *)malloc(sizeof(char)*98);
        tmp_at += snprintf(tmp, 22, "[[][#][U][10]\n    [N]");
        for (i=1; i<10; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 9, "\n    [Z]");
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(97, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 97);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_count_optimized_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
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
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_noop());
    for (i=1; i<10000; i++)
    {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(5+10000, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);
        TASSERT_EQUALUI(73, call_write->data[2]);
        TASSERT_EQUALUI(16, call_write->data[3]);
        TASSERT_EQUALUI(39, call_write->data[4]);
        TASSERT_EQUALUI(78, call_write->data[5]);
        for (i=1; i<10000; i++)
        {
            TASSERT_EQUALUI(90, call_write->data[5+i]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        unsigned int tmp_at=0;
        char *tmp;
        tmp=(char *)malloc(sizeof(char)*80021);
        tmp_at += snprintf(tmp, 25, "[[][#][I][10000]\n    [N]");
        for (i=1; i<10000; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 9, "\n    [Z]");
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(80020, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 80020);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_count_optimized_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;
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
    ubjs_prmtv_array_add_last(obj, ubjs_prmtv_noop());
    for (i=1; i<100000; i++)
    {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_null());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(100007, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(35, call_write->data[1]);

        TASSERT_EQUALUI(108, call_write->data[2]);
        TASSERT_EQUALUI(160, call_write->data[3]);
        TASSERT_EQUALUI(134, call_write->data[4]);
        TASSERT_EQUALUI(1, call_write->data[5]);
        TASSERT_EQUALUI(0, call_write->data[6]);
        TASSERT_EQUALUI(78, call_write->data[7]);
        for (i=1; i<100000; i++)
        {
            TASSERT_EQUALUI(90, call_write->data[7+i]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        unsigned int tmp_at=0;
        char *tmp;
        tmp=(char *)malloc(sizeof(char)*800022);
        tmp_at += snprintf(tmp, 26, "[[][#][l][100000]\n    [N]");
        for (i=1; i<100000; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 9, "\n    [Z]");
        }
        tmp_at += snprintf(tmp + tmp_at, 5, "\n[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(800021, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 800021);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}
