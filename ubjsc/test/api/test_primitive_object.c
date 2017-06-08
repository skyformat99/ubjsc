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

TestSuite(prmtv_object, .init = before, .fini = after);
Test(prmtv_object, ntype)
{
    ubjs_prmtv_ntype *n = &ubjs_prmtv_object_ntype;
    cr_expect_eq(123, n->marker);
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
    cr_expect_neq(0, n->parser_processor_read_byte_f);
    cr_expect_neq(0, n->writer_new_f);
    cr_expect_neq(0, n->writer_free_f);
    cr_expect_neq(0, n->writer_get_length_f);
    cr_expect_neq(0, n->writer_do_f);
    cr_expect_neq(0, n->printer_new_f);
    cr_expect_neq(0, n->printer_free_f);
    cr_expect_neq(0, n->printer_get_length_f);
    cr_expect_neq(0, n->printer_do_f);
}

Test(prmtv_object, object)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv_ntype *ntype = 0;
    unsigned int len = -1;
    ubjs_prmtv *child = 0;
    ubjs_prmtv wrong_prmtv = {0, 0};
    char tmp[25];

    cr_expect_eq(UR_ERROR, ubjs_prmtv_object(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object(lib, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_with_length(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_with_length(lib, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object(0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(0, &len));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(0, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(0, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(0, 0, 0, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(0, 0, "", &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(0, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(0, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(0, 0, 0, child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(0, 0, "", child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(0, 0, ""));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(&wrong_prmtv, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(&wrong_prmtv, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(&wrong_prmtv, 0, 0, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(&wrong_prmtv, 0, "", &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(&wrong_prmtv, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(&wrong_prmtv, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(&wrong_prmtv, 0, 0, child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(&wrong_prmtv, 0, "", child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(&wrong_prmtv, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(&wrong_prmtv, 0, ""));

    cr_expect_eq(UR_OK, ubjs_prmtv_object(lib, &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_get_ntype(object, &ntype));
    cr_expect_eq(&ubjs_prmtv_object_ntype, ntype);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(object, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(object, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(object, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(object, 0, "", 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(object, 0, 0));

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.debug_string_get_length_f)(0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.debug_string_get_length_f)(object, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.debug_string_get_length_f)(0, &len));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.debug_string_copy_f)(0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.debug_string_copy_f)(object, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.debug_string_copy_f)(0, tmp));

    len = -1;
    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 0);
    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.debug_string_get_length_f)(object, &len));
    cr_expect_eq(len, 9);

    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 0);
    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.debug_string_copy_f)(object, tmp));
    cr_expect_arr_eq("object(0)", tmp, 9);

    len = -1;
    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 2);
    twill_returnuic("dict_iterator_next", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_true(), "item 1");
    twill_returnuic("dict_iterator_next", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 2");
    twill_returnuic("dict_iterator_next", UR_ERROR, "eof");
    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.debug_string_get_length_f)(object, &len));
    cr_expect_eq(len, 25);

    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 2);
    twill_returnuic("dict_iterator_next", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 1");
    twill_returnuic("dict_iterator_copy_key", 1, "item 1");
    twill_returnoc("dict_iterator_copy_key", strdup("a"), "item 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_true(), "item 1");
    twill_returnuic("dict_iterator_next", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 2");
    twill_returnuic("dict_iterator_copy_key", 1, "item 2");
    twill_returnoc("dict_iterator_copy_key", strdup("b"), "item 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 2");
    twill_returnuic("dict_iterator_next", UR_ERROR, "eof");
    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.debug_string_copy_f)(object, tmp));
    cr_expect_arr_eq("object(2, a=true, b=null)", tmp, 25);

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.free_f)(0));
    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.free_f)(&object));
    cr_expect_eq(0, object);
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.free_f)(&object));

    twill_returnui("dict_builder_set_length", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_object_with_length(lib, 0, &object));
    cr_expect_neq(0, object);
    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.free_f)(&object));
    cr_expect_eq(0, object);
}

Test(prmtv_object, length)
{
    ubjs_prmtv *object = 0;
    unsigned int len = -1;

    cr_expect_eq(UR_OK, ubjs_prmtv_object(lib, &object));

    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 0);
    cr_expect_eq(UR_OK, ubjs_prmtv_object_get_length(object, &len));
    cr_expect_eq(0, len);

    twill_returnui("dict_get_length", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get_length(object, &len));

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.free_f)(&object));
}

