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

Test(writer, noop)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={78};
    char *pretty="[N]";
    sw_verify(lib, ubjs_prmtv_noop(),
              1, bytes,
              3, pretty);
}

Test(writer, true)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={84};
    char *pretty="[T]";
    sw_verify(lib, ubjs_prmtv_true(),
              1, bytes,
              3, pretty);
}

Test(writer, false)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={70};
    char *pretty="[F]";
    sw_verify(lib, ubjs_prmtv_false(),
              1, bytes,
              3, pretty);
}

Test(writer, int8)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={105, 0};
    char *pretty="[i][0]";
    ubjs_prmtv *value;
    ubjs_prmtv_int8(lib, 0, &value);
    sw_verify(lib, value,
              2, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, uint8)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={85, 0};
    char *pretty="[U][0]";
    ubjs_prmtv *value;
    ubjs_prmtv_uint8(lib, 0, &value);
    sw_verify(lib, value,
              2, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, int16)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={73, 0, 0};
    char *pretty="[I][0]";
    ubjs_prmtv *value;
    ubjs_prmtv_int16(lib, 0, &value);
    sw_verify(lib, value,
              3, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, int32)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={108, 0, 0, 0, 0};
    char *pretty="[l][0]";
    ubjs_prmtv *value;
    ubjs_prmtv_int32(lib, 0, &value);
    sw_verify(lib, value,
              5, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, int64)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={76, 0, 0, 0, 0, 0, 0, 0, 0};
    char *pretty="[L][0]";
    ubjs_prmtv *value;
    ubjs_prmtv_int64(lib, 0, &value);
    sw_verify(lib, value,
              9, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, float32)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={100, 0, 0, 0, 0};
    char *pretty="[d][0.000000]";
    ubjs_prmtv *value;
    ubjs_prmtv_float32(lib, 0, &value);
    sw_verify(lib, value,
              5, bytes,
              13, pretty);
    ubjs_prmtv_free(&value);
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

Test(writer, char)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={67, 82};
    char *pretty="[C][R]";
    ubjs_prmtv *value;
    ubjs_prmtv_char(lib, 'R', &value);
    sw_verify(lib, value,
              2, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, str_uint8)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={83, 85, 5, 'r', 'o', 'w', 'e', 'r'};
    char *pretty="[S][U][5][rower]";
    ubjs_prmtv *value;
    ubjs_prmtv_str(lib, 5, "rower", &value);
    sw_verify(lib, value,
              8, bytes,
              16, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, str_int16)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t *bytes;
    char *pretty;
    char *text;
    unsigned int i;
    ubjs_prmtv *value;
    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 10004);
    bytes[0] = 83;
    bytes[1] = 73;
    bytes[2] = 16;
    bytes[3] = 39;
    pretty = (char *)malloc(sizeof(char) * 100016);
    text = (char *)malloc(sizeof(char) * 10000);
    snprintf(pretty, 15, "[S][I][10000][");
    for (i=0; 10000>i; i++)
    {
        text[i] = 'r';
        bytes[4 + i] = 'r';
        pretty[14 + i] = 'r';
    }
    snprintf(pretty + 10014, 2, "]");
    ubjs_prmtv_str(lib, 10000, text, &value);
    sw_verify(lib, value,
              10004, bytes,
              10015, pretty);
    ubjs_prmtv_free(&value);
    free(text);
    free(pretty);
    free(bytes);
}

Test(writer, str_int32)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t *bytes;
    char *pretty;
    char *text;
    unsigned int i;
    ubjs_prmtv *value;
    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 100006);
    bytes[0] = 83;
    bytes[1] = 108;
    bytes[2] = 160;
    bytes[3] = 134;
    bytes[4] = 1;
    bytes[5] = 0;
    pretty = (char *)malloc(sizeof(char) * 100017);
    text = (char *)malloc(sizeof(char) * 100000);
    snprintf(pretty, 16, "[S][l][100000][");
    for (i=0; 100000>i; i++)
    {
        text[i] = 'r';
        bytes[6 + i] = 'r';
        pretty[15 + i] = 'r';
    }
    snprintf(pretty + 100015, 2, "]");
    ubjs_prmtv_str(lib, 100000, text, &value);
    sw_verify(lib, value,
              100006, bytes,
              100016, pretty);
    ubjs_prmtv_free(&value);
    free(text);
    free(pretty);
    free(bytes);
}

Test(writer, hpn_uint8)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t bytes[]={72, 85, 5, '1', '1', '1', '1', '1'};
    char *pretty="[H][U][5][11111]";
    ubjs_prmtv *value;
    ubjs_prmtv_hpn(lib, 5, "11111", &value);
    sw_verify(lib, value,
              8, bytes,
              16, pretty);
    ubjs_prmtv_free(&value);
}

Test(writer, hpn_int16)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t *bytes;
    char *pretty;
    char *text;
    unsigned int i;
    ubjs_prmtv *value;
    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 10004);
    bytes[0] = 72;
    bytes[1] = 73;
    bytes[2] = 16;
    bytes[3] = 39;
    pretty = (char *)malloc(sizeof(char) * 10016);
    text = (char *)malloc(sizeof(char) * 10000);
    snprintf(pretty, 15, "[H][I][10000][");
    for (i=0; 10000>i; i++)
    {
        text[i] = '1';
        bytes[4 + i] = '1';
        pretty[14 + i] = '1';
    }
    snprintf(pretty + 10014, 2, "]");
    ubjs_prmtv_hpn(lib, 10000, text, &value);
    sw_verify(lib, value,
              10004, bytes,
              10015, pretty);
    ubjs_prmtv_free(&value);
    free(text);
    free(pretty);
    free(bytes);
}

Test(writer, hpn_int32)
{
    ubjs_library *lib = (ubjs_library *)instance_lib;
    uint8_t *bytes;
    char *pretty;
    char *text;
    unsigned int i;
    ubjs_prmtv *value;
    bytes = (uint8_t *)malloc(sizeof(uint8_t) * 100006);
    bytes[0] = 72;
    bytes[1] = 108;
    bytes[2] = 160;
    bytes[3] = 134;
    bytes[4] = 1;
    bytes[5] = 0;
    pretty = (char *)malloc(sizeof(char) * 100017);
    text = (char *)malloc(sizeof(char) * 100000);
    snprintf(pretty, 16, "[H][l][100000][");
    for (i=0; 100000>i; i++)
    {
        text[i] = '1';
        bytes[6 + i] = '1';
        pretty[15 + i] = '1';
    }
    snprintf(pretty + 100015, 2, "]");
    ubjs_prmtv_hpn(lib, 100000, text, &value);
    sw_verify(lib, value,
              100006, bytes,
              100016, pretty);
    ubjs_prmtv_free(&value);
    free(text);
    free(pretty);
    free(bytes);
}
