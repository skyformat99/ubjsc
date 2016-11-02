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

#include "test_list.h"
#include "test_writer.h"
#include "test_writer_tools.h"

void test_writer_init_clean()
{
    ubjs_library *lib = 0;
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    ubjs_writer_context *writer_context=0;
    unsigned int len;

    ubjs_library_new_stdlib(&lib);

    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(0, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(0, &writer, 0));
    TASSERT_EQUAL(0, writer);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(lib, 0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(lib, &writer, 0));
    TASSERT_EQUAL(0, writer);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(writer, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_get_context(0, &writer_context));
    TASSERT_EQUAL(0, writer_context);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_free(0));

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.free = 0;
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(0, &writer, &context));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(lib, &writer, &context));

    context.free = writer_context_free;
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_new(0, &writer, &context));
    TASSERT_EQUAL(0, writer);
    TASSERT_EQUAL(UR_OK, ubjs_writer_new(lib, &writer, &context));
    TASSERT_NOT_EQUAL(0, writer);
    TASSERT_EQUAL(UR_OK, ubjs_writer_get_context(writer, &writer_context));
    TASSERT_EQUAL(&context, writer_context);

    TASSERT_EQUAL(UR_OK, ubjs_writer_free(&writer));
    TASSERT_EQUAL(0, writer);
    test_list_len(wrapped->calls_free, &len);
    TASSERT_EQUALUI(1, len);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_free(&writer));
    wrapped_writer_context_reset(wrapped);

    TASSERT_EQUAL(UR_OK, ubjs_writer_new(lib, &writer, &context));
    TASSERT_EQUAL(UR_OK, ubjs_writer_free(&writer));
    test_list_len(wrapped->calls_free, &len);
    TASSERT_EQUALUI(1, len);
    wrapped_writer_context_free(&wrapped);

    ubjs_library_free(&lib);
}

void test_writer_basics()
{
    ubjs_library *lib = 0;
    ubjs_writer *writer=0;
    wrapped_writer_context *wrapped;
    ubjs_writer_context context;
    unsigned int len;

    ubjs_library_new_stdlib(&lib);

    wrapped_writer_context_new(&wrapped);
    context.userdata = wrapped;
    context.would_write = writer_context_would_write;
    context.would_print = writer_context_would_print;
    context.free = writer_context_free;

    TASSERT_EQUAL(UR_OK, ubjs_writer_new(lib, &writer, &context));

    TASSERT_EQUAL(UR_ERROR, ubjs_writer_write(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_write(writer, 0));
    test_list_len(wrapped->calls_would_write, &len);
    TASSERT_EQUALUI(0, len);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_write(0, (ubjs_prmtv *)1));

    TASSERT_EQUAL(UR_ERROR, ubjs_writer_print(0, 0));
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_print(writer, 0));
    test_list_len(wrapped->calls_would_print, &len);
    TASSERT_EQUALUI(0, len);
    TASSERT_EQUAL(UR_ERROR, ubjs_writer_print(0, (ubjs_prmtv *)1));

    ubjs_writer_free(&writer);
    wrapped_writer_context_free(&wrapped);

    ubjs_library_free(&lib);
}

void test_writer_null()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={90};
    char *pretty="[Z]";

    ubjs_library_new_stdlib(&lib);
    sw_verify(lib, ubjs_prmtv_null(),
              1, bytes,
              3, pretty);
    ubjs_library_free(&lib);
}

void test_writer_noop()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={78};
    char *pretty="[N]";

    ubjs_library_new_stdlib(&lib);
    sw_verify(lib, ubjs_prmtv_noop(),
              1, bytes,
              3, pretty);
    ubjs_library_free(&lib);
}

void test_writer_true()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={84};
    char *pretty="[T]";

    ubjs_library_new_stdlib(&lib);
    sw_verify(lib, ubjs_prmtv_true(),
              1, bytes,
              3, pretty);
    ubjs_library_free(&lib);
}

