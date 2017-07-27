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
#include "test_glue_mock.h"

static ubjs_library *lib;
static void before(void)
{
    ubjs_library_builder builder;

    tbefore();

    ubjs_library_builder_init(&builder);
    ubjs_library_builder_set_glue_array_builder(&builder,
        ubjs_glue_array_mock_builder_new);
    ubjs_library_builder_set_glue_dict_builder(&builder,
        ubjs_glue_dict_mock_builder_new);
    ubjs_library_builder_build(&builder, &lib);
}

static void after(void)
{
    ubjs_library_free(&lib);
    tafter();
}

static void writer_glue_debug_unexpected(ubjs_prmtv_marker_writer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

TestSuite(prmtv_array_writer_upgrade, .init = before, .fini = after);
Test(prmtv_array_writer_upgrade, writer_upgrade_u8_to_16)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[15];
    uint8_t orig[15];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);

    orig[0] = 36;
    orig[1] = 73;
    orig[2] = 35;
    orig[3] = 85;
    orig[4] = 5;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 5, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[5] = 1;
    orig[6] = 0;

    for (i = 0; i < 4; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 1);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i16, name);
        orig[7 + i * 2] = 1;
        orig[8 + i * 2] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(15, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 15);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
}

Test(prmtv_array_writer_upgrade, writer_upgrade_8_to_16)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[15];
    uint8_t orig[15];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);

    orig[0] = 36;
    orig[1] = 73;
    orig[2] = 35;
    orig[3] = 85;
    orig[4] = 5;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 5, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[5] = 1;
    orig[6] = 0;

    for (i = 0; i < 4; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 1);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i16, name);
        orig[7 + i * 2] = 1;
        orig[8 + i * 2] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(15, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 15);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
}