Test(prmtv_object, sets)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *child = ubjs_prmtv_null();

    cr_expect_eq(UR_OK, ubjs_prmtv_object(lib, &object));

    twill_returnui("dict_set", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_object_set(object, 1, "a", child));

    twill_returnui("dict_set", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_set(object, 1, "a", child));

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.free_f)(&object));
}

Test(prmtv_object, deletes)
{
    ubjs_prmtv *object = 0;

    cr_expect_eq(UR_OK, ubjs_prmtv_object(lib, &object));

    twill_returnui("dict_delete", UR_OK);
    cr_expect_eq(UR_OK, ubjs_prmtv_object_delete(object, 1, "a"));

    twill_returnui("dict_delete", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_delete(object, 1, "a"));

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.free_f)(&object));
}

Test(prmtv_object, gets)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv *child = ubjs_prmtv_null();
    ubjs_prmtv *got = 0;

    cr_expect_eq(UR_OK, ubjs_prmtv_object(lib, &object));

    got = 0;
    twill_returnui("dict_get", UR_OK);
    twill_returno("dict_get", child);
    cr_expect_eq(UR_OK, ubjs_prmtv_object_get(object, 1, "a", &got));
    cr_expect_eq(child, got);

    got = 0;
    twill_returnui("dict_get", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_get(object, 1, "a", &got));
    cr_expect_eq(0, got);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.free_f)(&object));
}

Test(prmtv_object, iterator)
{
    ubjs_object_iterator *it = 0;
    ubjs_prmtv *object = 0;
    ubjs_prmtv *child = ubjs_prmtv_null();
    ubjs_prmtv *got = 0;
    ubjs_prmtv wrong_prmtv = {0, 0};
    unsigned int klen = -1;
    char key[2];

    cr_expect_eq(UR_OK, ubjs_prmtv_object(lib, &object));

    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(0, &it));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(object, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_next(0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_free(0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_key_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_key_length(0, &klen));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_copy_key(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_copy_key(0, key));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_value(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_value(0, &child));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_object_iterate(&wrong_prmtv, &it));
    cr_expect_eq(0, it);

    cr_expect_eq(UR_OK, ubjs_prmtv_object_iterate(object, &it));
    cr_expect_neq(0, it);

    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_key_length(it, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_copy_key(it, 0));
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_value(it, 0));

    twill_returnui("dict_iterator_next", UR_OK);
    cr_expect_eq(UR_OK, ubjs_object_iterator_next(it));

    twill_returnui("dict_iterator_next", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_next(it));

    klen = -1;
    twill_returnui("dict_iterator_get_key_length", UR_OK);
    twill_returnui("dict_iterator_get_key_length", 1);
    cr_expect_eq(UR_OK, ubjs_object_iterator_get_key_length(it, &klen));
    cr_expect_eq(1, klen);

    klen = -1;
    twill_returnui("dict_iterator_get_key_length", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_key_length(it, &klen));
    cr_expect_eq(-1, klen);

    key[0] = 0;
    twill_returnui("dict_iterator_copy_key", UR_OK);
    twill_returnui("dict_iterator_copy_key", 1);
    twill_returno("dict_iterator_copy_key", strdup("a"));
    cr_expect_eq(UR_OK, ubjs_object_iterator_copy_key(it, key));
    cr_expect_arr_eq("a", key, 1);

    key[0] = 0;
    twill_returnui("dict_iterator_copy_key", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_copy_key(it, key));

    got = 0;
    twill_returnui("dict_iterator_get_value", UR_OK);
    twill_returno("dict_iterator_get_value", child);
    cr_expect_eq(UR_OK, ubjs_object_iterator_get_value(it, &got));
    cr_expect_eq(child, got);

    got = 0;
    twill_returnui("dict_iterator_get_value", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_get_value(it, &got));
    cr_expect_eq(0, got);

    twill_returnui("dict_iterator_delete", UR_OK);
    cr_expect_eq(UR_OK, ubjs_object_iterator_delete(it));

    twill_returnui("dict_iterator_delete", UR_ERROR);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_delete(it));

    cr_expect_eq(UR_OK, ubjs_object_iterator_free(&it));
    cr_expect_eq(0, it);
    cr_expect_eq(UR_ERROR, ubjs_object_iterator_free(&it));

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.free_f)(&object));
}

