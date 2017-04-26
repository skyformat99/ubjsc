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

static ubjs_library *lib;
static void before(void)
{
    ubjs_library_builder builder;
    ubjs_library_builder_init(&builder);
    ubjs_library_builder_build(&builder, &lib);
}

static void after(void)
{
    ubjs_library_free(&lib);
}

TestSuite(prmtv_str, .init = before, .fini = after);
Test(prmtv_str, ntype)
{
    ubjs_prmtv_ntype *n = &ubjs_prmtv_str_ntype;
    cr_expect_eq(83, n->marker);
    cr_expect_neq(0, n->free_f);
    cr_expect_eq(0, n->new_from_int64_f);
    cr_expect_eq(0, n->get_value_int64_f);
    cr_expect_neq(0, n->debug_string_get_length_f);
    cr_expect_neq(0, n->debug_string_copy_f);
    cr_expect_neq(0, n->parser_processor_new_f);
    cr_expect_neq(0, n->parser_processor_free_f);
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

Test(prmtv_str, object)
{
    ubjs_prmtv *object = 0;
    ubjs_prmtv_ntype *ntype = 0;
    char *value = "rower";
    char *nvalue = 0;
    unsigned int len = -1;

    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(0, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(lib, 0, 0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(0, 0, 0, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(0, 0, value, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(lib, 0, value, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str(0, 0, value, &object));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_get_length(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_get_length(0, &len));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_copy_text(0, 0));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_copy_text(0, nvalue));

    cr_expect_eq(UR_OK, ubjs_prmtv_str(lib, strlen(value), value, &object));
    cr_expect_neq(0, object);

    cr_expect_eq(UR_OK, ubjs_prmtv_get_ntype(object, &ntype));
    cr_expect_eq(&ubjs_prmtv_str_ntype, ntype);

    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_get_length(object, 0));
    cr_expect_eq(UR_OK, ubjs_prmtv_str_get_length(object, &len));
    cr_expect_eq(len, 5);

    nvalue = (char *)malloc(sizeof(char) * strlen(value));
    cr_expect_eq(UR_ERROR, ubjs_prmtv_str_copy_text(object, 0));
    cr_expect_eq(UR_OK, ubjs_prmtv_str_copy_text(object, nvalue));
    cr_expect_arr_eq(nvalue, value, 5);
    free(nvalue);

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.free_f)(0));
    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.free_f)(&object));
    cr_expect_eq(0, object);
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.free_f)(&object));
}

static ubjs_bool parser_glue_return_control_called = UFALSE;
static ubjs_bool parser_glue_want_number_called = UFALSE;
static ubjs_bool parser_glue_error_called = UFALSE;
static ubjs_bool parser_glue_debug_called = UFALSE;

static void parser_glue_reset()
{
    parser_glue_return_control_called = UFALSE;
    parser_glue_want_number_called = UFALSE;
    parser_glue_error_called = UFALSE;
    parser_glue_debug_called = UFALSE;
}

static void parser_glue_return_control_0(ubjs_prmtv_ntype_parser_glue *glue,
    void *present)
{
    unsigned int len = -1;
    char txt[1] = {0};
    ubjs_prmtv *prmtv = (ubjs_prmtv *)present;

    parser_glue_return_control_called = UTRUE;
    cr_expect_eq(prmtv->ntype, &ubjs_prmtv_str_ntype);

    cr_expect_eq(UR_OK, ubjs_prmtv_str_get_length(prmtv, &len));
    cr_expect_eq(len, 0);

    cr_expect_eq(UR_OK, ubjs_prmtv_str_copy_text(prmtv, txt));
    cr_expect_eq(txt[0], 0);

    ubjs_prmtv_free(&prmtv);
}

static void parser_glue_return_control_2(ubjs_prmtv_ntype_parser_glue *glue,
    void *present)
{
    unsigned int len = -1;
    char txt[2];
    ubjs_prmtv *prmtv = (ubjs_prmtv *)present;

    parser_glue_return_control_called = UTRUE;
    cr_expect_eq(prmtv->ntype, &ubjs_prmtv_str_ntype);

    cr_expect_eq(UR_OK, ubjs_prmtv_str_get_length(prmtv, &len));
    cr_expect_eq(len, 2);

    cr_expect_eq(UR_OK, ubjs_prmtv_str_copy_text(prmtv, txt));
    cr_expect_arr_eq(txt, "ra", 2);

    ubjs_prmtv_free(&prmtv);
}