void test_writer_false()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={70};
    char *pretty="[F]";

    ubjs_library_new_stdlib(&lib);
    sw_verify(lib, ubjs_prmtv_false(),
              1, bytes,
              3, pretty);
    ubjs_library_free(&lib);
}

void test_writer_int8()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={105, 0};
    char *pretty="[i][0]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_int8(lib, 0, &value);
    sw_verify(lib, value,
              2, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_uint8()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={85, 0};
    char *pretty="[U][0]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_uint8(lib, 0, &value);
    sw_verify(lib, value,
              2, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_int16()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={73, 0, 0};
    char *pretty="[I][0]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_int16(lib, 0, &value);
    sw_verify(lib, value,
              3, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_int32()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={108, 0, 0, 0, 0};
    char *pretty="[l][0]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_int32(lib, 0, &value);
    sw_verify(lib, value,
              5, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_int64()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={76, 0, 0, 0, 0, 0, 0, 0, 0};
    char *pretty="[L][0]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_int64(lib, 0, &value);
    sw_verify(lib, value,
              9, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_float32()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={100, 0, 0, 0, 0};
    char *pretty="[d][0.000000]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_float32(lib, 0, &value);
    sw_verify(lib, value,
              5, bytes,
              13, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_float64()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={68, 0, 0, 0, 0, 0, 0, 0, 0};
    char *pretty="[D][0.000000]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_float64(lib, 0, &value);
    sw_verify(lib, value,
              9, bytes,
              13, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_char()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={67, 82};
    char *pretty="[C][R]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_char(lib, 'R', &value);
    sw_verify(lib, value,
              2, bytes,
              6, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_str_uint8()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={83, 85, 5, 'r', 'o', 'w', 'e', 'r'};
    char *pretty="[S][U][5][rower]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_str(lib, 5, "rower", &value);
    sw_verify(lib, value,
              8, bytes,
              16, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_str_int16()
{
    ubjs_library *lib = 0;
    uint8_t bytes[10004];
    char pretty[10016];
    char text[10000];
    unsigned int i;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 83;
    bytes[1] = 73;
    bytes[2] = 16;
    bytes[3] = 39;
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
    ubjs_library_free(&lib);
}

void test_writer_str_int32()
{
    ubjs_library *lib = 0;
    uint8_t bytes[100006];
    char pretty[100017];
    char text[100000];
    unsigned int i;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    bytes[0] = 83;
    bytes[1] = 108;
    bytes[2] = 160;
    bytes[3] = 134;
    bytes[4] = 1;
    bytes[5] = 0;
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
    ubjs_library_free(&lib);
}

void test_writer_hpn_uint8()
{
    ubjs_library *lib = 0;
    uint8_t bytes[]={72, 85, 5, '1', '1', '1', '1', '1'};
    char *pretty="[H][U][5][11111]";
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);
    ubjs_prmtv_hpn(lib, 5, "11111", &value);
    sw_verify(lib, value,
              8, bytes,
              16, pretty);
    ubjs_prmtv_free(&value);
    ubjs_library_free(&lib);
}

void test_writer_hpn_int16()
{
    ubjs_library *lib = 0;
    uint8_t bytes[10004];
    char pretty[10016];
    char text[10000];
    unsigned int i;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);

    bytes[0] = 72;
    bytes[1] = 73;
    bytes[2] = 16;
    bytes[3] = 39;
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
    ubjs_library_free(&lib);
}

void test_writer_hpn_int32()
{
    ubjs_library *lib = 0;
    uint8_t bytes[100006];
    char pretty[100017];
    char text[100000];
    unsigned int i;
    ubjs_prmtv *value;

    ubjs_library_new_stdlib(&lib);

    bytes[0] = 72;
    bytes[1] = 108;
    bytes[2] = 160;
    bytes[3] = 134;
    bytes[4] = 1;
    bytes[5] = 0;
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
    ubjs_library_free(&lib);
}
