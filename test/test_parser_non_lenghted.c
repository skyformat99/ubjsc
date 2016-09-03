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

void suite_parser(tcontext *context)
{
    tsuite *suite;
    TSUITE("parser", 0, 0, &suite);
    tcontext_add_suite(context, suite);

    TTEST(suite, test_parser_bad_init);
    TTEST(suite, test_parser_init_clean);
    TTEST(suite, test_parser_basics);
    TTEST(suite, test_parser_unknown_marker);
    TTEST(suite, test_parser_null);
    TTEST(suite, test_parser_noop);
    TTEST(suite, test_parser_true);
    TTEST(suite, test_parser_false);
    TTEST(suite, test_parser_int8);
    TTEST(suite, test_parser_uint8);
    TTEST(suite, test_parser_int16);
    TTEST(suite, test_parser_int32);
    TTEST(suite, test_parser_int64);
    TTEST(suite, test_parser_float32);
    TTEST(suite, test_parser_float64);
    TTEST(suite, test_parser_char);

    TTEST(suite, test_parser_str_empty);
    TTEST(suite, test_parser_str_null);
    TTEST(suite, test_parser_str_noop);
    TTEST(suite, test_parser_str_true);
    TTEST(suite, test_parser_str_false);
    TTEST(suite, test_parser_str_uint8);
    TTEST(suite, test_parser_str_int8);
    TTEST(suite, test_parser_str_int8_negative);
    TTEST(suite, test_parser_str_int16);
    TTEST(suite, test_parser_str_int16_negative);
    TTEST(suite, test_parser_str_int32);
    TTEST(suite, test_parser_str_int32_negative);
    TTEST(suite, test_parser_str_int64);
    TTEST(suite, test_parser_str_float32);
    TTEST(suite, test_parser_str_float64);
    TTEST(suite, test_parser_str_char);
    TTEST(suite, test_parser_str_str);
    TTEST(suite, test_parser_str_hpn);
    TTEST(suite, test_parser_str_array);
    TTEST(suite, test_parser_str_object);

    TTEST(suite, test_parser_hpn_empty);
    TTEST(suite, test_parser_hpn_null);
    TTEST(suite, test_parser_hpn_noop);
    TTEST(suite, test_parser_hpn_true);
    TTEST(suite, test_parser_hpn_false);
    TTEST(suite, test_parser_hpn_uint8);
    TTEST(suite, test_parser_hpn_int8);
    TTEST(suite, test_parser_hpn_int8_negative);
    TTEST(suite, test_parser_hpn_int16);
    TTEST(suite, test_parser_hpn_int16_negative);
    TTEST(suite, test_parser_hpn_int32);
    TTEST(suite, test_parser_hpn_int32_negative);
    TTEST(suite, test_parser_hpn_int64);
    TTEST(suite, test_parser_hpn_float32);
    TTEST(suite, test_parser_hpn_float64);
    TTEST(suite, test_parser_hpn_char);
    TTEST(suite, test_parser_hpn_str);
    TTEST(suite, test_parser_hpn_hpn);
    TTEST(suite, test_parser_hpn_array);
    TTEST(suite, test_parser_hpn_object);

    TTEST(suite, test_parser_array_empty);
    TTEST(suite, test_parser_array_unknown_marker);
    TTEST(suite, test_parser_array_uint8);
    TTEST(suite, test_parser_array_int8);
    TTEST(suite, test_parser_array_int16);
    TTEST(suite, test_parser_array_int32);
    TTEST(suite, test_parser_array_null);
    TTEST(suite, test_parser_array_noop);
    TTEST(suite, test_parser_array_true);
    TTEST(suite, test_parser_array_false);
    TTEST(suite, test_parser_array_char);
    TTEST(suite, test_parser_array_str);
    TTEST(suite, test_parser_array_hpn);
    TTEST(suite, test_parser_array_int64);
    TTEST(suite, test_parser_array_float32);
    TTEST(suite, test_parser_array_float64);
    TTEST(suite, test_parser_array_array);
    TTEST(suite, test_parser_array_object);
    TTEST(suite, test_parser_array_optimized_count_empty);
    TTEST(suite, test_parser_array_optimized_count_null);
    TTEST(suite, test_parser_array_optimized_count_noop);
    TTEST(suite, test_parser_array_optimized_count_true);
    TTEST(suite, test_parser_array_optimized_count_false);
    TTEST(suite, test_parser_array_optimized_count_uint8);
    TTEST(suite, test_parser_array_optimized_count_char);
    TTEST(suite, test_parser_array_optimized_count_int8);
    TTEST(suite, test_parser_array_optimized_count_int8_negative);
    TTEST(suite, test_parser_array_optimized_count_int16);
    TTEST(suite, test_parser_array_optimized_count_int16_negative);
    TTEST(suite, test_parser_array_optimized_count_int32);
    TTEST(suite, test_parser_array_optimized_count_int32_negative);
    TTEST(suite, test_parser_array_optimized_count_int64);
    TTEST(suite, test_parser_array_optimized_count_str);
    TTEST(suite, test_parser_array_optimized_count_hpn);
    TTEST(suite, test_parser_array_optimized_count_array);
    TTEST(suite, test_parser_array_optimized_count_object);
    TTEST(suite, test_parser_array_optimized_type_unknown_marker);
    TTEST(suite, test_parser_array_optimized_type_null_empty);
    TTEST(suite, test_parser_array_optimized_type_noop_empty);
    TTEST(suite, test_parser_array_optimized_type_true_empty);
    TTEST(suite, test_parser_array_optimized_type_false_empty);
    TTEST(suite, test_parser_array_optimized_type_uint8_empty);
    TTEST(suite, test_parser_array_optimized_type_char_empty);
    TTEST(suite, test_parser_array_optimized_type_int8_empty);
    TTEST(suite, test_parser_array_optimized_type_int16_empty);
    TTEST(suite, test_parser_array_optimized_type_int32_empty);
    TTEST(suite, test_parser_array_optimized_type_int64_empty);
    TTEST(suite, test_parser_array_optimized_type_str_empty);
    TTEST(suite, test_parser_array_optimized_type_hpn_empty);
    TTEST(suite, test_parser_array_optimized_type_array_empty);
    TTEST(suite, test_parser_array_optimized_type_object_empty);
    TTEST(suite, test_parser_array_optimized_type_null_lots);
    TTEST(suite, test_parser_array_optimized_type_noop_lots);
    TTEST(suite, test_parser_array_optimized_type_true_lots);
    TTEST(suite, test_parser_array_optimized_type_false_lots);
    TTEST(suite, test_parser_array_optimized_type_uint8_lots);
    TTEST(suite, test_parser_array_optimized_type_char_lots);
    TTEST(suite, test_parser_array_optimized_type_int8_lots);
    TTEST(suite, test_parser_array_optimized_type_int16_lots);
    TTEST(suite, test_parser_array_optimized_type_int32_lots);
    TTEST(suite, test_parser_array_optimized_type_int64_lots);
    TTEST(suite, test_parser_array_optimized_type_str_lots);
    TTEST(suite, test_parser_array_optimized_type_hpn_lots);
    TTEST(suite, test_parser_array_optimized_type_array_lots);
    TTEST(suite, test_parser_array_optimized_type_object_lots);

    TTEST(suite, test_parser_object_empty);
    TTEST(suite, test_parser_object_unknown_marker);
    TTEST(suite, test_parser_object_null);
    TTEST(suite, test_parser_object_noop);
    TTEST(suite, test_parser_object_false);
    TTEST(suite, test_parser_object_true);
    TTEST(suite, test_parser_object_uint8);
    TTEST(suite, test_parser_object_int8);
    TTEST(suite, test_parser_object_int16);
    TTEST(suite, test_parser_object_int32);
    TTEST(suite, test_parser_object_int64);
    TTEST(suite, test_parser_object_float32);
    TTEST(suite, test_parser_object_float64);
    TTEST(suite, test_parser_object_char);
    TTEST(suite, test_parser_object_str);
    TTEST(suite, test_parser_object_hpn);
    TTEST(suite, test_parser_object_array);
    TTEST(suite, test_parser_object_object);
    TTEST(suite, test_parser_object_optimized_count_empty);
    TTEST(suite, test_parser_object_optimized_count_null);
    TTEST(suite, test_parser_object_optimized_count_noop);
    TTEST(suite, test_parser_object_optimized_count_true);
    TTEST(suite, test_parser_object_optimized_count_false);
    TTEST(suite, test_parser_object_optimized_count_uint8);
    TTEST(suite, test_parser_object_optimized_count_char);
    TTEST(suite, test_parser_object_optimized_count_int8);
    TTEST(suite, test_parser_object_optimized_count_int8_negative);
    TTEST(suite, test_parser_object_optimized_count_int16);
    TTEST(suite, test_parser_object_optimized_count_int16_negative);
    TTEST(suite, test_parser_object_optimized_count_int32);
    TTEST(suite, test_parser_object_optimized_count_int32_negative);
    TTEST(suite, test_parser_object_optimized_count_int64);
    TTEST(suite, test_parser_object_optimized_count_str);
    TTEST(suite, test_parser_object_optimized_count_hpn);
    TTEST(suite, test_parser_object_optimized_count_array);
    TTEST(suite, test_parser_object_optimized_count_object);
    TTEST(suite, test_parser_object_optimized_type_unknown_marker);
    TTEST(suite, test_parser_object_optimized_type_null_empty);
    TTEST(suite, test_parser_object_optimized_type_noop_empty);
    TTEST(suite, test_parser_object_optimized_type_true_empty);
    TTEST(suite, test_parser_object_optimized_type_false_empty);
    TTEST(suite, test_parser_object_optimized_type_uint8_empty);
    TTEST(suite, test_parser_object_optimized_type_char_empty);
    TTEST(suite, test_parser_object_optimized_type_int8_empty);
    TTEST(suite, test_parser_object_optimized_type_int16_empty);
    TTEST(suite, test_parser_object_optimized_type_int32_empty);
    TTEST(suite, test_parser_object_optimized_type_int64_empty);
    TTEST(suite, test_parser_object_optimized_type_str_empty);
    TTEST(suite, test_parser_object_optimized_type_hpn_empty);
    TTEST(suite, test_parser_object_optimized_type_array_empty);
    TTEST(suite, test_parser_object_optimized_type_object_empty);
    TTEST(suite, test_parser_object_optimized_type_null_lots);
    TTEST(suite, test_parser_object_optimized_type_noop_lots);
    TTEST(suite, test_parser_object_optimized_type_true_lots);
    TTEST(suite, test_parser_object_optimized_type_false_lots);
    TTEST(suite, test_parser_object_optimized_type_uint8_lots);
    TTEST(suite, test_parser_object_optimized_type_char_lots);
    TTEST(suite, test_parser_object_optimized_type_int8_lots);
    TTEST(suite, test_parser_object_optimized_type_int16_lots);
    TTEST(suite, test_parser_object_optimized_type_int32_lots);
    TTEST(suite, test_parser_object_optimized_type_int64_lots);
    TTEST(suite, test_parser_object_optimized_type_str_lots);
    TTEST(suite, test_parser_object_optimized_type_hpn_lots);
    TTEST(suite, test_parser_object_optimized_type_array_lots);
    TTEST(suite, test_parser_object_optimized_type_object_lots);
}

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
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {0};
    unsigned int len;
    char *error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    TASSERT_EQUALI(UR_OK, ubjs_parser_new(&parser, &context));

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&error);
        TASSERT_STRING_EQUAL("At 0 [0] unknown marker", error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_null()
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {90, 90, 90, 90, 90};
    unsigned int len;
    void *parsed;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        TASSERT_EQUAL(ubjs_prmtv_null(), parsed);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(5, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_noop()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {78, 78, 78, 78, 78};
    void *parsed;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        TASSERT_EQUAL(ubjs_prmtv_noop(), parsed);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(5, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_true()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {84, 84, 84, 84, 84};

    void *parsed;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        TASSERT_EQUAL(ubjs_prmtv_true(), parsed);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(5, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_false()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {70, 70, 70, 70, 70};
    void *parsed;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        TASSERT_EQUAL(ubjs_prmtv_false(), parsed);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(5, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_int8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    uint8_t data[]= {105, 129, 105, 0, 105, 255};
    int8_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    ubjs_parser_context context;
    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(obj, &value));
        TASSERT_EQUAL(-127, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(3, len);
    if (3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(obj, &value));
        TASSERT_EQUALI(0, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int8(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int8_get(obj, &value));
        TASSERT_EQUAL(-1, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_uint8()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {85, 129, 85, 0, 85, 255};
    uint8_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(obj, &value));
        TASSERT_EQUALI(129, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(3, len);

    if (3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(obj, &value));
        TASSERT_EQUALI(0, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_uint8(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_uint8_get(obj, &value));
        TASSERT_EQUALUI(255, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_int16()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {73, 0, 129, 73, 129, 0, 73, 85, 255};
    int16_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(obj, &value));
        TASSERT_EQUAL(-32512, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 9));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(3, len);

    if (3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(obj, &value));
        TASSERT_EQUALI(129, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int16(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int16_get(obj, &value));
        TASSERT_EQUAL(-171, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_int32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {108, 0, 129, 0, 129, 108, 129, 0, 129, 0, 108, 85, 255, 85, 255};
    int32_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(obj, &value));
        TASSERT_EQUAL(-2130673408, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 15));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(3, len);

    if (3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(obj, &value));
        TASSERT_EQUALI(8454273, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int32(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int32_get(obj, &value));
        TASSERT_EQUAL(-11141291, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_int64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {76, 1, 2, 3, 4, 5, 6, 7, 8,
                     76, 255, 254, 253, 252, 251, 250, 249, 248,
                     76, 0, 255, 1, 254, 2, 253, 3, 252
                    };
    int64_t value=0;
    ubjs_bool ret=UTRUE;
    ubjs_prmtv *obj=0;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 9));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(obj, &value));
        TASSERT_EQUALI(67305985, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 27));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(3, len);

    if (3 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(obj, &value));
        TASSERT_EQUALI(4244504319, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_int64(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_int64_get(obj, &value));
        TASSERT_EQUALI(4261543680, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_float32()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {100, 0, 0, 128, 64, 100, 0, 0, 255, 194, 100, 0, 0, 128, 65};
    float32_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_float32_get(obj, &value));
        TASSERT_EQUALI(4, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 15));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(3, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_float32_get(obj, &value));
        TASSERT_EQUAL(-127.5, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float32(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_float32_get(obj, &value));
        TASSERT_EQUALI(16.0, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_float64()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {68, 0, 0, 0, 0, 0, 0, 128, 64,
                     68, 0, 0, 255, 194, 0, 0, 255, 194,
                     68, 0, 0, 128, 65, 0, 0, 128, 65
                    };
    float64_t value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 9));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_float64_get(obj, &value));
        TASSERT_EQUALI(512.0, value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 27));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(3, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_float64_get(obj, &value));
        TASSERT_EQUAL(-545357971845120.000000, value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_float64(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_float64_get(obj, &value));
        TASSERT_EQUALI(33554440.187500, value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_char()
{
    ubjs_parser *parser=0;
    unsigned int len;

    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[]= {67, 82, 67, 67, 67, 68};
    char value;
    ubjs_bool ret;
    ubjs_prmtv *obj;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;

    ubjs_parser_new(&parser, &context);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 2));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(obj, &value));
        TASSERT_EQUAL('R', value);
    }

    wrapped_parser_context_reset(wrapped);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(3, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 1, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(obj, &value));
        TASSERT_EQUAL('C', value);

        test_list_get(wrapped->calls_parsed, 2, (void **)&obj);
        TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_char(obj, &ret));
        TASSERT_EQUALI(UTRUE, ret);

        TASSERT_EQUALI(UR_OK, ubjs_prmtv_char_get(obj, &value));
        TASSERT_EQUAL('D', value);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}