static ubjs_bool parser_glue_return_control_called = UFALSE;
static ubjs_bool parser_glue_want_marker_called = UFALSE;
static ubjs_bool parser_glue_want_child_called = UFALSE;
static ubjs_bool parser_glue_error_called = UFALSE;
static ubjs_bool parser_glue_debug_called = UFALSE;

static void parser_glue_return_control(ubjs_prmtv_ntype_parser_glue *glue,
    void *present)
{
    ubjs_prmtv *prmtv = (ubjs_prmtv *)present;

    parser_glue_return_control_called = UTRUE;
    cr_expect_eq(prmtv->ntype, &ubjs_prmtv_object_ntype);

    ubjs_prmtv_free(&prmtv);
}

static void parser_glue_return_control_unexpected(ubjs_prmtv_ntype_parser_glue *glue,
    void *present)
{
    parser_glue_return_control_called = UTRUE;
    cr_expect_fail("%s", "Unexpected return control");
}

static void parser_glue_want_marker_unexpected(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_glue_array *ntypes)
{
    parser_glue_want_marker_called = UTRUE;
    cr_expect_fail("%s", "Unexpected want number");
}

static void parser_glue_want_marker_type_count_int64s_end(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_glue_array *ntypes)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_marker_int64s_end(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_glue_array *ntypes)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_marker_int64s(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_glue_array *ntypes)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_marker_child(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_glue_array *ntypes)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_marker_count(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_glue_array *ntypes)
{
    parser_glue_want_marker_called = UTRUE;
}

static void parser_glue_want_child_unexpected(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_prmtv_ntype *marker)
{
    parser_glue_want_marker_called = UTRUE;
    cr_expect_fail("Unexpected want child: %p", marker);
}

static void parser_glue_want_child_uint8(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_prmtv_ntype *marker)
{
    parser_glue_want_child_called = UTRUE;
    cr_expect_eq(&ubjs_prmtv_uint8_ntype, marker);
}


static void parser_glue_want_child_int8(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_prmtv_ntype *marker)
{
    parser_glue_want_child_called = UTRUE;
    cr_expect_eq(&ubjs_prmtv_int8_ntype, marker);
}

static void parser_glue_want_child_null(ubjs_prmtv_ntype_parser_glue *glue,
    ubjs_prmtv_ntype *marker)
{
    parser_glue_want_child_called = UTRUE;
    cr_expect_eq(&ubjs_prmtv_null_ntype, marker);
}

