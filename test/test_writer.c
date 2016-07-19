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

#include "test_list.h"
#include "test_writer.h"
#include "test_writer_tools.h"

void suite_writer(tcontext *context)
{
    tsuite *suite;
    TSUITE("writer", 0, 0, &suite);
    tcontext_add_suite(context, suite);

    TTEST(suite, test_writer_init_clean);
    TTEST(suite, test_writer_basics);
    TTEST(suite, test_writer_null);
    TTEST(suite, test_writer_noop);
    TTEST(suite, test_writer_true);
    TTEST(suite, test_writer_false);
    TTEST(suite, test_writer_int8);
    TTEST(suite, test_writer_uint8);
    TTEST(suite, test_writer_int16);
    TTEST(suite, test_writer_int32);
    TTEST(suite, test_writer_int64);
    TTEST(suite, test_writer_float32);
    TTEST(suite, test_writer_float64);
    TTEST(suite, test_writer_char);

    TTEST(suite, test_writer_str_uint8);
    TTEST(suite, test_writer_str_int16);
    TTEST(suite, test_writer_str_int32);

    TTEST(suite, test_writer_array_empty);
    TTEST(suite, test_writer_array_uint8);
    TTEST(suite, test_writer_array_int8);
    TTEST(suite, test_writer_array_int16);
    TTEST(suite, test_writer_array_int32);
    TTEST(suite, test_writer_array_int64);
    TTEST(suite, test_writer_array_null);
    TTEST(suite, test_writer_array_noop);
    TTEST(suite, test_writer_array_true);
    TTEST(suite, test_writer_array_false);
    TTEST(suite, test_writer_array_char);
    TTEST(suite, test_writer_array_str);
    TTEST(suite, test_writer_array_float32);
    TTEST(suite, test_writer_array_float64);
    TTEST(suite, test_writer_array_array);
    TTEST(suite, test_writer_array_object);
    TTEST(suite, test_writer_array_count_optimized_uint8);
    TTEST(suite, test_writer_array_count_optimized_int16);
    TTEST(suite, test_writer_array_count_optimized_int32);
    TTEST(suite, test_writer_array_type_optimized_null);
    TTEST(suite, test_writer_array_type_optimized_noop);
    TTEST(suite, test_writer_array_type_optimized_true);
    TTEST(suite, test_writer_array_type_optimized_false);
    TTEST(suite, test_writer_array_type_optimized_uint8);
    TTEST(suite, test_writer_array_type_optimized_char);
    TTEST(suite, test_writer_array_type_optimized_int8);
    TTEST(suite, test_writer_array_type_optimized_int16);
    TTEST(suite, test_writer_array_type_optimized_int32);
    TTEST(suite, test_writer_array_type_optimized_int64);
    TTEST(suite, test_writer_array_type_optimized_str);
    TTEST(suite, test_writer_array_type_optimized_array);
    TTEST(suite, test_writer_array_type_optimized_object);
    TTEST(suite, test_writer_array_upgraded_from_uint8_to_int16);
    TTEST(suite, test_writer_array_upgraded_from_int8_to_int16);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_to_int16_too_little);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_to_int16_are_int32);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_to_int16_are_int64);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_to_int16_are_other_types);
    TTEST(suite, test_writer_array_upgraded_from_int8_int16_to_int32);
    TTEST(suite, test_writer_array_upgraded_from_uint8_int16_to_int32);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_to_int32_too_little);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_to_int32_are_int64);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_to_int32_are_other_types);
    TTEST(suite, test_writer_array_upgraded_from_int8_int16_int32_to_int64);
    TTEST(suite, test_writer_array_upgraded_from_uint8_int16_int32_to_int64);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_too_little);
    TTEST(suite, test_writer_array_not_upgraded_from_int8_int16_int32_to_int64_are_other_types);

    TTEST(suite, test_writer_object_empty);
    TTEST(suite, test_writer_object_uint8);
    TTEST(suite, test_writer_object_int8);
    TTEST(suite, test_writer_object_int16);
    TTEST(suite, test_writer_object_int32);
    TTEST(suite, test_writer_object_int64);
    TTEST(suite, test_writer_object_null);
    TTEST(suite, test_writer_object_noop);
    TTEST(suite, test_writer_object_true);
    TTEST(suite, test_writer_object_false);
    TTEST(suite, test_writer_object_char);
    TTEST(suite, test_writer_object_str);
    TTEST(suite, test_writer_object_float32);
    TTEST(suite, test_writer_object_float64);
    TTEST(suite, test_writer_object_array);
    TTEST(suite, test_writer_object_object);
    TTEST(suite, test_writer_object_count_optimized_uint8);
    TTEST(suite, test_writer_object_count_optimized_int16);
    TTEST(suite, test_writer_object_count_optimized_int32);
    TTEST(suite, test_writer_object_type_optimized_null);
    TTEST(suite, test_writer_object_type_optimized_noop);
    TTEST(suite, test_writer_object_type_optimized_true);
    TTEST(suite, test_writer_object_type_optimized_false);
    TTEST(suite, test_writer_object_type_optimized_uint8);
    TTEST(suite, test_writer_object_type_optimized_char);
    TTEST(suite, test_writer_object_type_optimized_int8);
    TTEST(suite, test_writer_object_type_optimized_int16);
    TTEST(suite, test_writer_object_type_optimized_int32);
    TTEST(suite, test_writer_object_type_optimized_int64);
    TTEST(suite, test_writer_object_type_optimized_str);
    TTEST(suite, test_writer_object_type_optimized_array);
    TTEST(suite, test_writer_object_type_optimized_object);
    TTEST(suite, test_writer_object_upgraded_from_uint8_to_int16);
    TTEST(suite, test_writer_object_upgraded_from_int8_to_int16);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_to_int16_too_little);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_to_int16_are_int32);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_to_int16_are_int64);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_to_int16_are_other_types);
    TTEST(suite, test_writer_object_upgraded_from_int8_int16_to_int32);
    TTEST(suite, test_writer_object_upgraded_from_uint8_int16_to_int32);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_to_int32_too_little);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_to_int32_are_int64);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_to_int32_are_other_types);
    TTEST(suite, test_writer_object_upgraded_from_int8_int16_int32_to_int64);
    TTEST(suite, test_writer_object_upgraded_from_uint8_int16_int32_to_int64);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_too_little);
    TTEST(suite, test_writer_object_not_upgraded_from_int8_int16_int32_to_int64_are_other_types);
}