static void parser_glue_return_control_unexpected(ubjs_prmtv_ntype_parser_glue *glue,
    void *present)
{
    parser_glue_return_control_called = UTRUE;
    cr_expect_fail("%s", "Unexpected return control");
}

static void parser_glue_want_number_unexpected(ubjs_prmtv_ntype_parser_glue *glue)
{
    parser_glue_want_number_called = UTRUE;
    cr_expect_fail("%s", "Unexpected want number");
}

static void parser_glue_want_number(ubjs_prmtv_ntype_parser_glue *glue)
{
    parser_glue_want_number_called = UTRUE;
}

static void parser_glue_error_unexpected(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_fail("Unexpected error: %.*s", len, msg);
}

static void parser_glue_error_limit(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(30, len);
    cr_expect_arr_eq("Reached limit of string length", msg, 30);
}

static void parser_glue_error_invalid_number(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(14, len);
    cr_expect_arr_eq("Invalid length", msg, 14);
}

static void parser_glue_error_no_number(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(9, len);
    cr_expect_arr_eq("No number", msg, 9);
}

static void parser_glue_error_unexpected_got_control(ubjs_prmtv_ntype_parser_glue *glue,
    unsigned int len, char *msg)
{
    parser_glue_error_called = UTRUE;
    cr_expect_eq(22, len);
    cr_expect_arr_eq("Unexpected got control", msg, 22);
}

static void parser_glue_debug_unexpected(ubjs_prmtv_ntype_parser_glue *glue, unsigned int len,
    char *msg)
{
    parser_glue_debug_called = UTRUE;
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_str, parser_basic)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_new_f)(0, 0,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, 0,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_new_f)(0, &glue,
        &parser_processor));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));
    cr_expect_neq(0, parser_processor);
    cr_expect_eq(&ubjs_prmtv_str_ntype, parser_processor->ntype);
    cr_expect_eq(lib, parser_processor->lib);
    cr_expect_str_eq("str", parser_processor->name);
    cr_expect_eq(&glue, parser_processor->glue);
    cr_expect_eq(0, parser_processor->userdata);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_str, parser_phase_consume_number_when_in_init)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *prmtv = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_0;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    ubjs_prmtv_uint8(lib, 0, &prmtv);
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, prmtv);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_str, parser_phase_init_length_null_number)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_no_number;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_str, parser_phase_init_length_not_number)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_invalid_number;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, ubjs_prmtv_null());
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_unexpected_got_control;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_str, parser_phase_init_length_negative_number)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *prmtv = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_invalid_number;
    glue.debug_f = parser_glue_debug_unexpected;
    ubjs_prmtv_int8(lib, -1, &prmtv);
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, prmtv);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_unexpected_got_control;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_str, parser_0)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *prmtv;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_want_number_called);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_0;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    ubjs_prmtv_uint8(lib, 0, &prmtv);
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, prmtv);
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_str, parser_2)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *prmtv = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_want_number_called);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    ubjs_prmtv_uint8(lib, 2, &prmtv);
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, prmtv);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_read_byte_f)(parser_processor, 'r');

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_2;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_read_byte_f)(parser_processor, 'a');
    cr_expect_eq(UTRUE, parser_glue_return_control_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_str, parser_limit_length)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *prmtv = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.limit_string_length = 1;

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_want_number_called);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_limit;
    glue.debug_f = parser_glue_debug_unexpected;
    ubjs_prmtv_uint8(lib, 2, &prmtv);
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, prmtv);
    cr_expect_eq(UTRUE, parser_glue_error_called);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

Test(prmtv_str, parser_no_limit_length)
{
    ubjs_prmtv_ntype_parser_glue glue;
    ubjs_prmtv_ntype_parser_processor *parser_processor = 0;
    ubjs_prmtv *prmtv = 0;

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_parser_glue));
    glue.userdata = 0;
    glue.parent = (void *)666;
    glue.limit_string_length = 2;

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_new_f)(lib, &glue,
        &parser_processor));

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, 0);
    cr_expect_eq(UTRUE, parser_glue_want_number_called);

    parser_glue_reset();
    glue.return_control_f = parser_glue_return_control_unexpected;
    glue.want_number_f = parser_glue_want_number_unexpected;
    glue.error_f = parser_glue_error_unexpected;
    glue.debug_f = parser_glue_debug_unexpected;
    ubjs_prmtv_uint8(lib, 1, &prmtv);
    (ubjs_prmtv_str_ntype.parser_processor_got_control_f)(parser_processor, prmtv);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.parser_processor_free_f)(&parser_processor));
    cr_expect_eq(0, parser_processor);
}

