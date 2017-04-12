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

Test(parser, builder)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    void *auserdata = 0;

    wrapped_parser_context_new(&wrapped);

    cr_expect_eq(UR_ERROR, ubjs_parser_builder_new(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_new(0, &builder));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_new(lib, 0));

    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_neq(0, builder);

    cr_expect_eq(UR_ERROR, ubjs_parser_builder_build(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_build(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_build(0, &parser));

    cr_expect_eq(UR_ERROR, ubjs_parser_builder_build(builder, &parser));

    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_userdata(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_userdata(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_userdata(0, wrapped));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_parsed_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_parsed_f(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_parsed_f(0, parser_context_parsed));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_error_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_error_f(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_error_f(0, parser_context_error));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_free_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_free_f(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_free_f(0, parser_context_free));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_debug_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_debug_f(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_debug_f(0, parser_context_debug));

    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_bytes_since_last_callback(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_bytes_since_last_callback(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_bytes_since_last_callback(0, 3));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_container_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_container_length(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_container_length(0, 3));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_string_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_string_length(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_string_length(0, 3));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_recursion_level(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_recursion_level(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_limit_recursion_level(0, 3));
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_set_silently_ignore_toplevel_noops(0, UFALSE));

    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_neq(0, parser);

    cr_expect_eq(UR_ERROR, ubjs_parser_get_userdata(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_get_userdata(parser, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_get_userdata(0, &auserdata));

    cr_expect_eq(UR_OK, ubjs_parser_get_userdata(parser, &auserdata));
    cr_expect_eq(auserdata, wrapped);

    cr_expect_eq(UR_ERROR, ubjs_parser_builder_free(0));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));
    cr_expect_eq(0, builder);
    cr_expect_eq(UR_ERROR, ubjs_parser_builder_free(&builder));

    cr_expect_eq(UR_ERROR, ubjs_parser_free(0));
    cr_expect_eq(UR_OK, ubjs_parser_free(&parser));
    cr_expect_eq(0, parser);
    cr_expect_eq(UR_ERROR, ubjs_parser_free(&parser));

    wrapped_parser_context_free(&wrapped);
}

Test(parser, basics)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data;
    unsigned int message_length;
    unsigned int len;
    char message_text[] = {0};
    void *mock_error;

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    cr_expect_eq(UR_ERROR, ubjs_parser_parse(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, 0, 0));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);

    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, &data, 0));

    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(0, len);

    cr_expect_eq(UR_ERROR, ubjs_parser_error_get_message_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_error_get_message_length(0, &message_length));
    cr_expect_eq(UR_ERROR, ubjs_parser_error_get_message_length((ubjs_parser_error *)&mock_error,
        0));

    cr_expect_eq(UR_ERROR, ubjs_parser_error_get_message_text(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_parser_error_get_message_text(0, message_text));
    cr_expect_eq(UR_ERROR, ubjs_parser_error_get_message_text((ubjs_parser_error *)&mock_error,
        0));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, no_error_f)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[] = {0};
    unsigned int len = 0;

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(0, len);

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_bytes_since_last_callback_below)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[4];

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_bytes_since_last_callback(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 83;
    data[1] = 85;
    data[2] = 0;
    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 3));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_bytes_since_last_callback_above)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
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
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_bytes_since_last_callback(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 72;
    data[1] = 85;
    data[2] = 1;
    data[3] = 0;
    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 4));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(1, len);
    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        cr_expect_str_eq("Reached limit of bytes since last callback",
            (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, silently_ignore_toplevel_noops)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[] = {78};
    unsigned int len;

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_silently_ignore_toplevel_noops(builder, UTRUE));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 1));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(0, len);
    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, unknown_marker)
{
    uint8_t data[] = {0};
    sp_verify_error((ubjs_library *)instance_lib, 1, data, "At 0 [0] unknown marker");
}

void __test_parser_int16(ubjs_prmtv *obj)
{
    int16_t value;
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_int16(obj, &ret));
    cr_expect_eq(UTRUE, ret);

    cr_expect_eq(UR_OK, ubjs_prmtv_int16_get(obj, &value));
    cr_expect_eq(-32512, value);
}

Test(parser, int16)
{
    uint8_t data[]= {73, 0, 129};
    sp_verify_parsed((ubjs_library *)instance_lib, 3, data, __test_parser_int16);
}

void __test_parser_int32(ubjs_prmtv *obj)
{
    int32_t value;
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_int32(obj, &ret));
    cr_expect_eq(UTRUE, ret);

    cr_expect_eq(UR_OK, ubjs_prmtv_int32_get(obj, &value));
    cr_expect_eq(-2130673408, value);
}

Test(parser, int32)
{
    uint8_t data[]= {108, 0, 129, 0, 129};
    sp_verify_parsed((ubjs_library *)instance_lib, 5, data, __test_parser_int32);
}

void __test_parser_int64(ubjs_prmtv *obj)
{
    int64_t value = 0;
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_int64(obj, &ret));
    cr_expect_eq(UTRUE, ret);

    cr_expect_eq(UR_OK, ubjs_prmtv_int64_get(obj, &value));
    cr_expect_eq(578437695752307201, value);
}

Test(parser, int64)
{
    uint8_t data[]= {76, 1, 2, 3, 4, 5, 6, 7, 8};
    sp_verify_parsed((ubjs_library *)instance_lib, 9, data, __test_parser_int64);
}

void __test_parser_float32(ubjs_prmtv *obj)
{
    float32_t value;
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_float32(obj, &ret));
    cr_expect_eq(UTRUE, ret);

    cr_expect_eq(UR_OK, ubjs_prmtv_float32_get(obj, &value));
    cr_expect_eq(4, value);
}

Test(parser, float32)
{
    uint8_t data[]= {100, 0, 0, 128, 64};
    sp_verify_parsed((ubjs_library *)instance_lib, 5, data, __test_parser_float32);
}

void __test_parser_float64(ubjs_prmtv *obj)
{
    float64_t value;
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_float64(obj, &ret));
    cr_expect_eq(UTRUE, ret);

    cr_expect_eq(UR_OK, ubjs_prmtv_float64_get(obj, &value));
    cr_expect_eq(512.0, value);
}

Test(parser, float64)
{
    uint8_t data[]= {68, 0, 0, 0, 0, 0, 0, 128, 64};
    sp_verify_parsed((ubjs_library *)instance_lib, 9, data, __test_parser_float64);
}

void __test_parser_char(ubjs_prmtv *obj)
{
    char value;
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_char(obj, &ret));
    cr_expect_eq(UTRUE, ret);

    cr_expect_eq(UR_OK, ubjs_prmtv_char_get(obj, &value));
    cr_expect_eq('R', value);
}

Test(parser, char)
{
    uint8_t data[]= {67, 82};
    sp_verify_parsed((ubjs_library *)instance_lib, 2, data, __test_parser_char);
}