static void parser_glue_error_unexpected(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_fail("Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_recursion_level(ubjs_prmtv_ntype_parser_glue *glue,
    unsigned int len, char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(29, len);
    cr_expect_arr_eq("Reached recursion level limit", msg, 29, "Unexpected error: %.*s",
        len, msg);
}

static void parser_glue_error_length_limit(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(33, len);
    cr_expect_arr_eq("Reached limit of container length", msg, 33, "Unexpected error: %.*s",
        len, msg);
}

static void parser_glue_error_invalid_length(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(14, len);
    cr_expect_arr_eq("Invalid length", msg, 9, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_unexpected_got_control(ubjs_prmtv_ntype_parser_glue *glue,
    unsigned int len, char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(22, len);
    cr_expect_arr_eq("Unexpected got control", msg, 22, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_unexpected_got_child(ubjs_prmtv_ntype_parser_glue *glue,
    unsigned int len, char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(22, len);
    cr_expect_arr_eq("Unexpected got present", msg, 22, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_unexpected_got_marker(ubjs_prmtv_ntype_parser_glue *glue,
    unsigned int len, char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(21, len);
    cr_expect_arr_eq("Unexpected got marker", msg, 21, "Unexpected error: %.*s", len, msg);
}

static void parser_glue_debug_unexpected(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_debug_called = UTRUE;
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

static void parser_glue_reset(ubjs_prmtv_ntype_parser_glue *glue)
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

Test(prmtv_object, parser_basic)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_new_f)(0, 0,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, 0,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_new_f)(0, &glue,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));
    cr_expect_neq(0, parser_processor);
    cr_expect_eq(&ubjs_prmtv_object_ntype, parser_processor->ntype);
    cr_expect_eq(lib, parser_processor->lib);
    cr_expect_str_eq("object", parser_processor->name);
    cr_expect_eq(&glue, parser_processor->glue);
    cr_expect_eq(0, parser_processor->userdata);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

static void parser_broken(
    ubjs_prmtv_ntype_parser_processor *parser_processor,
    ubjs_prmtv_ntype_parser_glue *glue)
{
    parser_glue_reset(glue);
    glue->error_f = parser_glue_error_unexpected_got_control;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_glue_reset(glue);
    glue->error_f = parser_glue_error_unexpected_got_child;
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_glue_reset(glue);
    glue->error_f = parser_glue_error_unexpected_got_marker;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_error_called);
}

Test(prmtv_object, parser_empty)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_end_ntype);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_recursion_limit_hit_on_untyped)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.recursion_level = 1;
    glue.limit_recursion_level = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_recursion_level;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_ntype);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_recursion_limit_hit_on_count_when_non_empty)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.recursion_level = 1;
    glue.limit_recursion_level = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_recursion_level;
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_length_limit_hit_on_count)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.limit_container_length = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_length_limit;
    ubjs_prmtv_uint8(lib, 2, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_length_limit_not_hit_on_count)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.limit_container_length = 2;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    ubjs_prmtv_uint8(lib, 1, &child);
    twill_returnui("dict_builder_set_length", UR_OK);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_recursion_limit_not_hit_on_count_when_non_empty)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.recursion_level = 1;
    glue.limit_recursion_level = 2;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    ubjs_prmtv_uint8(lib, 0, &child);
    twill_returnui("dict_builder_set_length", UR_OK);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_2_untyped)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* Item 1 */

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_read_byte_f)(parser_processor, 'a');
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("dict_set", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor,
        ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* Item 2 */

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_read_byte_f)(parser_processor, 'b');
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("dict_set", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* End */

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_end_ntype);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_limit_length_hit_upon_child)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.limit_container_length = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* Item 1 */

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_read_byte_f)(parser_processor, 'a');
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("dict_set", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor,
        ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* Item 2 */

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_length_limit;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_empty_count)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    ubjs_prmtv_uint8(lib, 0, &child);
    twill_returnui("dict_builder_set_length", UR_OK);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_negative_count)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_int8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_int8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.error_f = parser_glue_error_invalid_length;
    ubjs_prmtv_int8(lib, -1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_2_count)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    ubjs_prmtv_uint8(lib, 2, &child);
    twill_returnui("dict_builder_set_length", UR_OK);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* Item 1 */

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_read_byte_f)(parser_processor, 'a');
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("dict_set", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* Item 2 */

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_read_byte_f)(parser_processor, 'b');
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("dict_set", UR_OK);
    glue.return_control_f = parser_glue_return_control;
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_empty_type_count)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_type_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_count;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.return_control_f = parser_glue_return_control;
    ubjs_prmtv_uint8(lib, 0, &child);
    twill_returnui("dict_builder_set_length", UR_OK);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_object, parser_2_type_count)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *child = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_type_count_int64s_end;
    (ubjs_prmtv_object_ntype.parser_processor_got_control_f)(parser_processor);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_type_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_count;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_null_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_object_count_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    glue.want_marker_f = parser_glue_want_marker_int64s;
    ubjs_prmtv_uint8(lib, 2, &child);
    twill_returnui("dict_builder_set_length", UR_OK);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* Item 1 */

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_object_ntype.parser_processor_read_byte_f)(parser_processor, 'a');
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("dict_set", UR_OK);
    glue.want_marker_f = parser_glue_want_marker_child;
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_want_marker_called);

    /* Item 2 */

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_uint8;
    (ubjs_prmtv_object_ntype.parser_processor_got_marker_f)(parser_processor,
        &ubjs_prmtv_uint8_ntype);
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    ubjs_prmtv_uint8(lib, 1, &child);
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, child);

    parser_glue_reset(&glue);
    glue.want_child_f = parser_glue_want_child_null;
    (ubjs_prmtv_object_ntype.parser_processor_read_byte_f)(parser_processor, 'b');
    cr_expect_eq(UTRUE, parser_glue_want_child_called);

    parser_glue_reset(&glue);
    twill_returnui("dict_set", UR_OK);
    glue.return_control_f = parser_glue_return_control;
    (ubjs_prmtv_object_ntype.parser_processor_got_child_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    parser_broken(parser_processor, &glue);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

static void writer_glue_debug_unexpected(ubjs_prmtv_ntype_writer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_object, writer_0)
{
    ubjs_prmtv_ntype_writer_glue glue;
    ubjs_prmtv_ntype_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[1];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_new_f)(0, 0, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_new_f)(lib, 0, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_new_f)(0, &glue, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.writer_free_f)(&writer));

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 0, "get length");
    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.writer_new_f)(lib, &glue, &writer));
    cr_expect_neq(0, writer);
    cr_expect_eq(lib, writer->lib);
    cr_expect_eq(&ubjs_prmtv_object_ntype, writer->ntype);
    cr_expect_str_eq("object", writer->name);
    cr_expect_eq(&glue, writer->glue);
    cr_expect_eq(0, writer->userdata);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.writer_get_length_f)(writer, &len);
    cr_expect_eq(1, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 125);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.writer_free_f)(&writer));
    cr_expect_eq(0, writer);
    (ubjs_prmtv_object_ntype.free_f)(&(glue.prmtv));
}

