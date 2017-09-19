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

TestSuite(prmtv_object_writer_upgrade, .init = before, .fini = after);

Test(prmtv_object_writer_upgrade, upgrade_u8_to_16)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[25];
    uint8_t orig[25];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 5, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[5] = 85;
    orig[6] = 0;
    orig[7] = 1;
    orig[8] = 0;

    for (i = 0; i < 4; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 1);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i16, name);
        orig[9 + i * 4] = 85;
        orig[10 + i * 4] = 0;
        orig[11 + i * 4] = 1;
        orig[12 + i * 4] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(25, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 25);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
}


Test(prmtv_object_writer_upgrade, upgrade_8_to_16)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[25];
    uint8_t orig[25];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 5, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[5] = 85;
    orig[6] = 0;
    orig[7] = 1;
    orig[8] = 0;

    for (i = 0; i < 4; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 1);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i16, name);
        orig[9 + i * 4] = 85;
        orig[10 + i * 4] = 0;
        orig[11 + i * 4] = 1;
        orig[12 + i * 4] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(25, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 25);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
}

Test(prmtv_object_writer_upgrade, upgrade_u8_16_to_32)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[59];
    uint8_t orig[59];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 9, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[5] = 85;
    orig[6] = 0;
    orig[7] = 1;
    orig[8] = 0;
    orig[9] = 0;
    orig[10] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[11] = 85;
    orig[12] = 0;
    orig[13] = 1;
    orig[14] = 0;
    orig[15] = 0;
    orig[16] = 0;

    for (i = 0; i < 7; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 2);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i32, name);
        orig[17 + i * 6] = 85;
        orig[18 + i * 6] = 0;
        orig[19 + i * 6] = 1;
        orig[20 + i * 6] = 0;
        orig[21 + i * 6] = 0;
        orig[22 + i * 6] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(59, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 59);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}


