/*
 * Copyright (c) 2016-2017 Tomasz Sieprawski
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

void __test_parser_array(ubjs_prmtv *obj)
{
    ubjs_bool ret;
    TASSERT_EQUALI(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    TASSERT_EQUALI(UTRUE, ret);
}

void test_parser_array_empty(void)
{
    uint8_t data[] = {91, 93};
    sp_verify_parsed((ubjs_library *)tstate, 2, data, __test_parser_array);
}

void test_parser_array_unknown_marker(void)
{
    uint8_t data[] = {91, 0};
    sp_verify_error((ubjs_library *)tstate, 2, data, "At 1 [0] unknown marker");
}

void test_parser_array_uint8(void)
{
    uint8_t data[] = {91, 85, 5, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 4, data, __test_parser_array);
}

void test_parser_array_int8(void)
{
    uint8_t data[] = {91, 105, 255, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 4, data, __test_parser_array);
}

void test_parser_array_int16(void)
{
    uint8_t data[] = {91, 73, 0, 129, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 5, data, __test_parser_array);
}

void test_parser_array_int32(void)
{
    uint8_t data[] = {91, 108, 0, 129, 0, 129, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 7, data, __test_parser_array);
}

void test_parser_array_int64(void)
{
    uint8_t data[]= {91, 76, 1, 2, 3, 4, 5, 6, 7, 8, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 11, data, __test_parser_array);
}

void test_parser_array_float32(void)
{
    uint8_t data[] = {91, 100, 0, 0, 128, 64, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 7, data, __test_parser_array);
}

void test_parser_array_float64(void)
{
    uint8_t data[]= {91, 68, 0, 0, 0, 0, 0, 0, 128, 64, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 11, data, __test_parser_array);
}

void test_parser_array_null(void)
{
    uint8_t data[]= {91, 90, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 3, data, __test_parser_array);
}

void test_parser_array_noop(void)
{
    uint8_t data[]= {91, 78, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 3, data, __test_parser_array);
}

void test_parser_array_true(void)
{
    uint8_t data[]= {91, 84, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 3, data, __test_parser_array);
}

void test_parser_array_false(void)
{
    uint8_t data[]= {91, 70, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 3, data, __test_parser_array);
}

void test_parser_array_char(void)
{
    uint8_t data[]= {91, 67, 'r', 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 4, data, __test_parser_array);
}

void test_parser_array_str(void)
{
    uint8_t data[]= {91, 83, 85, 1, 'r', 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 6, data, __test_parser_array);
}

void test_parser_array_hpn(void)
{
    uint8_t data[]= {91, 72, 85, 1, '1', 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 6, data, __test_parser_array);
}

void test_parser_array_array(void)
{
    uint8_t data[]= {91, 91, 93, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 4, data, __test_parser_array);
}

void test_parser_array_object(void)
{
    uint8_t data[]= {91, 123, 125, 93};
    twill_returnui("array_add_last", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 4, data, __test_parser_array);
}

void test_parser_array_optimized_count_empty(void)
{
    uint8_t data[]= {91, 35, 85, 0};
    twill_returnui("array_builder_set_length", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 4, data, __test_parser_array);
}

void test_parser_array_optimized_count_null(void)
{
    uint8_t data[]= {91, 35, 90};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [90] unknown marker");
}

void test_parser_array_optimized_count_noop(void)
{
    uint8_t data[]= {91, 35, 78};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [78] unknown marker");
}

void test_parser_array_optimized_count_true(void)
{
    uint8_t data[]= {91, 35, 84};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [84] unknown marker");
}

void test_parser_array_optimized_count_false(void)
{
    uint8_t data[]= {91, 35, 70};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [70] unknown marker");
}

void test_parser_array_optimized_count_char(void)
{
    uint8_t data[]= {91, 35, 67};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [67] unknown marker");
}

void test_parser_array_optimized_count_uint8(void)
{
    uint8_t data[]= {91, 35, 85, 0};
    twill_returnui("array_builder_set_length", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 4, data, __test_parser_array);
}

void test_parser_array_optimized_count_int8(void)
{
    uint8_t data[]= {91, 35, 105, 0};
    twill_returnui("array_builder_set_length", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 4, data, __test_parser_array);
}

void test_parser_array_optimized_count_int8_negative(void)
{
    uint8_t data[]= {91, 35, 105, 255};
    sp_verify_error((ubjs_library *)tstate, 4, data, "Got int8 negative length");
}

void test_parser_array_optimized_count_int16(void)
{
    uint8_t data[]= {91, 35, 73, 0, 0};
    twill_returnui("array_builder_set_length", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 5, data, __test_parser_array);
}

void test_parser_array_optimized_count_int16_negative(void)
{
    uint8_t data[]= {91, 35, 73, 0, 255};
    sp_verify_error((ubjs_library *)tstate, 5, data, "Got int16 negative length");
}

void test_parser_array_optimized_count_int32(void)
{
    uint8_t data[]= {91, 35, 108, 0, 0, 0, 0};
    twill_returnui("array_builder_set_length", 1, UR_OK);
    sp_verify_parsed((ubjs_library *)tstate, 7, data, __test_parser_array);
}

void test_parser_array_optimized_count_int32_negative(void)
{
    uint8_t data[]= {91, 35, 108, 0, 0, 0, 255};
    sp_verify_error((ubjs_library *)tstate, 7, data, "Got int32 negative length");
}

void test_parser_array_optimized_count_int64(void)
{
    uint8_t data[]= {91, 35, 76};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [76] unknown marker");
}

void test_parser_array_optimized_count_str(void)
{
    uint8_t data[]= {91, 35, 83};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [83] unknown marker");
}

void test_parser_array_optimized_count_hpn(void)
{
    uint8_t data[]= {91, 35, 72};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [72] unknown marker");
}

void test_parser_array_optimized_count_array(void)
{
    uint8_t data[]= {91, 35, 91};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [91] unknown marker");
}

void test_parser_array_optimized_count_object(void)
{
    uint8_t data[]= {91, 35, 123};
    sp_verify_error((ubjs_library *)tstate, 3, data, "At 2 [123] unknown marker");
}

void test_parser_settings_limit_container_length_array_unoptimized_below(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[5];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 3;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 90;
    data[2] = 90;
    data[3] = 90;
    data[4] = 93;
    twill_returnui("array_add_last", 3, UR_OK);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 5));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_settings_limit_container_length_array_unoptimized_above(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[5];
    unsigned int len;
    test_list_item *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 3;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 90;
    data[2] = 90;
    data[3] = 90;
    data[4] = 90;
    twill_returnui("array_add_last", 3, UR_OK);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        TASSERT_STRING_EQUAL("Reached limit of container length",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_settings_limit_container_length_array_optimized_below(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[5];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 3;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 35;
    data[2] = 85;
    data[3] = 3;
    twill_returnui("array_builder_set_length", 1, UR_OK);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 4));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_settings_limit_container_length_array_optimized_above(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    uint8_t data[5];
    ubjs_parser_settings settings;
    unsigned int len;
    test_list_item *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 3;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UFALSE;

    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
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
        test_list_get(wrapped->calls_error, 0, &real_error);
        TASSERT_STRING_EQUAL("Reached limit of container length",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_settings_limit_recursion_level_array_below(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[6];

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 3;
    settings.debug = UFALSE;

    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 91;
    data[2] = 91;
    data[3] = 93;
    data[4] = 93;
    data[5] = 93;
    twill_returnui("array_add_last", 2, UR_OK);
    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, 6));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void test_parser_settings_limit_recursion_level_array_above(void)
{
    ubjs_library *lib = (ubjs_library *)tstate;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    uint8_t data[4];
    unsigned int len;
    test_list_item *real_error;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 3;
    settings.debug = UFALSE;

    ubjs_parser_new(lib, &settings, &context, &parser);

    data[0] = 91;
    data[1] = 91;
    data[2] = 91;
    data[3] = 91;
    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        TASSERT_STRING_EQUAL("Reached limit of recursion level",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}