static void writer_glue_debug_unexpected(ubjs_prmtv_ntype_writer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_str, writer)
{
    ubjs_prmtv_ntype_writer_glue glue;
    ubjs_prmtv_ntype_writer *writer = 0;
    ubjs_prmtv wrong_prmtv = {0, 0, 0};
    unsigned int len = -1;
    uint8_t data[3];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_writer_glue));
    glue.userdata = 0;
    glue.prmtv = 0;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_new_f)(0, 0, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_new_f)(lib, 0, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_new_f)(0, &glue, &writer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_free_f)(&writer));

    glue.prmtv = &wrong_prmtv;
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.writer_new_f)(lib, &glue, &writer));

    ubjs_prmtv_str(lib, 1, "r", &(glue.prmtv));
    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.writer_new_f)(lib, &glue, &writer));
    cr_expect_neq(0, writer);
    cr_expect_eq(lib, writer->lib);
    cr_expect_eq(&ubjs_prmtv_str_ntype, writer->ntype);
    cr_expect_str_eq("str", writer->name);
    cr_expect_eq(&glue, writer->glue);
    cr_expect_eq(0, writer->userdata);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.writer_get_length_f)(writer, &len);
    cr_expect_eq(3, len);

    glue.debug_f = writer_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.writer_do_f)(writer, data);
    cr_expect_eq(data[0], 'U');
    cr_expect_eq(data[1], 1);
    cr_expect_eq(data[2], 'r');

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.writer_free_f)(&writer));
    cr_expect_eq(0, writer);
    (ubjs_prmtv_str_ntype.free_f)(&(glue.prmtv));
}

static void printer_glue_debug_unexpected(ubjs_prmtv_ntype_printer_glue *glue, unsigned int len,
    char *msg)
{
    cr_expect_fail("Unexpected debug: %.*s", len, msg);
}

Test(prmtv_str, printer)
{
    ubjs_prmtv_ntype_printer_glue glue;
    ubjs_prmtv_ntype_printer *printer = 0;
    ubjs_prmtv wrong_prmtv = {0, 0, 0};
    unsigned int len = -1;
    char data[9];

    memset(&glue, 0, sizeof(struct ubjs_prmtv_ntype_printer_glue));
    glue.userdata = 0;
    glue.indent = 0;
    glue.prmtv = 0;

    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_new_f)(0, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_new_f)(lib, 0, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_new_f)(0, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_new_f)(lib, &glue, 0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_new_f)(0, 0, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_new_f)(lib, 0, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_new_f)(0, &glue, &printer));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_free_f)(0));
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_free_f)(&printer));

    glue.prmtv = &wrong_prmtv;
    cr_expect_eq(UR_ERROR, (ubjs_prmtv_str_ntype.printer_new_f)(lib, &glue, &printer));

    ubjs_prmtv_str(lib, 1, "r", &(glue.prmtv));
    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.printer_new_f)(lib, &glue, &printer));
    cr_expect_neq(0, printer);
    cr_expect_eq(lib, printer->lib);
    cr_expect_eq(&ubjs_prmtv_str_ntype, printer->ntype);
    cr_expect_str_eq("str", printer->name);
    cr_expect_eq(&glue, printer->glue);
    cr_expect_eq(0, printer->userdata);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.printer_get_length_f)(printer, &len);
    cr_expect_eq(9, len);

    glue.debug_f = printer_glue_debug_unexpected;
    (ubjs_prmtv_str_ntype.printer_do_f)(printer, data);
    cr_expect_arr_eq(data, "[U][1][r]", 9);

    cr_expect_eq(UR_OK, (ubjs_prmtv_str_ntype.printer_free_f)(&printer));
    cr_expect_eq(0, printer);
    (ubjs_prmtv_str_ntype.free_f)(&(glue.prmtv));
}