void test_writer_init_clean()
{
    ubjs_writer *writer=0;

    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_writer_context *writer_context=0;

    unsigned int len;

    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(&writer, 0));
    TASSERT_EQUAL(0, writer);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(writer, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(0, &writer_context));
    TASSERT_EQUAL(0, writer_context);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_free(0));

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.free = 0;
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(&writer, &context));

    context.free = writer_context_free;
    TASSERT_EQUAL(UR_OK, ubjs_writer_new(&writer, &context));
    TASSERT_NOT_EQUAL(0, writer);
    TASSERT_EQUAL(UR_OK, ubjs_writer_get_context(writer, &writer_context));
    TASSERT_EQUAL(&context, writer_context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_free(&writer));
    TASSERT_EQUAL(0, writer);
    test_list_len(wrapped->calls_free, &len);
    TASSERT_EQUALUI(1, len);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_free(&writer));
    wrapped_writer_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_writer_new(&writer, &context));
    TASSERT_EQUAL(UR_OK, ubjs_writer_free(&writer));
    test_list_len(wrapped->calls_free, &len);
    TASSERT_EQUALUI(1, len);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_basics()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    TASSERT_EQUAL(UR_OK, ubjs_writer_new(&writer, &context));

    TASSERT_EQUAL(UR_ERROR, ubjs_writer_write(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_write(writer, 0));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(0, len);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_write(0, (ubjs_prmtv *)1));

    TASSERT_EQUAL(UR_ERROR, ubjs_writer_print(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_print(writer, 0));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(0, len);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_print(0, (ubjs_prmtv *)1));

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_null()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    unsigned int len;
    would_write_call *call_write;
    would_print_call *call_print;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_prmtv_null()));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(1, call_write->len);
        TASSERT_EQUALUI(90, call_write->data[0]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, ubjs_prmtv_null()));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(3, call_print->len);
        TASSERT_NSTRING_EQUAL("[Z]", call_print->data, 3);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_noop()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_prmtv_noop()));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(1, call_write->len);
        TASSERT_EQUALUI(78, call_write->data[0]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, ubjs_prmtv_noop()));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(3, call_print->len);
        TASSERT_NSTRING_EQUAL("[N]", call_print->data, 3);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_true()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_prmtv_true()));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(1, call_write->len);
        TASSERT_EQUALUI(84, call_write->data[0]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, ubjs_prmtv_true()));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(3, call_print->len);
        TASSERT_NSTRING_EQUAL("[T]", call_print->data, 3);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_false()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, ubjs_prmtv_false()));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(1, call_write->len);
        TASSERT_EQUALUI(70, call_write->data[0]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, ubjs_prmtv_false()));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(3, call_print->len);
        TASSERT_NSTRING_EQUAL("[F]", call_print->data, 3);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_int8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    int8_t value=-17;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_int8(value, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(2, call_write->len);
        TASSERT_EQUALUI(105, call_write->data[0]);
        TASSERT_EQUALUI(239, call_write->data[1]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(8, call_print->len);
        TASSERT_NSTRING_EQUAL("[i][-17]", call_print->data, 8);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_uint8()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    int8_t value=17;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_uint8(value, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(2, call_write->len);
        TASSERT_EQUALUI(85, call_write->data[0]);
        TASSERT_EQUALUI(17, call_write->data[1]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(7, call_print->len);
        TASSERT_NSTRING_EQUAL("[U][17]", call_print->data, 7);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    int16_t value=-32512;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_int16(value, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(3, call_write->len);
        TASSERT_EQUALUI(73, call_write->data[0]);
        TASSERT_EQUALUI(0, call_write->data[1]);
        TASSERT_EQUALUI(129, call_write->data[2]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(11, call_print->len);
        TASSERT_NSTRING_EQUAL("[I][-32512]", call_print->data, 11);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_int32()
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

    ubjs_prmtv_int32(100000, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(5, call_write->len);
        TASSERT_EQUALUI(108, call_write->data[0]);
        TASSERT_EQUALUI(160, call_write->data[1]);
        TASSERT_EQUALUI(134, call_write->data[2]);
        TASSERT_EQUALUI(1, call_write->data[3]);
        TASSERT_EQUALUI(0, call_write->data[4]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(11, call_print->len);
        TASSERT_NSTRING_EQUAL("[l][100000]", call_print->data, 11);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_int64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    int64_t value=1048575;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_int64(value, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(9, call_write->len);
        TASSERT_EQUALUI(76, call_write->data[0]);
        TASSERT_EQUALUI(255, call_write->data[1]);
        TASSERT_EQUALUI(255, call_write->data[2]);
        TASSERT_EQUALUI(15, call_write->data[3]);
        TASSERT_EQUALUI(0, call_write->data[4]);
        TASSERT_EQUALUI(0, call_write->data[5]);
        TASSERT_EQUALUI(0, call_write->data[6]);
        TASSERT_EQUALUI(0, call_write->data[7]);
        TASSERT_EQUALUI(0, call_write->data[8]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(12, call_print->len);
        TASSERT_NSTRING_EQUAL("[L][1048575]", call_print->data, 12);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_float32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    float32_t value=(float32_t)65535.949219;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_float32(value, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(5, call_write->len);
        TASSERT_EQUALUI(100, call_write->data[0]);
        TASSERT_EQUALUI(243, call_write->data[1]);
        TASSERT_EQUALUI(255, call_write->data[2]);
        TASSERT_EQUALUI(127, call_write->data[3]);
        TASSERT_EQUALUI(71, call_write->data[4]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(17, call_print->len);
        TASSERT_NSTRING_EQUAL("[d][65535.949219]", call_print->data, 17);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_float64()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    float64_t value=12345.6789;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_float64(value, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(9, call_write->len);
        TASSERT_EQUALUI(68, call_write->data[0]);
        TASSERT_EQUALUI(161, call_write->data[1]);
        TASSERT_EQUALUI(248, call_write->data[2]);
        TASSERT_EQUALUI(49, call_write->data[3]);
        TASSERT_EQUALUI(230, call_write->data[4]);
        TASSERT_EQUALUI(214, call_write->data[5]);
        TASSERT_EQUALUI(28, call_write->data[6]);
        TASSERT_EQUALUI(200, call_write->data[7]);
        TASSERT_EQUALUI(64, call_write->data[8]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(17, call_print->len);
        TASSERT_NSTRING_EQUAL("[D][12345.678900]", call_print->data, 17);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_char()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    char value='R';
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    ubjs_prmtv_char(value, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(2, call_write->len);
        TASSERT_EQUALUI(67, call_write->data[0]);
        TASSERT_EQUALUI(82, call_write->data[1]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(6, call_print->len);
        TASSERT_NSTRING_EQUAL("[C][R]", call_print->data, 6);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_str_uint8()
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

    ubjs_prmtv_str(5, "rower", &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(8, call_write->len);
        TASSERT_EQUALUI(83, call_write->data[0]);
        TASSERT_EQUALUI(85, call_write->data[1]);
        TASSERT_EQUALUI(5, call_write->data[2]);
        TASSERT_NSTRING_EQUAL((char *)call_write->data + 3, "rower", 5);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(16, call_print->len);
        TASSERT_NSTRING_EQUAL("[S][U][5][rower]", call_print->data, 16);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_str_int16()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    unsigned int i;
    char *text=(char *)malloc(sizeof(char)*10000);

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    for (i=0; 10000>i; i++)
    {
        text[i]='r';
    }

    ubjs_prmtv_str(10000, text, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(10004, call_write->len);
        TASSERT_EQUALUI(83, call_write->data[0]);
        TASSERT_EQUALUI(73, call_write->data[1]);
        TASSERT_EQUALUI(16, call_write->data[2]);
        TASSERT_EQUALUI(39, call_write->data[3]);
        TASSERT_NSTRING_EQUAL((char *)call_write->data + 4, text, 10000);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        tmp = (char *)malloc(sizeof(char)*(10016));
        snprintf(tmp, 15, "[S][I][10000][");
        strncpy(tmp + 14, text, 10000);
        snprintf(tmp + 10014, 2, "]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(10015, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 10015);
        free(tmp);
    }

    free(text);
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_str_int32()
{
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_prmtv *obj;

    would_write_call *call_write;
    would_print_call *call_print;
    unsigned int len;

    unsigned int i;
    char *text=(char *)malloc(sizeof(char)*100000);

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    for (i=0; 100000>i; i++)
    {
        text[i]='r';
    }

    ubjs_prmtv_str(100000, text, &obj);

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(100006, call_write->len);
        TASSERT_EQUALUI(83, call_write->data[0]);
        TASSERT_EQUALUI(108, call_write->data[1]);
        TASSERT_EQUALUI(160, call_write->data[2]);
        TASSERT_EQUALUI(134, call_write->data[3]);
        TASSERT_EQUALUI(1, call_write->data[4]);
        TASSERT_EQUALUI(0, call_write->data[5]);
        TASSERT_NSTRING_EQUAL((char *)call_write->data + 6, text, 100000);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        char *tmp;
        tmp = (char *)malloc(sizeof(char)*(100017));
        snprintf(tmp, 16, "[S][l][100000][");
        strncpy(tmp + 15, text, 100000);
        snprintf(tmp + 100015, 2, "]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(100016, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 100016);
        free(tmp);
    }

    free(text);
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

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
        TASSERT_EQUALUI(14, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][U][240][]]", call_print->data, 14);
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
        TASSERT_EQUALUI(12, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][C][r][]]", call_print->data, 12);
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
        TASSERT_EQUALUI(13, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][i][-5][]]", call_print->data, 13);
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
        TASSERT_EQUALUI(17, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][I][-32512][]]", call_print->data, 17);
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
        TASSERT_EQUALUI(17, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][l][100000][]]", call_print->data, 17);
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
        TASSERT_EQUALUI(18, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][L][1048575][]]", call_print->data, 18);
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
        TASSERT_EQUALUI(23, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][d][65535.949219][]]", call_print->data, 23);
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
        TASSERT_EQUALUI(23, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][D][12345.678900][]]", call_print->data, 23);
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
        TASSERT_EQUALUI(9, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][Z][]]", call_print->data, 9);
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
        TASSERT_EQUALUI(9, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][N][]]", call_print->data, 9);
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
        TASSERT_EQUALUI(9, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][T][]]", call_print->data, 9);
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
        TASSERT_EQUALUI(9, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][F][]]", call_print->data, 9);
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
        TASSERT_EQUALUI(22, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][S][U][5][rower][]]", call_print->data, 22);
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
        TASSERT_EQUALUI(12, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][[][]][]]", call_print->data, 12);
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
        TASSERT_EQUALUI(12, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][{][}][]]", call_print->data, 12);
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
        tmp=(char *)malloc(sizeof(char)*47);
        tmp_at += snprintf(tmp, 17, "[[][#][U][10][N]");
        for (i=1; i<10; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 4, "[Z]");
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(46, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 46);
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
        tmp=(char *)malloc(sizeof(char)*30020);
        tmp_at += snprintf(tmp, 20, "[[][#][I][10000][N]");
        for (i=1; i<10000; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 4, "[Z]");
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(30019, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 30019);
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
        TASSERT_EQUALUI(7+100000, call_write->len);
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
        tmp=(char *)malloc(sizeof(char)*300021);
        tmp_at += snprintf(tmp, 21, "[[][#][l][100000][N]");
        for (i=1; i<100000; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 4, "[Z]");
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(300020, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 300020);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_null()
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
    for (i=0; i<3; i++)
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
        TASSERT_EQUALUI(6, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(90, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(21, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][Z][#][U][3][]]", call_print->data, 21);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_noop()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_noop());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(6, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(78, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(21, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][N][#][U][3][]]", call_print->data, 21);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_true()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_true());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(6, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(84, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(21, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][T][#][U][3][]]", call_print->data, 21);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_false()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array_add_last(obj, ubjs_prmtv_false());
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(6, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(70, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(21, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][F][#][U][3][]]", call_print->data, 21);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_uint8()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_uint8(96, &item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(9, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(85, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(96, call_write->data[6 + i]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(33, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][U][#][U][3][96][96][96][]]", call_print->data, 33);
    }
    
    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_char()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_char('r', &item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(9, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(67, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALC('r', call_write->data[6 + i]);
        }
    }
    
    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(30, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][C][#][U][3][r][r][r][]]", call_print->data, 30);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_int8()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_int8(-1, &item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(9, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(105, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(255, call_write->data[6 + i]);
        }
    }
    
    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(33, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][i][#][U][3][-1][-1][-1][]]", call_print->data, 33);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_int16()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_int16(10000, &item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(12, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(73, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(16, call_write->data[6 + i * 2]);
            TASSERT_EQUALUI(39, call_write->data[7 + i * 2]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(42, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][I][#][U][3][10000][10000][10000][]]", call_print->data, 42);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_int32()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_int32(100000, &item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(18, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(108, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(160, call_write->data[6 + i * 4]);
            TASSERT_EQUALUI(134, call_write->data[7 + i * 4]);
            TASSERT_EQUALUI(1, call_write->data[8 + i * 4]);
            TASSERT_EQUALUI(0, call_write->data[9 + i * 4]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(45, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][l][#][U][3][100000][100000][100000][]]",
            call_print->data, 45);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_int64()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_int64(1048575, &item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(30, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(76, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(255, call_write->data[6 + i * 8]);
            TASSERT_EQUALUI(255, call_write->data[7 + i * 8]);
            TASSERT_EQUALUI(15, call_write->data[8 + i * 8]);
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
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(48, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][L][#][U][3][1048575][1048575][1048575][]]",
            call_print->data, 48);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_str()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_str(0, "", &item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(12, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(83, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(85, call_write->data[6 + i * 2]);
            TASSERT_EQUALUI(0, call_write->data[7 + i * 2]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(45, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][S][#][U][3][U][0][][U][0][][U][0][][]]",
            call_print->data, 45);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_array()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_array(&item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(9, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(91, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(93, call_write->data[6 + i]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(30, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][[][#][U][3][]][]][]][]]", call_print->data, 30);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void test_writer_array_type_optimized_object()
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
    for (i=0; i<3; i++)
    {
        ubjs_prmtv_object(&item);
        ubjs_prmtv_array_add_last(obj, item);
    }

    ubjs_writer_new(&writer, &context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_write, 0, (void **)&call_write);
        TASSERT_EQUALUI(9, call_write->len);
        TASSERT_EQUALUI(91, call_write->data[0]);
        TASSERT_EQUALUI(36, call_write->data[1]);
        TASSERT_EQUALUI(123, call_write->data[2]);
        TASSERT_EQUALUI(35, call_write->data[3]);
        TASSERT_EQUALUI(85, call_write->data[4]);
        TASSERT_EQUALUI(3, call_write->data[5]);
        for (i=0; i<3; i++)
        {
            TASSERT_EQUALUI(125, call_write->data[6 + i]);
        }
    }

    TASSERT_EQUAL(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(30, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][$][{][#][U][3][}][}][}][]]", call_print->data, 30);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

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
        tmp=(char *)malloc(sizeof(char)*42);
        tmp_at += snprintf(tmp, 19, "[[][$][I][#][U][5]");
        for (i=0; i<5; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 5, "[%u]", 0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(41, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 41);
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
        tmp=(char *)malloc(sizeof(char)*42);
        tmp_at += snprintf(tmp, 19, "[[][$][I][#][U][5]");
        for (i=0; i<5; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 5, "[%u]", 0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(41, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 41);
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
        tmp=(char *)malloc(sizeof(char)*44);
        tmp_at += snprintf(tmp, 13, "[[][#][U][4]");
        for (i=0; i<4; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 8, "[%c][%u]",
                0 == i ? 'U' : 'I',
                0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(43, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 43);
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
        TASSERT_EQUALUI(50, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][#][U][5][U][66][l][96][I][69][I][69][I][69][]]", call_print->data,
            50);
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
        TASSERT_EQUALUI(50, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][#][U][5][U][66][L][96][I][69][I][69][I][69][]]", call_print->data,
            50);
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
        TASSERT_EQUALUI(46, call_print->len);
        TASSERT_NSTRING_EQUAL("[[][#][U][5][U][66][Z][I][69][I][69][I][69][]]", call_print->data,
            46);
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
        tmp=(char *)malloc(sizeof(char)*58);
        tmp_at += snprintf(tmp, 19, "[[][$][l][#][U][9]");
        for (i=0; i<9; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 5, "[%u]", 0 == i ? 66 : (1 == i ? 67 : 68));
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(57, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 57);
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
        tmp=(char *)malloc(sizeof(char)*58);
        tmp_at += snprintf(tmp, 19, "[[][$][l][#][U][9]");
        for (i=0; i<9; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 5, "[%u]", 0 == i ? 66 : (1 == i ? 67 : 68));
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(57, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 57);
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
        tmp=(char *)malloc(sizeof(char)*72);
        tmp_at += snprintf(tmp, 27, "[[][#][U][8][U][66][I][67]");
        for (i=0; i<6; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 8, "[l][68]");
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(71, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 71);
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
        tmp=(char *)malloc(sizeof(char)*87);
        tmp_at += snprintf(tmp, 35, "[[][#][U][10][U][66][I][67][L][69]");
        for (i=0; i<7; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 8, "[l][68]");
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(86, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 86);
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
        tmp=(char *)malloc(sizeof(char)*83);
        tmp_at += snprintf(tmp, 31, "[[][#][U][10][U][66][I][67][Z]");
        for (i=0; i<7; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 8, "[l][68]");
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(82, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 82);
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
        tmp=(char *)malloc(sizeof(char)*107);
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
            tmp_at += snprintf(tmp + tmp_at, 5, "[%u]", expected);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(106, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 106);
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
        tmp=(char *)malloc(sizeof(char)*107);
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
            tmp_at += snprintf(tmp + tmp_at, 5, "[%u]", expected);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(106, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 106);
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
        tmp=(char *)malloc(sizeof(char)*157);
        tmp_at += snprintf(tmp, 35, "[[][#][U][20][U][66][I][67][l][68]");
        for (i=0; i<17; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 8, "[L][69]");
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(156, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 156);
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
        tmp=(char *)malloc(sizeof(char)*160);
        tmp_at += snprintf(tmp, 38, "[[][#][U][21][U][66][I][67][l][68][Z]");
        for (i=0; i<17; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 8, "[L][69]");
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[]]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(159, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 159);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

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
        TASSERT_EQUALUI(23, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][U][240][}]", call_print->data, 23);
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
        TASSERT_EQUALUI(21, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][C][r][}]", call_print->data, 21);
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
        TASSERT_EQUALUI(22, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][i][-5][}]", call_print->data, 22);
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
        TASSERT_EQUALUI(26, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][I][-32512][}]", call_print->data, 26);
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
        TASSERT_EQUALUI(26, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][l][100000][}]", call_print->data, 26);
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
        TASSERT_EQUALUI(27, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][L][1048575][}]", call_print->data, 27);
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
        TASSERT_EQUALUI(32, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][d][65535.949219][}]", call_print->data, 32);
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
        TASSERT_EQUALUI(32, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][D][12345.678900][}]", call_print->data, 32);
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
        TASSERT_EQUALUI(18, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][Z][}]", call_print->data, 18);
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
        TASSERT_EQUALUI(18, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][N][}]", call_print->data, 18);
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
        TASSERT_EQUALUI(18, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][T][}]", call_print->data, 18);
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
        TASSERT_EQUALUI(18, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][F][}]", call_print->data, 18);
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
        TASSERT_EQUALUI(31, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][S][U][5][rower][}]", call_print->data, 31);
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
        TASSERT_EQUALUI(21, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][[][]][}]", call_print->data, 21);
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
        TASSERT_EQUALUI(21, call_print->len);
        TASSERT_NSTRING_EQUAL("[{][U][1][a][{][}][}]", call_print->data, 21);
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
        tmp=(char *)malloc(sizeof(char)*137);
        tmp_at += snprintf(tmp, 14, "[{][#][U][10]");
        for (i=0; i<10; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "[U][1][%01u][%c]", i,
                0 == i ? 'N' : 'Z');
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(136, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 136);
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
        tmp=(char *)malloc(sizeof(char)*150020);
        tmp_at += snprintf(tmp, 17, "[{][#][I][10000]");
        for (i=0; i<10000; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 16, "[U][4][%04u][%c]", i,
                0 == i ? 'N' : 'Z');
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(150019, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 150019);
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
        tmp=(char *)malloc(sizeof(char)*1600021);
        tmp_at += snprintf(tmp, 18, "[{][#][l][100000]");
        for (i=0; i<100000; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][5][%05u][%c]", i,
                0 == i ? 'N' : 'Z');
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(1600020, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 1600020);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

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
        tmp=(char *)malloc(sizeof(char)*49);
        tmp_at += snprintf(tmp, 19, "[{][$][Z][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 10, "[U][1][%01u]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(48, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 48);
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
        tmp=(char *)malloc(sizeof(char)*49);
        tmp_at += snprintf(tmp, 19, "[{][$][N][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 10, "[U][1][%01u]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(48, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 48);
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
        tmp=(char *)malloc(sizeof(char)*49);
        tmp_at += snprintf(tmp, 19, "[{][$][T][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 10, "[U][1][%01u]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(48, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 48);
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
        tmp=(char *)malloc(sizeof(char)*49);
        tmp_at += snprintf(tmp, 19, "[{][$][F][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 10, "[U][1][%01u]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(48, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 48);
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
        tmp=(char *)malloc(sizeof(char)*61);
        tmp_at += snprintf(tmp, 19, "[{][$][U][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 14, "[U][1][%01u][96]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(60, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 60);
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
        tmp=(char *)malloc(sizeof(char)*58);
        tmp_at += snprintf(tmp, 19, "[{][$][C][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "[U][1][%01u][r]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(57, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 57);
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
        tmp=(char *)malloc(sizeof(char)*61);
        tmp_at += snprintf(tmp, 19, "[{][$][i][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 14, "[U][1][%01u][-5]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(60, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 60);
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
        tmp=(char *)malloc(sizeof(char)*70);
        tmp_at += snprintf(tmp, 19, "[{][$][I][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][1][%01u][10000]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(69, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 69);
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
        tmp=(char *)malloc(sizeof(char)*73);
        tmp_at += snprintf(tmp, 19, "[{][$][l][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 18, "[U][1][%01u][100000]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(72, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 72);
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
        tmp=(char *)malloc(sizeof(char)*76);
        tmp_at += snprintf(tmp, 19, "[{][$][L][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 19, "[U][1][%01u][1048575]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(75, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 75);
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
        tmp=(char *)malloc(sizeof(char)*73);
        tmp_at += snprintf(tmp, 19, "[{][$][S][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 18, "[U][1][%01u][U][0][]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(72, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 72);
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
        tmp=(char *)malloc(sizeof(char)*58);
        tmp_at += snprintf(tmp, 19, "[{][$][[][#][U][3]");
        for (i=0; i<3; i++)
        {
            tmp_at += snprintf(tmp + tmp_at, 13, "[U][1][%01u][]]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(57, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 57);
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
        tmp=(char *)malloc(sizeof(char)*58);
        tmp_at += snprintf(tmp, 19, "[{][$][{][#][U][3]");
        for (i=0; i<3; i++)
        {
        tmp_at += snprintf(tmp + tmp_at, 13, "[U][1][%01u][}]", i);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(57, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 57);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

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
        tmp=(char *)malloc(sizeof(char)*87);
        tmp_at += snprintf(tmp, 19, "[{][$][I][#][U][5]");
        for (i=0; i<5; i++)
        {
            snprintf(key, 2, "%01u", i);
            tmp_at += snprintf(tmp + tmp_at, 14, "[U][1][%s][%u]", key, 0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(86, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 86);
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
        tmp=(char *)malloc(sizeof(char)*87);
        tmp_at += snprintf(tmp, 19, "[{][$][I][#][U][5]");
        for (i=0; i<5; i++)
        {
            snprintf(key, 2, "%01u", i);
            tmp_at += snprintf(tmp + tmp_at, 14, "[U][1][%s][%u]", key, 0 == i ? 66 : 69);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(86, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 86);
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
        tmp=(char *)malloc(sizeof(char)*80);
        tmp_at += snprintf(tmp, 29, "[{][#][U][4][U][1][0][U][66]");
        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 1);
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][1][%s][I][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(79, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 79);
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
        tmp=(char *)malloc(sizeof(char)*96);
        tmp_at += snprintf(tmp, 45, "[{][#][U][5][U][1][0][U][66][U][1][1][l][96]");
        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][1][%s][I][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(95, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 95);
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
        tmp=(char *)malloc(sizeof(char)*96);
        tmp_at += snprintf(tmp, 45, "[{][#][U][5][U][1][0][U][66][U][1][1][L][96]");
        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][1][%s][I][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(95, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 95);
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
        tmp=(char *)malloc(sizeof(char)*92);
        tmp_at += snprintf(tmp, 41, "[{][#][U][5][U][1][0][U][66][U][1][1][Z]");
        for (i=0; i<3; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][1][%s][I][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(91, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 91);
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
        tmp=(char *)malloc(sizeof(char)*139);
        tmp_at += snprintf(tmp, 19, "[{][$][l][#][U][9]");
        for (i=0; i<9; i++)
        {
            snprintf(key, 2, "%01u", i);
            tmp_at += snprintf(tmp + tmp_at,14, "[U][1][%s][%u]",
                key, 
                0 == i ? 66 : (1 == i ? 67 : 68));
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(138, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 138);
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
        tmp=(char *)malloc(sizeof(char)*139);
        tmp_at += snprintf(tmp, 19, "[{][$][l][#][U][9]");
        for (i=0; i<9; i++)
        {
            snprintf(key, 2, "%01u", i);
            tmp_at += snprintf(tmp + tmp_at,14, "[U][1][%s][%u]",
                key, 
                0 == i ? 66 : (1 == i ? 67 : 68));
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(138, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 138);
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
        tmp=(char *)malloc(sizeof(char)*144);
        tmp_at += snprintf(tmp, 45, "[{][#][U][8][U][1][0][U][66][U][1][1][I][67]");
        for (i=0; i<6; i++)
        {
            snprintf(key, 2, "%01u", i + 2);
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][1][%s][l][68]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(143, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 143);
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
        tmp=(char *)malloc(sizeof(char)*177);
        tmp_at += snprintf(tmp, 62, "[{][#][U][10][U][1][0][U][66][U][1][1][I][67][U][1][2][L][69]");
        for (i=0; i<7; i++)
        {
            snprintf(key, 2, "%01u", i + 3);
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][1][%s][l][68]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(176, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 176);
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
        tmp=(char *)malloc(sizeof(char)*173);
        tmp_at += snprintf(tmp, 58, "[{][#][U][10][U][1][0][U][66][U][1][1][I][67][U][1][2][Z]");
        for (i=0; i<7; i++)
        {
            snprintf(key, 2, "%01u", i + 3);
            tmp_at += snprintf(tmp + tmp_at, 17, "[U][1][%s][l][68]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(172, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 172);
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
        tmp=(char *)malloc(sizeof(char)*317);
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
            tmp_at += snprintf(tmp + tmp_at, 15, "[U][2][%s][%u]", key, expected);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(316, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 316);
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
        tmp=(char *)malloc(sizeof(char)*317);
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
            tmp_at += snprintf(tmp + tmp_at, 15, "[U][2][%s][%u]", key, expected);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(316, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 316);
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
        tmp=(char *)malloc(sizeof(char)*357);
        tmp_at += snprintf(tmp, 65, "[{][#][U][20][U][2][00][U][66][U][2][01][I][67]"
            "[U][2][02][l][68]");
        for (i=0; i<17; i++)
        {
            snprintf(key, 3, "%02u", i + 3);
            tmp_at += snprintf(tmp + tmp_at, 18, "[U][2][%s][L][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(356, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 356);
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
        tmp=(char *)malloc(sizeof(char)*387);
        tmp_at += snprintf(tmp, 78, "[{][#][U][22][U][2][00][U][66][U][2][01][I][67][U][2][02][l][68][U][2][03][Z]");
        for (i=0; i<18; i++)
        {
            snprintf(key, 3, "%02u", i + 4);
            tmp_at += snprintf(tmp + tmp_at, 18, "[U][2][%s][L][69]", key);
        }
        tmp_at += snprintf(tmp + tmp_at, 4, "[}]");

        test_list_get(wrapped->calls_would_print, 0, (void **)&call_print);
        TASSERT_EQUALUI(386, call_print->len);
        TASSERT_NSTRING_EQUAL(tmp, call_print->data, 386);
        free(tmp);
    }

    ubjs_prmtv_free(&obj);
    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}
