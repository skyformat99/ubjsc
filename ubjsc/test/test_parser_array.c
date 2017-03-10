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

#include "test_common.h"
#include "test_list.h"
#include "test_parser.h"
#include "test_parser_tools.h"

void __test_parser_array(ubjs_prmtv *obj)
{
    ubjs_bool ret;
    cr_expect_eq(UR_OK, ubjs_prmtv_is_array(obj, &ret));
    cr_expect_eq(UTRUE, ret);
}

Test(parser, array_empty)
{
    uint8_t data[] = {91, 93};
    sp_verify_parsed((ubjs_library *)tlib, 2, data, __test_parser_array);
}

Test(parser, array_unknown_marker)
{
    uint8_t data[] = {91, 0};
    sp_verify_error((ubjs_library *)tlib, 2, data, "At 1 [0] unknown marker");
}

Test(parser, array_uint8)
{
    uint8_t data[] = {91, 85, 5, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 4, data, __test_parser_array);
}

Test(parser, array_int8)
{
    uint8_t data[] = {91, 105, 255, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 4, data, __test_parser_array);
}

Test(parser, array_int16)
{
    uint8_t data[] = {91, 73, 0, 129, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 5, data, __test_parser_array);
}

Test(parser, array_int32)
{
    uint8_t data[] = {91, 108, 0, 129, 0, 129, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 7, data, __test_parser_array);
}

Test(parser, array_int64)
{
    uint8_t data[]= {91, 76, 1, 2, 3, 4, 5, 6, 7, 8, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 11, data, __test_parser_array);
}

Test(parser, array_float32)
{
    uint8_t data[] = {91, 100, 0, 0, 128, 64, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 7, data, __test_parser_array);
}

Test(parser, array_float64)
{
    uint8_t data[]= {91, 68, 0, 0, 0, 0, 0, 0, 128, 64, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 11, data, __test_parser_array);
}

Test(parser, array_null)
{
    uint8_t data[]= {91, 90, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 3, data, __test_parser_array);
}

Test(parser, array_noop)
{
    uint8_t data[]= {91, 78, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 3, data, __test_parser_array);
}

Test(parser, array_true)
{
    uint8_t data[]= {91, 84, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 3, data, __test_parser_array);
}

Test(parser, array_false)
{
    uint8_t data[]= {91, 70, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 3, data, __test_parser_array);
}

Test(parser, array_char)
{
    uint8_t data[]= {91, 67, 'r', 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 4, data, __test_parser_array);
}

Test(parser, array_str)
{
    uint8_t data[]= {91, 83, 85, 1, 'r', 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 6, data, __test_parser_array);
}

Test(parser, array_hpn)
{
    uint8_t data[]= {91, 72, 85, 1, '1', 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 6, data, __test_parser_array);
}

Test(parser, array_array)
{
    uint8_t data[]= {91, 91, 93, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 4, data, __test_parser_array);
}

Test(parser, array_object)
{
    uint8_t data[]= {91, 123, 125, 93};
    twill_returnui("array_add_last", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 4, data, __test_parser_array);
}

