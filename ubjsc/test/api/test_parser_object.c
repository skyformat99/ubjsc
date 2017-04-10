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

Test(parser, object_unknown_marker)
{
    uint8_t data[] = {123, 0};
    sp_verify_error((ubjs_library *)instance_lib, 2, data, "At 1 [0] unknown marker");
}

void __test_parser_object(ubjs_prmtv *obj)
{
    ubjs_bool ret;

    cr_expect_eq(UR_OK, ubjs_prmtv_is_object(obj, &ret));
    cr_expect_eq(UTRUE, ret);
}

Test(parser, object_empty)
{
    uint8_t data[]= {123, 125};
    sp_verify_parsed((ubjs_library *)instance_lib, 2, data, __test_parser_object);
}

Test(parser, object_false)
{
    uint8_t data[]= {123, 85, 1, 'a', 70, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 6, data, __test_parser_object);
}

Test(parser, object_uint8)
{
    uint8_t data[]= {123, 85, 1, 'a', 85, 0, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 7, data, __test_parser_object);
}

Test(parser, object_int8)
{
    uint8_t data[]= {123, 85, 1, 'a', 105, 0, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 7, data, __test_parser_object);
}

Test(parser, object_int16)
{
    uint8_t data[]= {123, 85, 1, 'a', 73, 0, 0, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 8, data, __test_parser_object);
}

Test(parser, object_int32)
{
    uint8_t data[]= {123, 85, 1, 'a', 108, 0, 0, 0, 0, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 10, data, __test_parser_object);
}

Test(parser, object_int64)
{
    uint8_t data[]= {123, 85, 1, 'a', 76, 0, 0, 0, 0, 0, 0, 0, 0, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 14, data, __test_parser_object);
}

Test(parser, object_float32)
{
    uint8_t data[]= {123, 85, 1, 'a', 100, 0, 0, 0, 0, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 10, data, __test_parser_object);
}

Test(parser, object_float64)
{
    uint8_t data[]= {123, 85, 1, 'a', 68, 0, 0, 0, 0, 0, 0, 0, 0, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 14, data, __test_parser_object);
}

Test(parser, object_char)
{
    uint8_t data[]= {123, 85, 1, 'a', 67, 'r', 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 7, data, __test_parser_object);
}

Test(parser, object_str)
{
    uint8_t data[]= {123, 85, 1, 'a', 83, 85, 0, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 8, data, __test_parser_object);
}

Test(parser, object_hpn)
{
    uint8_t data[]= {123, 85, 1, 'a', 72, 85, 1, '1', 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 9, data, __test_parser_object);
}

Test(parser, object_array)
{
    uint8_t data[]= {123, 85, 1, 'a', 91, 93, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 7, data, __test_parser_object);
}

Test(parser, object_object)
{
    uint8_t data[]= {123, 85, 1, 'a', 123, 125, 125};
    twill_returnui("dict_set", UR_OK);
    sp_verify_parsed((ubjs_library *)instance_lib, 7, data, __test_parser_object);
}

Test(parser, object_optimized_count_uint8)
{
    uint8_t data[44];
    unsigned int i;

    data[0] = 123;
    data[1] = 35;
    data[2] = 85;
    data[3] = 10;

    for (i=0; i<10; i++)
    {
        data[4 + i * 4] = 85;
        data[5 + i * 4] = 1;
        snprintf((char *)data + 6 + i * 4, 2, "%01u", i);
        data[7 + i * 4] = (i == 0 ? 78 : 90);
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);

    sp_verify_parsed((ubjs_library *)instance_lib, 44, data, __test_parser_object);
}

Test(parser, object_optimized_count_int8)
{
    uint8_t data[44];
    unsigned int i;

    data[0] = 123;
    data[1] = 35;
    data[2] = 105;
    data[3] = 10;
    for (i=0; i<10; i++)
    {
        data[4 + i * 4] = 85;
        data[5 + i * 4] = 1;
        snprintf((char *)data + 6 + i * 4, 2, "%01u", i);
        data[7 + i * 4] = (i == 0 ? 78 : 90);
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);

    sp_verify_parsed((ubjs_library *)instance_lib, 44, data, __test_parser_object);
}

Test(parser, object_optimized_count_int16)
{
    uint8_t *data;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 70005);
    data[0] = 123;
    data[1] = 35;
    data[2] = 73;
    data[3] = 16;
    data[4] = 39;
    for (i=0; i<10000; i++)
    {
        data[5 + i * 7] = 85;
        data[6 + i * 7] = 4;
        snprintf((char *)data + 7 + i * 7, 5, "%04u", i);
        data[11 + i * 7] = (i == 0 ? 78 : 90);
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);

    sp_verify_parsed((ubjs_library *)instance_lib, 70005, data, __test_parser_object);
    free(data);
}

