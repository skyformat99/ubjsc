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

#include "test_common.h"
#include "test_list.h"
#include "test_parser.h"
#include "test_parser_tools.h"

Test(parser, limit_string_length_optimized_below)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[3];

    wrapped_parser_context_new(&wrapped);
    ubjs_parser_builder_new(lib, &builder);
    ubjs_parser_builder_set_userdata(builder, wrapped);
    ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed);
    ubjs_parser_builder_set_error_f(builder, parser_context_error);
    ubjs_parser_builder_set_free_f(builder, parser_context_free);
    ubjs_parser_builder_set_limit_string_length(builder, 3);
    ubjs_parser_builder_build(builder, &parser);
    ubjs_parser_builder_free(&builder);

    data[0] = 83;
    data[1] = 85;
    data[2] = 3;
    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 3));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_string_length_optimized_above)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[3];
    unsigned int len;
    test_list_item *real_error;

    wrapped_parser_context_new(&wrapped);
    ubjs_parser_builder_new(lib, &builder);
    ubjs_parser_builder_set_userdata(builder, wrapped);
    ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed);
    ubjs_parser_builder_set_error_f(builder, parser_context_error);
    ubjs_parser_builder_set_free_f(builder, parser_context_free);
    ubjs_parser_builder_set_limit_string_length(builder, 3);
    ubjs_parser_builder_build(builder, &parser);
    ubjs_parser_builder_free(&builder);

    data[0] = 83;
    data[1] = 85;
    data[2] = 4;
    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        cr_expect_str_eq("Reached limit of string length",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_hpn_length_optimized_below)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[3];

    wrapped_parser_context_new(&wrapped);
    ubjs_parser_builder_new(lib, &builder);
    ubjs_parser_builder_set_userdata(builder, wrapped);
    ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed);
    ubjs_parser_builder_set_error_f(builder, parser_context_error);
    ubjs_parser_builder_set_free_f(builder, parser_context_free);
    ubjs_parser_builder_set_limit_string_length(builder, 3);
    ubjs_parser_builder_build(builder, &parser);
    ubjs_parser_builder_free(&builder);

    data[0] = 72;
    data[1] = 85;
    data[2] = 3;
    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 3));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_hpn_length_optimized_above)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[3];
    unsigned int len;
    test_list_item *real_error;

    wrapped_parser_context_new(&wrapped);
    ubjs_parser_builder_new(lib, &builder);
    ubjs_parser_builder_set_userdata(builder, wrapped);
    ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed);
    ubjs_parser_builder_set_error_f(builder, parser_context_error);
    ubjs_parser_builder_set_free_f(builder, parser_context_free);
    ubjs_parser_builder_set_limit_string_length(builder, 3);
    ubjs_parser_builder_build(builder, &parser);
    ubjs_parser_builder_free(&builder);

    data[0] = 72;
    data[1] = 85;
    data[2] = 4;
    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 3));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        cr_expect_str_eq("Reached limit of string length",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void __test_parser_str_empty(ubjs_prmtv *obj)
{
    unsigned int length;
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_str(obj, &ret));
    cr_expect_eq(UTRUE, ret);
    cr_expect_eq(UR_OK, ubjs_prmtv_str_get_length(obj, &length));
    cr_expect_eq(0, length);
}

Test(parser, str_empty)
{
    uint8_t data[]= {83, 85, 0};
    sp_verify_parsed((ubjs_library *)tlib, 3, data, __test_parser_str_empty);
}

void __test_parser_str_nonempty(ubjs_prmtv *obj)
{
    unsigned int length;
    ubjs_bool ret;
    char text[6];

    cr_expect_eq(UR_OK, ubjs_prmtv_is_str(obj, &ret));
    cr_expect_eq(UTRUE, ret);
    cr_expect_eq(UR_OK, ubjs_prmtv_str_get_length(obj, &length));
    cr_expect_eq(5, length);
    cr_expect_eq(UR_OK, ubjs_prmtv_str_copy_text(obj, text));
    cr_assert_arr_eq("rower", text, 5);
}

Test(parser, str_uint8)
{
    uint8_t data[]= {83, 85, 5, 'r', 'o', 'w', 'e', 'r'};
    sp_verify_parsed((ubjs_library *)tlib, 8, data, __test_parser_str_nonempty);
}

Test(parser, str_int8)
{
    uint8_t data[]= {83, 105, 5, 'r', 'o', 'w', 'e', 'r'};
    sp_verify_parsed((ubjs_library *)tlib, 8, data, __test_parser_str_nonempty);
}

Test(parser, str_int16)
{
    uint8_t data[]= {83, 73, 5, 0, 'r', 'o', 'w', 'e', 'r'};
    sp_verify_parsed((ubjs_library *)tlib, 9, data, __test_parser_str_nonempty);
}

Test(parser, str_int32)
{
    uint8_t data[]= {83, 108, 5, 0, 0, 0, 'r', 'o', 'w', 'e', 'r'};
    sp_verify_parsed((ubjs_library *)tlib, 11, data, __test_parser_str_nonempty);
}

Test(parser, str_int8_negative)
{
    uint8_t data[]= {83, 105, 255};
    sp_verify_error((ubjs_library *)tlib, 3, data, "Got negative length");
}

