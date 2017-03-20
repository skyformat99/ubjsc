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
#include "test_writer.h"
#include "test_writer_tools.h"

TestSuite(writer, .init = suite_writer_before, .fini = suite_writer_after);

void suite_writer_before(void)
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

void suite_writer_after(void)
{
    ubjs_library_free((ubjs_library **)&instance_lib);

    tafter();
}

void sw_verifyd(ubjs_library *lib, ubjs_prmtv *obj, unsigned int bytes_len, uint8_t *bytes,
    unsigned int pretty_len, char *pretty, ubjs_bool debug)
{
    ubjs_writer_builder *builder=0;
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    unsigned int len;
    test_list_item *it;

    wrapped_writer_context_new(&wrapped);

    ubjs_writer_builder_new(lib, &builder);
    ubjs_writer_builder_set_userdata(builder, wrapped);
    ubjs_writer_builder_set_would_write_f(builder, writer_context_would_write);
    ubjs_writer_builder_set_would_print_f(builder, writer_context_would_print);
    ubjs_writer_builder_set_free_f(builder, writer_context_free);
    if (UTRUE == debug)
    {
        ubjs_writer_builder_set_debug_f(builder, writer_context_debug);
    }
    ubjs_writer_builder_build(builder, &writer);
    ubjs_writer_builder_free(&builder);

    cr_expect_eq(UR_OK, ubjs_writer_write(writer, obj));
    test_list_len(wrapped->calls_would_write, &len);
    cr_expect_eq(1, len);

    if (1 == len)
    {
        unsigned int i;
        would_write_call *call_write;

        test_list_get(wrapped->calls_would_write, 0, &it);
        call_write = (would_write_call *)it->obj;
        cr_expect_eq(bytes_len, call_write->len);
        for (i = 0; i < bytes_len; i++)
        {
            cr_expect_eq(bytes[i], call_write->data[i]);
        }
    }

    cr_expect_eq(UR_OK, ubjs_writer_print(writer, obj));
    test_list_len(wrapped->calls_would_print, &len);
    cr_expect_eq(1, len);

    if (1 == len)
    {
        would_print_call *call_print;

        test_list_get(wrapped->calls_would_print, 0, &it);
        call_print = (would_print_call *)it->obj;
        cr_expect_eq(pretty_len, call_print->len);
        cr_assert_arr_eq(pretty, call_print->data, pretty_len);
    }

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);
}

void sw_verify(ubjs_library *lib, ubjs_prmtv *obj, unsigned int bytes_len, uint8_t *bytes,
    unsigned int pretty_len, char *pretty)
{
    sw_verifyd(lib, obj, bytes_len, bytes, pretty_len, pretty, UFALSE);
}