Test(prmtv_object_writer_upgrade, upgrade_8_16_to_32)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[59];
    uint8_t orig[59];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 9, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[5] = 85;
    orig[6] = 0;
    orig[7] = 1;
    orig[8] = 0;
    orig[9] = 0;
    orig[10] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[11] = 85;
    orig[12] = 0;
    orig[13] = 1;
    orig[14] = 0;
    orig[15] = 0;
    orig[16] = 0;

    for (i = 0; i < 7; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 2);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i32, name);
        orig[17 + i * 6] = 85;
        orig[18 + i * 6] = 0;
        orig[19 + i * 6] = 1;
        orig[20 + i * 6] = 0;
        orig[21 + i * 6] = 0;
        orig[22 + i * 6] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(59, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 59);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_object_writer_upgrade, upgrade_u8_16_32_to_64)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[215];
    uint8_t orig[215];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 21, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[5] = 85;
    orig[6] = 0;
    orig[7] = 1;
    orig[8] = 0;
    orig[9] = 0;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;
    orig[13] = 0;
    orig[14] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[15] = 85;
    orig[16] = 0;
    orig[17] = 1;
    orig[18] = 0;
    orig[19] = 0;
    orig[20] = 0;
    orig[21] = 0;
    orig[22] = 0;
    orig[23] = 0;
    orig[24] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 32 1");
    twill_returnoc("dict_iterator_get_value", i32, "item 32 1");
    orig[25] = 85;
    orig[26] = 0;
    orig[27] = 1;
    orig[28] = 0;
    orig[29] = 0;
    orig[30] = 0;
    orig[31] = 0;
    orig[32] = 0;
    orig[33] = 0;
    orig[34] = 0;

    for (i = 0; i < 18; i++)
    {
        char name[11];
        sprintf(name, "item 64 %u", i + 3);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i64, name);

        orig[35 + i * 10] = 85;
        orig[36 + i * 10] = 0;
        orig[37 + i * 10] = 1;
        orig[38 + i * 10] = 0;
        orig[39 + i * 10] = 0;
        orig[40 + i * 10] = 0;
        orig[41 + i * 10] = 0;
        orig[42 + i * 10] = 0;
        orig[43 + i * 10] = 0;
        orig[44 + i * 10] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(215, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 215);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_writer_upgrade, upgrade_8_16_32_to_64)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[215];
    uint8_t orig[215];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 21, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[5] = 85;
    orig[6] = 0;
    orig[7] = 1;
    orig[8] = 0;
    orig[9] = 0;
    orig[10] = 0;
    orig[11] = 0;
    orig[12] = 0;
    orig[13] = 0;
    orig[14] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[15] = 85;
    orig[16] = 0;
    orig[17] = 1;
    orig[18] = 0;
    orig[19] = 0;
    orig[20] = 0;
    orig[21] = 0;
    orig[22] = 0;
    orig[23] = 0;
    orig[24] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 32 1");
    twill_returnoc("dict_iterator_get_value", i32, "item 32 1");
    orig[25] = 85;
    orig[26] = 0;
    orig[27] = 1;
    orig[28] = 0;
    orig[29] = 0;
    orig[30] = 0;
    orig[31] = 0;
    orig[32] = 0;
    orig[33] = 0;
    orig[34] = 0;

    for (i = 0; i < 18; i++)
    {
        char name[11];
        sprintf(name, "item 64 %u", i + 3);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i64, name);

        orig[35 + i * 10] = 85;
        orig[36 + i * 10] = 0;
        orig[37 + i * 10] = 1;
        orig[38 + i * 10] = 0;
        orig[39 + i * 10] = 0;
        orig[40 + i * 10] = 0;
        orig[41 + i * 10] = 0;
        orig[42 + i * 10] = 0;
        orig[43 + i * 10] = 0;
        orig[44 + i * 10] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(215, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 215);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_to_16_too_little)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[22];
    uint8_t orig[22];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 4, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 105;
    orig[6] = 1;

    for (i = 0; i < 3; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 1);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i16, name);
        orig[7 + i * 5] = 85;
        orig[8 + i * 5] = 0;
        orig[9 + i * 5] = 73;
        orig[10 + i * 5] = 1;
        orig[11 + i * 5] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(22, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 22);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_to_16_32s)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[29];
    uint8_t orig[29];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 5, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 105;
    orig[6] = 1;

    twill_returnuic("dict_iterator_next", UR_OK, "item 1 32");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1 32");
    twill_returnoc("dict_iterator_get_value", i32, "item 1 32");
    orig[7] = 85;
    orig[8] = 0;
    orig[9] = 108;
    orig[10] = 1;
    orig[11] = 0;
    orig[12] = 0;
    orig[13] = 0;

    for (i = 0; i < 3; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 2);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i16, name);
        orig[14 + i * 5] = 85;
        orig[15 + i * 5] = 0;
        orig[16 + i * 5] = 73;
        orig[17 + i * 5] = 1;
        orig[18 + i * 5] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(29, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 29);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_to_16_str)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[29];
    uint8_t orig[29];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 5, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 105;
    orig[6] = 1;

    twill_returnuic("dict_iterator_next", UR_OK, "item 1 32");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1 32");
    twill_returnoc("dict_iterator_get_value", istr, "item 1 32");
    orig[7] = 85;
    orig[8] = 0;
    orig[9] = 83;
    orig[10] = 85;
    orig[11] = 2;
    orig[12] = 32;
    orig[13] = 32;

    for (i = 0; i < 3; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 2);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i16, name);
        orig[14 + i * 5] = 85;
        orig[15 + i * 5] = 0;
        orig[16 + i * 5] = 73;
        orig[17 + i * 5] = 1;
        orig[18 + i * 5] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(29, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 29);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&istr);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_to_16_64s)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[33];
    uint8_t orig[33];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 5, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 85;
    orig[6] = 1;

    twill_returnuic("dict_iterator_next", UR_OK, "item 1 64");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1 64");
    twill_returnoc("dict_iterator_get_value", i64, "item 1 64");
    orig[7] = 85;
    orig[8] = 0;
    orig[9] = 76;
    orig[10] = 1;
    orig[11] = 0;
    orig[12] = 0;
    orig[13] = 0;
    orig[14] = 0;
    orig[15] = 0;
    orig[16] = 0;
    orig[17] = 0;

    for (i = 0; i < 3; i++)
    {
        char name[10];
        sprintf(name, "item 16 %u", i + 2);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i16, name);
        orig[18 + i * 5] = 85;
        orig[19 + i * 5] = 0;
        orig[20 + i * 5] = 73;
        orig[21 + i * 5] = 1;
        orig[22 + i * 5] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(33, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 33);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_16_to_32_too_little)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[54];
    uint8_t orig[54];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 8, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 85;
    orig[6] = 1;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[7] = 85;
    orig[8] = 0;
    orig[9] = 73;
    orig[10] = 1;
    orig[11] = 0;

    for (i = 0; i < 6; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 2);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i32, name);
        orig[12 + i * 7] = 85;
        orig[13 + i * 7] = 0;
        orig[14 + i * 7] = 108;
        orig[15 + i * 7] = 1;
        orig[16 + i * 7] = 0;
        orig[17 + i * 7] = 0;
        orig[18 + i * 7] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(54, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 54);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_16_to_32_64s)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[72];
    uint8_t orig[72];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 10, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 85;
    orig[6] = 1;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[7] = 85;
    orig[8] = 0;
    orig[9] = 73;
    orig[10] = 1;
    orig[11] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 64 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 64 2");
    twill_returnoc("dict_iterator_get_value", i64, "item 64 2");
    orig[12] = 85;
    orig[13] = 0;
    orig[14] = 76;
    orig[15] = 1;
    orig[16] = 0;
    orig[17] = 0;
    orig[18] = 0;
    orig[19] = 0;
    orig[20] = 0;
    orig[21] = 0;
    orig[22] = 0;

    for (i = 0; i < 7; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 3);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i32, name);
        orig[23 + i * 7] = 85;
        orig[24 + i * 7] = 0;
        orig[25 + i * 7] = 108;
        orig[26 + i * 7] = 1;
        orig[27 + i * 7] = 0;
        orig[28 + i * 7] = 0;
        orig[29 + i * 7] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(72, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 72);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_16_to_32_str)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[72];
    uint8_t orig[72];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 10, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 85;
    orig[6] = 1;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[7] = 85;
    orig[8] = 0;
    orig[9] = 73;
    orig[10] = 1;
    orig[11] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 64 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 64 2");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 64 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 64 2");
    twill_returnuic("dict_iterator_copy_key", 0, "item 64 2");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 64 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 64 2");
    twill_returnoc("dict_iterator_get_value", istr, "item 64 2");
    orig[12] = 85;
    orig[13] = 0;
    orig[14] = 83;
    orig[15] = 85;
    orig[16] = 6;
    orig[17] = 32;
    orig[18] = 32;
    orig[19] = 32;
    orig[20] = 32;
    orig[21] = 32;
    orig[22] = 32;

    for (i = 0; i < 7; i++)
    {
        char name[10];
        sprintf(name, "item 32 %u", i + 3);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i32, name);
        orig[23 + i * 7] = 85;
        orig[24 + i * 7] = 0;
        orig[25 + i * 7] = 108;
        orig[26 + i * 7] = 1;
        orig[27 + i * 7] = 0;
        orig[28 + i * 7] = 0;
        orig[29 + i * 7] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(72, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 72);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&istr);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_16_32_to_64_too_little)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[206];
    uint8_t orig[206];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 20, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 85;
    orig[6] = 1;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[7] = 85;
    orig[8] = 0;
    orig[9] = 73;
    orig[10] = 1;
    orig[11] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 2");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 32 2");
    twill_returnoc("dict_iterator_get_value", i32, "item 32 2");
    orig[12] = 85;
    orig[13] = 0;
    orig[14] = 108;
    orig[15] = 1;
    orig[16] = 0;
    orig[17] = 0;
    orig[18] = 0;

    for (i = 0; i < 17; i++)
    {
        char name[11];
        sprintf(name, "item 64 %u", i + 3);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i64, name);
        orig[19 + i * 11] = 85;
        orig[20 + i * 11] = 0;
        orig[21 + i * 11] = 76;
        orig[22 + i * 11] = 1;
        orig[23 + i * 11] = 0;
        orig[24 + i * 11] = 0;
        orig[25 + i * 11] = 0;
        orig[26 + i * 11] = 0;
        orig[27 + i * 11] = 0;
        orig[28 + i * 11] = 0;
        orig[29 + i * 11] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(206, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 206);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_writer_upgrade, no_upgrade_8_16_32_to_64_str)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[222];
    uint8_t orig[222];
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

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 22, "get length");

    twill_returnuic("dict_iterator_next", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 8 0");
    twill_returnoc("dict_iterator_get_value", i8, "item 8 0");
    orig[3] = 85;
    orig[4] = 0;
    orig[5] = 85;
    orig[6] = 1;

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    orig[7] = 85;
    orig[8] = 0;
    orig[9] = 73;
    orig[10] = 1;
    orig[11] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 2");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 32 2");
    twill_returnoc("dict_iterator_get_value", i32, "item 32 2");
    orig[12] = 85;
    orig[13] = 0;
    orig[14] = 108;
    orig[15] = 1;
    orig[16] = 0;
    orig[17] = 0;
    orig[18] = 0;

    twill_returnuic("dict_iterator_next", UR_OK, "item str 3");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item str 3");
    twill_returnuic("dict_iterator_get_key_length", 0, "item str 3");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item str 3");
    twill_returnuic("dict_iterator_copy_key", 0, "item str 3");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item str 3");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item str 3");
    twill_returnoc("dict_iterator_get_value", istr, "item str 3");
    orig[19] = 85;
    orig[20] = 0;
    orig[21] = 83;
    orig[22] = 85;
    orig[23] = 0;

    for (i = 0; i < 18; i++)
    {
        char name[11];
        sprintf(name, "item 64 %u", i + 4);
        twill_returnuic("dict_iterator_next", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", UR_OK, name);
        twill_returnuic("dict_iterator_get_key_length", 0, name);
        twill_returnuic("dict_iterator_copy_key", UR_OK, name);
        twill_returnuic("dict_iterator_copy_key", 0, name);
        twill_returnoc("dict_iterator_copy_key", strdup(""), name);
        twill_returnuic("dict_iterator_get_value", UR_OK, name);
        twill_returnoc("dict_iterator_get_value", i64, name);
        orig[24 + i * 11] = 85;
        orig[25 + i * 11] = 0;
        orig[26 + i * 11] = 76;
        orig[27 + i * 11] = 1;
        orig[28 + i * 11] = 0;
        orig[29 + i * 11] = 0;
        orig[30 + i * 11] = 0;
        orig[31 + i * 11] = 0;
        orig[32 + i * 11] = 0;
        orig[33 + i * 11] = 0;
        orig[34 + i * 11] = 0;
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(222, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.writer_do_f)(writer, data);
    cr_expect_arr_eq(data, orig, 222);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.writer_free_f)(&writer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
    ubjs_prmtv_free(&istr);
}