Test(prmtv_object, writer_2)
{
    ubjs_prmtv_ntype_writer_glue glue;
    ubjs_prmtv_ntype_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[9];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 2);
    twill_returnuic("dict_iterator_next", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 1");
    twill_returnuic("dict_iterator_copy_key", 1, "item 1");
    twill_returnoc("dict_iterator_copy_key", strdup("a"), "item 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_true(), "item 1");
    twill_returnuic("dict_iterator_next", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 2");
    twill_returnuic("dict_iterator_copy_key", 1, "item 2");
    twill_returnoc("dict_iterator_copy_key", strdup("b"), "item 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 2");
    twill_returnuic("dict_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.writer_get_length_f)(writer, &len);
    cr_expect_eq(9, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 85);
    cr_expect_eq(data[1], 1);
    cr_expect_eq(data[2], 'a');
    cr_expect_eq(data[3], 84);
    cr_expect_eq(data[4], 85);
    cr_expect_eq(data[5], 1);
    cr_expect_eq(data[6], 'b');
    cr_expect_eq(data[7], 90);
    cr_expect_eq(data[8], 125);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.writer_free_f)(&writer));
    (ubjs_prmtv_object_ntype.free_f)(&(glue.prmtv));
}

Test(prmtv_object, writer_3_count)
{
    ubjs_prmtv_ntype_writer_glue glue;
    ubjs_prmtv_ntype_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[15];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 3);
    twill_returnuic("dict_iterator_next", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 1");
    twill_returnuic("dict_iterator_copy_key", 1, "item 1");
    twill_returnoc("dict_iterator_copy_key", strdup("a"), "item 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_true(), "item 1");
    twill_returnuic("dict_iterator_next", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 2");
    twill_returnuic("dict_iterator_copy_key", 1, "item 2");
    twill_returnoc("dict_iterator_copy_key", strdup("b"), "item 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 2");
    twill_returnuic("dict_iterator_next", UR_OK, "item 3");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 3");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 3");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 3");
    twill_returnuic("dict_iterator_copy_key", 1, "item 3");
    twill_returnoc("dict_iterator_copy_key", strdup("c"), "item 3");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 3");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 3");
    twill_returnuic("dict_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.writer_get_length_f)(writer, &len);
    cr_expect_eq(15, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 35);
    cr_expect_eq(data[1], 85);
    cr_expect_eq(data[2], 3);
    cr_expect_eq(data[3], 85);
    cr_expect_eq(data[4], 1);
    cr_expect_eq(data[5], 'a');
    cr_expect_eq(data[6], 84);
    cr_expect_eq(data[7], 85);
    cr_expect_eq(data[8], 1);
    cr_expect_eq(data[9], 'b');
    cr_expect_eq(data[10], 90);
    cr_expect_eq(data[11], 85);
    cr_expect_eq(data[12], 1);
    cr_expect_eq(data[13], 'c');
    cr_expect_eq(data[14], 90);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.writer_free_f)(&writer));
    (ubjs_prmtv_object_ntype.free_f)(&(glue.prmtv));
}

