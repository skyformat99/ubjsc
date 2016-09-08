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

void test_parser_bad_init()
{
    ubjs_parser *parser=0;
    ubjs_parser_context context;
    context.parsed=0;
    context.error=0;
    context.free=0;

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=parser_context_parsed;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=0;
    context.error=parser_context_error;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=parser_context_parsed;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=0;
    context.error=0;
    context.free=parser_context_free;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=parser_context_parsed;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(&parser, &context));

    context.parsed=0;
    context.error=parser_context_error;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(&parser, &context));
}

void test_parser_init_clean()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_context *parser_context=0;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(&parser, 0));
    TASSERT_EQUAL(0, parser);
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_new(0, &context));

    TASSERT_EQUALI(UR_OK, ubjs_parser_new(&parser, &context));
    TASSERT_NOT_EQUAL(0, parser);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_get_context(0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_get_context(parser, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_get_context(0, &parser_context));
    TASSERT_EQUAL(0, parser_context);
    TASSERT_EQUALI(UR_OK, ubjs_parser_get_context(parser, &parser_context));
    TASSERT_EQUAL(&context, parser_context);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_free(0));
    TASSERT_EQUALI(UR_OK, ubjs_parser_free(&parser));
    TASSERT_EQUAL(0, parser);
    test_list_len(wrapped->calls_free, &len);
    TASSERT_EQUALI(1, len);
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_free(&parser));
    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_new(&parser, &context));
    TASSERT_EQUALI(UR_OK, ubjs_parser_free(&parser));
    test_list_len(wrapped->calls_free, &len);
    TASSERT_EQUALI(1, len);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_basics()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data;
    unsigned int message_length;
    unsigned int len;
    char message_text[] = {0};
    void *mock_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    TASSERT_EQUALI(UR_OK, ubjs_parser_new(&parser, &context));

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(0, 0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, 0, 0));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, &data, 0));

    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_error_get_message_length(0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_error_get_message_length(0, &message_length));
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_error_get_message_length((ubjs_parser_error *)&mock_error,
        0));

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_error_get_message_text(0, 0));
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_error_get_message_text(0, message_text));
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_error_get_message_text((ubjs_parser_error *)&mock_error,
        0));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_unknown_marker()
{
    uint8_t data[] = {0};
    sp_verify_error(1, data, "At 0 [0] unknown marker");
}

void __test_parser_null(ubjs_prmtv *obj)
{
    TASSERT_EQUAL(ubjs_prmtv_null(), obj);
}

void test_parser_null()
{
    uint8_t data[] = {90};
    sp_verify_parsed(1, data, __test_parser_null);
}

void __test_parser_noop(ubjs_prmtv *obj)
{
    TASSERT_EQUAL(ubjs_prmtv_noop(), obj);
}

void test_parser_noop()
{
    uint8_t data[] = {78};
    sp_verify_parsed(1, data, __test_parser_noop);
}

void __test_parser_true(ubjs_prmtv *obj)
{
    TASSERT_EQUAL(ubjs_prmtv_true(), obj);
}

void test_parser_true()
{
    uint8_t data[] = {84};
    sp_verify_parsed(1, data, __test_parser_true);
}

void __test_parser_false(ubjs_prmtv *obj)
{
    TASSERT_EQUAL(ubjs_prmtv_false(), obj);
}

void test_parser_false()
{
    uint8_t data[] = {70};
    sp_verify_parsed(1, data, __test_parser_false);
}

void __test_parser_int8(ubjs_prmtv *obj)
{
    int8_t value;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(obj, &value));
    TASSERT_EQUAL(-127, value);
}

void test_parser_int8()
{
    uint8_t data[]= {105, 129};
    sp_verify_parsed(2, data, __test_parser_int8);
}

void __test_parser_uint8(ubjs_prmtv *obj)
{
    uint8_t value;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(obj, &value));
    TASSERT_EQUAL(129, value);
}

void test_parser_uint8()
{
    uint8_t data[]= {85, 129};
    sp_verify_parsed(2, data, __test_parser_uint8);
}

void __test_parser_int16(ubjs_prmtv *obj)
{
    int16_t value;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(obj, &value));
    TASSERT_EQUAL(-32512, value);
}

void test_parser_int16()
{
    uint8_t data[]= {73, 0, 129};
    sp_verify_parsed(3, data, __test_parser_int16);
}

void __test_parser_int32(ubjs_prmtv *obj)
{
    int32_t value;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(obj, &value));
    TASSERT_EQUAL(-2130673408, value);
}

void test_parser_int32()
{
    uint8_t data[]= {108, 0, 129, 0, 129};
    sp_verify_parsed(5, data, __test_parser_int32);
}

void __test_parser_int64(ubjs_prmtv *obj)
{
    int64_t value = 0;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(obj, &value));
    TASSERT_EQUAL(140728965726721, value);
}

void test_parser_int64()
{
    uint8_t data[]= {76, 1, 2, 3, 4, 5, 6, 7, 8};
    sp_verify_parsed(9, data, __test_parser_int64);
}

void __test_parser_float32(ubjs_prmtv *obj)
{
    float32_t value;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_float32_get(obj, &value));
    TASSERT_EQUAL(4, value);
}

void test_parser_float32()
{
    uint8_t data[]= {100, 0, 0, 128, 64};
    sp_verify_parsed(5, data, __test_parser_float32);
}

void __test_parser_float64(ubjs_prmtv *obj)
{
    float64_t value;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_float64_get(obj, &value));
    TASSERT_EQUAL(512.0, value);
}

void test_parser_float64()
{
    uint8_t data[]= {68, 0, 0, 0, 0, 0, 0, 128, 64};
    sp_verify_parsed(9, data, __test_parser_float64);
}

void __test_parser_char(ubjs_prmtv *obj)
{
    char value;
    ubjs_bool ret;

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);

    TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(obj, &value));
    TASSERT_EQUALC('R', value);
}

void test_parser_char()
{
    uint8_t data[]= {67, 82};
    sp_verify_parsed(2, data, __test_parser_char);
}
