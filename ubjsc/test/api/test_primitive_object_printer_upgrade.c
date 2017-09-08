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

static void printer_glue_debug_unexpected(ubjs_prmtv_marker_printer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

TestSuite(prmtv_object_printer_upgrade, .init = before, .fini = after);

Test(prmtv_object_printer_upgrade, upgrade_8_to_16)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[96];
    char orig[96];
    unsigned int i;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    unsigned int at = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);

    at += snprintf(orig + at, 16, "[$][I][#][U][5]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 17, "\n    [U][0][][1]");

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
        at += snprintf(orig + at, 17, "\n    [U][0][][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(95, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 95);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
}

Test(prmtv_object_printer_upgrade, upgrade_8_16_to_32)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[160];
    char orig[160];
    unsigned int i;
    unsigned int at = 0;
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

    at += snprintf(orig + at, 16, "[$][l][#][U][9]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 17, "\n    [U][0][][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    at += snprintf(orig + at, 17, "\n    [U][0][][1]");

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
        at += snprintf(orig + at, 17, "\n    [U][0][][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(159, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 159);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_object_printer_upgrade, upgrade_8_16_32_to_64)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[353];
    char orig[353];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_int64(lib, 1, &i64);

    at += snprintf(orig + at, 17, "[$][L][#][U][21]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 17, "\n    [U][0][][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    at += snprintf(orig + at, 17, "\n    [U][0][][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 32 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 32 1");
    twill_returnoc("dict_iterator_get_value", i32, "item 32 1");
    at += snprintf(orig + at, 17, "\n    [U][0][][1]");

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
        at += snprintf(orig + at, 17, "\n    [U][0][][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(352, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 352);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_to_16_too_little)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[86];
    char orig[86];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    orig[0] = 35;
    orig[1] = 85;
    orig[2] = 4;
    at += snprintf(orig + at, 10, "[#][U][4]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][i][1]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(85, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 85);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_to_16_32s)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[105];
    char orig[105];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);

    at += snprintf(orig + at, 10, "[#][U][5]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][i][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 1 32");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 8 0");
    twill_returnuic("dict_iterator_copy_key", 0, "item 8 0");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 8 0");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1 32");
    twill_returnoc("dict_iterator_get_value", i32, "item 1 32");
    at += snprintf(orig + at, 20, "\n    [U][0][][l][1]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(104, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 104);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_to_16_str)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[110];
    char orig[110];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *istr = 0;

    ubjs_prmtv_int8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_str(lib, 0, "", &istr);

    at += snprintf(orig + at, 10, "[#][U][5]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][i][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item str 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item str 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item str 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item str 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item str 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item str 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item str 1");
    twill_returnoc("dict_iterator_get_value", istr, "item str 1");
    at += snprintf(orig + at, 25, "\n    [U][0][][S][U][0][]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(109, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 109);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&istr);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_to_16_64s)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[105];
    char orig[105];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int64(lib, 1, &i64);

    at += snprintf(orig + at, 10, "[#][U][5]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][U][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 64 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 64 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 64 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 64 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 64 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 64 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 64 1");
    twill_returnoc("dict_iterator_get_value", i64, "item 64 1");
    at += snprintf(orig + at, 20, "\n    [U][0][][L][1]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(104, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 104);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_16_to_32_too_little)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[162];
    char orig[162];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);

    at += snprintf(orig + at, 10, "[#][U][8]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][U][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][l][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(161, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 161);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_16_to_32_64s)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[201];
    char orig[201];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_int64(lib, 1, &i64);

    at += snprintf(orig + at, 11, "[#][U][10]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][U][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 2 64");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2 64");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 2 64");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 2 64");
    twill_returnuic("dict_iterator_copy_key", 0, "item 2 64");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 2 64");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2 64");
    twill_returnoc("dict_iterator_get_value", i64, "item 2 64");
    at += snprintf(orig + at, 20, "\n    [U][0][][L][1]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][l][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(200, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 200);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_16_to_32_str)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[206];
    char orig[206];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *istr = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_str(lib, 0, "", &istr);

    at += snprintf(orig + at, 11, "[#][U][10]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][U][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 2 str");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item item 2 str");
    twill_returnuic("dict_iterator_get_key_length", 0, "item item 2 str");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item item 2 str");
    twill_returnuic("dict_iterator_copy_key", 0, "item item 2 str");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item item 2 str");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2 str");
    twill_returnoc("dict_iterator_get_value", istr, "item 2 str");
    at += snprintf(orig + at, 25, "\n    [U][0][][S][U][0][]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][l][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(205, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 205);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&istr);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_16_32_to_64_too_little)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[391];
    char orig[391];
    unsigned int i;
    unsigned int at = 0;
    ubjs_prmtv *i8 = 0;
    ubjs_prmtv *i16 = 0;
    ubjs_prmtv *i32 = 0;
    ubjs_prmtv *i64 = 0;

    ubjs_prmtv_uint8(lib, 1, &i8);
    ubjs_prmtv_int16(lib, 1, &i16);
    ubjs_prmtv_int32(lib, 1, &i32);
    ubjs_prmtv_int64(lib, 1, &i64);

    at += snprintf(orig + at, 11, "[#][U][20]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][U][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 2");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 32 2");
    twill_returnoc("dict_iterator_get_value", i32, "item 32 2");
    at += snprintf(orig + at, 20, "\n    [U][0][][l][1]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][L][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(390, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 390);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
}

Test(prmtv_object_printer_upgrade, no_upgrade_8_16_32_to_64_str)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[434];
    char orig[434];
    unsigned int i;
    unsigned int at = 0;
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

    at += snprintf(orig + at, 11, "[#][U][22]");

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
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
    at += snprintf(orig + at, 20, "\n    [U][0][][U][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 16 1");
    twill_returnuic("dict_iterator_copy_key", 0, "item 16 1");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 16 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 16 1");
    twill_returnoc("dict_iterator_get_value", i16, "item 16 1");
    at += snprintf(orig + at, 20, "\n    [U][0][][I][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_get_key_length", 0, "item 32 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 32 2");
    twill_returnuic("dict_iterator_copy_key", 0, "item 32 2");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item 32 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 32 2");
    twill_returnoc("dict_iterator_get_value", i32, "item 32 2");
    at += snprintf(orig + at, 20, "\n    [U][0][][l][1]");

    twill_returnuic("dict_iterator_next", UR_OK, "item str 3");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item str 3");
    twill_returnuic("dict_iterator_get_key_length", 0, "item str 3");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item str 3");
    twill_returnuic("dict_iterator_copy_key", 0, "item str 3");
    twill_returnoc("dict_iterator_copy_key", strdup(""), "item str 3");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item str 3");
    twill_returnoc("dict_iterator_get_value", istr, "item str 3");
    at += snprintf(orig + at, 25, "\n    [U][0][][S][U][0][]");

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
        at += snprintf(orig + at, 20, "\n    [U][0][][L][1]");
    }

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(433, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, orig, 433);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_marker.printer_free_f)(&printer));
    (ubjs_prmtv_object_marker.free_f)(&(glue.prmtv));

    ubjs_prmtv_free(&i8);
    ubjs_prmtv_free(&i16);
    ubjs_prmtv_free(&i32);
    ubjs_prmtv_free(&i64);
    ubjs_prmtv_free(&istr);
}
