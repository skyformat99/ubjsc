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

#include "test_glue_mock.h"
#include "test_list.h"
#include "test_parser.h"
#include "test_parser_tools.h"

void suite_parser(tcontext *context)
{
    tsuite *suite;
    TSUITE("parser", suite_parser_before, suite_parser_after, &suite);
    tcontext_add_suite(context, suite);

    TTEST(suite, test_parser_builder);
    TTEST(suite, test_parser_basics);
    TTEST(suite, test_parser_unknown_marker);

    TTEST(suite, test_parser_settings_limit_bytes_since_last_callback_below);
    TTEST(suite, test_parser_settings_limit_bytes_since_last_callback_above);
    TTEST(suite, test_parser_settings_limit_container_length_array_unoptimized_below);
    TTEST(suite, test_parser_settings_limit_container_length_array_unoptimized_above);
    TTEST(suite, test_parser_settings_limit_container_length_array_optimized_below);
    TTEST(suite, test_parser_settings_limit_container_length_array_optimized_above);
    TTEST(suite, test_parser_settings_limit_container_length_object_unoptimized_below);
    TTEST(suite, test_parser_settings_limit_container_length_object_unoptimized_above);
    TTEST(suite, test_parser_settings_limit_container_length_object_optimized_below);
    TTEST(suite, test_parser_settings_limit_container_length_object_optimized_above);
    TTEST(suite, test_parser_settings_limit_string_length_optimized_below);
    TTEST(suite, test_parser_settings_limit_string_length_optimized_above);
    TTEST(suite, test_parser_settings_limit_hpn_length_optimized_below);
    TTEST(suite, test_parser_settings_limit_hpn_length_optimized_above);
    TTEST(suite, test_parser_settings_limit_recursion_level_array_below);
    TTEST(suite, test_parser_settings_limit_recursion_level_array_above);
    TTEST(suite, test_parser_settings_limit_recursion_level_object_above);
    TTEST(suite, test_parser_settings_limit_recursion_level_object_below);

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
    TTEST(suite, test_parser_array_optimized_type_float32_empty);
    TTEST(suite, test_parser_array_optimized_type_float64_empty);
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
    TTEST(suite, test_parser_array_optimized_type_float32_lots);
    TTEST(suite, test_parser_array_optimized_type_float64_lots);
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
    TTEST(suite, test_parser_object_optimized_type_float32_empty);
    TTEST(suite, test_parser_object_optimized_type_float64_empty);
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
    TTEST(suite, test_parser_object_optimized_type_float32_lots);
    TTEST(suite, test_parser_object_optimized_type_float64_lots);
    TTEST(suite, test_parser_object_optimized_type_str_lots);
    TTEST(suite, test_parser_object_optimized_type_hpn_lots);
    TTEST(suite, test_parser_object_optimized_type_array_lots);
    TTEST(suite, test_parser_object_optimized_type_object_lots);
}

void suite_parser_before(void)
{
    ubjs_library_builder *builder=0;
    ubjs_library_builder_new(&builder);
    ubjs_library_builder_set_glue_array_builder(builder,
        ubjs_glue_array_mock_builder_new);
    ubjs_library_builder_set_glue_dict_builder(builder,
        ubjs_glue_dict_mock_builder_new);
    ubjs_library_builder_build(builder, (ubjs_library **)&tstate);
    ubjs_library_builder_free(&builder);
}

void suite_parser_after(void)
{
    ubjs_library_free((ubjs_library **)&tstate);
}

void sp_verify_parsed(ubjs_library *lib, unsigned int length, uint8_t *data,
    sp_verify_parsed_callback callback)
{
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    test_list_item *parsed = 0;
    unsigned int len = 0;

    wrapped_parser_context_new(&wrapped);
    ubjs_parser_builder_new(lib, &builder);
    ubjs_parser_builder_set_userdata(builder, wrapped);
    ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed);
    ubjs_parser_builder_set_error_f(builder, parser_context_error);
    ubjs_parser_builder_set_free_f(builder, parser_context_free);
    ubjs_parser_builder_build(builder, &parser);
    ubjs_parser_builder_free(&builder);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, length));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, &parsed);
        if (callback != 0)
        {
            (callback)((ubjs_prmtv *)parsed->obj);
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void sp_verify_error(ubjs_library *lib, unsigned int length, uint8_t *data, char *error)
{
    ubjs_parser_builder *builder=0;
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    unsigned int len = 0;
    test_list_item *real_error = 0;

    wrapped_parser_context_new(&wrapped);
    ubjs_parser_builder_new(lib, &builder);
    ubjs_parser_builder_set_userdata(builder, wrapped);
    ubjs_parser_builder_set_parsed_f(builder, parser_context_parsed);
    ubjs_parser_builder_set_error_f(builder, parser_context_error);
    ubjs_parser_builder_set_free_f(builder, parser_context_free);
    ubjs_parser_builder_build(builder, &parser);
    ubjs_parser_builder_free(&builder);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, length));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        TASSERT_STRING_EQUAL(error, (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

/*
void dsp_verify_parsed(ubjs_library *lib, unsigned int length, uint8_t *data,
    sp_verify_parsed_callback callback)
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    ubjs_prmtv *parsed = 0;
    unsigned int len = 0;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UTRUE;

    ubjs_parser_new(lib, &settings, &context, &parser);

    TASSERT_EQUALI(UR_OK, ubjs_parser_parse(parser, data, length));
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_parsed, 0, (void **)&parsed);
        if (callback != 0)
        {
            (callback)(parsed);
        }
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}

void dsp_verify_error(ubjs_library *lib, unsigned int length, uint8_t *data, char *error)
{
    ubjs_parser *parser=0;
    wrapped_parser_context *wrapped;
    ubjs_parser_context context;
    ubjs_parser_settings settings;
    unsigned int len = 0;
    char *real_error = 0;

    wrapped_parser_context_new(&wrapped);
    context.userdata = wrapped;
    context.parsed = parser_context_parsed;
    context.error = parser_context_error;
    context.free = parser_context_free;
    settings.limit_bytes_since_last_callback = 0;
    settings.limit_container_length = 0;
    settings.limit_string_length = 0;
    settings.limit_recursion_level = 0;
    settings.debug = UTRUE;

    ubjs_parser_new(lib, &settings, &context, &parser);

    TASSERT_EQUALI(UR_ERROR, ubjs_parser_parse(parser, data, length));
    test_list_len(wrapped->calls_parsed, &len);
    TASSERT_EQUALI(0, len);
    test_list_len(wrapped->calls_error, &len);
    TASSERT_EQUALI(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, (void **)&real_error);
        TASSERT_STRING_EQUAL(error, real_error);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}
*/
