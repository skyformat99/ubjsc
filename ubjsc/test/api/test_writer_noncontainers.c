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
#include "test_writer.h"
#include "test_writer_tools.h"

Test(writer, init_clean)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_writer_builder *builder=0;
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    void *userdata=0;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);

    cr_expect_eq(UR_ERROR, ubjs_writer_builder_new(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_new(lib, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_new(0, &builder));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_free(0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_free(&builder));

    cr_expect_eq(UR_OK, ubjs_writer_builder_new(lib, &builder));
    cr_expect_neq(0, builder);

    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_userdata(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_userdata(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_userdata(0, wrapped));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_would_write_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_would_write_f(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_would_write_f(0, writer_context_would_write));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_would_print_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_would_print_f(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_would_print_f(0, writer_context_would_print));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_free_f(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_free_f(builder, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_set_free_f(0, writer_context_free));

    cr_expect_eq(UR_OK, ubjs_writer_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_writer_builder_set_would_write_f(builder,
        writer_context_would_write));
    cr_expect_eq(UR_OK, ubjs_writer_builder_set_would_print_f(builder,
        writer_context_would_print));
    cr_expect_eq(UR_OK, ubjs_writer_builder_set_free_f(builder, writer_context_free));
    cr_expect_eq(UR_OK, ubjs_writer_builder_build(builder, &writer));
    cr_expect_neq(0, writer);

    cr_expect_eq(UR_OK, ubjs_writer_builder_free(&builder));
    cr_expect_eq(0, builder);
    cr_expect_eq(UR_ERROR, ubjs_writer_builder_free(&builder));

    cr_expect_eq(UR_ERROR, ubjs_writer_get_userdata(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_get_userdata(writer, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_get_userdata(0, &userdata));
    cr_expect_eq(UR_ERROR, ubjs_writer_free(0));

    cr_expect_eq(UR_OK, ubjs_writer_get_userdata(writer, &userdata));
    cr_expect_eq(wrapped, userdata);

    cr_expect_eq(UR_OK, ubjs_writer_free(&writer));
    cr_expect_eq(0, writer);
    test_list_len(wrapped->calls_free, &len);
    cr_expect_eq(1, len);
    cr_expect_eq(UR_ERROR, ubjs_writer_free(&writer));

    wrapped_writer_context_free(&wrapped);
}

Test(writer, basics)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    ubjs_writer_builder *builder=0;
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    unsigned int len;

    wrapped_writer_context_new(&wrapped);

    cr_expect_eq(UR_OK, ubjs_writer_builder_new(lib, &builder));
    cr_expect_eq(UR_OK, ubjs_writer_builder_set_userdata(builder, wrapped));
    cr_expect_eq(UR_OK, ubjs_writer_builder_set_would_write_f(builder,
        writer_context_would_write));
    cr_expect_eq(UR_OK, ubjs_writer_builder_set_would_print_f(builder,
        writer_context_would_print));
    cr_expect_eq(UR_OK, ubjs_writer_builder_set_free_f(builder, writer_context_free));
    cr_expect_eq(UR_OK, ubjs_writer_builder_build(builder, &writer));
    cr_expect_eq(UR_OK, ubjs_writer_builder_free(&builder));

    cr_expect_eq(UR_ERROR, ubjs_writer_write(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_write(writer, 0));
    test_list_len(wrapped->calls_would_write, &len);
    cr_expect_eq(0, len);
    cr_expect_eq(UR_ERROR, ubjs_writer_write(0, (ubjs_prmtv *)1));

    cr_expect_eq(UR_ERROR, ubjs_writer_print(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_writer_print(writer, 0));
    test_list_len(wrapped->calls_would_print, &len);
    cr_expect_eq(0, len);
    cr_expect_eq(UR_ERROR, ubjs_writer_print(0, (ubjs_prmtv *)1));

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);

}

Test(writer, float64)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={68, 0, 0, 0, 0, 0, 0, 0, 0};
    char *pretty="[D][0.000000]";
    ubjs_prmtv *value;
    ubjs_prmtv_float64(lib, 0, &value);
    sw_verify(lib, value,
              9, bytes,
              13, pretty);
    ubjs_prmtv_free(&value);
}