Test(prmtv_object, writer_3_count_type)
{
    ubjs_prmtv_ntype_writer_glue glue;
    ubjs_prmtv_ntype_writer *writer = 0;
    unsigned int len = -1;
    uint8_t data[14];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 3);
    twill_returnuic("dict_iterator_next", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 1");
    twill_returnuic("dict_iterator_copy_key", 1, "item 1");
    twill_returnoc("dict_iterator_copy_key", strdup("a"), "item 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 1");
    twill_returnuic("dict_iterator_next", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 2");
    twill_returnuic("dict_iterator_copy_key", 1, "item 2");
    twill_returnoc("dict_iterator_copy_key", strdup("b"), "item 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 2");
    twill_returnuic("dict_iterator_next", UR_OK, "item 3");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 3");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 3");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 3");
    twill_returnuic("dict_iterator_copy_key", 1, "item 3");
    twill_returnoc("dict_iterator_copy_key", strdup("c"), "item 3");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 3");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 3");
    twill_returnuic("dict_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.writer_new_f)(lib, &glue, &writer));

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.writer_get_length_f)(writer, &len);
    cr_expect_eq(14, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 36);
    cr_expect_eq(data[1], 90);
    cr_expect_eq(data[2], 35);
    cr_expect_eq(data[3], 85);
    cr_expect_eq(data[4], 3);
    cr_expect_eq(data[5], 85);
    cr_expect_eq(data[6], 1);
    cr_expect_eq(data[7], 'a');
    cr_expect_eq(data[8], 85);
    cr_expect_eq(data[9], 1);
    cr_expect_eq(data[10], 'b');
    cr_expect_eq(data[11], 85);
    cr_expect_eq(data[12], 1);
    cr_expect_eq(data[13], 'c');

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.writer_free_f)(&writer));
    (ubjs_prmtv_object_ntype.free_f)(&(glue.prmtv));
}

///


static void printer_glue_debug_unexpected(ubjs_prmtv_ntype_printer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_object, printer_0)
{
    ubjs_prmtv_ntype_printer_glue glue;
    ubjs_prmtv_ntype_printer *printer = 0;
    unsigned int len = -1;
    char data[3];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_printer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_new_f)(0, 0, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_new_f)(lib, 0, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_new_f)(0, &glue, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_object_ntype.printer_free_f)(&printer));

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnuic("dict_get_length", UR_OK, "get length");
    twill_returnuic("dict_get_length", 0, "get length");
    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.printer_new_f)(lib, &glue, &printer));
    cr_expect_neq(0, printer);
    cr_expect_eq(lib, printer->lib);
    cr_expect_eq(&ubjs_prmtv_object_ntype, printer->ntype);
    cr_expect_str_eq("object", printer->name);
    cr_expect_eq(&glue, printer->glue);
    cr_expect_eq(0, printer->userdata);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.printer_get_length_f)(printer, &len);
    cr_expect_eq(3, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "[}]", 3);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.printer_free_f)(&printer));
    cr_expect_eq(0, printer);
    (ubjs_prmtv_object_ntype.free_f)(&(glue.prmtv));
}