Test(prmtv_array_writer_upgrade, writer_upgrade_u8_16_to_32)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[41];
    uint8_t orig[41];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);

    orig[0] = 36;
    orig[1] = 108;
    orig[2] = 35;
    orig[3] = 85;
    orig[4] = 9;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 9, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[5] = 1;
    orig[6] = 0;
    orig[7] = 0;
    orig[8] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[9] = 1;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;

    for (i = 0; i < 7; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 2);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i32, name);
        orig[13 + i * 4] = 1;
        orig[14 + i * 4] = 0;
        orig[15 + i * 4] = 0;
        orig[16 + i * 4] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(41, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 41);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_array_writer_upgrade, writer_upgrade_8_16_to_32)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[41];
    uint8_t orig[41];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);

    orig[0] = 36;
    orig[1] = 108;
    orig[2] = 35;
    orig[3] = 85;
    orig[4] = 9;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 9, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[5] = 1;
    orig[6] = 0;
    orig[7] = 0;
    orig[8] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[9] = 1;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;

    for (i = 0; i < 7; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 2);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i32, name);
        orig[13 + i * 4] = 1;
        orig[14 + i * 4] = 0;
        orig[15 + i * 4] = 0;
        orig[16 + i * 4] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(41, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 41);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_array_writer_upgrade, writer_upgrade_u8_16_32_to_64)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[173];
    uint8_t orig[173];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_int64(lib, 1, &i64);

    orig[0] = 36;
    orig[1] = 76;
    orig[2] = 35;
    orig[3] = 85;
    orig[4] = 21;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 21, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[5] = 1;
    orig[6] = 0;
    orig[7] = 0;
    orig[8] = 0;
    orig[9] = 0;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[13] = 1;
    orig[14] = 0;
    orig[15] = 0;
    orig[16] = 0;
    orig[17] = 0;
    orig[18] = 0;
    orig[19] = 0;
    orig[20] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 32 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 32 1");
    twill_returnoc("array_iterator_get", i32, "item 32 1");
    orig[21] = 1;
    orig[22] = 0;
    orig[23] = 0;
    orig[24] = 0;
    orig[25] = 0;
    orig[26] = 0;
    orig[27] = 0;
    orig[28] = 0;

    for (i = 0; i < 18; i++)
    {
        char name[11];
        sprintf(name, "item 64 %u", i + 3);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i64, name);

        orig[29 + i * 8] = 1;
        orig[30 + i * 8] = 0;
        orig[31 + i * 8] = 0;
        orig[32 + i * 8] = 0;
        orig[33 + i * 8] = 0;
        orig[34 + i * 8] = 0;
        orig[35 + i * 8] = 0;
        orig[36 + i * 8] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(173, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 173);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_array_writer_upgrade, writer_upgrade_8_16_32_to_64)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[173];
    uint8_t orig[173];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_int64(lib, 1, &i64);

    orig[0] = 36;
    orig[1] = 76;
    orig[2] = 35;
    orig[3] = 85;
    orig[4] = 21;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 21, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[5] = 1;
    orig[6] = 0;
    orig[7] = 0;
    orig[8] = 0;
    orig[9] = 0;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[13] = 1;
    orig[14] = 0;
    orig[15] = 0;
    orig[16] = 0;
    orig[17] = 0;
    orig[18] = 0;
    orig[19] = 0;
    orig[20] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 32 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 32 1");
    twill_returnoc("array_iterator_get", i32, "item 32 1");
    orig[21] = 1;
    orig[22] = 0;
    orig[23] = 0;
    orig[24] = 0;
    orig[25] = 0;
    orig[26] = 0;
    orig[27] = 0;
    orig[28] = 0;

    for (i = 0; i < 18; i++)
    {
        char name[11];
        sprintf(name, "item 64 %u", i + 3);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i64, name);

        orig[29 + i * 8] = 1;
        orig[30 + i * 8] = 0;
        orig[31 + i * 8] = 0;
        orig[32 + i * 8] = 0;
        orig[33 + i * 8] = 0;
        orig[34 + i * 8] = 0;
        orig[35 + i * 8] = 0;
        orig[36 + i * 8] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(173, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 173);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_to_16_too_little)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[14];
    uint8_t orig[14];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 4;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 4, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 105;
    orig[4] = 1;

    for (i = 0; i < 3; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 1);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i16, name);
        orig[5 + i * 3] = 73;
        orig[6 + i * 3] = 1;
        orig[7 + i * 3] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(14, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 14);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_to_16_32s)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[19];
    uint8_t orig[19];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);

    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 5;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 5, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 105;
    orig[4] = 1;

    twill_returnuic("array_iterator_next", UR_OK, "item 1 32");
    twill_returnuic("array_iterator_get", UR_OK, "item 1 32");
    twill_returnoc("array_iterator_get", i32, "item 1 32");
    orig[5] = 108;
    orig[6] = 1;
    orig[7] = 0;
    orig[8] = 0;
    orig[9] = 0;

    for (i = 0; i < 3; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 2);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i16, name);
        orig[10 + i * 3] = 73;
        orig[11 + i * 3] = 1;
        orig[12 + i * 3] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(19, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 19);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_to_16_str)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[19];
    uint8_t orig[19];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *istr = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_str(lib, 2, "  ", &istr);

    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 5;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 5, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 105;
    orig[4] = 1;

    twill_returnuic("array_iterator_next", UR_OK, "item 1 32");
    twill_returnuic("array_iterator_get", UR_OK, "item 1 32");
    twill_returnoc("array_iterator_get", istr, "item 1 32");
    orig[5] = 83;
    orig[6] = 85;
    orig[7] = 2;
    orig[8] = 32;
    orig[9] = 32;

    for (i = 0; i < 3; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 2);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i16, name);
        orig[10 + i * 3] = 73;
        orig[11 + i * 3] = 1;
        orig[12 + i * 3] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(19, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 19);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&istr);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_to_16_64s)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[23];
    uint8_t orig[23];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int64(lib, 1, &i64);

    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 5;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 5, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 1;

    twill_returnuic("array_iterator_next", UR_OK, "item 1 64");
    twill_returnuic("array_iterator_get", UR_OK, "item 1 64");
    twill_returnoc("array_iterator_get", i64, "item 1 64");
    orig[5] = 76;
    orig[6] = 1;
    orig[7] = 0;
    orig[8] = 0;
    orig[9] = 0;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;
    orig[13] = 0;

    for (i = 0; i < 3; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 2);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i16, name);
        orig[14 + i * 3] = 73;
        orig[15 + i * 3] = 1;
        orig[16 + i * 3] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(23, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 23);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_16_to_32_too_little)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[38];
    uint8_t orig[38];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);

    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 8;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 8, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 1;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[5] = 73;
    orig[6] = 1;
    orig[7] = 0;

    for (i = 0; i < 6; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 2);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i32, name);
        orig[8 + i * 5] = 108;
        orig[9 + i * 5] = 1;
        orig[10 + i * 5] = 0;
        orig[11 + i * 5] = 0;
        orig[12 + i * 5] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(38, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 38);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_16_to_32_64s)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[52];
    uint8_t orig[52];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_int64(lib, 1, &i64);

    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 10;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 10, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 1;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[5] = 73;
    orig[6] = 1;
    orig[7] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 2 64");
    twill_returnuic("array_iterator_get", UR_OK, "item 2 64");
    twill_returnoc("array_iterator_get", i64, "item 2 64");
    orig[8] = 76;
    orig[9] = 1;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;
    orig[13] = 0;
    orig[14] = 0;
    orig[15] = 0;
    orig[16] = 0;

    for (i = 0; i < 7; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 3);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i32, name);
        orig[17 + i * 5] = 108;
        orig[18 + i * 5] = 1;
        orig[19 + i * 5] = 0;
        orig[20 + i * 5] = 0;
        orig[21 + i * 5] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(52, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 52);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_16_to_32_str)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[52];
    uint8_t orig[52];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *istr = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_str(lib, 6, "      ", &istr);

    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 10;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 10, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 1;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[5] = 73;
    orig[6] = 1;
    orig[7] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 2 64");
    twill_returnuic("array_iterator_get", UR_OK, "item 2 str");
    twill_returnoc("array_iterator_get", istr, "item 2 str");
    orig[8] = 83;
    orig[9] = 85;
    orig[10] = 6;
    orig[11] = 32;
    orig[12] = 32;
    orig[13] = 32;
    orig[14] = 32;
    orig[15] = 32;
    orig[16] = 32;

    for (i = 0; i < 7; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 3);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i32, name);
        orig[17 + i * 5] = 108;
        orig[18 + i * 5] = 1;
        orig[19 + i * 5] = 0;
        orig[20 + i * 5] = 0;
        orig[21 + i * 5] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(52, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 52);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&istr);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_16_32_to_64_too_little)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[166];
    uint8_t orig[166];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_int64(lib, 1, &i64);

    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 20;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 20, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 1;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[5] = 73;
    orig[6] = 1;
    orig[7] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 32 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 32 2");
    twill_returnoc("array_iterator_get", i32, "item 32 2");
    orig[8] = 108;
    orig[9] = 1;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;

    for (i = 0; i < 17; i++)
    {
        char name[11];
        sprintf(name, "item 64 %u", i + 3);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i64, name);
        orig[13 + i * 9] = 76;
        orig[14 + i * 9] = 1;
        orig[15 + i * 9] = 0;
        orig[16 + i * 9] = 0;
        orig[17 + i * 9] = 0;
        orig[18 + i * 9] = 0;
        orig[19 + i * 9] = 0;
        orig[20 + i * 9] = 0;
        orig[21 + i * 9] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(166, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 166);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_array_writer_upgrade, writer_no_upgrade_8_16_32_to_64_str)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[178];
    uint8_t orig[178];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *i64 = 0;
    ubjs_prmtv *istr = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_int64(lib, 1, &i64);
    ubjs_prmtv_str(lib, 0, "", &istr);

    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 22;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 22, "get length");

    twill_returnuic("array_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("array_iterator_get", UR_OK, "item 8 0");
    twill_returnoc("array_iterator_get", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 1;

    twill_returnuic("array_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 16 1");
    twill_returnoc("array_iterator_get", i16, "item 16 1");
    orig[5] = 73;
    orig[6] = 1;
    orig[7] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item 32 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 32 2");
    twill_returnoc("array_iterator_get", i32, "item 32 2");
    orig[8] = 108;
    orig[9] = 1;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;

    twill_returnuic("array_iterator_next", UR_OK, "item str 3");
    twill_returnuic("array_iterator_get", UR_OK, "item str 3");
    twill_returnoc("array_iterator_get", istr, "item str 3");
    orig[13] = 83;
    orig[14] = 85;
    orig[15] = 0;

    for (i = 0; i < 18; i++)
    {
        char name[11];
        sprintf(name, "item 64 %u", i + 4);
        twill_returnuic("array_iterator_next", UR_OK, name);
        twill_returnuic("array_iterator_get", UR_OK, name);
        twill_returnoc("array_iterator_get", i64, name);
        orig[16 + i * 9] = 76;
        orig[17 + i * 9] = 1;
        orig[18 + i * 9] = 0;
        orig[19 + i * 9] = 0;
        orig[20 + i * 9] = 0;
        orig[21 + i * 9] = 0;
        orig[22 + i * 9] = 0;
        orig[23 + i * 9] = 0;
        orig[24 + i * 9] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(178, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 178);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
    ubjs_prmtv_free(&istr);
}