Test(parser, array_optimized_count_empty)
{
    uint8_t data[]= {91, 35, 85, 0};
    twill_returnui("array_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 4, data, __test_parser_array);
}

Test(parser, array_optimized_count_null)
{
    uint8_t data[]= {91, 35, 90};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [90] unknown marker");
}

Test(parser, array_optimized_count_noop)
{
    uint8_t data[]= {91, 35, 78};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [78] unknown marker");
}

Test(parser, array_optimized_count_true)
{
    uint8_t data[]= {91, 35, 84};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [84] unknown marker");
}

Test(parser, array_optimized_count_false)
{
    uint8_t data[]= {91, 35, 70};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [70] unknown marker");
}

Test(parser, array_optimized_count_char)
{
    uint8_t data[]= {91, 35, 67};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [67] unknown marker");
}

Test(parser, array_optimized_count_uint8)
{
    uint8_t data[]= {91, 35, 85, 0};
    twill_returnui("array_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 4, data, __test_parser_array);
}

Test(parser, array_optimized_count_int8)
{
    uint8_t data[]= {91, 35, 105, 0};
    twill_returnui("array_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 4, data, __test_parser_array);
}

Test(parser, array_optimized_count_int8_negative)
{
    uint8_t data[]= {91, 35, 105, 255};
    sp_verify_error((ubjs_library *)tlib, 4, data, "Got negative length");
}

Test(parser, array_optimized_count_int16)
{
    uint8_t data[]= {91, 35, 73, 0, 0};
    twill_returnui("array_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 5, data, __test_parser_array);
}

Test(parser, array_optimized_count_int16_negative)
{
    uint8_t data[]= {91, 35, 73, 0, 255};
    sp_verify_error((ubjs_library *)tlib, 5, data, "Got negative length");
}

Test(parser, array_optimized_count_int32)
{
    uint8_t data[]= {91, 35, 108, 0, 0, 0, 0};
    twill_returnui("array_builder_set_length", UR_OK);
    sp_verify_parsed((ubjs_library *)tlib, 7, data, __test_parser_array);
}

Test(parser, array_optimized_count_int32_negative)
{
    uint8_t data[]= {91, 35, 108, 0, 0, 0, 255};
    sp_verify_error((ubjs_library *)tlib, 7, data, "Got negative length");
}

Test(parser, array_optimized_count_int64)
{
    uint8_t data[]= {91, 35, 76};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [76] unknown marker");
}

Test(parser, array_optimized_count_str)
{
    uint8_t data[]= {91, 35, 83};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [83] unknown marker");
}

Test(parser, array_optimized_count_hpn)
{
    uint8_t data[]= {91, 35, 72};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [72] unknown marker");
}

Test(parser, array_optimized_count_array)
{
    uint8_t data[]= {91, 35, 91};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [91] unknown marker");
}

Test(parser, array_optimized_count_object)
{
    uint8_t data[]= {91, 35, 123};
    sp_verify_error((ubjs_library *)tlib, 3, data, "At 2 [123] unknown marker");
}

Test(parser, limit_container_length_array_unoptimized_below)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[5];

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_container_length(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 91;
    data[1] = 90;
    data[2] = 90;
    data[3] = 90;
    data[4] = 93;
    twill_returnui("array_add_last", UR_OK);
    twill_returnui("array_add_last", UR_OK);
    twill_returnui("array_add_last", UR_OK);
    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 5));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_container_length_array_unoptimized_above)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[5];
    unsigned int len;
    test_list_item *real_error;

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_container_length(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 91;
    data[1] = 90;
    data[2] = 90;
    data[3] = 90;
    data[4] = 90;
    twill_returnui("array_add_last", UR_OK);
    twill_returnui("array_add_last", UR_OK);
    twill_returnui("array_add_last", UR_OK);

    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 5));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        cr_expect_str_eq("Reached limit of container length",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_container_length_array_optimized_below)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[5];

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_container_length(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 91;
    data[1] = 35;
    data[2] = 85;
    data[3] = 3;
    twill_returnui("array_builder_set_length", UR_OK);
    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 4));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_container_length_array_optimized_above)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[5];
    unsigned int len;
    test_list_item *real_error;

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_container_length(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 91;
    data[1] = 35;
    data[2] = 85;
    data[3] = 4;
    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        cr_expect_str_eq("Reached limit of container length",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_recursion_level_array_below)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[6];

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_recursion_level(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 91;
    data[1] = 91;
    data[2] = 91;
    data[3] = 93;
    data[4] = 93;
    data[5] = 93;
    twill_returnui("array_add_last", UR_OK);
    twill_returnui("array_add_last", UR_OK);
    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 6));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_recursion_level_array_above)
{
    ubjs_library *lib = (ubjs_library *)tlib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[4];
    unsigned int len;
    test_list_item *real_error;

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_recursion_level(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 91;
    data[1] = 91;
    data[2] = 91;
    data[3] = 91;
    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        cr_expect_str_eq("Reached limit of recursion level",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}