Test(parser, str_int32_negative)
{
    uint8_t data[]= {83, 108, 0, 0, 0, 255};
    sp_verify_error((ubjs_library *)tlib, 6, data, "Got negative length");
}

Test(parser, str_int16_negative)
{
    uint8_t data[]= {83, 73, 0, 255};
    sp_verify_error((ubjs_library *)tlib, 4, data, "Got negative length");
}

Test(parser, str_null)
{
    uint8_t data[]= {83, 90};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [90] unknown marker");
}

Test(parser, str_noop)
{
    uint8_t data[]= {83, 78};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [78] unknown marker");
}

Test(parser, str_true)
{
    uint8_t data[]= {83, 84};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [84] unknown marker");
}

Test(parser, str_false)
{
    uint8_t data[]= {83, 70};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [70] unknown marker");
}

Test(parser, str_char)
{
    uint8_t data[]= {83, 67};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [67] unknown marker");
}

Test(parser, str_str)
{
    uint8_t data[]= {83, 83};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [83] unknown marker");
}

Test(parser, str_int64)
{
    uint8_t data[]= {83, 76};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [76] unknown marker");
}

Test(parser, str_float32)
{
    uint8_t data[]= {83, 100};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [100] unknown marker");
}

Test(parser, str_float64)
{
    uint8_t data[]= {83, 68};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [68] unknown marker");
}

Test(parser, str_array)
{
    uint8_t data[]= {83, 91};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [91] unknown marker");
}

Test(parser, str_object)
{
    uint8_t data[]= {83, 123};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [123] unknown marker");
}

Test(parser, str_hpn)
{
    uint8_t data[]= {83, 72};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [72] unknown marker");
}

Test(parser, hpn_empty)
{
    uint8_t data[]= {72, 85, 0};
    sp_verify_error((ubjs_library *)tlib, 3, data, "Syntax error for high-precision number.");
}

void __test_parser_hpn_nonempty(ubjs_prmtv *obj)
{
    unsigned int length;
    ubjs_bool ret;
    char text[6];

    cr_expect_eq(UR_OK, ubjs_prmtv_is_hpn(obj, &ret));
    cr_expect_eq(UTRUE, ret);
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_get_length(obj, &length));
    cr_expect_eq(5, length);
    cr_expect_eq(UR_OK, ubjs_prmtv_hpn_copy_text(obj, text));
    cr_assert_arr_eq("12345", text, 5);
}

Test(parser, hpn_uint8)
{
    uint8_t data[]= {72, 85, 5, '1', '2', '3', '4', '5'};
    sp_verify_parsed((ubjs_library *)tlib, 8, data, __test_parser_hpn_nonempty);
}

Test(parser, hpn_int8)
{
    uint8_t data[]= {72, 105, 5, '1', '2', '3', '4', '5'};
    sp_verify_parsed((ubjs_library *)tlib, 8, data, __test_parser_hpn_nonempty);
}

Test(parser, hpn_int16)
{
    uint8_t data[]= {72, 73, 5, 0, '1', '2', '3', '4', '5'};
    sp_verify_parsed((ubjs_library *)tlib, 9, data, __test_parser_hpn_nonempty);
}

Test(parser, hpn_int32)
{
    uint8_t data[]= {72, 108, 5, 0, 0, 0, '1', '2', '3', '4', '5'};
    sp_verify_parsed((ubjs_library *)tlib, 11, data, __test_parser_hpn_nonempty);
}

Test(parser, hpn_int8_negative)
{
    uint8_t data[]= {72, 105, 255};
    sp_verify_error((ubjs_library *)tlib, 3, data, "Got negative length");
}

Test(parser, hpn_int32_negative)
{
    uint8_t data[]= {72, 108, 0, 0, 0, 255};
    sp_verify_error((ubjs_library *)tlib, 6, data, "Got negative length");
}

Test(parser, hpn_int16_negative)
{
    uint8_t data[]= {72, 73, 0, 255};
    sp_verify_error((ubjs_library *)tlib, 4, data, "Got negative length");
}

Test(parser, hpn_null)
{
    uint8_t data[]= {72, 90};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [90] unknown marker");
}

Test(parser, hpn_noop)
{
    uint8_t data[]= {72, 78};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [78] unknown marker");
}

Test(parser, hpn_true)
{
    uint8_t data[]= {72, 84};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [84] unknown marker");
}

Test(parser, hpn_false)
{
    uint8_t data[]= {72, 70};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [70] unknown marker");
}

Test(parser, hpn_char)
{
    uint8_t data[]= {72, 67};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [67] unknown marker");
}

Test(parser, hpn_str)
{
    uint8_t data[]= {72, 83};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [83] unknown marker");
}

Test(parser, hpn_int64)
{
    uint8_t data[]= {72, 76};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [76] unknown marker");
}

Test(parser, hpn_float32)
{
    uint8_t data[]= {72, 100};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [100] unknown marker");
}

Test(parser, hpn_float64)
{
    uint8_t data[]= {72, 68};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [68] unknown marker");
}

Test(parser, hpn_array)
{
    uint8_t data[]= {72, 91};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [91] unknown marker");
}

Test(parser, hpn_object)
{
    uint8_t data[]= {72, 123};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [123] unknown marker");
}

Test(parser, hpn_hpn)
{
    uint8_t data[]= {72, 72};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [72] unknown marker");
}