Test(prmtv_object, printer_2)
{
    ubjs_prmtv_ntype_printer_glue glue;
    ubjs_prmtv_ntype_printer *printer = 0;
    unsigned int len = -1;
    char data[38];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_printer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 2);
    twill_returnuic("dict_iterator_next", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 1");
    twill_returnuic("dict_iterator_copy_key", 1, "item 1");
    twill_returnoc("dict_iterator_copy_key", strdup("a"), "item 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_true(), "item 1");
    twill_returnuic("dict_iterator_next", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 2");
    twill_returnuic("dict_iterator_copy_key", 1, "item 2");
    twill_returnoc("dict_iterator_copy_key", strdup("b"), "item 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 2");
    twill_returnuic("dict_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.printer_get_length_f)(printer, &len);
    cr_expect_eq(38, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "\n    [U][1][a][T]\n    [U][1][b][Z]\n[}]", 38);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.printer_free_f)(&printer));
    (ubjs_prmtv_object_ntype.free_f)(&(glue.prmtv));
}

Test(prmtv_object, printer_3_count)
{
    ubjs_prmtv_ntype_printer_glue glue;
    ubjs_prmtv_ntype_printer *printer = 0;
    unsigned int len = -1;
    char data[60];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_printer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 3);
    twill_returnuic("dict_iterator_next", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 1");
    twill_returnuic("dict_iterator_copy_key", 1, "item 1");
    twill_returnoc("dict_iterator_copy_key", strdup("a"), "item 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_true(), "item 1");
    twill_returnuic("dict_iterator_next", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 2");
    twill_returnuic("dict_iterator_copy_key", 1, "item 2");
    twill_returnoc("dict_iterator_copy_key", strdup("b"), "item 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 2");
    twill_returnuic("dict_iterator_next", UR_OK, "item 3");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 3");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 3");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 3");
    twill_returnuic("dict_iterator_copy_key", 1, "item 3");
    twill_returnoc("dict_iterator_copy_key", strdup("c"), "item 3");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 3");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 3");
    twill_returnuic("dict_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.printer_get_length_f)(printer, &len);
    cr_expect_eq(60, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "[#][U][3]\n    [U][1][a][T]\n    [U][1][b][Z]\n    [U][1][c][Z]", 60);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.printer_free_f)(&printer));
    (ubjs_prmtv_object_ntype.free_f)(&(glue.prmtv));
}

Test(prmtv_object, printer_3_count_type)
{
    ubjs_prmtv_ntype_printer_glue glue;
    ubjs_prmtv_ntype_printer *printer = 0;
    unsigned int len = -1;
    char data[57];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_printer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    ubjs_prmtv_object(lib, &(glue.prmtv));
    twill_returnui("dict_get_length", UR_OK);
    twill_returnui("dict_get_length", 3);
    twill_returnuic("dict_iterator_next", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 1");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 1");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 1");
    twill_returnuic("dict_iterator_copy_key", 1, "item 1");
    twill_returnoc("dict_iterator_copy_key", strdup("a"), "item 1");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 1");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 1");
    twill_returnuic("dict_iterator_next", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 2");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 2");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 2");
    twill_returnuic("dict_iterator_copy_key", 1, "item 2");
    twill_returnoc("dict_iterator_copy_key", strdup("b"), "item 2");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 2");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 2");
    twill_returnuic("dict_iterator_next", UR_OK, "item 3");
    twill_returnuic("dict_iterator_get_key_length", UR_OK, "item 3");
    twill_returnuic("dict_iterator_get_key_length", 1, "item 3");
    twill_returnuic("dict_iterator_copy_key", UR_OK, "item 3");
    twill_returnuic("dict_iterator_copy_key", 1, "item 3");
    twill_returnoc("dict_iterator_copy_key", strdup("c"), "item 3");
    twill_returnuic("dict_iterator_get_value", UR_OK, "item 3");
    twill_returnoc("dict_iterator_get_value", ubjs_prmtv_null(), "item 3");
    twill_returnuic("dict_iterator_next", UR_ERROR, "eof");

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.printer_new_f)(lib, &glue, &printer));

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.printer_get_length_f)(printer, &len);
    cr_expect_eq(57, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_object_ntype.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "[$][Z][#][U][3]\n    [U][1][a]\n    [U][1][b]\n    [U][1][c]", 57);

    cr_expect_eq(UR_OK, (ubjs_prmtv_object_ntype.printer_free_f)(&printer));
    (ubjs_prmtv_object_ntype.free_f)(&(glue.prmtv));
}