Test(parser, object_optimized_count_int32)
{
    uint8_t *data;
    unsigned int i;

    data = (uint8_t *)malloc(sizeof(uint8_t) * 800007);
    data[0] = 123;
    data[1] = 35;
    data[2] = 108;
    data[3] = 160;
    data[4] = 134;
    data[5] = 1;
    data[6] = 0;
    for (i=0; i<100000; i++)
    {
        data[7 + i * 8] = 85;
        data[8 + i * 8] = 5;
        snprintf((char *)data + 9 + i * 8, 6, "%05u", i);
        data[14 + i * 8] = (i == 0 ? 78 : 90);
        twill_returnui("dict_set", UR_OK);
    }
    twill_returnui("dict_builder_set_length", UR_OK);

    sp_verify_parsed((ubjs_library *)instance_lib, 800007, data, __test_parser_object);
    free(data);
}

Test(parser, object_optimized_count_false)
{
    uint8_t data[]= {123, 35, 70};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [70] unknown marker");
}

Test(parser, object_optimized_count_char)
{
    uint8_t data[]= {123, 35, 67};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [67] unknown marker");
}

Test(parser, object_optimized_count_int64)
{
    uint8_t data[]= {123, 35, 76};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [76] unknown marker");
}

Test(parser, object_optimized_count_str)
{
    uint8_t data[]= {123, 35, 83};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [83] unknown marker");
}

Test(parser, object_optimized_count_hpn)
{
    uint8_t data[]= {123, 35, 72};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [72] unknown marker");
}

Test(parser, object_optimized_count_array)
{
    uint8_t data[]= {123, 35, 91};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [91] unknown marker");
}

Test(parser, object_optimized_count_object)
{
    uint8_t data[]= {123, 35, 123};
    sp_verify_error((ubjs_library *)instance_lib, 3, data, "At 2 [123] unknown marker");
}

Test(parser, object_optimized_count_int8_negative)
{
    uint8_t data[]= {123, 35, 105, 255};
    sp_verify_error((ubjs_library *)instance_lib, 4, data, "Got negative length");
}

Test(parser, object_optimized_count_int16_negative)
{
    uint8_t data[]= {123, 35, 73, 0, 255};
    sp_verify_error((ubjs_library *)instance_lib, 5, data, "Got negative length");
}

Test(parser, object_optimized_count_int32_negative)
{
    uint8_t data[] = {123, 35, 108, 0, 0, 0, 255};
    sp_verify_error((ubjs_library *)instance_lib, 7, data, "Got negative length");
}

Test(parser, limit_container_length_object_unoptimized_below)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[13];

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_container_length(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 123;

    data[1] = 85;
    data[2] = 1;
    data[3] = 'a';
    data[4] = 90;

    data[5] = 85;
    data[6] = 1;
    data[7] = 'b';
    data[8] = 90;

    data[9] = 85;
    data[10] = 1;
    data[11] = 'c';
    data[12] = 90;

    /* 1 */
    /* object_set */
    twill_returnui("dict_set", UR_OK);

    /* 2 */
    /* object_set */
    twill_returnui("dict_set", UR_OK);

    /* 3 */
    /* object_set */
    twill_returnui("dict_set", UR_OK);

    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 13));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_container_length_object_unoptimized_above)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[14];
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

    data[0] = 123;

    data[1] = 85;
    data[2] = 1;
    data[3] = 'a';
    data[4] = 90;

    data[5] = 85;
    data[6] = 1;
    data[7] = 'b';
    data[8] = 90;

    data[9] = 85;
    data[10] = 1;
    data[11] = 'c';
    data[12] = 90;

    data[13] = 85;

    /* 1 */
    /* object_set */
    twill_returnui("dict_set", UR_OK);

    /* 2 */
    /* object_set */
    twill_returnui("dict_set", UR_OK);

    /* 3 */
    /* object_set */
    twill_returnui("dict_set", UR_OK);

    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 14));
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

Test(parser, limit_container_length_object_optimized_below)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
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

    data[0] = 123;
    data[1] = 35;
    data[2] = 85;
    data[3] = 3;

    twill_returnui("dict_builder_set_length", UR_OK);
    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 4));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_container_length_object_optimized_above)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
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

    data[0] = 123;
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

Test(parser, limit_recursion_level_object_below)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[12];

    wrapped_parser_context_new(&wrapped);
    cr_expect_eq(UR_OK, ubjs_parser_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_error_f(builder, parser_context_error));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_free_f(builder, parser_context_free));
    cr_expect_eq(UR_OK, ubjs_parser_builder_set_limit_recursion_level(builder, 3));
    cr_expect_eq(UR_OK, ubjs_parser_builder_build(builder, &parser));
    cr_expect_eq(UR_OK, ubjs_parser_builder_free(&builder));

    data[0] = 123;

    data[1] = 85;
    data[2] = 1;
    data[3] = 'a';
    data[4] = 123;

    data[5] = 85;
    data[6] = 1;
    data[7] = 'a';
    data[8] = 123;

    data[9] = 85;
    data[10] = 1;
    data[11] = 'a';

    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, 12));

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

Test(parser, limit_recursion_level_object_above)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    uint8_t data[13];
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

    data[0] = 123;

    data[1] = 85;
    data[2] = 1;
    data[3] = 'a';
    data[4] = 123;

    data[5] = 85;
    data[6] = 1;
    data[7] = 'a';
    data[8] = 123;

    data[9] = 85;
    data[10] = 1;
    data[11] = 'a';
    data[12] = 123;

    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, 13));
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
