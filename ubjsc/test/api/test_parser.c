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
#include "test_glue_mock.h"
#include "test_list.h"
#include "test_parser.h"
#include "test_parser_tools.h"

TestSuite(parser, .init = suite_parser_before, .fini = suite_parser_after);

void suite_parser_before(void)
{
    ubjs_library_builder builder;

    tbefore();

    ubjs_library_builder_init(&builder);
    ubjs_library_builder_set_glue_array_builder(&builder,
        ubjs_glue_array_mock_builder_new);
    ubjs_library_builder_set_glue_dict_builder(&builder,
        ubjs_glue_dict_mock_builder_new);
    ubjs_library_builder_build(&builder, (ubjs_library **)&instance_lib);
}

void suite_parser_after(void)
{
    ubjs_library_free((ubjs_library **)&instance_lib);

    tafter();
}

void dsp_verify_parsed(ubjs_library *lib, unsigned int length, uint8_t *data,
    sp_verify_parsed_callback callback, ubjs_bool debug)
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
    if (UTRUE == debug)
    {
        ubjs_parser_builder_set_debug_f(builder, parser_context_debug);
    }
    ubjs_parser_builder_set_free_f(builder, parser_context_free);
    ubjs_parser_builder_build(builder, &parser);
    ubjs_parser_builder_free(&builder);

    cr_expect_eq(UR_OK, ubjs_parser_parse(parser, data, length));
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(1, len);

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

void dsp_verify_error(ubjs_library *lib, unsigned int length, uint8_t *data, char *error, ubjs_bool debug)
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
    if (UTRUE == debug)
    {
        ubjs_parser_builder_set_debug_f(builder, parser_context_debug);
    }
    ubjs_parser_builder_set_free_f(builder, parser_context_free);
    ubjs_parser_builder_build(builder, &parser);
    ubjs_parser_builder_free(&builder);

    cr_expect_eq(UR_ERROR, ubjs_parser_parse(parser, data, length));
    test_list_len(wrapped->calls_parsed, &len);
    cr_expect_eq(0, len);
    test_list_len(wrapped->calls_error, &len);
    cr_expect_eq(1, len);

    if (1 == len)
    {
        test_list_get(wrapped->calls_error, 0, &real_error);
        cr_expect_str_eq(error, (char *)real_error->obj);
    }

    ubjs_parser_free(&parser);
    wrapped_parser_context_free(&wrapped);
}


void sp_verify_parsed(ubjs_library *lib, unsigned int length, uint8_t *data,
    sp_verify_parsed_callback callback)
{
    dsp_verify_parsed(lib, length, data, callback, UFALSE);
}

void sp_verify_error(ubjs_library *lib, unsigned int length, uint8_t *data, char *error)
{
    dsp_verify_error(lib, length, data, error, UFALSE);
}
