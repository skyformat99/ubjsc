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
 * copies or su`bstantial portions of the Software.
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

TestSuite(prmtv_array, .init = before, .fini = after);
Test(prmtv_array, marker)
{
    ubjs_prmtv_marker *n = &ubjs_prmtv_array_marker;
    cr_expect_eq(91, n->abyte);
    cr_expect_neq(0, n->free_f);
    cr_expect_eq(0, n->new_from_int64_f);
    cr_expect_eq(0, n->get_value_int64_f);
    cr_expect_neq(0, n->debug_string_get_length_f);
    cr_expect_neq(0, n->debug_string_copy_f);
    cr_expect_neq(0, n->parser_processor_new_f);
    cr_expect_neq(0, n->parser_processor_free_f);
    cr_expect_neq(0, n->parser_processor_got_child_f);
    cr_expect_neq(0, n->parser_processor_got_marker_f);
    cr_expect_neq(0, n->parser_processor_got_control_f);
    cr_expect_eq(0, n->parser_processor_read_byte_f);
    cr_expect_neq(0, n->writer_new_f);
    cr_expect_neq(0, n->writer_free_f);
    cr_expect_neq(0, n->writer_get_length_f);
    cr_expect_neq(0, n->writer_do_f);
    cr_expect_neq(0, n->printer_new_f);
    cr_expect_neq(0, n->printer_free_f);
    cr_expect_neq(0, n->printer_get_length_f);
    cr_expect_neq(0, n->printer_do_f);
}

Test(prmtv_array, object)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv_marker *marker = 0;
    unsigned int len = -1;
    ubjs_prmtv *child = 0;
    ubjs_prmtv wrong_prmtv = {0, 0};
    char tmp[20];

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array(lib, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_with_length(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_with_length(lib, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array(0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(0, &len));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(0, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(0, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(0, 0, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(0, child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(0, child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(0, 0, child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_first(0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_last(0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_at(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(&wrong_prmtv, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(&wrong_prmtv, &len));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(&wrong_prmtv, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(&wrong_prmtv, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(&wrong_prmtv, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(&wrong_prmtv, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(&wrong_prmtv, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(&wrong_prmtv, 0, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(&wrong_prmtv, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(&wrong_prmtv, child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(&wrong_prmtv, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(&wrong_prmtv, child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(&wrong_prmtv, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(&wrong_prmtv, 0, child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_first(&wrong_prmtv));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_last(&wrong_prmtv));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_at(&wrong_prmtv, 0));

    cr_expect_eq(UR_OK, ubjs_prmtv_array(lib, &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_get_marker(object, &marker));
    cr_expect_eq(&ubjs_prmtv_array_marker, marker);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, 0));

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.debug_string_get_length_f)(0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.debug_string_get_length_f)(object, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.debug_string_get_length_f)(0, &len));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.debug_string_copy_f)(0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.debug_string_copy_f)(object, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.debug_string_copy_f)(0, tmp));

    twill_returnui("array_get_length", UR_OK);
    twill_returnui("array_get_length", 0);
    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.debug_string_get_length_f)(object, &len));
    cr_expect_eq(len, 8);

    twill_returnui("array_get_length", UR_OK);
    twill_returnui("array_get_length", 0);
    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.debug_string_copy_f)(object, tmp));
    cr_expect_arr_eq("array(0)", tmp, 8);

    twill_returnui("array_get_length", UR_OK);
    twill_returnui("array_get_length", 2);
    twill_returnuic("array_iterator_next", UR_OK, "item 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 1");
    twill_returnoc("array_iterator_get", ubjs_prmtv_true(), "item 1");
    twill_returnuic("array_iterator_next", UR_OK, "item 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 2");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 2");
    twill_returnuic("array_iterator_next", UR_ERROR, "eof");
    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.debug_string_get_length_f)(object, &len));
    cr_expect_eq(len, 20);

    twill_returnui("array_get_length", UR_OK);
    twill_returnui("array_get_length", 2);
    twill_returnuic("array_iterator_next", UR_OK, "item 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 1");
    twill_returnoc("array_iterator_get", ubjs_prmtv_true(), "item 1");
    twill_returnuic("array_iterator_next", UR_OK, "item 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 2");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 2");
    twill_returnuic("array_iterator_next", UR_ERROR, "eof");
    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.debug_string_copy_f)(object, tmp));
    cr_expect_arr_eq("array(2, true, null)", tmp, 20);

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.free_f)(0));
    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.free_f)(&object));
    cr_expect_eq(0, object);
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.free_f)(&object));

    twill_returnui("array_builder_set_length", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_with_length(lib, 0, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.free_f)(&object));
    cr_expect_eq(0, object);
}

Test(prmtv_array, length)
{
    ubjs_prmtv *object = 0;
    unsigned int len = -1;

    cr_expect_eq(UR_OK, ubjs_prmtv_array(lib, &object));

    twill_returnui("array_get_length", UR_OK);
    twill_returnui("array_get_length", 0);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_get_length(object, &len));
    cr_expect_eq(0, len);

    twill_returnui("array_get_length", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_length(object, &len));

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.free_f)(&object));
}

Test(prmtv_array, adds)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *child = ubjs_prmtv_null();

    cr_expect_eq(UR_OK, ubjs_prmtv_array(lib, &object));

    twill_returnui("array_add_first", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_add_first(object, child));
    twill_returnui("array_add_last", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_add_last(object, child));
    twill_returnui("array_add_at", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_add_at(object, 0, child));

    twill_returnui("array_add_first", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_first(object, child));
    twill_returnui("array_add_last", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_last(object, child));
    twill_returnui("array_add_at", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_add_at(object, 0, child));

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.free_f)(&object));
}

Test(prmtv_array, deletes)
{
    ubjs_prmtv *object = 0;

    cr_expect_eq(UR_OK, ubjs_prmtv_array(lib, &object));

    twill_returnui("array_delete_first", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_delete_first(object));
    twill_returnui("array_delete_last", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_delete_last(object));
    twill_returnui("array_delete_at", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_delete_at(object, 0));

    twill_returnui("array_delete_first", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_first(object));
    twill_returnui("array_delete_last", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_last(object));
    twill_returnui("array_delete_at", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_delete_at(object, 0));

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.free_f)(&object));
}

Test(prmtv_array, gets)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *child = ubjs_prmtv_null();
    ubjs_prmtv *got = 0;

    cr_expect_eq(UR_OK, ubjs_prmtv_array(lib, &object));

    got = 0;
    twill_returnui("array_get_first", UR_OK);
    twill_returno("array_get_first", child);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_get_first(object, &got));
    cr_expect_eq(child, got);

    got = 0;
    twill_returnui("array_get_last", UR_OK);
    twill_returno("array_get_last", child);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_get_last(object, &got));
    cr_expect_eq(child, got);

    got = 0;
    twill_returnui("array_get_at", UR_OK);
    twill_returno("array_get_at", child);
    cr_expect_eq(UR_OK, ubjs_prmtv_array_get_at(object, 0, &got));
    cr_expect_eq(child, got);

    got = 0;
    twill_returnui("array_get_first", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_first(object, &got));
    cr_expect_eq(0, got);

    got = 0;
    twill_returnui("array_get_last", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_last(object, &got));
    cr_expect_eq(0, got);

    got = 0;
    twill_returnui("array_get_at", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_get_at(object, 0, &got));
    cr_expect_eq(0, got);


    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.free_f)(&object));
}

Test(prmtv_array, iterator)
{
    ubjs_array_iterator *it = 0;
    ubjs_prmtv *object = 0;
    ubjs_prmtv *child = ubjs_prmtv_null();
    ubjs_prmtv *got = 0;
    ubjs_prmtv wrong_prmtv = {0, 0};

    cr_expect_eq(UR_OK, ubjs_prmtv_array(lib, &object));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_iterate(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_iterate(0, &it));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_iterate(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_next(0));
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_free(0));
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_get(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_get(0, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_array_iterate(&wrong_prmtv, &it));
    cr_expect_eq(0, it);

    cr_expect_eq(UR_OK, ubjs_prmtv_array_iterate(object, &it));
    cr_expect_neq(0, it);

    cr_expect_eq(UR_ERROR, ubjs_array_iterator_get(it, 0));

    twill_returnui("array_iterator_next", UR_OK);
    cr_expect_eq(UR_OK, ubjs_array_iterator_next(it));

    twill_returnui("array_iterator_next", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_next(it));

    got = 0;
    twill_returnui("array_iterator_get", UR_OK);
    twill_returno("array_iterator_get", child);
    cr_expect_eq(UR_OK, ubjs_array_iterator_get(it, &got));
    cr_expect_eq(child, got);

    got = 0;
    twill_returnui("array_iterator_get", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_get(it, &got));
    cr_expect_eq(0, got);

    twill_returnui("array_iterator_delete", UR_OK);
    cr_expect_eq(UR_OK, ubjs_array_iterator_delete(it));

    twill_returnui("array_iterator_delete", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_delete(it));

    cr_expect_eq(UR_OK, ubjs_array_iterator_free(&it));
    cr_expect_eq(0, it);
    cr_expect_eq(UR_ERROR, ubjs_array_iterator_free(&it));

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.free_f)(&object));
}

static ubjs_bool parser_glue_return_control_called = UFALSE;
static ubjs_bool parser_glue_want_marker_called = UFALSE;
static ubjs_bool parser_glue_want_child_called = UFALSE;
static ubjs_bool parser_glue_error_called = UFALSE;
static ubjs_bool parser_glue_debug_called = UFALSE;

static void parser_glue_return_control(ubjs_prmtv_marker_parser_glue *glue,
    void *present)
{
    ubjs_prmtv *prmtv = (ubjs_prmtv *)present;

    parser_glue_return_control_called = UTRUE;
    cr_expect_eq(prmtv->marker, &ubjs_prmtv_array_marker);

    ubjs_prmtv_free(&prmtv);
}

static void parser_glue_return_control_unexpected(ubjs_prmtv_marker_parser_glue *glue,
    void *present)
{
    parser_glue_return_control_called = UTRUE;
    cr_expect_fail("%s", "Unexpected return control");
}

static void parser_glue_want_marker_unexpected(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_glue_array *markers)
{
    parser_glue_want_marker_called = UTRUE;
    cr_expect_fail("%s", "Unexpected want number");
}

static void parser_glue_want_marker_type_count_child_end(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_glue_array *markers)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_marker_child_end(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_glue_array *markers)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_marker_int64s(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_glue_array *markers)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_marker_child(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_glue_array *markers)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_marker_count(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_glue_array *markers)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_child_unexpected(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_prmtv_marker *marker)
{
    parser_glue_want_marker_called = UTRUE;
    cr_expect_fail("Unexpected want child: %p", marker);
}

static void parser_glue_want_child_uint8(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_prmtv_marker *marker)
{
    parser_glue_want_child_called = UTRUE;
    cr_expect_eq(&ubjs_prmtv_uint8_marker, marker);
}


static void parser_glue_want_child_int8(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_prmtv_marker *marker)
{
    parser_glue_want_child_called = UTRUE;
    cr_expect_eq(&ubjs_prmtv_int8_marker, marker);
}

static void parser_glue_want_child_null(ubjs_prmtv_marker_parser_glue *glue,
    ubjs_prmtv_marker *marker)
{
    parser_glue_want_child_called = UTRUE;
    cr_expect_eq(&ubjs_prmtv_null_marker, marker);
}

static void parser_glue_error_unexpected(ubjs_prmtv_marker_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_fail("Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_recursion_level(ubjs_prmtv_marker_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(29, len);
    cr_expect_arr_eq("Reached recursion level limit", msg, 29, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_length_limit(ubjs_prmtv_marker_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(33, len);
    cr_expect_arr_eq("Reached limit of container length", msg, 33, "Unexpected error: %.*s",
    len, msg);
}

static void parser_glue_error_invalid_length(ubjs_prmtv_marker_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(14, len);
    cr_expect_arr_eq("Invalid length", msg, 9, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_unexpected_got_control(ubjs_prmtv_marker_parser_glue *glue,
    unsigned int len, char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(22, len);
    cr_expect_arr_eq("Unexpected got control", msg, 22, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_unexpected_got_child(ubjs_prmtv_marker_parser_glue *glue,
    unsigned int len, char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(22, len);
    cr_expect_arr_eq("Unexpected got present", msg, 22, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_unexpected_got_marker(ubjs_prmtv_marker_parser_glue *glue,
    unsigned int len, char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(21, len);
    cr_expect_arr_eq("Unexpected got marker", msg, 21, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_debug_unexpected(ubjs_prmtv_marker_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_debug_called = UTRUE;
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

static void parser_glue_reset(ubjs_prmtv_marker_parser_glue *glue)
{
    parser_glue_return_control_called = UFALSE;
    parser_glue_want_marker_called = UFALSE;
    parser_glue_want_child_called = UFALSE;
    parser_glue_error_called = UFALSE;
    parser_glue_debug_called = UFALSE;

    glue->return_control_f = parser_glue_return_control_unexpected;
    glue->want_marker_f = parser_glue_want_marker_unexpected;
    glue->want_child_f = parser_glue_want_child_unexpected;
    glue->error_f = parser_glue_error_unexpected;
    glue->debug_f = parser_glue_debug_unexpected;
}

Test(prmtv_array, parser_basic)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_new_f)(0, 0,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, 0,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_new_f)(0, &glue,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));
    cr_expect_neq(0, parser_processor);
    cr_expect_eq(&ubjs_prmtv_array_marker, parser_processor->marker);
    cr_expect_eq(lib, parser_processor->lib);
    cr_expect_str_eq("array", parser_processor->name);
    cr_expect_eq(&glue, parser_processor->glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

static void parser_broken(
    ubjs_prmtv_marker_parser_processor *parser_processor,
    ubjs_prmtv_marker_parser_glue *glue)
{
    parser_glue_reset(glue);
    glue->error_f = parser_glue_error_unexpected_got_control;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_glue_reset(glue);
    glue->error_f = parser_glue_error_unexpected_got_child;
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_glue_reset(glue);
    glue->error_f = parser_glue_error_unexpected_got_marker;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_error_called);
}

Test(prmtv_array, parser_empty)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_end_marker);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_recursion_limit_hit_on_umarkerd)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.recursion_level = 1;
    glue.limit_recursion_level = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_recursion_level;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_recursion_limit_hit_on_count_when_non_empty)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.recursion_level = 1;
    glue.limit_recursion_level = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_recursion_level;
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_length_limit_hit_on_count)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.limit_container_length = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_length_limit;
    ubjs_prmtv_uint8(lib, 2, &child);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_length_limit_not_hit_on_count)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.limit_container_length = 2;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    ubjs_prmtv_uint8(lib, 1, &child);
    twill_returnui("array_builder_set_length", UR_OK);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_recursion_limit_not_hit_on_count_when_non_empty)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.recursion_level = 1;
    glue.limit_recursion_level = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    ubjs_prmtv_uint8(lib, 0, &child);
    twill_returnui("array_builder_set_length", UR_OK);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_2_umarkerd)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("array_add_last", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("array_add_last", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_end_marker);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_limit_length_hit_upon_child)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.limit_container_length = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("array_add_last", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_length_limit;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_empty_count)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    ubjs_prmtv_uint8(lib, 0, &child);
    twill_returnui("array_builder_set_length", UR_OK);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_negative_count)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_int8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_int8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_invalid_length;
    ubjs_prmtv_int8(lib, -1, &child);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_2_count)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    ubjs_prmtv_uint8(lib, 2, &child);
    twill_returnui("array_builder_set_length", UR_OK);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("array_add_last", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor,
        ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("array_add_last", UR_OK);
    glue.return_control_f = parser_glue_return_control;
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor,
        ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_empty_type_count)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_type_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_count;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    ubjs_prmtv_uint8(lib, 0, &child);
    twill_returnui("array_builder_set_length", UR_OK);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_array, parser_2_type_count)
{
    ubjs_prmtv_marker_parser_glue glue;
    ubjs_prmtv_marker_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_child_end;
    (ubjs_prmtv_array_marker.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_type_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_count;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_array_count_marker);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_array_marker.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_marker);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    ubjs_prmtv_uint8(lib, 2, &child);
    twill_returnui("array_builder_set_length", UR_OK);
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("array_add_last", UR_OK);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor,
        ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("array_add_last", UR_OK);
    glue.return_control_f = parser_glue_return_control;
    (ubjs_prmtv_array_marker.parser_processor_got_child_f)(parser_processor,
        ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

static void writer_glue_debug_unexpected(ubjs_prmtv_marker_writer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_array, writer_0)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[1];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_new_f)(0, 0, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_new_f)(lib, 0, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_new_f)(0, &glue, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.writer_free_f)(&writer));

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 0, "get length");
    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));
    cr_expect_neq(0, writer);
    cr_expect_eq(lib, writer->lib);
    cr_expect_eq(&ubjs_prmtv_array_marker, writer->marker);
    cr_expect_str_eq("array", writer->name);
    cr_expect_eq(&glue, writer->glue);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(1, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 93);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    cr_expect_eq(0, writer);
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));
}

Test(prmtv_array, writer_2)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[3];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 2, "get length");
    twill_returnuic("array_iterator_next", UR_OK, "item 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 1");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 1");
    twill_returnuic("array_iterator_next", UR_OK, "item 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 2");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 2");
    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(3, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 90);
    cr_expect_eq(data[1], 90);
    cr_expect_eq(data[2], 93);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));
}

Test(prmtv_array, writer_3_count)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[6];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 3, "get length");
    twill_returnuic("array_iterator_next", UR_OK, "item 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 1");
    twill_returnoc("array_iterator_get", ubjs_prmtv_true(), "item 1");
    twill_returnuic("array_iterator_next", UR_OK, "item 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 2");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 2");
    twill_returnuic("array_iterator_next", UR_OK, "item 3");
    twill_returnuic("array_iterator_get", UR_OK, "item 3");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 3");
    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(6, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 35);
    cr_expect_eq(data[1], 85);
    cr_expect_eq(data[2], 3);
    cr_expect_eq(data[3], 84);
    cr_expect_eq(data[4], 90);
    cr_expect_eq(data[5], 90);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));
}

Test(prmtv_array, writer_3_count_type)
{
    ubjs_prmtv_marker_writer_glue glue;
    ubjs_prmtv_marker_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[5];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 3, "get length");
    twill_returnuic("array_iterator_next", UR_OK, "item 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 1");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 1");
    twill_returnuic("array_iterator_next", UR_OK, "item 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 2");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 2");
    twill_returnuic("array_iterator_next", UR_OK, "item 3");
    twill_returnuic("array_iterator_get", UR_OK, "item 3");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 3");
    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_get_length_f)(writer, &len);
    cr_expect_eq(5, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 36);
    cr_expect_eq(data[1], 90);
    cr_expect_eq(data[2], 35);
    cr_expect_eq(data[3], 85);
    cr_expect_eq(data[4], 3);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.writer_free_f)(&writer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));
}

Test(prmtv_array, writer_upgrade_u8_to_16)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_upgrade_u8_16_to_32)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_upgrade_8_16_to_32)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_no_upgrade_8_to_16_too_little)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_no_upgrade_8_to_16_32s)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_no_upgrade_8_to_16_str)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_no_upgrade_8_to_16_64s)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_no_upgrade_8_16_to_32_too_little)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_no_upgrade_8_16_to_32_64s)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

Test(prmtv_array, writer_no_upgrade_8_16_to_32_str)
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

    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

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

static void printer_glue_debug_unexpected(ubjs_prmtv_marker_printer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_array, printer_0)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[3];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_new_f)(0, 0, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_new_f)(lib, 0, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_new_f)(0, &glue, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_array_marker.printer_free_f)(&printer));

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 0, "get length");
    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.printer_new_f)(lib, &glue, &printer));
    cr_expect_neq(0, printer);
    cr_expect_eq(lib, printer->lib);
    cr_expect_eq(&ubjs_prmtv_array_marker, printer->marker);
    cr_expect_str_eq("array", printer->name);
    cr_expect_eq(&glue, printer->glue);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(3, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "[]]", 3);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.printer_free_f)(&printer));
    cr_expect_eq(0, printer);
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));
}

Test(prmtv_array, printer_2)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[20];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 2, "get length");
    twill_returnuic("array_iterator_next", UR_OK, "item 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 1");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 1");
    twill_returnuic("array_iterator_next", UR_OK, "item 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 2");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 2");
    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(20, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "\n    [Z]\n    [Z]\n[]]", 20);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.printer_free_f)(&printer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));
}

Test(prmtv_array, printer_3_count)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[33];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 3, "get length");
    twill_returnuic("array_iterator_next", UR_OK, "item 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 1");
    twill_returnoc("array_iterator_get", ubjs_prmtv_true(), "item 1");
    twill_returnuic("array_iterator_next", UR_OK, "item 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 2");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 2");
    twill_returnuic("array_iterator_next", UR_OK, "item 3");
    twill_returnuic("array_iterator_get", UR_OK, "item 3");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 3");
    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(33, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "[#][U][3]\n    [T]\n    [Z]\n    [Z]", 33);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.printer_free_f)(&printer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));
}

Test(prmtv_array, printer_3_count_type)
{
    ubjs_prmtv_marker_printer_glue glue;
    ubjs_prmtv_marker_printer *printer = 0;
    unsigned int len = -1;
    char data[15];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_marker_printer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_array(lib, &(glue.prmtv));
    twill_returnuic("array_get_length", UR_OK, "get length");
    twill_returnuic("array_get_length", 3, "get length");
    twill_returnuic("array_iterator_next", UR_OK, "item 1");
    twill_returnuic("array_iterator_get", UR_OK, "item 1");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 1");
    twill_returnuic("array_iterator_next", UR_OK, "item 2");
    twill_returnuic("array_iterator_get", UR_OK, "item 2");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 2");
    twill_returnuic("array_iterator_next", UR_OK, "item 3");
    twill_returnuic("array_iterator_get", UR_OK, "item 3");
    twill_returnoc("array_iterator_get", ubjs_prmtv_null(), "item 3");
    twill_returnuic("array_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.printer_get_length_f)(printer, &len);
    cr_expect_eq(15, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_array_marker.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "[$][Z][#][U][3]", 15);

    cr_expect_eq(UR_OK, (ubjs_prmtv_array_marker.printer_free_f)(&printer));
    (ubjs_prmtv_array_marker.free_f)(&(glue.prmtv));
}
